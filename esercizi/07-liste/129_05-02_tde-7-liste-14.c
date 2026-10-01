//
//  main.c
//  tde  7 liste -14
//
//  Created by Francesco Roscio Ricon on 05/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef struct d {
    int giorno, mese, anno;
} Data;

typedef struct spe {
    char codice[N], titolo[N], descrizione[N];
    int costoBiglietto;
    Data data;
    struct spe *next;
} spettacolo;

typedef spettacolo *ListaSpettacoli;

/* =========================================================
   PROTOTIPI (le 2 funzioni richieste + utility per test)
   ========================================================= */
int spettacoloMigliore(ListaSpettacoli spettacoli, char titolo[]);
int eliminaSpettacoliVecchi(ListaSpettacoli spettacoli, Data oggi);

/* utility */
static int dataConfronta(Data a, Data b); /* <0 se a<b, 0 se =, >0 se a>b */
static void stampaData(Data d);
static void stampaLista(ListaSpettacoli l);
static spettacolo* nuovoSpettacolo(const char *codice, const char *titolo,
                                   const char *descr, int costo, Data data);
static ListaSpettacoli inserisciInCoda(ListaSpettacoli l, spettacolo *nodo);
static void distruggiLista(ListaSpettacoli l);

/* =========================================================
   MAIN DI TEST
   ========================================================= */
int f(ListaSpettacoli head, char titolo[]);
int main(void) {
    ListaSpettacoli archivio = NULL;

    /* Creo una lista ORDINATA PER CODICE (come da consegna) */
    archivio = inserisciInCoda(archivio, nuovoSpettacolo("A001", "Amleto", "Tragedia", 35, (Data){10,  1, 2020}));
    archivio = inserisciInCoda(archivio, nuovoSpettacolo("A005", "Amleto", "Replica serale", 25, (Data){20,  2, 2022}));
    archivio = inserisciInCoda(archivio, nuovoSpettacolo("B010", "Cats",   "Musical", 45, (Data){ 3,  6, 2018}));
    archivio = inserisciInCoda(archivio, nuovoSpettacolo("C002", "Cats",   "Matinée", 30, (Data){15, 12, 2016}));
    archivio = inserisciInCoda(archivio, nuovoSpettacolo("D777", "Dune",   "Sci-fi",  40, (Data){ 1,  3, 2024}));

    printf("=== Archivio iniziale ===\n");
    stampaLista(archivio);

    /* TEST 1: spettacoloMigliore */
    {
        char titoloRicerca[N] = "Cats";
        int best = f(archivio, titoloRicerca);

        printf("\n=== TEST spettacoloMigliore ===\n");
        printf("Titolo cercato: \"%s\"\n", titoloRicerca);
        printf("Risultato funzione (placeholder finche' non la implementi): %d\n", best);
        printf("(Dovrebbe essere il costo minimo tra gli spettacoli con titolo ESATTO \"%s\")\n", titoloRicerca);
    }

    /* TEST 2: eliminaSpettacoliVecchi */
    {
        Data oggi = (Data){1, 1, 2020};
        printf("\n=== TEST eliminaSpettacoliVecchi ===\n");
        printf("Data oggi: ");
        stampaData(oggi);
        printf("\n");

        int eliminati = eliminaSpettacoliVecchi(archivio, oggi);

        printf("Numero eliminati (placeholder finche' non la implementi): %d\n", eliminati);
        printf("Lista dopo chiamata (placeholder: finche' non implementi, la lista potrebbe non cambiare):\n");
        stampaLista(archivio);

        printf("\nNOTA IMPORTANTE: la firma data nella consegna e' `int eliminaSpettacoliVecchi(ListaSpettacoli spettacoli, Data oggi)`.\n");
        printf("Cosi' com'e', NON puoi aggiornare la testa se elimini i primi nodi.\n");
        printf("In pratica, nell'esame di solito accettano che tu restituisca la nuova testa, oppure passi un puntatore a testa.\n");
        printf("Qui lasciamo la firma invariata e facciamo solo scaffold (senza soluzione).\n");
    }
}

static int dataConfronta(Data a, Data b) {
    if (a.anno != b.anno) return a.anno - b.anno;
    if (a.mese != b.mese) return a.mese - b.mese;
    return a.giorno - b.giorno;
}

static void stampaData(Data d) {
    printf("%02d/%02d/%04d", d.giorno, d.mese, d.anno);
}

static void stampaLista(ListaSpettacoli l) {
    if (!l) {
        printf("(lista vuota)\n");
        return;
    }
    while (l) {
        printf("Codice=%s | Titolo=%s | Costo=%d | Data=",
               l->codice, l->titolo, l->costoBiglietto);
        stampaData(l->data);
        printf(" | Desc=%s\n", l->descrizione);
        l = l->next;
    }
}
int f(ListaSpettacoli head, char titolo[])
    {
        if(head==NULL)
            return 0;
        int flag=0;
        ListaSpettacoli scorri=head;
        int min=0;
        while (scorri!=NULL)
        {
            if(strcmp(scorri->titolo, titolo)==0)
                {
                    if(flag==0)
                    {
                        min=scorri->costoBiglietto;
                        flag=1;
                    }
                    else
                    {
                        if(min>scorri->costoBiglietto)
                            min=scorri->costoBiglietto;
                    }
                }
        scorri=scorri->next;
        }
    return min;
    }
/* =========================================================
   UTILITY PER DATE / STAMPA / COSTRUZIONE LISTA
   ========================================================= */

static spettacolo* nuovoSpettacolo(const char *codice, const char *titolo,
                                   const char *descr, int costo, Data data) {
    spettacolo *p = (spettacolo*)malloc(sizeof(spettacolo));
    if (!p) { perror("malloc"); exit(1); }

    strncpy(p->codice, codice, N);
    p->codice[N-1] = '\0';

    strncpy(p->titolo, titolo, N);
    p->titolo[N-1] = '\0';

    strncpy(p->descrizione, descr, N);
    p->descrizione[N-1] = '\0';

    p->costoBiglietto = costo;
    p->data = data;
    p->next = NULL;
    return p;
}

static ListaSpettacoli inserisciInCoda(ListaSpettacoli l, spettacolo *nodo) {
    if (!l) return nodo;
    spettacolo *cur = l;
    while (cur->next) cur = cur->next;
    cur->next = nodo;
    return l;
}

static void distruggiLista(ListaSpettacoli l) {
    while (l) {
        spettacolo *tmp = l->next;
        free(l);
        l = tmp;
    }
}
//Si codifichi in C la seguente funzione:
//int eliminaSpettacoliVecchi(ListaSpettacoli spettacoli, Data oggi)
//che elimina gli spettacoli precedenti rispetto alla data passata nel parametro oggi [4 punti].
int ver(spettacolo spett, Data data)
    {
        if(dataConfronta(spett.data, data)<0) //in questo caso voglio eliminare lo spettacolo
            {
                return 1;
            }
    return 0;
    }

int eliminaSpettacoliVecchi(ListaSpettacoli spettacoli, Data oggi)
    {
        if(spettacoli==NULL)
            return 0;
        if(ver(*spettacoli, oggi))
            {
                ListaSpettacoli temp=spettacoli->next;
                free(spettacoli);
                return 1+eliminaSpettacoliVecchi(temp, oggi);
            }
        return eliminaSpettacoliVecchi(spettacoli->next, oggi);
    }
