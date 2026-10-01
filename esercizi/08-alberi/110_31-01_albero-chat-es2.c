//
//  main.c
//  albero chat es2
//
//  Created by Francesco Roscio Ricon on 31/01/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =======================
   STRUTTURE DATI
   ======================= */

typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;

typedef Node* Tree;

/* =======================
   UTILITY
   ======================= */

Tree newNode(int val, Tree left, Tree right) {
    Tree t = (Tree)malloc(sizeof(Node));
    if (!t) { perror("malloc"); exit(1); }
    t->val = val;
    t->left = left;
    t->right = right;
    return t;
}

/* (opzionale) libero memoria: utile se fai tanti test */
void freeTree(Tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =======================
   ESERCIZIO (DA FARE TU)
   ======================= */

int foglieInterneIncrociate(Tree TA, Tree TB);

/* =======================
   MAIN CON ESEMPI
   ======================= */

int main() {

    Tree TA = newNode(10,
                newNode(7,
                    newNode(3, NULL, NULL),
                    NULL),
                newNode(6,
                    newNode(1, NULL, NULL),
                    NULL)
            );

    Tree TB = newNode(20,
                newNode(3,
                    newNode(7, NULL, NULL),
                    NULL),
                newNode(1,
                    NULL,
                    newNode(6, NULL, NULL))
            );

    printf("Caso VERO (atteso 1): %d\n", foglieInterneIncrociate(TA, TB));
}

int èinterno(int val, Tree albero)
    {
        if(albero==NULL)
            return 0;
        if(val==albero->val)
            {
                if(albero->left==NULL && albero->right==NULL)
                    return 0;
                return 1;
            }
    return èinterno(val, albero->left) || èinterno(val, albero->right);
    }
int f(Tree TA, Tree TB) // - tutte le foglie di TA sono nodi interni di TB
    {
        if(TA==NULL)
            return 1;
        if(TA->left==NULL && TA->right==NULL)
            {
                if(èinterno(TA->val, TB)==0)
                    return 0;
            }
        return f(TA->left, TB) && f(TA->right, TB);
    }
int g(Tree TA, Tree TB)   // - tutte le foglie di TB sono nodi interni di TA
    {
        if(TB==NULL)
            return 1;
//        if(TA==NULL && TB==NULL)
//            return 1;
//        if(TA==NULL || TB==NULL)
//            return 0;
        if(TB->left==NULL && TB->right==NULL)
            {
                if(èinterno(TB->val, TA)==0)
                    return 0;
            }
        return g(TA, TB->left) && g(TA, TB->right);
    }

int foglieInterneIncrociate(Tree TA, Tree TB)
    {
    return f(TA, TB) && g(TA, TB);
    }
