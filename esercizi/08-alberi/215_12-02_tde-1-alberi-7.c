//  Created by Francesco Roscio Ricon on 12/02/26.
#include <stdio.h>
#include <stdlib.h>

typedef struct nodeS {
    int val;
    struct nodeS *left, *right;
} node;

typedef node* tree;


int alternaPariDispari(tree T);

tree newNode(int x) {
    tree t = (tree)malloc(sizeof(node));
    if (!t) exit(1);
    t->val = x;
    t->left = t->right = NULL;
    return t;
}

void printInOrder(tree T) {
    if (!T) return;
    printInOrder(T->left);
    printf("%d ", T->val);
    printInOrder(T->right);
}

void freeTree(tree T) {
    if (!T) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* ====== MAIN DI TEST ====== */
int f(tree albero, int prec);
int main(void) {

    /*
        T1: contiene un percorso alternato root->leaf:
            8 (pari) -> 3 (dispari) -> 6 (pari) -> 1 (dispari)

                 8
               /   \
              3     10
             / \
            6   4
           /
          1
    */
    tree T1 = newNode(8);
    T1->left = newNode(3);
    T1->right = newNode(10);
    T1->left->left = newNode(6);
    T1->left->right = newNode(4);
    T1->left->left->left = newNode(1);

    /*
        T2: NON contiene nessun percorso alternato (esempio)
        Qui i cammini rompono l’alternanza subito o più avanti.

                 2
               /   \
              4     6
             /
            8
    */
    tree T2 = newNode(2);
    T2->left = newNode(4);
    T2->right = newNode(6);
    T2->left->left = newNode(8);

    printf("T1 inorder: ");
    printInOrder(T1);
    printf("\nRisultato alternaPariDispari(T1) = %d\n\n", alternaPariDispari(T1));

    printf("T2 inorder: ");
    printInOrder(T2);
    printf("\nRisultato alternaPariDispari(T2) = %d\n", alternaPariDispari(T2));

    freeTree(T1);
    freeTree(T2);

    return 0;
}
int alternaPariDispari(tree T)
    {
        if(T==NULL)
            return 0;
    return f(T, 1) || f(T, -1);
    }
int èpari(int x)
    {
        if(x%2==0)
            return 1;
    return -1;
    }
int f(tree albero, int prec)
    {
        if(albero==NULL)
            return 0;
        if(èpari(albero->val)==prec)
            return 0;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
    int newprec=-prec;
    int sx=0;
    int dx=0;
    if(albero->left!=NULL)
        sx=f(albero->left, newprec);
    if(albero->right!=NULL)
        dx=f(albero->right, newprec);
    return sx||dx;
    }
