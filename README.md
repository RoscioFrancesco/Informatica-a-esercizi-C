# Informatica A — esercizi in C

Raccolta personale di esercizi, tentativi e varianti svolti durante lo studio di Informatica A, condivisa da Francesco Roscio Ricon per aiutare altri studenti a esercitarsi in C.

**866 file C · 4 header · 11 sezioni · 855 programmi compilati e collegati**

[Percorso per iniziare](PERCORSO.md) · [Indice completo](INDICE.md) · [Come compilare](GUIDA.md) · [Stato della raccolta](verifiche/README.md)

Per mettere online la raccolta, segui [Pubblicare su GitHub](PUBBLICARE.md).

## Da dove iniziare

Segui il [percorso di otto esempi](PERCORSO.md), dai primi input fino a liste e alberi. Ogni esempio del percorso ha un caso di esecuzione documentato. Per cercare un esercizio specifico, apri la sezione dell'argomento oppure usa l'indice completo: riporta titoli ripuliti e date delle intestazioni.

Per esercitarti, scegli un programma dall’indice e prova a ricostruire il problema a partire dal codice. Alcuni file contengono solo frammenti, prove o soluzioni parziali; le consegne di terzi non sono riprodotte.

## Argomenti

| Argomento | File C |
|---|---:|
| [Fondamenti e problemi numerici](esercizi/01-fondamenti/README.md) | 45 |
| [Array e matrici](esercizi/02-array-e-matrici/README.md) | 87 |
| [Stringhe](esercizi/03-stringhe/README.md) | 12 |
| [Ricorsione e backtracking](esercizi/04-ricorsione-e-backtracking/README.md) | 12 |
| [Puntatori e memoria dinamica](esercizi/05-puntatori-e-memoria/README.md) | 18 |
| [Struct e file](esercizi/06-struct-e-file/README.md) | 77 |
| [Liste concatenate](esercizi/07-liste/README.md) | 337 |
| [Alberi binari e BST](esercizi/08-alberi/README.md) | 269 |
| [Ordinamento e ricerca](esercizi/09-ordinamento-e-ricerca/README.md) | 7 |
| [Giochi](esercizi/10-giochi/README.md) | 2 |
| [Frammenti e file vuoti](esercizi/11-frammenti-e-file-vuoti/README.md) | 0 |

La suddivisione è stata ricavata automaticamente da nomi e contenuti dei sorgenti. Un esercizio può usare più concetti: per esempio, una visita ricorsiva rimane nella sezione alberi. I tag del [catalogo JSON](catalogo.json) aiutano a trovare questi collegamenti. Le categorie sono un punto di partenza e possono essere perfezionate.

## Primo programma

Dalla cartella principale della repository, con un compilatore C disponibile:

```sh
mkdir -p build
cc -std=c11 -Wall -Wextra -Wpedantic esercizi/01-fondamenti/020_30-09_es-1-lab.c -o build/somma
./build/somma
```

Inserisci `7` e `5`: il programma stampa `7+5=12`. Su Windows l'eseguibile può essere chiamato `somma.exe`; la [guida](GUIDA.md) spiega anche come lavorare da un IDE.

**Compila un file C alla volta.** Molti programmi hanno un proprio `main`: non sono parti di una singola applicazione.

## Stato delle verifiche

| Esito | File C |
|---|---:|
| Compilazione e link riusciti, senza avvisi con i flag usati | 263 |
| Compilazione e link riusciti, con avvisi | 592 |
| Errori di compilazione | 0 |
| Errori di link | 0 |
| Frammenti compilabili come oggetti, senza `main` | 11 |
| File senza codice attivo | 0 |
| **Totale** | **866** |

Verifica con Apple clang version 17.0.0 (clang-1700.0.13.5) su macOS, C11, `-Wall -Wextra -Wpedantic`; link con `-lm`. I risultati possono differire con altri compilatori.

**Compilare non dimostra che una soluzione sia corretta o completa.** Tutti i sorgenti C sono stati compilati separatamente; solo gli otto esempi del percorso iniziale sono stati anche eseguiti, ciascuno su un singolo caso. I diagnostici e le istruzioni per ripetere la verifica sono in [verifiche](verifiche/README.md).

I commenti `TODO` o `STUB` sono segnalati nell'indice e indicano parti ancora da sviluppare. Non equivalgono automaticamente a un errore.

## Come è organizzato l'archivio

I sorgenti sono direttamente nelle **11 sezioni numerate**, senza una sottocartella per ogni programma. Ogni nome di file contiene numero progressivo, giorno-mese e titolo: per esempio `020_30-09_es-1-lab.c`.

All'interno di ogni sezione i file seguono la data dell'intestazione, considerando anche l'anno. I numeri ripartono da `001` in ogni sezione; l'ID completo unisce sezione e numero, come `01-020`. A parità di data i titoli seguono un ordine alfabetico naturale.

**860 file riportano una data di creazione nell'intestazione.** I restanti 6 hanno `data-non-indicata` nel nome e sono in fondo alla loro sezione. Il giorno e il mese visualizzati non sono ricavati dalla data di modifica. Le regole e le eccezioni sono in [Date e numerazione](DATE-E-NUMERAZIONE.md).

Sono conservati i 866 sorgenti C e i 4 header; sono state rimosse le copie identiche e i file senza codice utilizzabile. Il catalogo contiene date e indici aggiornati.

I file di Xcode e i metadati di sistema non sono necessari per usare la raccolta. I documenti originali non fanno parte di questa repository.

## Contribuire

Segnalazioni e correzioni sono benvenute. Indica l'ID dell'esercizio, l'input usato e il risultato atteso: trovi un esempio in [CONTRIBUTING.md](CONTRIBUTING.md).

## Licenza

Salvo diversa indicazione, i contenuti originali sono distribuiti con licenza [CC BY-NC 4.0](LICENSE.md): è richiesta l'attribuzione e l'uso commerciale non è consentito. Materiali e opere di terzi sono esclusi; consulta le [note sui materiali originali](docs/materiali-originali.md).
