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
int dueFoglieStessoGrado(tree T);   

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
int f(tree albero, int val_somma, int *hasprev, int *prima_somma);
int main(void)
{
    /*
            Esempio 1 (atteso: 1)

                     5
                   /   \
                  2     3
                 /       \
                7         6

        Gradi foglie:
        5+2+7 = 14
        5+3+6 = 14   -> uguali
    */

    tree T1 = newNode(5,
                newNode(2,
                    newNode(7, NULL, NULL),
                    NULL),
                newNode(3,
                    NULL,
                    newNode(6, NULL, NULL)));

    /*
            Esempio 2 (atteso: 0)

                     1
                   /   \
                  2     3
                 / \     \
                4   5     6

        Gradi foglie:
        1+2+4 = 7
        1+2+5 = 8
        1+3+6 = 10   -> tutti diversi
    */

    tree T2 = newNode(1,
                newNode(2,
                    newNode(4, NULL, NULL),
                    newNode(5, NULL, NULL)),
                newNode(3,
                    NULL,
                    newNode(6, NULL, NULL)));

    printf("Albero T1 (preorder): ");
    stampaPreorder(T1);
    printf("\n");
    printf("dueFoglieStessoGrado(T1) = %d (atteso 1)\n\n",
           dueFoglieStessoGrado(T1));

    printf("Albero T2 (preorder): ");
    stampaPreorder(T2);
    printf("\n");
    printf("dueFoglieStessoGrado(T2) = %d (atteso 0)\n\n",
           dueFoglieStessoGrado(T2));

    liberaAlbero(T1);
    liberaAlbero(T2);

    return 0;
}

/* =========================================================
   FUNZIONE DELL'ESERCIZIO (DA SVOLGERE)
   ========================================================= */
int f(tree albero, int val_somma, int *hasprev, int *prima_somma)
    {
        if(albero==NULL)
            return 1;
        val_somma=val_somma+albero->v;
        if(albero->left==NULL && albero->right==NULL)
            {
                if(*hasprev==0)
                {
                    *prima_somma=val_somma;
                    *hasprev=1;
                }
                else
                {
                    if(val_somma==*prima_somma)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
    return f(albero->left, val_somma, hasprev, prima_somma)&&f(albero->right, val_somma, hasprev, prima_somma);
    }
int dueFoglieStessoGrado(tree T)
    {
    int hasprev=0;
    int *rpimasomma=0;
    return f(T, 0, &hasprev, &rpimasomma);
    }
