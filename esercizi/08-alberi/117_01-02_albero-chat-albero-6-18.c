//
//  main.c
//  albero chat albero 6 -18
//
//  Created by Francesco Roscio Ricon on 01/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =======================
   STRUTTURE DATI
   ======================= */

typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;

typedef Node* Albero;

/* =======================
   UTILITY: CREA NODO
   ======================= */
int cammino(Albero t, int somma);
static Albero newNode(int v, Albero l, Albero r)
{
    Albero n = (Albero)malloc(sizeof(Node));
    if (!n) return NULL;
    n->val = v;
    n->left = l;
    n->right = r;
    return n;
}

/* =======================
   SOLUZIONE ESERCIZIO
   ======================= */

/*
  Ritorna 1 se esiste un cammino radice->foglia tale che:
  - ogni nodo è strettamente maggiore del padre (cammino strettamente crescente)
  - la somma dei valori sul cammino è pari
*/

int esisteCammino(Albero t)
{
    return cammino(t,0);
}

/* =======================
   STAMPA + FREE (comode)
   ======================= */

void stampaPreorder(Albero t)
{
    if (t == NULL) return;
    printf("%d ", t->val);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

void freeTree(Albero t)
{
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =======================
   MAIN DI TEST
   ======================= */

int main(void)
{
    

    Albero t =
        newNode(5,
            newNode(7,
                newNode(9,
                    newNode(12, NULL, NULL),
                    NULL
                ),
                newNode(8, NULL, NULL)
            ),
            newNode(6,
                NULL,
                newNode(10, NULL, NULL)
            )
        );

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n");

    int ok = esisteCammino(t);

    printf("Esiste cammino radice->foglia crescente con somma pari? %s\n",
           ok ? "SI" : "NO");

    freeTree(t);
    return 0;
}
/*
  Ritorna 1 se esiste un cammino radice->foglia tale che:
  - ogni nodo è strettamente maggiore del padre (cammino strettamente crescente)
  - la somma dei valori sul cammino è pari
*/
int cammino(Albero t, int somma)
    {
        if(t==NULL)
            return 0;
    somma=(somma)+t->val;
    int okL=0;
    int okR=0;
        if(t->left!=NULL && t->left->val>t->val)
            {
                okL=cammino(t->left, somma);
            }
        if(t->left!=NULL && t->left->val>t->val)
            {
            okR=cammino(t->right, somma);
            }
        if(t->left==NULL && t->right==NULL)
        {
            if(somma%2==0)
                return 1;
        }
    return okL || okR;
    }
