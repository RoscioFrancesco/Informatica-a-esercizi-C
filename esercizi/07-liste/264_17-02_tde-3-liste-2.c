//
//  main.c
//  tde 3 liste  -2
//
//  Created by Francesco Roscio Ricon on 17/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef struct d {
    int giorno, mese, anno;
} Data;

typedef struct job {
    char codice[N], descrizione[N], titoloStudioRichiesto[N];
    int stipendio;
    Data dataInserimento;
    struct job *next;
} offertaDiLavoro;

typedef offertaDiLavoro *ListaOfferte;

/* =========================
   PROTOTIPI ESERCIZIO
   ========================= */
int offertaMigliore(ListaOfferte offerte, char titolo[]);
int offertaMigliore(ListaOfferte offerte, char titolo[]);
int eliminaOfferteVecchie(ListaOfferte Lis, Data oggi);

/* =========================
   SUPPORTO PER TEST
   ========================= */
static offertaDiLavoro *newJob(const char *cod, const char *desc, const char *tit, int stip, int g, int m, int a) {
    offertaDiLavoro *n = (offertaDiLavoro*)malloc(sizeof(offertaDiLavoro));
    strncpy(n->codice, cod, N);
    strncpy(n->descrizione, desc, N);
    strncpy(n->titoloStudioRichiesto, tit, N);
    n->stipendio = stip;
    n->dataInserimento.giorno = g;
    n->dataInserimento.mese = m;
    n->dataInserimento.anno = a;
    n->next = NULL;
    return n;
}

/* Inserimento in coda SOLO per costruire i test (non garantisce ordine) */
static ListaOfferte pushBack(ListaOfferte L, offertaDiLavoro *node) {
    if (!L) return node;
    offertaDiLavoro *cur = L;
    while (cur->next) cur = cur->next;
    cur->next = node;
    return L;
}

static void printData(Data d) {
    printf("%02d/%02d/%04d", d.giorno, d.mese, d.anno);
}

static void printOfferte(const char *title, ListaOfferte L) {
    printf("%s\n", title);
    if (!L) {
        printf("  (lista vuota)\n");
        return;
    }
    while (L) {
        printf("  Codice=%s | Titolo=%s | Stipendio=%d | Data=",
               L->codice, L->titoloStudioRichiesto, L->stipendio);
        printData(L->dataInserimento);
        printf("\n");
        L = L->next;
    }
}

static void freeOfferte(ListaOfferte L) {
    while (L) {
        offertaDiLavoro *tmp = L;
        L = L->next;
        free(tmp);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int ver(Data oggi, Data d);
void f(ListaOfferte *l, Data oggi, int *count);
int main(void) {

    /* Costruiamo una lista ordinata per codice (come da testo) */
    ListaOfferte L = NULL;

    /* Oggi fissato per i test: 07/02/2012 */
    Data oggi = {7, 2, 2012};

    /* Inserimenti (codici in ordine crescente) */
    L = pushBack(L, newJob("A001", "Dev C junior",     "DIPLOMA",       1200, 1, 11, 2012));
    L = pushBack(L, newJob("A010", "Helpdesk",         "DIPLOMA",       1300, 10, 12, 2011));
    L = pushBack(L, newJob("B020", "Web developer",    "LAUREA",        1700, 20, 10, 2011));
    L = pushBack(L, newJob("C015", "DB admin",         "LAUREA",        2200, 25,  1, 2012));
    L = pushBack(L, newJob("D100", "Ricercatore",      "DOTTORATO",     3000,  1,  2, 2012));
    L = pushBack(L, newJob("E005", "Segreteria",       "DIPLOMA",       1100,  5,  2, 2012));
    L = pushBack(L, newJob("F777", "Analista dati",    "LAUREA",        2400, 15, 11, 2011));

    printf("===== STATO INIZIALE =====\n");
    printf("Oggi = "); printData(oggi); printf("\n");
    printOfferte("Lista offerte:", L);
    printf("\n");

    /* =========================
       TEST 1: offertaMigliore
       ========================= */
    printf("===== TEST 1: offertaMigliore =====\n");

    printf("Richiesta titolo: LAUREA\n");
    int best1 = offertaMigliore(L, "LAUREA");
    printf("Risultato offertaMigliore = %d\n\n", best1);

    printf("Richiesta titolo: DIPLOMA\n");
    int best2 = offertaMigliore(L, "DIPLOMA");
    printf("Risultato offertaMigliore = %d\n\n", best2);

    printf("Richiesta titolo: MASTER (inesistente)\n");
    int best3 = offertaMigliore(L, "MASTER");
    printf("Risultato offertaMigliore = %d\n\n", best3);

    /* =========================
       TEST 2: eliminaOfferteVecchie
       ========================= */
    printf("===== TEST 2: eliminaOfferteVecchie =====\n");
    printf("Elimino offerte più vecchie di 90 giorni rispetto a oggi.\n");

    int numElim = eliminaOfferteVecchie(L, oggi);
    printf("Numero offerte eliminate = %d\n", numElim);

    printf("\nLista dopo eliminaOfferteVecchie:\n");
    printOfferte("Lista offerte:", L);

    freeOfferte(L);
    return 0;
}


/*
int offertaMigliore(ListaOfferte offerte, char titolo[]) {
    // TODO
}

int eliminaOfferteVecchie(ListaOfferte Lis, Data oggi) {
    // TODO
}
*/

int offertaMigliore(ListaOfferte offerte, char titolo[])
    {
    int max=0;
    while(offerte!=NULL)
        {
            if(strcmp(offerte->titoloStudioRichiesto, titolo)==0)
                {
                    if(offerte->stipendio>max)
                        {
                            max=offerte->stipendio;
                        }
                }
            offerte=offerte->next;
        }
    return max;
    }

int eliminaOfferteVecchie(ListaOfferte Lis, Data oggi)
    {
    int count=0;
    f(&Lis, oggi, &count);
    return count;
    }

int ver(Data oggi, Data d)
    {
        int somma=0;
        somma=somma+365*(oggi.anno-d.anno);
        somma=somma+31*(oggi.mese-d.mese);
        somma=somma+(oggi.giorno-d.giorno);
        if(somma>90)
            return 1;
        return 0;
    }

void f(ListaOfferte *l, Data oggi, int *count)
    {
        if(*l==NULL)
            return;
    ListaOfferte *pp=l;
    while (*pp!=NULL) {
        if(ver(oggi, (*pp)->dataInserimento))
            {
                ListaOfferte temp=(*pp);
                (*pp)=(*pp)->next;
                free(temp);
                (*count)++;
            }
        else
            {
                pp=&(*pp)->next;
            }
    }
    }
