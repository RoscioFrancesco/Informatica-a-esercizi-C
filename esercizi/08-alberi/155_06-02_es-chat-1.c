//  Created by Francesco Roscio Ricon on 06/02/26.

#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   STRUTTURE (come da testo)
   ========================================================= */
typedef struct nodeS {
    int v;
    struct nodeS *left, *right;
} node;

typedef node* tree;

/* =========================================================
   PROTOTIPI
   ========================================================= */
int sommaCammino(tree T, int X);   

/* =========================================================
   FUNZIONI DI SUPPORTO (test)
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
int f(tree T, int *somma, int X);
int main(void)
{
    /*
              10
             /  \
            5    3
           / \    \
          2   7    4

        Esempi:
        X = 7  -> 10 + 5 + 7 = 22
        X = 4  -> 10 + 3 + 4 = 17
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

    printf("sommaCammino(T, 7) = %d (atteso 22)\n",
           sommaCammino(T, 7));

    printf("sommaCammino(T, 4) = %d (atteso 17)\n",
           sommaCammino(T, 4));

    liberaAlbero(T);
    return 0;
}

/* =========================================================
   FUNZIONE DELL'ESERCIZIO (DA SVOLGERE)
   ========================================================= */
int sommaCammino(tree T, int X)
    {
    int somma=0;
    (void)f(T, &somma, X);
    return somma;
    }

int f(tree T, int *somma, int X)
    {
        if(T==NULL)
            return 0;
        if(T->v==X)
        {
            *somma=*somma+T->v;
            return 1;
        }
        if(f(T->left, somma, X))
            {
                *somma=(*somma)+T->v;
                return 1;
            }
        if(f(T->right, somma, X))
            {
                *somma=(*somma)+T->v;
                return 1;
            }
        return 0;
    }
