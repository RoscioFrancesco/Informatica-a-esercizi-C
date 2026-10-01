//
//  main.c
//  liste ric
//
//  Created by Francesco Roscio Ricon on 26/01/26.
//
#include <stdio.h>
#include <stdlib.h>

/*** STRUTTURE ***/
typedef struct nodo {
    int val;
    struct nodo* next;
} Nodo;

typedef Nodo* Lista;

/*** PROTOTIPI ***/
Lista inserisciInCoda(Lista l, int x);
void stampaLista(Lista l);
void freeLista(Lista l);

// funzione dell'esercizio
Lista inverti(Lista l);

/*** FUNZIONI DI SUPPORTO ***/
Lista inserisciInCoda(Lista l, int x) {
    Nodo* nuovo = (Nodo*)malloc(sizeof(Nodo));
    nuovo->val = x;
    nuovo->next = NULL;

    if (l == NULL) return nuovo;

    Nodo* temp = l;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = nuovo;
    return l;
}

void stampaLista(Lista l) {
    while (l != NULL) {
        printf("%d -> ", l->val);
        l = l->next;
    }
    printf("NULL\n");
}

void freeLista(Lista l) {
    while (l != NULL) {
        Nodo* tmp = l;
        l = l->next;
        free(tmp);
    }
}


Lista inverti(Lista l) {
    if (l == NULL || l->next == NULL)
        return l;

    // inverti il resto
    Lista nuovaTesta = inverti(l->next);

    // attacca il primo nodo in fondo
    l->next->next = l;
    l->next = NULL;

    return nuovaTesta;
}
Lista inverti_iterative(Lista head);
int main() {
    Lista l = NULL;

    int valori[] = {1, 2, 3, 4, 5};
    int n = sizeof(valori) / sizeof(valori[0]);

    // costruzione lista
    for (int i = 0; i < n; i++) {
        l = inserisciInCoda(l, valori[i]);
    }

    printf("Lista originale:\n");
    stampaLista(l);

    // inversione
    l = inverti_iterative(l);

    printf("\nLista invertita:\n");
    stampaLista(l);

    freeLista(l);
    return 0;
}
Lista inverti_iterative(Lista head)
    {
    Lista prec=NULL;
    Lista scorri=head;
    Lista succ=NULL;
    while (scorri!=NULL) {
            succ=scorri->next;
            scorri->next=prec;
            prec=scorri;
            scorri=succ;
        }
    return prec;
    }
