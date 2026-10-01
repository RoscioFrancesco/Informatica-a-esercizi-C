//
//  main.c
//  tde 3 liste -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */

typedef struct EL {
    int dato;
    struct EL *next;
} nodo;

typedef nodo *lista;



lista differenzaSimmetrica(lista A, lista B);

/* =========================
   FUNZIONI DI SUPPORTO LISTE
   ========================= */

static nodo *newNode(int x) {
    nodo *n = (nodo *)malloc(sizeof(nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = x;
    n->next = NULL;
    return n;
}

static lista inserisciInCoda(lista L, int x) {
    nodo *n = newNode(x);
    if (L == NULL) return n;

    nodo *cur = L;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = n;
    return L;
}

static void stampaLista(lista L) {
    printf("[ ");
    while (L != NULL) {
        printf("%d ", L->dato);
        L = L->next;
    }
    printf("]\n");
}

static void liberaLista(lista L) {
    while (L != NULL) {
        nodo *tmp = L->next;
        free(L);
        L = tmp;
    }
}

int main(void) {
    lista A = NULL;
    lista B = NULL;

    /* Costruisco due liste senza duplicati */
    A = inserisciInCoda(A, 1);
    A = inserisciInCoda(A, 3);
    A = inserisciInCoda(A, 5);
    A = inserisciInCoda(A, 7);

    B = inserisciInCoda(B, 3);
    B = inserisciInCoda(B, 4);
    B = inserisciInCoda(B, 7);
    B = inserisciInCoda(B, 9);

    printf("Lista A = ");
    stampaLista(A);

    printf("Lista B = ");
    stampaLista(B);

    /* Chiamata funzione dell'esercizio (stub) */
    lista R = differenzaSimmetrica(A, B);

    printf("Risultato (elementi presenti in una sola lista): ");
    stampaLista(R);

    /* Pulizia memoria */
    liberaLista(A);
    liberaLista(B);
    liberaLista(R);

    return 0;
}


int trova(int x, lista head)
    {
        if(head==NULL)
            return 0;
    lista scorri=head;
    while (scorri!=NULL) {
        if(scorri->dato==x)
            return 1;
        scorri=scorri->next;
        }
    return 0;
    }
lista inseriscincoda(lista head, int x)
    {
        if(head==NULL)
            {
                lista new=(lista)malloc(sizeof(*new));
                new->next=NULL;
                new->dato=x;
                return new;
            }
        head->next=inseriscincoda(head->next, x);
        return head;
    }
lista differenzaSimmetrica(lista l1, lista l2)
    {
    lista new=NULL;
    lista scorril1=l1;
    lista scorril2=l2;
    while (scorril1!=NULL) {
        if(trova(scorril1->dato, l2)==0)
            new=inseriscincoda(new, scorril1->dato);
        scorril1=scorril1->next;
    }
    while (scorril2!=NULL) {
        if(trova(scorril2->dato, l1)==0)
            new=inseriscincoda(new, scorril2->dato);
        scorril2=scorril2->next;
    }
    return new;
}
