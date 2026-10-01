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
void funz(tree albero, int vettore[], int len, int *segna, int somma);

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
int contafoglie(tree albero)
    {
        if(albero==NULL)
            return 0;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
    return contafoglie(albero->left)+contafoglie(albero->right);
    }
void funz(tree albero, int vettore[], int len, int *segna, int somma)
    {
        if(*segna==len)
            return;
        if(albero==NULL)
            return;
        somma=somma+albero->v;
        if(albero->left==NULL && albero->right==NULL)
            {
                vettore[*segna]=somma;
                (*segna)++;
            }
    funz(albero->left, vettore, len, segna, somma);
    funz(albero->right, vettore, len, segna, somma);
    }

int dueFoglieStessoGrado(tree albero)
    {
        if(albero==NULL)
            return 0;
        int num_caselle=contafoglie(albero);
        int *vettore=malloc(sizeof(int)*num_caselle);
        int segna=0;
        funz(albero, vettore, num_caselle, &segna, 0);
        for(int i=0; i<num_caselle; i++)
            {
                for(int j=i+1; j<num_caselle; j++)
                    {
                        if(vettore[i]==vettore[j])
                        {
                            free(vettore);
                            return 1;
                        }
                    }
            }
        free(vettore);
        return 0;
    }
