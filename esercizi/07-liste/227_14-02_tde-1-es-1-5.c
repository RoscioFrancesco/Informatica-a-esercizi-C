//
//  main.c
//  tde 1 es 1 -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct EL {
    int dato;
    struct EL *next;
} nodo;

typedef nodo* lista;

/* =========================
   PROTOTIPO RICHIESTO
   ========================= */

lista Merge(lista lista1, lista lista2);  // TODO: da implementare

/* =========================
   FUNZIONI DI SUPPORTO
   ========================= */

nodo* newNodo(int x) {
    nodo* n = (nodo*)malloc(sizeof(nodo));
    n->dato = x;
    n->next = NULL;
    return n;
}

lista inserisciCoda(lista L, int x) {
    nodo* nn = newNodo(x);
    if(L == NULL)
        return nn;

    nodo* tmp = L;
    while(tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = nn;
    return L;
}

lista buildFromArray(int a[], int n) {
    lista L = NULL;
    for(int i = 0; i < n; i++)
        L = inserisciCoda(L, a[i]);
    return L;
}

void stampaLista(lista L) {
    if(L == NULL) {
        printf("NULL\n");
        return;
    }

    while(L != NULL) {
        printf("%d", L->dato);
        if(L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

void freeLista(lista L) {
    while(L) {
        nodo* tmp = L;
        L = L->next;
        free(tmp);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
lista inserimentooridnato(lista head, int x);
int main() {

    /* Test 1 */
    int a1[] = {1,3,5,7};
    int b1[] = {2,4,6,8};

    lista L1 = buildFromArray(a1, 4);
    lista L2 = buildFromArray(b1, 4);

    printf("=== TEST 1 ===\n");
    printf("Lista1: ");
    stampaLista(L1);
    printf("Lista2: ");
    stampaLista(L2);

    lista R1 = Merge(L1, L2);
    printf("Merge:  ");
    stampaLista(R1);

    freeLista(L1);
    freeLista(L2);
    freeLista(R1);


    /* Test 2: con duplicati */
    int a2[] = {1,2,4,4,7};
    int b2[] = {2,4,6};

    L1 = buildFromArray(a2, 5);
    L2 = buildFromArray(b2, 3);

    printf("\n=== TEST 2 (duplicati) ===\n");
    printf("Lista1: ");
    stampaLista(L1);
    printf("Lista2: ");
    stampaLista(L2);

    lista R2 = Merge(L1, L2);
    printf("Merge:  ");
    stampaLista(R2);

    freeLista(L1);
    freeLista(L2);
    freeLista(R2);


    /* Test 3: una lista vuota */
    L1 = NULL;
    int b3[] = {5,6,7};
    L2 = buildFromArray(b3, 3);

    printf("\n=== TEST 3 (una vuota) ===\n");
    printf("Lista1: ");
    stampaLista(L1);
    printf("Lista2: ");
    stampaLista(L2);

    lista R3 = Merge(L1, L2);
    printf("Merge:  ");
    stampaLista(R3);

    freeLista(L2);
    freeLista(R3);

    return 0;
}



lista Merge(lista lista1, lista lista2) {
    lista new=NULL;
    while (lista1!=NULL) {
        new=inserimentooridnato(new, lista1->dato);
        lista1=lista1->next;
    }
    while(lista2!=NULL)
        {
            new=inserimentooridnato(new, lista2->dato);
            lista2=lista2->next;
        }
    return new;
}
//fornisce in output una nuova lista ordinata contenente tutti gli elementi delle due liste (duplicati inclusi).

lista inserimentooridnato(lista head, int x)
    {
        if(head==NULL || x<head->dato)
            {
                lista new=(lista)malloc(sizeof(*new));
                new->next=head;
                new->dato=x;
                return new;
            }
        head->next=inserimentooridnato(head->next, x);
        return head;
    }
