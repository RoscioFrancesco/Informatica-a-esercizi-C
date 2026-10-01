//
//  main.c
//  liste tde 2 alberi -12
//
//  Created by Francesco Roscio Ricon on 07/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA DATO
   ========================= */
typedef struct t {
    int val;
    struct t *left, *right;
} Nodo;

typedef Nodo *Tree;

/* =========================
   PROTOTIPI
   ========================= */
int contaComuni(Tree a, Tree b); 

Tree newNode(int v);
void freeTree(Tree t);
void printPreorder(Tree t);

/* =========================
   MAIN DI TEST
   ========================= */
int trovaval(int x, Tree albero);
void f(Tree a, Tree b, int *count);
int main(void) {
    /* Costruisco due alberi di esempio (non BST per forza) */

    /* Albero A:
            5
           / \
          3   8
         /   / \
        1   5   9
    */
    Tree A = newNode(5);
    A->left = newNode(3);
    A->right = newNode(8);
    A->left->left = newNode(1);
    A->right->left = newNode(5);
    A->right->right = newNode(9);

    /* Albero B:
            7
           / \
          3   8
           \   \
            5   10
    */
    Tree B = newNode(7);
    B->left = newNode(3);
    B->right = newNode(8);
    B->left->right = newNode(5);
    B->right->right = newNode(10);
    

    printf("Albero A (preorder): ");
    printPreorder(A);
    printf("\n");

    printf("Albero B (preorder): ");
    printPreorder(B);
    printf("\n");

    /* Chiamata alla funzione richiesta */
    int comuni = contaComuni(A, B);
    printf("\nNumero di elementi comuni tra A e B: %d\n", comuni);

    /* Cleanup */
    freeTree(A);
    freeTree(B);

    return 0;
}

/* =========================
   FUNZIONE DA SVOLGERE (TODO)
   ========================= */

int contaComuni(Tree a, Tree b) {
    int count=0;
    f(a, b, &count);
    return count;
}

/* =========================
   UTILITY
   ========================= */
Tree newNode(int v) {
    Tree n = (Tree)malloc(sizeof(Nodo));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->val = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void freeTree(Tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

void printPreorder(Tree t) {
    if (!t) return;
    printf("%d ", t->val);
    printPreorder(t->left);
    printPreorder(t->right);
}
int trovaval(int x, Tree albero)
    {
        if(albero==NULL)
            return 0;
        if(x==albero->val)
            return 1;
    return trovaval(x, albero->left) || trovaval(x, albero->right);
    }
void f(Tree a, Tree b, int *count)
    {
        if(a==NULL || b==NULL)
            return;
        if(trovaval(a->val, b))
            (*count)++;
    f(a->left, b, count);
    f(a->right, b, count);
    }
