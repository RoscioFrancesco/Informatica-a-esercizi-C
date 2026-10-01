//
//  main.c
//  albero chat es8 -18
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

typedef Node* Tree;

/* =======================
   UTILITY
   ======================= */

Tree newNode(int val, Tree left, Tree right) {
    Tree t = (Tree)malloc(sizeof(Node));
    if (!t) { perror("malloc"); exit(1); }
    t->val = val;
    t->left = left;
    t->right = right;
    return t;
}

void freeTree(Tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =======================
   ESERCIZIO (DA FARE TU)
   ======================= */

int foglieInterneAsimmetriche(Tree TA, Tree TB);

/* =======================
   MAIN + ESEMPI
   ======================= */

int main() {

    /* ============================================================
       CASO 1: VERO (atteso 1)

       TA:                     TB:
            10                     20
           /  \                   /  \
          7    6                 3    1
         /    /                 /      \
        3    1                 7        6

       Foglie TA = {3,1}
       → 3 e 1 sono nodi interni in TB

       Foglie TB = {7,6}
       → 7 e 6 NON sono foglie in TA
       ============================================================ */

    Tree TA1 = newNode(10,
                newNode(7,
                    newNode(3, NULL, NULL),
                    NULL),
                newNode(6,
                    newNode(1, NULL, NULL),
                    NULL)
            );

    Tree TB1 = newNode(20,
                newNode(3,
                    newNode(7, NULL, NULL),
                    NULL),
                newNode(1,
                    NULL,
                    newNode(6, NULL, NULL))
            );

    /* ============================================================
       CASO 2: FALSO (atteso 0)
       Fallisce la condizione 2 (foglia comune)

       TC:                     TD:
            5                      8
           / \                    / \
          2   9                  2   4

       Foglie TC = {2,9}
       Foglie TD = {2,4}
       → 2 è foglia in ENTRAMBI ⇒ vietato
       ============================================================ */

    Tree TC = newNode(5,
                newNode(2, NULL, NULL),
                newNode(9, NULL, NULL)
            );

    Tree TD = newNode(8,
                newNode(2, NULL, NULL),
                newNode(4, NULL, NULL)
            );

    /* ============================================================
       CASO 3: FALSO (atteso 0)
       Fallisce la condizione 1

       TE:                     TF:
            7                      9
           / \                    / \
          3   1                  3   4

       Foglie TE = {3,1}
       In TF: 1 NON è nodo interno
       ============================================================ */

    Tree TE = newNode(7,
                newNode(3, NULL, NULL),
                newNode(1, NULL, NULL)
            );

    Tree TF = newNode(9,
                newNode(3,
                    newNode(5, NULL, NULL),
                    NULL),
                newNode(4, NULL, NULL)
            );

    /* =======================
       PRINTF
       ======================= */

    printf("Caso 1 (atteso 1): %d\n",
           foglieInterneAsimmetriche(TA1, TB1));

    printf("Caso 2 (atteso 0): %d\n",
           foglieInterneAsimmetriche(TC, TD));

    printf("Caso 3 (atteso 0): %d\n",
           foglieInterneAsimmetriche(TE, TF));

    /* libero memoria */
    freeTree(TA1); freeTree(TB1);
    freeTree(TC);  freeTree(TD);
    freeTree(TE);  freeTree(TF);

    return 0;
}


int èinterno(int x, Tree albero)
    {
        if(albero==NULL)
            return 0;
        if(x==albero->val)
            {
                if(albero->left==NULL && albero->right==NULL)
                    return 0;
                return 1;
            }
    return èinterno(x, albero->left)||èinterno(x, albero->right);
    }
int èfoglia(int x, Tree albero)
{
    if(albero==NULL)
        return 0;
    if(x==albero->val)
        {
            if(albero->left==NULL && albero->right==NULL)
                return 1;
            return 0;
        }
return èfoglia(x, albero->left)||èfoglia(x, albero->right);
}
int f(Tree TA, Tree TB)
    {
        if(TA==NULL)
            return 1;
        if(TA->left==NULL && TA->right==NULL)
            {
                return èinterno(TA->val, TB);
            }
    return f(TA->left, TB) && f(TA->right, TB);
    }
// 2) nessuna foglia di TB è foglia di TA

int g(Tree TA, Tree TB)
    {
        if(TB==NULL)
            return 1;
        if(TB->left==NULL && TB->right==NULL)
            {
                if(èfoglia(TB->val, TA))
                    return 0;
                return 1;
            }
    return g(TA, TB->left)&& g(TA, TB->right);
    }
int foglieInterneAsimmetriche(Tree TA, Tree TB)
    {
//    if(TA==NULL || TB==NULL)
//        return 1;
    return  f(TA, TB) && g(TA, TB);
    }

