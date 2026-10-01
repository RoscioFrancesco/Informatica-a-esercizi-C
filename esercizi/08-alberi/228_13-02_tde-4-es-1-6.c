//
//  main.c
//  tde 4 es 1 -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node* tree;

int verificaLivelli(tree T);

tree creaNodo(int x) {
    tree n = (tree)malloc(sizeof(node));
    n->dato = x;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/* stampa inorder con livello */
void stampaConLivello(tree T, int livello) {
    if (T == NULL)
        return;

    stampaConLivello(T->left, livello + 1);

    printf("Nodo %d al livello %d\n", T->dato, livello);

    stampaConLivello(T->right, livello + 1);
}

/* ============================ MAIN ============================ */

int main() {

    /* ===== TEST 1: valido ===== */

    tree T1 = creaNodo(5);
    T1->left = creaNodo(3);
    T1->right = creaNodo(4);
    T1->left->left = creaNodo(2);
    T1->left->right = creaNodo(2);

    printf("=== TEST 1 ===\n");
    stampaConLivello(T1, 0);
    printf("Verifica: %d\n\n", verificaLivelli(T1));


    /* ===== TEST 2: non valido (radice ok, figlio no) ===== */

    tree T2 = creaNodo(5);
    T2->left = creaNodo(0);   // livello 1 → 0 > 1? NO
    T2->right = creaNodo(3);

    printf("=== TEST 2 ===\n");
    stampaConLivello(T2, 0);
    printf("Verifica: %d\n\n", verificaLivelli(T2));


    /* ===== TEST 3: nodo interno non valido ===== */

    tree T3 = creaNodo(4);
    T3->left = creaNodo(3);
    T3->right = creaNodo(3);
    T3->left->left = creaNodo(1);  // livello 2 → 1 > 2? NO

    printf("=== TEST 3 ===\n");
    stampaConLivello(T3, 0);
    printf("Verifica: %d\n\n", verificaLivelli(T3));


    /* ===== TEST 4: albero vuoto ===== */

    tree T4 = NULL;

    printf("=== TEST 4 ===\n");
    printf("Albero vuoto\n");
    printf("Verifica: %d\n\n", verificaLivelli(T4));

    return 0;
}

int f(tree albero ,int livello)
    {
        if(albero==NULL)
            return 1;
        if(albero->dato<livello)
            return 0;
        return f(albero->left, livello+1) &&f(albero->right, livello+1);
    }
int verificaLivelli(tree T)
    {
    return f(T, 0);
    }
