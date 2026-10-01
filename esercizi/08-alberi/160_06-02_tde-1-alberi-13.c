//
//  main.c
//  tde 1 alberi -13
//
//  Created by Francesco Roscio Ricon on 06/02/26.
//


#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   STRUTTURE (come da testo)
   ========================================================= */
typedef struct NO {
    int dato;
    struct NO *next;
} nodo;
typedef nodo *lista;

typedef struct EL {
    int dato;
    struct EL *left, *right;
} node;
typedef node *tree;

/* =========================================================
   PROTOTIPI (f è quella dell'esercizio)
   ========================================================= */
int f(lista L, tree T);   

/* =========================================================
   UTILITY PER I TEST (costruzione, stampa, free)
   ========================================================= */
static nodo* newNodo(int x, nodo* next) {
    nodo* n = (nodo*)malloc(sizeof(nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = x;
    n->next = next;
    return n;
}

static node* newNode(int x, node* left, node* right) {
    node* t = (node*)malloc(sizeof(node));
    if (!t) { perror("malloc"); exit(1); }
    t->dato = x;
    t->left = left;
    t->right = right;
    return t;
}

static void stampaLista(lista L) {
    printf("[ ");
    for (; L != NULL; L = L->next) printf("%d ", L->dato);
    printf("]\n");
}

static void stampaAlberoPreorder(tree T) {
    if (!T) { printf("NULL "); return; }
    printf("%d ", T->dato);
    stampaAlberoPreorder(T->left);
    stampaAlberoPreorder(T->right);
}

static void freeLista(lista L) {
    while (L) {
        nodo* tmp = L->next;
        free(L);
        L = tmp;
    }
}

static void freeTree(tree T) {
    if (!T) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* =========================================================
   MAIN DI TEST
   ========================================================= */
int main(void) {
    /*
        Costruiamo un albero di esempio:

                 5
               /   \
              3     8
             / \     \
            1   4     9

        Cammini radice->foglia:
        5-3-1
        5-3-4
        5-8-9
    */
    tree T = newNode(5,
                newNode(3,
                    newNode(1, NULL, NULL),
                    newNode(4, NULL, NULL)),
                newNode(8,
                    NULL,
                    newNode(9, NULL, NULL)));

    /* Liste di test */
    lista L1 = newNodo(5, newNodo(3, newNodo(1, NULL)));      /* match (5-3-1) */
    lista L2 = newNodo(5, newNodo(8, newNodo(9, NULL)));      /* match (5-8-9) */
    lista L3 = newNodo(5, newNodo(3, newNodo(9, NULL)));      /* no match */
    lista L4 = newNodo(5, newNodo(3, NULL));                  /* prefisso: dipende dal testo (qui chiedono radice->FOGLIA) */
    lista L5 = newNodo(5, newNodo(3, newNodo(4, NULL)));      /* match (5-3-4) */

    printf("Albero (preorder): ");
    stampaAlberoPreorder(T);
    printf("\n\n");

    printf("Test 1: L1 = "); stampaLista(L1);
    printf("f(L1,T) = %d\n\n", f(L1, T));

    printf("Test 2: L2 = "); stampaLista(L2);
    printf("f(L2,T) = %d\n\n", f(L2, T));

    printf("Test 3: L3 = "); stampaLista(L3);
    printf("f(L3,T) = %d\n\n", f(L3, T));

    printf("Test 4: L4 = "); stampaLista(L4);
    printf("f(L4,T) = %d\n\n", f(L4, T));

    printf("Test 5: L5 = "); stampaLista(L5);
    printf("f(L5,T) = %d\n\n", f(L5, T));

    freeLista(L1);
    freeLista(L2);
    freeLista(L3);
    freeLista(L4);
    freeLista(L5);
    freeTree(T);

    return 0;
}
int f(lista L, tree T)
    {
        if(T==NULL)
            return 0;
        if(L==NULL)
            return 0;
        if(L->dato!=T->dato)
            return 0;
        if(T->left==NULL && T->right==NULL && L->next==NULL)
            return 1;
        if(L->next==NULL)
            return 0;
        int sx=0;
        int dx=0;
        if(T->left!=NULL)
            {
                sx=f(L->next, T->left);
            }
        if(T->right!=NULL)
            {
                dx=f(L->next, T->right);
            }
    return sx||dx;
    }
