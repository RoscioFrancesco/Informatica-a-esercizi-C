//
//  main.c
//  liste tde 3 alberi -12
//
//  Created by Francesco Roscio Ricon on 07/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA DELL'ALBERO
   ========================= */
typedef struct nodo {
    int valore;
    struct nodo *left;
    struct nodo *right;
} Nodo;

typedef Nodo* Albero;

/* =========================
   PROTOTIPO FUNZIONE RICHIESTA
   ========================= */
int verificaESomma(Albero T1, Albero T2, Albero T3);

/* =========================
   FUNZIONI DI SUPPORTO (TEST)
   ========================= */
Albero nuovoNodo(int v) {
    Albero n = (Albero)malloc(sizeof(Nodo));
    n->valore = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void stampaPreorder(Albero t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }
    printf("%d ", t->valore);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

/* =========================
   MAIN
   ========================= */
void riempizeri(Albero t);
void casopostivio(Albero t1, Albero t2, Albero t3);
int f(Albero t1, Albero t2, Albero t3);
int verificastruttura(Albero t1, Albero t2);

int main() {

    /* Costruzione alberi di test */
    Albero T1 = nuovoNodo(1);
    T1->left = nuovoNodo(2);
    T1->right = nuovoNodo(3);

    Albero T2 = nuovoNodo(10);
    T2->left = nuovoNodo(20);
    T2->right = nuovoNodo(30);

    /* T3 inizialmente vuoto ma strutturalmente uguale */
    Albero T3 = nuovoNodo(0);
    T3->left = nuovoNodo(0);
    T3->right = nuovoNodo(0);

    printf("Albero T1 (preorder): ");
    stampaPreorder(T1);
    printf("\n");

    printf("Albero T2 (preorder): ");
    stampaPreorder(T2);
    printf("\n");

    printf("Albero T3 prima della funzione (preorder): ");
    stampaPreorder(T3);
    printf("\n");

    /* Chiamata funzione */
    int esito = f(T1, T2, T3);

    printf("\nValore restituito dalla funzione: %d\n", esito);

    printf("Albero T3 dopo la funzione (preorder): ");
    stampaPreorder(T3);
    printf("\n");

    return 0;
}


int verificastruttura(Albero t1, Albero t2)
    {
        if(t1==NULL && t2==NULL)
            return 1;
        if(t1==NULL || t2==NULL)
            return 0;
    return verificastruttura(t1->left, t2->left) && verificastruttura(t1->right, t2->right);
    }
int f(Albero t1, Albero t2, Albero t3)
    {
        if(verificastruttura(t1, t2)&&verificastruttura(t2, t3))
            {
                casopostivio(t1, t2, t3);
                return 1;
            }
        else
            {
                riempizeri(t3);
                return 0;
            }
    }
void riempizeri(Albero t)
    {
        if(t==NULL)
            return;
        t->valore=0;
        riempizeri(t->left);
        riempizeri(t->right);
    }
void casopostivio(Albero t1, Albero t2, Albero t3)
    {
        if(t1==NULL) // se t1 è null lo sono anche gli alri perch hanno la setssa struttura
            return;
    t3->valore=t1->valore+t2->valore;
    casopostivio(t1->left, t2->left, t3->left);
    casopostivio(t1->right, t2->right, t3->right);
    }
