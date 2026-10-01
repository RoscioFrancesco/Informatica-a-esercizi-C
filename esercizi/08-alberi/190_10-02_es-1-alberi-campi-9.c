//
//  main.c
//  es 1 alberi campi -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA DELL'ALBERO
   ========================= */
typedef struct Nodo {
    int valore;
    struct Nodo *left;
    struct Nodo *right;
} Nodo;

typedef Nodo * Albero;

/* =========================
   PROTOTIPO FUNZIONE
   ========================= */

int alberiIdentici(Albero A, Albero B);

/* =========================
   FUNZIONI DI SUPPORTO
   (solo per costruire alberi di test)
   ========================= */
Albero nuovoNodo(int v) {
    Albero n = (Albero)malloc(sizeof(Nodo));
    n->valore = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/* =========================
   MAIN
   ========================= */
int main() {
    Albero T1, T2;
    int risultato;

    /* Costruzione primo albero */
    T1 = nuovoNodo(1);
    T1->left = nuovoNodo(2);
    T1->right = nuovoNodo(3);

    /* Costruzione secondo albero */
    T2 = nuovoNodo(1);
    T2->left = nuovoNodo(2);
    T2->right = nuovoNodo(3);

    risultato = alberiIdentici(T1, T2);

    /* Stampa risultato */
    if (risultato)
        printf("I due alberi sono identici\n");
    else
        printf("I due alberi NON sono identici\n");

    return 0;
}

int alberiIdentici(Albero A, Albero B)
    {
        if(A==NULL && B==NULL)
            return 1;
        if(A==NULL || B==NULL)
            return 0;
        if(A->valore!=B->valore)
            return 0;
    return alberiIdentici(A->left, B->left) && alberiIdentici(A->right, B->right);
    }
