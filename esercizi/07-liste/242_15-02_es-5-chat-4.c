//
//  main.c
//  es 5 chat -4
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
   ESERCIZIO 5 (DA SVOLGERE)
   ============================ */


/* Helpers per l'esercizio (DA COMPLETARE se vuoi) */

/* STUB: compila e gira, ma NON risolve l'esercizio */
int fondiPrimi(lista *L);

/* ============================
   MAIN DI TEST
   ============================ */
void f(lista *L, int *count);
int main(void) {
    /* TEST 1: fusioni multiple con “backtrack” (riparti dal precedente) */
    int a1[] = {2, 3, 4, 1, 6};
    /* Atteso:
       - 2+3=5 primo -> fondi in 6: 6 -> 4 -> 1 -> 6
       - riparti dal precedente: è testa, quindi riparti dal nuovo 6
       - 6+4=10 non primo -> avanti
       - 4+1=5 primo -> fondi in 4: 6 -> 4 -> 6
       - riparti dal precedente (6)
       - 6+4=10 non primo -> avanti
       - 4+6=10 non primo -> stop
       Output: 6 -> 4 -> 6, fusioni=2
    */
    lista L1 = buildFromArray(a1, (int)(sizeof(a1)/sizeof(a1[0])));

    printf("=== TEST 1 ===\n");
    printf("Input:\n");
    stampaLista(L1);

    int fusi1 = fondiPrimi(&L1);

    printf("Output (ottenuto) lista:\n");
    stampaLista(L1);
    printf("Fusioni (ottenuto): %d\n", fusi1);

    printf("Output ATTESO (corretto):\n");
    printf("Lista: 6 -> 4 -> 6\n");
    printf("Fusioni: 2\n\n");

    liberaLista(L1);

    /* TEST 2: fusione in testa + possibile rifusione col successivo */
    int a2[] = {1, 2, 2, 1};
    /* Atteso:
       - 1+2=3 primo -> fondi: 2 -> 2 -> 1
       - riparti dal precedente: non esiste, riparti dalla testa (2)
       - 2+2=4 non primo -> avanti
       - 2+1=3 primo -> fondi: 2 -> 2
       - riparti dal precedente (primo 2): 2+2=4 non primo
       Output: 2 -> 2, fusioni=2
    */
    lista L2 = buildFromArray(a2, (int)(sizeof(a2)/sizeof(a2[0])));

    printf("=== TEST 2 ===\n");
    printf("Input:\n");
    stampaLista(L2);

    int fusi2 = fondiPrimi(&L2);

    printf("Output (ottenuto) lista:\n");
    stampaLista(L2);
    printf("Fusioni (ottenuto): %d\n", fusi2);

    printf("Output ATTESO (corretto):\n");
    printf("Lista: 2 -> 2\n");
    printf("Fusioni: 2\n\n");

    liberaLista(L2);

    /* TEST 3: nessuna fusione */
    int a3[] = {4, 6, 8, 10};
    /* Tutte le somme sono pari > 2, quindi non prime */
    lista L3 = buildFromArray(a3, (int)(sizeof(a3)/sizeof(a3[0])));

    printf("=== TEST 3 ===\n");
    printf("Input:\n");
    stampaLista(L3);

    int fusi3 = fondiPrimi(&L3);

    printf("Output (ottenuto) lista:\n");
    stampaLista(L3);
    printf("Fusioni (ottenuto): %d\n", fusi3);

    printf("Output ATTESO (corretto):\n");
    printf("Lista: 4 -> 6 -> 8 -> 10\n");
    printf("Fusioni: 0\n\n");

    liberaLista(L3);

    /* TEST 4: fusione che abilita una fusione successiva (effetto a cascata) */
    int a4[] = {3, 4, 2, 5};
    /* Atteso:
       - 3+4=7 primo -> fondi in 12: 12 -> 2 -> 5
       - riparti dalla testa (12)
       - 12+2=14 non primo -> avanti
       - 2+5=7 primo -> fondi in 10: 12 -> 10
       Output: 12 -> 10, fusioni=2
    */
    lista L4 = buildFromArray(a4, (int)(sizeof(a4)/sizeof(a4[0])));

    printf("=== TEST 4 ===\n");
    printf("Input:\n");
    stampaLista(L4);

    int fusi4 = fondiPrimi(&L4);

    printf("Output (ottenuto) lista:\n");
    stampaLista(L4);
    printf("Fusioni (ottenuto): %d\n", fusi4);

    printf("Output ATTESO (corretto):\n");
    printf("Lista: 12 -> 10\n");
    printf("Fusioni: 2\n\n");

    liberaLista(L4);

    return 0;
}
int isPrimo(int n)
{
    if (n < 2)
        return 0;

    if (n == 2)
        return 1;

    if (n % 2 == 0)
        return 0;

    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
            return 0;
    }

    return 1;
}
int fondiPrimi(lista *L) {
    if(*L==NULL)
        return 0;
    int count=0;
    f(L, &count);
    return count;
}
void f(lista *L, int *count)
    {
        if(*L==NULL)
            return;
        lista *pp=L;
    while (*pp!=NULL && (*pp)->next!=NULL) {
            if(isPrimo((*pp)->dato+(*pp)->next->dato))
                {
                    (*pp)->dato=((*pp)->dato*(*pp)->next->dato);
                    lista temp=(*pp)->next;
                    (*pp)->next=temp->next;
                    free(temp);
                    pp=L;
                }
            else
                {
                    pp=&(*pp)->next;
                }
    }
    }
