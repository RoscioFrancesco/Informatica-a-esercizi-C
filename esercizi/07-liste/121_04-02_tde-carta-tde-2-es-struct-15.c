//
//  main.c
//  tde carta tde 2 es struct -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct DataT {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct InterpreteT {
    char *cognome;
    char *nome;
    char *cittadinanza;   /* es: "ITA" */
    struct InterpreteT *next;
} Interprete;

typedef Interprete* ListaInterpreti;

typedef struct ConcertoT {
    ListaInterpreti lista;      /* lista interpreti del concerto */
    Data data;
    int prezzoBiglietto;
    struct ConcertoT *next;
} Concerto;

typedef Concerto* ListaConcerti;


int sommaPrezziConItaliano(ListaConcerti concerti); /* TODO */

/* consigliate: funzioni ausiliarie (TU) */
int haItaliano(ListaInterpreti li);                 /* TODO */

/* =========================
   UTILITY (per test: cicli OK)
   ========================= */
static char* dupstr(const char *s) {
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static ListaInterpreti newInterprete(const char *cognome, const char *nome,
                                     const char *citt, ListaInterpreti next) {
    Interprete *i = (Interprete*)malloc(sizeof(Interprete));
    if (!i) { perror("malloc"); exit(1); }
    i->cognome = dupstr(cognome);
    i->nome = dupstr(nome);
    i->cittadinanza = dupstr(citt);
    i->next = next;
    return i;
}

static ListaConcerti newConcerto(ListaInterpreti li, Data d, int prezzo, ListaConcerti next) {
    Concerto *c = (Concerto*)malloc(sizeof(Concerto));
    if (!c) { perror("malloc"); exit(1); }
    c->lista = li;
    c->data = d;
    c->prezzoBiglietto = prezzo;
    c->next = next;
    return c;
}

static void printInterpreti(ListaInterpreti li) {
    printf("[");
    while (li != NULL) {
        printf("%s %s (%s)", li->nome, li->cognome, li->cittadinanza);
        if (li->next) printf(", ");
        li = li->next;
    }
    printf("]");
}

static void printConcerti(ListaConcerti lc) {
    while (lc != NULL) {
        printf("Concerto %02d/%02d/%04d | prezzo=%d | interpreti=",
               lc->data.giorno, lc->data.mese, lc->data.anno, lc->prezzoBiglietto);
        printInterpreti(lc->lista);
        printf("\n");
        lc = lc->next;
    }
}

static void freeInterpreti(ListaInterpreti li) {
    while (li != NULL) {
        ListaInterpreti tmp = li->next;
        free(li->cognome);
        free(li->nome);
        free(li->cittadinanza);
        free(li);
        li = tmp;
    }
}

static void freeConcerti(ListaConcerti lc) {
    while (lc != NULL) {
        ListaConcerti tmp = lc->next;
        freeInterpreti(lc->lista);
        free(lc);
        lc = tmp;
    }
}

int verifica(ListaInterpreti interpreti);
int main(void) {
    /* Costruiamo una lista di concerti di esempio */

    /* Concerto A: contiene almeno un ITA */
    ListaInterpreti A = NULL;
    A = newInterprete("Rossi", "Mario", "ITA", A);
    A = newInterprete("Smith", "John", "USA", A);

    /* Concerto B: nessun ITA */
    ListaInterpreti B = NULL;
    B = newInterprete("Dubois", "Claire", "FRA", B);
    B = newInterprete("Tanaka", "Ken", "JPN", B);

    /* Concerto C: contiene ITA */
    ListaInterpreti C = NULL;
    C = newInterprete("Bianchi", "Luca", "ITA", C);

    ListaConcerti concerti = NULL;
    concerti = newConcerto(C, (Data){10, 3, 2026}, 60, concerti);
    concerti = newConcerto(B, (Data){25, 2, 2026}, 40, concerti);
    concerti = newConcerto(A, (Data){ 1, 2, 2026}, 50, concerti);

    printf("LISTA CONCERTI:\n");
    printConcerti(concerti);

    
    int somma = sommaPrezziConItaliano(concerti);

    printf("\nSomma prezzi (concerti con almeno un ITA): %d\n", somma);
    printf("Nota: il valore atteso dipende dai concerti che riconosci come 'con ITA'.\n");

    freeConcerti(concerti);
    return 0;
}


void f(ListaConcerti listaconcerti, int *somma)
    {
    ListaConcerti scorri_conc=listaconcerti;
    while(scorri_conc!=NULL)
        {
            if(verifica(scorri_conc->lista))
                *somma=*somma+scorri_conc->prezzoBiglietto;
            scorri_conc=scorri_conc->next;
        }
    }
int verifica(ListaInterpreti interpreti)
    {
    ListaInterpreti scorri=interpreti;
    while (scorri!=NULL) {
        if(strcmp(scorri->cittadinanza,"ITA")==0)
            return 1;
        scorri=scorri->next;
        }
    return 0;
    }

int sommaPrezziConItaliano(ListaConcerti concerti)
    {
    int somma=0;
    f(concerti, &somma);
    return somma;
    }
