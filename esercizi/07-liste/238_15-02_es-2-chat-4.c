//
//  main.c
//  es 2 chat -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo *next;
} Nodo;

typedef Nodo* lista;

/* ============================
   HELPERS: costruzione / stampa / free
   ============================ */
static lista pushBack(lista L, int x) {
    if (L == NULL) {
        lista n = (lista)malloc(sizeof(Nodo));
        n->dato = x;
        n->next = NULL;
        return n;
    }
    L->next = pushBack(L->next, x);
    return L;
}

static lista buildFromArray(const int a[], int n) {
    lista L = NULL;
    for (int i = 0; i < n; i++) L = pushBack(L, a[i]);
    return L;
}

static void stampaLista(lista L) {
    while (L != NULL) {
        printf("%d", L->dato);
        if (L->next) printf(" -> ");
        L = L->next;
    }
    printf("\n");
}

static void liberaLista(lista L) {
    while (L) {
        lista t = L;
        L = L->next;
        free(t);
    }
}

/* ============================
   ESERCIZIO (DA SVOLGERE)
   ============================ */


/* STUB: compila e gira, ma NON risolve l'esercizio */
int collassaPicchi(lista *L, int K);


/* ============================
   MAIN DI TEST
   ============================ */
void f(lista *L, int K, int *count);
int main(void) {
    /* TEST 1: domino (dopo una rimozione nasce un nuovo super-picco) */
    int a1[] = {5, 20, 6, 25, 7, 1};
    int K1 = 10;
    lista L1 = buildFromArray(a1, (int)(sizeof(a1)/sizeof(a1[0])));

    printf("=== TEST 1 (domino) ===\n");
    printf("K = %d\n", K1);
    printf("Input:\n");
    stampaLista(L1);

    int rimossi1 = collassaPicchi(&L1, K1);

    printf("Output lista (ottenuta):\n");
    stampaLista(L1);
    printf("Rimossi (ottenuto): %d\n", rimossi1);

    /* Output atteso corretto:
       - 20 è super-picco (vs 5 e 6, differenze 15 e 14) -> elimina, restart
       - diventa: 5 -> 6 -> 25 -> 7 -> 1
       - 25 è super-picco (vs 6 e 7, differenze 19 e 18) -> elimina, restart
       - diventa: 5 -> 6 -> 7 -> 1
       - nessun altro super-picco
    */
    printf("Output ATTESO (corretto):\n");
    printf("Lista: 5 -> 6 -> 7 -> 1\n");
    printf("Rimossi: 2\n\n");

    liberaLista(L1);

    /* TEST 2: nessun picco (o differenze insufficienti) */
    int a2[] = {1, 9, 2, 8, 3};
    int K2 = 10;
    lista L2 = buildFromArray(a2, (int)(sizeof(a2)/sizeof(a2[0])));

    printf("=== TEST 2 (nessun picco) ===\n");
    printf("K = %d\n", K2);
    printf("Input:\n");
    stampaLista(L2);

    int rimossi2 = collassaPicchi(&L2, K2);

    printf("Output lista (ottenuta):\n");
    stampaLista(L2);
    printf("Rimossi (ottenuto): %d\n", rimossi2);

    /* Output atteso corretto: nessuna eliminazione */
    printf("Output ATTESO (corretto):\n");
    printf("Lista: 1 -> 9 -> 2 -> 8 -> 3\n");
    printf("Rimossi: 0\n\n");

    liberaLista(L2);

    /* TEST 3: eliminazioni multiple con restart dall’inizio ogni volta */
    int a3[] = {2, 30, 1, 25, 2, 40, 3, 1};
    int K3 = 20;
    lista L3 = buildFromArray(a3, (int)(sizeof(a3)/sizeof(a3[0])));

    printf("=== TEST 3 (multi-restart) ===\n");
    printf("K = %d\n", K3);
    printf("Input:\n");
    stampaLista(L3);

    int rimossi3 = collassaPicchi(&L3, K3);

    printf("Output lista (ottenuta):\n");
    stampaLista(L3);
    printf("Rimossi (ottenuto): %d\n", rimossi3);

    /* Output atteso corretto (spiegazione):
       Lista iniziale: 2 -> 30 -> 1 -> 25 -> 2 -> 40 -> 3 -> 1
       - 30 è super-picco (vs 2 e 1, diff 28 e 29) -> elimina, restart
         2 -> 1 -> 25 -> 2 -> 40 -> 3 -> 1
       - 25 è super-picco (vs 1 e 2, diff 24 e 23) -> elimina, restart
         2 -> 1 -> 2 -> 40 -> 3 -> 1
       - 40 NON è super-picco per K=20: vs 2 diff 38 ok, vs 3 diff 37 ok,
         MA attenzione: è maggiore di entrambi e ha pred/succ -> sì, quindi elimina, restart
         2 -> 1 -> 2 -> 3 -> 1
       - nessun altro
    */
    printf("Output ATTESO (corretto):\n");
    printf("Lista: 2 -> 1 -> 2 -> 3 -> 1\n");
    printf("Rimossi: 3\n\n");

    liberaLista(L3);

    return 0;
}
int verificasuperpicco(int prec, int now, int succ, int K)
    {
        if(prec>=now ||succ>=now)
            return 0;
        if(now-prec>=K && now-succ>=K)
            return 1;
        return 0;
    }

int collassaPicchi(lista *L, int K) {
    int count=0;
    f(L, K, &count);
    return count;
}


void f(lista *L, int K, int *count)
    {
        if(*L==NULL)
            return;
        lista *pp=L;
    lista prec=NULL;
    while (*pp!=NULL && (*pp)->next!=NULL) {
        if(prec!=NULL && verificasuperpicco(prec->dato, (*pp)->dato, (*pp)->next->dato, K))
            {
                (*count)++;
                lista temp=(*pp);
                (*pp)=(*pp)->next;
                free(temp);
                pp=L;
            }
        else
            {
                prec=*pp;
                pp=&(*pp)->next;
            }
    }
    }
