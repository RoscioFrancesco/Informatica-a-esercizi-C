# Verifica dei sorgenti

[README](../README.md) · [Indice](../INDICE.md)

Compilazione separata dei 866 file C con Apple clang version 17.0.0 (clang-1700.0.13.5), C11, `-Wall -Wextra -Wpedantic`, link con `-lm`. I 4 header non sono compilati separatamente.

**Compilare non dimostra la correttezza o completezza del programma.** Nessun eseguibile è stato avviato.

| Esito | File C |
|---|---:|
| Compila | 263 |
| Compila con avvisi | 592 |
| Frammento senza main | 11 |
| Errore di compilazione | 0 |
| Errore di link | 0 |
| Senza codice attivo | 0 |
| **Totale** | **866** |

Il [report completo](risultati.json) contiene diagnostici e risultati. Le istruzioni per ripetere il controllo sono in `strumenti/verifica.py`.
