//
//  main.c
//  es 4 alberi campi -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
struct Knot;
typedef struct Knot * Albero;

typedef struct Branch {
    Albero child;
    struct Branch *next;
} Ramo;

typedef struct Knot {
    int dato;
    Ramo *rami;   /* lista di figli */
} Nodo;

/* =========================
   PROTOTIPO FUNZIONE RICHIESTA
   ========================= */
int conta(Albero t);

/* =========================
   SUPPORTO PER CREARE ALBERI DI TEST
   ========================= */
static Albero nuovoNodo(int v) {
    Albero n = (Albero)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = v;
    n->rami = NULL;
    return n;
}

/* aggiunge un figlio in testa alla lista dei rami del padre */
static void aggiungiFiglio(Albero padre, Albero figlio) {
    Ramo *r = (Ramo*)malloc(sizeof(Ramo));
    if (!r) { perror("malloc"); exit(1); }
    r->child = figlio;
    r->next = padre->rami;
    padre->rami = r;
}
void f(Albero tree ,int *count);

int conta(Albero t) {
    int count=0;
    f(t, &count);
    return count;
}

/* =========================
   MAIN
   ========================= */
int main() {
    Albero T;
    int n;

    /* Creo un albero N-ario di esempio:
       1 ha figli 2,3,4
       3 ha figli 5,6
    */
    T = nuovoNodo(1);

    Albero n2 = nuovoNodo(2);
    Albero n3 = nuovoNodo(3);
    Albero n4 = nuovoNodo(4);
    aggiungiFiglio(T, n4);
    aggiungiFiglio(T, n3);
    aggiungiFiglio(T, n2);

    Albero n5 = nuovoNodo(5);
    Albero n6 = nuovoNodo(6);
    aggiungiFiglio(n3, n6);
    aggiungiFiglio(n3, n5);

    /* Chiamata funzione richiesta */
    n = conta(T);

    /* Stampa risultato */
    printf("Numero di nodi dell'albero: %d\n", n);

    return 0;
}

void f(Albero tree ,int *count)
    {
        if(tree==NULL)
            return;
        (*count)++;
    Ramo *scorrirami=tree->rami;
    while (scorrirami!=NULL) {
        f(scorrirami->child, count);
        scorrirami=scorrirami->next;
    }
    }
