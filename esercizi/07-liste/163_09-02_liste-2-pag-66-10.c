//  Created by Francesco Roscio Ricon on 09/02/26.

//• Si consiglia fortemente l’utilizzo di funzioni ausiliarie.
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
    char *cittadinanza; /* es: "ITA" */
    struct InterpreteT *next; /* per fare una lista concatenata */
} Interprete;

typedef Interprete *ListaInterpreti;

typedef struct ConcertoT {
    ListaInterpreti Lista; /* lista interpreti */
    Data data;
    int prezzoBiglietto;
    struct ConcertoT *next;
} Concerto;

typedef Concerto *ListaConcerti;



int sommaPrezziConcertiConItaliano(ListaConcerti concerti);

/* =========================
   UTILITY PER CREARE DATI DI TEST
   ========================= */
static char *dupstr(const char *s) {
    char *p = (char *)malloc(strlen(s) + 1);
    if (!p) { perror("malloc"); exit(1); }
    strcpy(p, s);
    return p;
}

static ListaInterpreti nuovoInterprete(const char *cognome, const char *nome, const char *citt) {
    ListaInterpreti x = (ListaInterpreti)malloc(sizeof(Interprete));
    if (!x) { perror("malloc"); exit(1); }
    x->cognome = dupstr(cognome);
    x->nome = dupstr(nome);
    x->cittadinanza = dupstr(citt);
    x->next = NULL;
    return x;
}

static ListaInterpreti inserisciInterpreteInCoda(ListaInterpreti head, ListaInterpreti x) {
    if (head == NULL) return x;
    ListaInterpreti cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = x;
    return head;
}

static ListaConcerti nuovoConcerto(Data d, int prezzo, ListaInterpreti listaInterpreti) {
    ListaConcerti c = (ListaConcerti)malloc(sizeof(Concerto));
    if (!c) { perror("malloc"); exit(1); }
    c->data = d;
    c->prezzoBiglietto = prezzo;
    c->Lista = listaInterpreti;
    c->next = NULL;
    return c;
}

static ListaConcerti inserisciConcertoInCoda(ListaConcerti head, ListaConcerti x) {
    if (head == NULL) return x;
    ListaConcerti cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = x;
    return head;
}

/* =========================
   STAMPE DI DEBUG
   ========================= */
static void stampaInterpreti(ListaInterpreti L) {
    while (L != NULL) {
        printf("    - %s %s (%s)\n", L->nome, L->cognome, L->cittadinanza);
        L = L->next;
    }
}

static void stampaConcerti(ListaConcerti C) {
    int i = 1;
    while (C != NULL) {
        printf("Concerto %d: %02d/%02d/%04d, prezzo=%d\n",
               i, C->data.giorno, C->data.mese, C->data.anno, C->prezzoBiglietto);
        printf("  Interpreti:\n");
        stampaInterpreti(C->Lista);
        C = C->next;
        i++;
    }
}

/* =========================
   FREE (per evitare leak nel test)
   ========================= */
static void freeInterpreti(ListaInterpreti L) {
    while (L != NULL) {
        ListaInterpreti nxt = L->next;
        free(L->cognome);
        free(L->nome);
        free(L->cittadinanza);
        free(L);
        L = nxt;
    }
}

static void freeConcerti(ListaConcerti C) {
    while (C != NULL) {
        ListaConcerti nxt = C->next;
        freeInterpreti(C->Lista);
        free(C);
        C = nxt;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int almenounitaliano(ListaInterpreti head);
int sommaPrezziConcertiConItaliano(ListaConcerti concerti);
int main(void) {
    ListaConcerti concerti = NULL;

    /* Concerto 1: contiene un ITA */
    Data d1 = {10, 2, 2026};
    ListaInterpreti L1 = NULL;
    L1 = inserisciInterpreteInCoda(L1, nuovoInterprete("Rossi", "Mario", "ITA"));
    L1 = inserisciInterpreteInCoda(L1, nuovoInterprete("Smith", "John", "USA"));
    concerti = inserisciConcertoInCoda(concerti, nuovoConcerto(d1, 50, L1));

    /* Concerto 2: nessun ITA */
    Data d2 = {11, 2, 2026};
    ListaInterpreti L2 = NULL;
    L2 = inserisciInterpreteInCoda(L2, nuovoInterprete("Garcia", "Ana", "ESP"));
    L2 = inserisciInterpreteInCoda(L2, nuovoInterprete("Muller", "Karl", "DEU"));
    concerti = inserisciConcertoInCoda(concerti, nuovoConcerto(d2, 30, L2));

    /* Concerto 3: contiene un ITA */
    Data d3 = {12, 2, 2026};
    ListaInterpreti L3 = NULL;
    L3 = inserisciInterpreteInCoda(L3, nuovoInterprete("Bianchi", "Luca", "ITA"));
    concerti = inserisciConcertoInCoda(concerti, nuovoConcerto(d3, 70, L3));

    printf("=== LISTA CONCERTI (input) ===\n");
    stampaConcerti(concerti);

    int somma = sommaPrezziConcertiConItaliano(concerti);
    printf("%d", somma);
    freeConcerti(concerti);
    concerti = NULL;

    return 0;
}


int almenounitaliano(ListaInterpreti head)
    {
        if(head==NULL)
            return 0;
        while(head!=NULL)
            {
                if(strcmp("ITA", head->cittadinanza)==0)
                    return 1;
                head=head->next;
            }
        return 0;
    }

int sommaPrezziConcertiConItaliano(ListaConcerti concerti)
    {
    int somma=0;
    if(concerti==NULL)
        return somma;
    while (concerti!=NULL) {
        if(almenounitaliano(concerti->Lista))
            {
                somma=somma+concerti->prezzoBiglietto;
            }
        concerti=concerti->next;
    }
    return somma;
    }
