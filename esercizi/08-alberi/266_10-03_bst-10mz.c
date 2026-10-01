//
//  main.c
//  BST 10mz
//
//  Created by Francesco Roscio Ricon on 10/03/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int val;
    struct nodo *left;
    struct nodo *right;
} Nodo;

typedef Nodo *Tree;

/* prototipo della funzione da svolgere */
int isBST(Tree t);

/* funzione di supporto per creare un nodo */
Tree creaNodo(int x) {
    Tree nuovo = (Tree)malloc(sizeof(Nodo));
    if (nuovo == NULL) {
        printf("Errore di allocazione\n");
        exit(1);
    }
    nuovo->val = x;
    nuovo->left = NULL;
    nuovo->right = NULL;
    return nuovo;
}
void minimo(Tree t, int *min);
int min(Tree t);
int massimo(Tree t);
int ver(Tree t, int min, int max);


int main() {
    Tree root = NULL;

    /* ESEMPIO di albero */
    root = creaNodo(8);
    root->left = creaNodo(4);
    root->right = creaNodo(12);

    root->left->left = creaNodo(2);
    root->left->right = creaNodo(6);

    root->right->left = creaNodo(10);
    root->right->right = creaNodo(14);

    /* chiamata della funzione */
    if (isBST(root)) {
        printf("L'albero e' un BST\n");
    } else {
        printf("L'albero NON e' un BST\n");
    }

    return 0;
}

/* DA SVOLGERE TU */
int isBST(Tree t) {
    int mas=massimo(t);
    int m=min(t);
    return ver(t->left, m-1, t->val) && ver(t->right, t->val, mas+1);
}
//Per ogni nodo dell’albero vale:
//tutti i valori nel sottoalbero sinistro sono minori del valore del nodo
//tutti i valori nel sottoalbero destro sono maggiori del valore del nodo
int ver(Tree t, int min, int max)
    {
        if(t==NULL)
            return 1;
        if(!(t->val<max && t->val>min))
            return 0;
    return ver(t->left, min, t->val) && ver(t->right, t->val, max);
    }
void trovamax(Tree t, int *max)
    {
        if(t==NULL)
            return;
        if(t->val>*max)
            {
                *max=t->val;
            }
    trovamax(t->left, max);
    trovamax(t->right, max);
    }
int massimo(Tree t)
    {
    int max=t->val;
    trovamax(t, &max);
    return max;
    }
void minimo(Tree t, int *min)
    {
        if(t==NULL)
            return;
        if(t->val<*min)
            {
                *min=t->val;
            }
    minimo(t->left, min);
    minimo(t->right, min);
    }
int min(Tree t)
    {
    int m=massimo(t);
    minimo(t, &m);
    return m;
    }
