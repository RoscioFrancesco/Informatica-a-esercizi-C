//
//  main.c
//  es chat 2
//
//  Created by Francesco Roscio Ricon on 06/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   STRUTTURE
   ========================================================= */
typedef struct nodeS {
    int v;
    struct nodeS *left, *right;
} node;

typedef node* tree;

/* =========================================================
   PROTOTIPI
   ========================================================= */
int profonditaNodo(tree T, int X);   

/* =========================================================
   FUNZIONI DI SUPPORTO (per test)
   ========================================================= */
tree newNode(int v, tree left, tree right)
{
    tree n = (tree)malloc(sizeof(node));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->v = v;
    n->left = left;
    n->right = right;
    return n;
}

void stampaPreorder(tree T)
{
    if (T == NULL) {
        printf("NULL ");
        return;
    }
    printf("%d ", T->v);
    stampaPreorder(T->left);
    stampaPreorder(T->right);
}

void liberaAlbero(tree T)
{
    if (T == NULL) return;
    liberaAlbero(T->left);
    liberaAlbero(T->right);
    free(T);
}

/* =========================================================
   MAIN DI TEST
   ========================================================= */
int main(void)
{
    /*
                10
               /  \
              5    3
             / \    \
            2   7    4

        Profondità:
        10 -> 0
        5  -> 1
        7  -> 2
        4  -> 2
    */

    tree T = newNode(10,
                newNode(5,
                    newNode(2, NULL, NULL),
                    newNode(7, NULL, NULL)),
                newNode(3,
                    NULL,
                    newNode(4, NULL, NULL)));

    printf("Albero (preorder): ");
    stampaPreorder(T);
    printf("\n\n");

    printf("profonditaNodo(T, 10) = %d (atteso 0)\n",
           profonditaNodo(T, 10));

    printf("profonditaNodo(T, 7) = %d (atteso 2)\n",
           profonditaNodo(T, 7));

    printf("profonditaNodo(T, 4) = %d (atteso 2)\n",
           profonditaNodo(T, 4));

    printf("profonditaNodo(T, 99) = %d (atteso -1)\n",
           profonditaNodo(T, 99));

    liberaAlbero(T);
    return 0;
}

/* =========================================================
   FUNZIONE DELL'ESERCIZIO (DA SVOLGERE)
   ========================================================= */
int f(tree albero ,int X, int *profondità, int livello)
    {
        if(albero==NULL)
            return 0;
        if(albero->v==X)
            {
                *profondità=livello;
                return 1; // uso il valore di return come flag per dire se + stato trovato oppure no
            }
    return f(albero->left, X, profondità, livello+1) || f(albero->right, X, profondità, livello+1);
    }
int profonditaNodo(tree T, int X)
    {
    int profondità=0;
    int ris=f(T, X, &profondità, 0);
    if(ris==0)
        return -1;
    return profondità;
    }
