//
//  main.c
//  tde albero -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* ======================================================
   STRUTTURA DATI (COME DA TESTO)
   ====================================================== */

typedef struct ET {
    int *dato;
    struct ET *left;
    struct ET *right;
} treeNode;

typedef treeNode *tree;



int alberoConGradoDoppio(tree t);

/* ======================================================
   FUNZIONI DI SUPPORTO (AMMESSE PER TEST)
   ====================================================== */

tree nuovoNodo(int valore, tree left, tree right) {
    treeNode *n = (treeNode *)malloc(sizeof(treeNode));
    n->dato = (int *)malloc(sizeof(int));
    *(n->dato) = valore;
    n->left = left;
    n->right = right;
    return n;
}

void stampaAlberoPreorder(tree t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }
    printf("%d ", *(t->dato));
    stampaAlberoPreorder(t->left);
    stampaAlberoPreorder(t->right);
}

/* ======================================================
   MAIN
   ====================================================== */
int max(int a, int b);
int *vettore(int k);

int main() {

    /*
            Albero di test:

                    5
                  /   \
                 3     7
                / \     \
               2   1     4

        Livelli:
        - livello 0: 5
        - livello 1: 3 + 7
        - livello 2: 2 + 1 + 4
    */

    tree t =
        nuovoNodo(5,
            nuovoNodo(3,
                nuovoNodo(5, NULL, NULL),
                nuovoNodo(1, NULL, NULL)
            ),
            nuovoNodo(7,
                NULL,
                nuovoNodo(4, NULL, NULL)
            )
        );

    printf("=== ALBERO (PREORDER) ===\n");
    stampaAlberoPreorder(t);
    printf("\n");

    printf("\n=== RISULTATO FUNZIONE ===\n");
    printf("alberoConGradoDoppio(t) = %d\n",
           alberoConGradoDoppio(t));

    return 0;
}


int profondità(tree albero)
    {
        if(albero==NULL)
            return 0;
        int sx=profondità(albero->left);
        int dx=profondità(albero->right);
        return max(sx, dx)+1;
    }
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int *vettore(int k)
    {
    int *v=malloc(sizeof(int)*k);
    for(int i=0; i<k; i++)
        v[i]=0;
    return v;
    }

void funz(tree albero, int v[], int livello)
    {
        if(albero==NULL)
            return;
    v[livello]=v[livello]+*albero->dato;
        funz(albero->left, v, livello+1);
        funz(albero->right, v, livello+1);
    }

int alberoConGradoDoppio(tree t)
    {
        if(t==NULL)
            return 0;
        int prof=profondità(t);
        int *v=vettore(prof);
        funz(t, v, 0);
    for(int i=0; i<prof; i++)
        {
            for(int j=i+1; j<prof; j++)
                {
                    if(v[i]==v[j])
                    {
                        free(v);
                        return 1;
                    }
                }
        }
    free(v);
    return 0;
    }
