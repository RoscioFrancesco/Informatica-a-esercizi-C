//
//  main.c
//  ppt pag 52 -7
//
//  Created by Francesco Roscio Ricon on 12/02/26.
//
//
#include <stdio.h>
#include <stdlib.h>

/* ====== TIPO ALBERO ====== */
typedef struct node {
    int v;
    struct node *left, *right;
} *tree;

/* ====== PROTOTIPO ====== */
int esisteEco(tree T, int K);

/* ====== CREAZIONE NODO ====== */
tree newNode(int v, tree L, tree R) {
    tree t = (tree)malloc(sizeof(*t));
    if (t == NULL) {
        printf("Errore malloc\n");
        exit(1);
    }
    t->v = v;
    t->left = L;
    t->right = R;
    return t;
}

/* ====== LIBERA ALBERO ====== */
void freeTree(tree T) {
    if (T == NULL)
        return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* =========================================================
   searchFrom:
   prev1 = lato precedente (-1 none, 0 left, 1 right)
   prev2 = lato due passi fa
   lastIgnored = 1 se il nodo precedente è stato ignorato
   ========================================================= */

int searchFrom(tree cur, int K, int sum,
               int prev1, int prev2, int lastIgnored) {
    if(cur==NULL)
        return 0;
    if(cur->left==NULL && cur->right==NULL)
    {
        int sommafinale=sum+cur->v;
        return (sommafinale%K==0);
    }
    if(cur->left!=NULL)
        {
            int chosen=0;
            int ignored=0;
            if(prev2!=-1)
                {
                    if(chosen==prev2)
                        ignored=1;
                }
            int add=0;
            if(!(lastIgnored==1 && ignored==1))
                {
                    if(ignored==1)
                        add=0;
                    else
                        add=cur->v;
                }
            if(searchFrom(cur->left, K, add+sum, chosen, prev1, ignored))
                return 1;
        }
    if(cur->right!=NULL)
        {
            int chosen=1;
            int ignored=0;
            if(prev2!=-1)
                {
                    if(chosen==prev2)
                        ignored=1;
                }
            int add=0;
            if(!(lastIgnored==1 && ignored==1))
                {
                    if(ignored==1)
                        add=0;
                    else
                        add=cur->v;
                }
            if(searchFrom(cur->right, K, sum+add, chosen, prev1, ignored))
                return 1;
        }
    return 0;
}

/* Può partire da QUALSIASI nodo */
int existsStartAnywhere(tree T, int K) {

    if (T == NULL)
        return 0;

    if (searchFrom(T, K, 0, -1, -1, 0) == 1)
        return 1;

    if (existsStartAnywhere(T->left, K) == 1)
        return 1;

    if (existsStartAnywhere(T->right, K) == 1)
        return 1;

    return 0;
}

int esisteEco(tree T, int K) {

    if (T == NULL)
        return 0;
    if (K == 0)
        return 0;
    return existsStartAnywhere(T, K);
}

/* ====== MAIN DI TEST ====== */
int main() {

    /* Albero:
             10
            /  \
           4    7
          / \    \
         3   6    2
    */

    tree n3 = newNode(3, NULL, NULL);
    tree n6 = newNode(6, NULL, NULL);
    tree n2 = newNode(2, NULL, NULL);
    tree n4 = newNode(4, n3, n6);
    tree n7 = newNode(7, NULL, n2);
    tree T  = newNode(10, n4, n7);

    int Kvals[] = {2, 3, 5, 7, 10};
    int i;

    for (i = 0; i < 5; i++) {
        int K = Kvals[i];
        printf("K = %d -> %d\n", K, esisteEco(T, K));
    }

    freeTree(T);

    return 0;
}
