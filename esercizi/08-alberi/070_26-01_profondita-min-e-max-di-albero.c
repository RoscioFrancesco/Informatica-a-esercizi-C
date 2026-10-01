//
//  main.c
//  profondità min e max di albero
//
//  Created by Francesco Roscio Ricon on 26/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*** STRUTTURE ***/
typedef struct t {
    int val;
    struct t *left, *right;
} Nodo;

typedef Nodo* Tree;

/*** PROTOTIPI ***/
Tree newNode(int v);
void freeTree(Tree t);
void stampaPreordine(Tree t);

//int profonditaMinima(Tree t);
int profonditaMassima(Tree t);

/*** SUPPORTO ***/
Tree newNode(int v) {
    Tree n = (Tree)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->left = n->right = NULL;
    return n;
}

void freeTree(Tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}




int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int profonditaMassima(Tree t) {
    if(t==NULL)
        return 0;
    int sx=profonditaMassima(t->left)+1;
    int dx=profonditaMassima(t->right)+1;
    return max(sx,dx);
}

int min(int a, int b)
    {
        if(a>b)
            return b;
    return a;
    }
int profonditaMinima(Tree t) {
   if(t==NULL)
       return 0;
    if(t->left==NULL && t->right==NULL)
        return 1;
    if(t->left==NULL)
        return 1+profonditaMinima(t->right);
    if(t->right==NULL)
        return 1+profonditaMinima(t->left);
    
    int sx=profonditaMinima(t->left);
    int dx=profonditaMinima(t->right);
    return min(sx, dx)+1;
}
int max(int a, int b);
void stampaPreordine(Tree t);
void stampaConParentesi(Tree t);

int main() {
    /*
            1
          /   \
         2     3
        /       \
       4         5
      /
     6

    Percorsi radice->foglia:
    - 1-2-4-6  (profondità foglia = 3)
    - 1-3-5    (profondità foglia = 2)

    min = 2, max = 3
    */

    Tree t = newNode(1);
    t->left = newNode(2);
    t->right = newNode(3);
    t->left->left = newNode(4);
    t->left->left->left = newNode(6);
    t->right->right = newNode(5);

    printf("Albero (preordine, '.' = NULL):\n");
    stampaConParentesi(t);
    printf("\n\n");

    int minD = profonditaMinima(t);
    int maxD = profonditaMassima(t);

    printf("Profondita minima (radice=0): %d\n", minD);
    printf("Profondita massima (radice=0): %d\n", maxD);

    freeTree(t);
    return 0;
}
void stampaConParentesi(Tree t) {
    if (t == NULL) {
        printf(".");   // nodo nullo
        return;
    }

    printf("(");
    stampaConParentesi(t->left);
    printf(" %d ", t->val);
    stampaConParentesi(t->right);
    printf(")");
}
