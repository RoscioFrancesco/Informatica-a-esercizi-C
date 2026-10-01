//
//  main.c
//  tde liste 3  -7
//
//  Created by Francesco Roscio Ricon on 12/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* ====== STRUCT DEL TESTO ====== */
typedef struct EL {
    int dato;
    struct EL *left, *right;
} node;

typedef node *tree;

/* ====== PROTOTIPO FUNZIONE DA FARE (NON LA RISOLVO) ====== */
int verificaDivisibilePerLivello(tree T);

/* ====== SUPPORTO: CREAZIONE / STAMPA / FREE ====== */
tree newNode(int x) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) { printf("malloc fallita\n"); exit(1); }
    n->dato = x;
    n->left = n->right = NULL;
    return n;
}

void freeTree(tree T) {
    if (!T) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

void stampaPreorder(tree T) {
    if (!T) return;
    printf("%d ", T->dato);
    stampaPreorder(T->left);
    stampaPreorder(T->right);
}

/* ====== MAIN DI TEST + PRINTF ====== */
int f(tree albero, int livello);
int main(void) {

    /*
        Esempio 1:
                6
              /   \
             4     9
            /     / \
           3     6   12

        Livelli (radice=livello 1):
        6  @1
        4,9 @2
        3,6,12 @3
    */
    tree T1 = newNode(6);
    T1->left = newNode(4);
    T1->right = newNode(9);
    T1->left->left = newNode(3);
    T1->right->left = newNode(6);
    T1->right->right = newNode(12);

    printf("T1 preorder: ");
    stampaPreorder(T1);
    printf("\n");

    int r1 = f(T1, 1);
    printf("verificaDivisibilePerLivello(T1) = %d\n", r1);

    /*
        Esempio 2 (altro test):
                5
               / \
              2   8
                 /
                3
    */
    tree T2 = newNode(5);
    T2->left = newNode(2);
    T2->right = newNode(8);
    T2->right->left = newNode(3);

    printf("\nT2 preorder: ");
    stampaPreorder(T2);
    printf("\n");

    int r2 = f(T2, 1);
    printf("verificaDivisibilePerLivello(T2) = %d\n", r2);

    /* Edge case */
    tree T3 = NULL;
    printf("\nT3 (NULL): verificaDivisibilePerLivello(T3) = %d\n",
           f(T3, 1));

    freeTree(T1);
    freeTree(T2);

    return 0;
}

/* ====== STUB: NON RISOLVO L'ESERCIZIO ====== */
int verificaDivisibilePerLivello(tree T) {
    (void)T;
    
    return -1; /* valore fittizio */
}
int max(int a,int b)
    {
        if(a>b)
            return a;
    return b;
    }
int depth(tree albero)
    {
        if(albero==NULL)
            return 0;
    int sx=depth(albero->left);
    int dx=depth(albero->right);
    return 1+max(sx, dx);
    }
int f(tree albero, int livello)
    {
        if(albero==NULL)
            return 1;
        if(albero->dato%livello!=0)
            return 0;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
        return f(albero->left,livello+1) && f(albero->right, livello+1);
    }


