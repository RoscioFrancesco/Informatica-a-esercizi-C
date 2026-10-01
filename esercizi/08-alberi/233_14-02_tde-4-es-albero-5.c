//
//  main.c
//  tde 4 es albero -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//
#include <stdio.h>
#include <stdlib.h>

#define N 31   /* "sufficientemente grande" */

/* =========================
   STRUTTURA ALBERO
   ========================= */
typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node* tree;

/* =========================
   PROTOTIPO RICHIESTO
   ========================= */
/* Riempie A[] rispettando:

   - padre di i in (i-1)/2
*/
void treeToArray(tree T, int A[]);   // TODO: da implementare

/* =========================
   UTILITY
   ========================= */
static tree newNode(int x) {
    tree n = (tree)malloc(sizeof(node));
    if(!n) { perror("malloc"); exit(1); }
    n->dato = x;
    n->left = n->right = NULL;
    return n;
}

static void freeTree(tree T) {
    if(!T) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* stampa solo le prime m posizioni dell’array con indici */
static void printArrayIdx(const int A[], int m) {
    for(int i = 0; i < m; i++) {
        printf("A[%2d] = %d\n", i, A[i]);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
void f(tree T, int A[], int segna);
int main(void) {
    /*
        Albero completo (perfetto) di profondità 2 (7 nodi):

                10
              /    \
             20     30
            / \     / \
           40 50   60 70

        L’array atteso (heap-style):
        i: 0  1  2  3  4  5  6
           10 20 30 40 50 60 70
    */

    tree T = newNode(10);
    T->left = newNode(20);
    T->right = newNode(30);
    T->left->left = newNode(40);
    T->left->right = newNode(50);
    T->right->left = newNode(60);
    T->right->right = newNode(70);

    int A[N];

    /* inizializzo a un valore sentinella per vedere cosa viene scritto */
    for(int i = 0; i < N; i++) A[i] = -1;

    printf("=== ALBERO -> ARRAY (heap indices) ===\n");
    treeToArray(T, A);

    printf("\nPrime 15 posizioni dell'array:\n");
    printArrayIdx(A, 15);

    freeTree(T);
    return 0;
}


void treeToArray(tree T, int A[]) {
    f(T, A, 0);
}
//- figli di i in 2i+1 e 2i+2
void f(tree T, int A[], int segna)
    {
        if(T==NULL)
            return;
        A[segna]=T->dato;
        if(T->left!=NULL)
            {
                A[2*segna+1]=T->left->dato;
                f(T->left, A, 2*segna+1);
            }
        if(T->right!=NULL)
            {
                A[2*segna+2]=T->right->dato;
                f(T->right, A, 2*segna+2);
            }
    }
