#!/usr/bin/env python3
"""Compila separatamente i sorgenti e salva i diagnostici, senza eseguirli."""
import argparse
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
from datetime import datetime, timezone
import json
import os
from pathlib import Path
import re
import shlex
import shutil
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
FLAGS = ['-std=c11', '-Wall', '-Wextra', '-Wpedantic', '-fdiagnostics-color=never']

def active_code(text):
    pattern = r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|//[^\n]*|/\*[\s\S]*?\*/'
    def replace(match):
        value = match.group(0)
        return '\n' * value.count('\n') if value.startswith('/') else '""'
    return re.sub(pattern, replace, text)

def run(command, timeout):
    try:
        result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True,
                                errors='replace', timeout=timeout,
                                env={**os.environ, 'LC_ALL': 'C'})
        return result.returncode, result.stdout + result.stderr
    except subprocess.TimeoutExpired as exc:
        output = exc.stdout or b''
        error = exc.stderr or b''
        if isinstance(output, bytes): output = output.decode(errors='replace')
        if isinstance(error, bytes): error = error.decode(errors='replace')
        return 124, output + error + '\nTempo massimo di compilazione superato.\n'

def check(row, compiler, build, output, timeout):
    key = row['id']
    code = active_code((ROOT/row['source']).read_text(encoding='utf-8', errors='replace'))
    has_main = bool(re.search(r'\bmain\s*\([^;{}]*\)\s*\{', code))
    obj = build / (key + '.o')
    binary = build / (key + '.out')
    compile_command = compiler + FLAGS + ['-c', row['source'], '-o', str(obj)]
    rc, diagnostics = run(compile_command, timeout)
    compile_diagnostics = diagnostics
    commands = [compile_command]
    link_rc = None
    link_diagnostics = ''
    if rc == 124:
        status = 'timeout'
    elif rc:
        status = 'errore-compilazione'
    elif not code.strip():
        status = 'senza-codice-attivo'
    elif not has_main:
        status = 'frammento-senza-main'
    else:
        link_command = compiler + [str(obj), '-lm', '-o', str(binary)]
        commands.append(link_command)
        link_rc, link_diagnostics = run(link_command, timeout)
        diagnostics += link_diagnostics
        if link_rc == 124: status = 'timeout'
        elif link_rc: status = 'errore-link'
        elif 'warning:' in diagnostics: status = 'compila-con-avvisi'
        else: status = 'compila'
    def clean(value):
        return value.replace(str(build), '<build-temporanea>').replace(str(ROOT)+'/', '')
    log = '\n\n'.join('$ ' + shlex.join(cmd) for cmd in commands)
    log += '\n\n[Compilazione]\n' + (compile_diagnostics or 'Nessun diagnostico.\n')
    if link_rc is not None:
        log += '\n[Link]\n' + (link_diagnostics or 'Nessun diagnostico.\n')
    log += '\nEsito: ' + status + '\n'
    (output/'log'/f'{key}.txt').write_text(clean(log), encoding='utf-8')
    return {'id':key,'source':row['source'],'status':status,
            'compile_returncode':rc,'link_returncode':link_rc,
            'warnings':len(re.findall(r'\bwarning:', diagnostics)),
            'errors':len(re.findall(r'\b(?:fatal )?error:', diagnostics)),
            'log':f'log/{key}.txt'}

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cc', default=os.environ.get('CC', 'cc'), help='Compilatore (default: CC oppure cc).')
    parser.add_argument('--jobs', type=int, default=4, help='Compilazioni contemporanee.')
    parser.add_argument('--id', action='append', help='Verifica solo questo ID; ripetibile.')
    parser.add_argument('--output', default='build/verifica', help='Cartella risultati, relativa alla repository.')
    parser.add_argument('--timeout', type=int, default=20, help='Secondi massimi per ogni fase.')
    args = parser.parse_args()
    compiler = shlex.split(args.cc)
    if not compiler or not shutil.which(compiler[0]): parser.error('Compilatore C non trovato.')
    if args.jobs < 1 or args.timeout < 1: parser.error('jobs e timeout devono essere positivi.')
    catalog = json.loads((ROOT/'catalogo.json').read_text(encoding='utf-8'))
    rows = catalog['exercises']
    if args.id:
        selected = {value.strip() for value in args.id}
        available = {row['id'] for row in rows}
        unknown = selected - available
        if unknown: parser.error('ID non trovati: ' + ', '.join(sorted(unknown)))
        rows = [row for row in rows if row['id'] in selected]
    output = ROOT / args.output
    (output/'log').mkdir(parents=True,exist_ok=True)
    (ROOT/'build').mkdir(exist_ok=True)
    _, version = run(compiler + ['--version'], args.timeout)
    with tempfile.TemporaryDirectory(prefix='compilazione-', dir=ROOT/'build') as tmp:
        build=Path(tmp)
        with ThreadPoolExecutor(max_workers=args.jobs) as executor:
            results = list(executor.map(lambda row:check(row,compiler,build,output,args.timeout),rows))
    report = {'date_utc':datetime.now(timezone.utc).isoformat(),
              'compiler':version.splitlines()[0] if version else args.cc,
              'compile_flags':FLAGS,'link_flags':['-lm'],
              'scope':'Compilazione e link dei file .c separatamente; nessun programma eseguito. Header non verificati separatamente.',
              'summary':dict(Counter(row['status'] for row in results)), 'results':results}
    (output/'risultati.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(report['summary'],ensure_ascii=False,indent=2))
    print('Risultati: ' + str(output/'risultati.json'))
    # Un errore nello script e' distinto dagli errori dei programmi in archivio.
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
