//
//  main.c
//  tde 4 alberi -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//
//


#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct EL {
    int dato;
    struct EL *left, *right;
} node;

typedef node *tree;


/* Ritorna 1 se esiste un cammino radice->foglia strettamente decrescente */
int esisteCamminoDecrescente(tree T);

/* (facoltativa) ausiliaria che potresti usare */
static int esisteCamminoDecrescente_aux(tree T, int prev, int hasPrev);

/* =========================
   UTILITY PER CREARE / STAMPARE / LIBERARE ALBERO
   ========================= */
static tree newNode(int v) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

static void freeTree(tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

static void printPreorder(tree t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }
    printf("%d ", t->dato);
    printPreorder(t->left);
    printPreorder(t->right);
}

/* =========================
   STUB FUNZIONE ESERCIZIO (NON RISOLVE)
   ========================= */


/* =========================
   MAIN DI TEST
   ========================= */
int f(tree albero);
int main(void) {
    /*
        Creo un albero di esempio:

                 10
               /    \
              7      12
             / \       \
            5   8       9
           /
          2

        Cammini radice->foglia:
        10-7-5-2  (strettamente decrescente)  -> YES
        10-7-8    (non decrescente)
        10-12-9   (non decrescente all'inizio)
    */
    tree T = newNode(10);
    T->left = newNode(7);
    T->right = newNode(12);
    T->left->left = newNode(5);
    T->left->right = newNode(8);
    T->left->left->left = newNode(2);
    T->right->right = newNode(9);

    printf("=== Albero (preorder) ===\n");
    printPreorder(T);
    printf("\n\n");

    int esito = f(T); /* stub */
    printf("esisteCamminoDecrescente(T) = %d (stub)\n", esito);

    freeTree(T);
    return 0;
}
int f(tree albero)
    {
        if(albero==NULL)
            return 0;
        int sx=0;
        int dx=0;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
        if(albero->left!=NULL)
            {
                if(albero->left->dato<albero->dato)
                    sx=f(albero->left);
            }
        if(albero->right!=NULL)
            {
                if(albero->right->dato<albero->dato)
                    dx=f(albero->right);
            }
    return sx|| dx;
    }
