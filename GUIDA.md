# Usare la raccolta

[README](README.md) · [Percorso iniziale](PERCORSO.md)

## Scegli un esercizio

Apri l'indice dell'argomento che stai studiando. Il collegamento al nome porta al sorgente, quello allo stato porta al log del compilatore. Un file che compila può comunque avere errori logici o un main che non prova le funzioni.

Ogni sezione contiene direttamente i file C numerati e datati. Il nome del file non implica che contenga un punto di ingresso `main`: consulta lo stato nell’indice.

## Compilare dal terminale

Serve un compilatore C, per esempio GCC o Clang. Il comando `cc --version` permette di vedere quello configurato. I comandi seguenti sono per un terminale compatibile con macOS/Linux e vanno eseguiti dalla radice della raccolta.

```sh
mkdir -p build
cc -std=c11 -Wall -Wextra -Wpedantic esercizi/09-ordinamento-e-ricerca/006_03-03_bubble-3mz.c -lm -o build/esercizio
./build/esercizio
```

Per questo esempio l'output è `12345`. Sostituisci il percorso del sorgente per provare un altro esercizio. `-lm` collega la libreria matematica nei sistemi che la richiedono.

Su Windows usa il compilatore configurato nel tuo ambiente e un nome come `build/esercizio.exe`; in PowerShell l'avvio avviene con `./build/esercizio.exe`. Puoi anche usare il pulsante di compilazione/esecuzione del tuo IDE.

## Usare Xcode o un altro IDE

Crea un progetto console in C e aggiungi **un solo esercizio**. Se il progetto ha già un `main.c`, sostituiscine il contenuto oppure rimuovilo prima di aggiungere il file scelto. Gli header conservati portano lo stesso numero e titolo del sorgente associato, seguiti dal nome dell’header; alcuni contengono a loro volta tentativi di codice.

Non aggiungere tutti i file della raccolta allo stesso target: molti definiscono `main` e funzioni con lo stesso nome.

## Ripetere il controllo automatico

Con Python 3 e un compilatore C disponibili:

```sh
python3 strumenti/verifica.py
python3 strumenti/verifica.py --id 01-020
python3 strumenti/verifica.py --cc gcc --jobs 4
```

Il controllo compila i file separatamente, effettua il link quando rileva `main`, salva risultati in `build/verifica/` e **non esegue** i programmi. Non installa dipendenze Python. Per verificare un altro compilatore puoi usare `--cc clang` se è disponibile.

I file `.h` non vengono compilati separatamente. L'esito del processo Python indica se lo strumento ha completato il lavoro: per conoscere gli errori degli esercizi bisogna leggere `risultati.json`, non il solo codice di uscita dello script.

Per aggiornare la fotografia dei diagnostici distribuita nella repository:

```sh
python3 strumenti/verifica.py --output verifiche
```

Gli indici Markdown e lo stato riportato nel catalogo descrivono la verifica iniziale: dopo modifiche ai sorgenti vanno aggiornati insieme ai diagnostici.
