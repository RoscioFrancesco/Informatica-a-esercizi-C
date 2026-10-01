//
//  main.c
//  tde 2 es 1 -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int numero;
    struct Node *next;
} Nodo;

typedef Nodo* Lista;

int monotonaCrescente(Lista L);

Nodo* newNodo(int x) {
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    n->numero = x;
    n->next = NULL;
    return n;
}

Lista inserisciCoda(Lista L, int x) {
    Nodo* nn = newNodo(x);
    if(L == NULL)
        return nn;

    Nodo* tmp = L;
    while(tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = nn;
    return L;
}

Lista buildFromArray(int a[], int n) {
    Lista L = NULL;
    for(int i = 0; i < n; i++)
        L = inserisciCoda(L, a[i]);
    return L;
}

void stampaLista(Lista L) {
    if(L == NULL) {
        printf("NULL\n");
        return;
    }

    while(L != NULL) {
        printf("%d", L->numero);
        if(L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

void freeLista(Lista L) {
    while(L) {
        Nodo* tmp = L;
        L = L->next;
        free(tmp);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int f(Lista head, int prec, int *hasprec);
int main() {

    /* Test 1: strettamente crescente */
    int a1[] = {1,2,3,4,5};
    Lista L1 = buildFromArray(a1, 5);

    printf("=== TEST 1 ===\n");
    printf("Lista: ");
    stampaLista(L1);
    printf("Monotona crescente? %d\n", monotonaCrescente(L1));
    freeLista(L1);

    /* Test 2: non strettamente crescente (uguale) */
    int a2[] = {1,2,2,4};
    Lista L2 = buildFromArray(a2, 4);

    printf("\n=== TEST 2 ===\n");
    printf("Lista: ");
    stampaLista(L2);
    printf("Monotona crescente? %d\n", monotonaCrescente(L2));
    freeLista(L2);

    /* Test 3: decrescente */
    int a3[] = {5,4,3};
    Lista L3 = buildFromArray(a3, 3);

    printf("\n=== TEST 3 ===\n");
    printf("Lista: ");
    stampaLista(L3);
    printf("Monotona crescente? %d\n", monotonaCrescente(L3));
    freeLista(L3);

    /* Test 4: un solo elemento */
    int a4[] = {7};
    Lista L4 = buildFromArray(a4, 1);

    printf("\n=== TEST 4 ===\n");
    printf("Lista: ");
    stampaLista(L4);
    printf("Monotona crescente? %d\n", monotonaCrescente(L4));
    freeLista(L4);

    /* Test 5: lista vuota */
    Lista L5 = NULL;

    printf("\n=== TEST 5 ===\n");
    printf("Lista: ");
    stampaLista(L5);
    printf("Monotona crescente? %d\n", monotonaCrescente(L5));

    return 0;
}



int monotonaCrescente(Lista L) {
    int hasprec=0;
    return f(L, 0, &hasprec);
}
//se ogni elemento è strettamente superiore al suo predecessore.
int f(Lista head, int prec, int *hasprec)
    {
        if(head==NULL)
            return 1;
        if(*hasprec==1)
            {
                if(!(head->numero>prec))
                    return 0;
            }
        if(*hasprec==0)
            {
                *hasprec=1;
                prec=head->numero;
            }
    return f(head->next, head->numero, hasprec);
    }
