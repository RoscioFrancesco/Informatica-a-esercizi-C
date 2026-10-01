//
//  main.c
//  es 2 alberi campi -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} Node;

typedef Node * tree;

int isobato(tree t);

tree nuovoNodo(int valore) {
    tree n = (tree)malloc(sizeof(Node));
    n->dato = valore;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/* =========================
   MAIN
   ========================= */
int d_min(tree albero);
int d_max(tree albero);
int max(int a, int b);
int min(int a, int b);
int main() {
    tree T;
    int risultato;

    /* Costruzione albero di esempio */
    T = nuovoNodo(1);
    T->left = nuovoNodo(2);
    T->right = nuovoNodo(3);
    T->left->left = nuovoNodo(4);
    T->right->right = nuovoNodo(5);

    
    risultato = isobato(T);

    /* Stampa risultato */
    if (risultato == 1)
        printf("L'albero e' isobato\n");
    else
        printf("L'albero NON e' isobato\n");

    return 0;
}
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int d_max(tree albero)
    {
        if(albero==NULL)
            return 0;
    int sx=d_max(albero->left);
    int dx=d_max(albero->right);
    return 1+max(sx, dx);
    }
int min(int a, int b)
    {
        if(a<b)
            return a;
    return b;
    }
int d_min(tree albero)
    {
        if(albero==NULL)
            return 0;
    int sx=0;
    int dx=0;
//    if(albero->left==NULL && albero->right==NULL)
//        return 1;
    if(albero->left!=NULL)
        sx=d_min(albero->left)+1;
    if(albero->right!=NULL)
        dx=d_min(albero->right)+1;
    return min(sx, dx)+1;
    }
int isobato(tree t)
    {
    return d_max(t)==d_min(t);
    }
