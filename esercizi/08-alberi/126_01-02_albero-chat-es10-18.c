//
//  main.c
//  albero chat es10 -18
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
/*
   Un albero è "quasi-simmetrico" se i suoi due sottoalberi (sinistro e destro)
   hanno la STESSA STRUTTURA in modo speculare.
   I valori dei nodi possono essere diversi: conta SOLO la forma.
*/

/* =======================
   MAIN + ESEMPI
   ======================= */
int quasiSimmetrico(Tree albero1);

int main() {

    /* ============================================================
       CASO 1: VERO (atteso 1) - stessa struttura speculare, valori diversi

                10
               /  \
              1    99
             /      \
            7        3

       Struttura:
       - a sinistra: nodo con solo figlio sinistro
       - a destra:   nodo con solo figlio destro
       => speculari
       ============================================================ */
    Tree T1 = newNode(10,
                newNode(1,
                    newNode(7, NULL, NULL),
                    NULL),
                newNode(99,
                    NULL,
                    newNode(3, NULL, NULL))
            );

    /* ============================================================
       CASO 2: FALSO (atteso 0) - struttura non speculare

                10
               /  \
              1    2
             /    /
            7    3

       Entrambi hanno figlio sinistro: NON sono speculari.
       ============================================================ */
    Tree T2 = newNode(10,
                newNode(1,
                    newNode(7, NULL, NULL),
                    NULL),
                newNode(2,
                    newNode(3, NULL, NULL),
                    NULL)
            );

    /* ============================================================
       CASO 3: VERO (atteso 1) - struttura perfettamente speculare (più profonda)

                    0
                  /   \
                 5     9
                / \   / \
               1  2  3   4
                    \   /
                     8 7

       Nota: valori a caso, conta solo la forma.
       ============================================================ */
    Tree T3 = newNode(0,
                newNode(5,
                    newNode(1, NULL, NULL),
                    newNode(2,
                        NULL,
                        newNode(8, NULL, NULL))
                ),
                newNode(9,
                    newNode(3,
                        newNode(7, NULL, NULL),
                        NULL),
                    newNode(4, NULL, NULL)
                )
            );

    /* ============================================================
       CASO 4: VERO (atteso 1) - albero con un solo nodo
       ============================================================ */
    Tree T4 = newNode(42, NULL, NULL);

    /* ============================================================
       CASO 5: VERO (atteso 1) - albero vuoto
       ============================================================ */
    Tree T5 = NULL;

    /* ============================================================
       CASO 6: FALSO (atteso 0) - stesso numero di nodi ma forma diversa

                1
               / \
              2   3
               \   \
                4   5
       Sinistra: nodo con figlio destro
       Destra:   nodo con figlio destro (dovrebbe essere sinistro per specchio)
       ============================================================ */
    Tree T6 = newNode(1,
                newNode(2,
                    NULL,
                    newNode(4, NULL, NULL)),
                newNode(3,
                    NULL,
                    newNode(5, NULL, NULL))
            );

    /* =======================
       PRINTF
       ======================= */

    printf("Quasi-simmetrico - Caso 1 (atteso 1): %d\n", quasiSimmetrico(T1));
    printf("Quasi-simmetrico - Caso 2 (atteso 0): %d\n", quasiSimmetrico(T2));
    printf("Quasi-simmetrico - Caso 3 (atteso 1): %d\n", quasiSimmetrico(T3));
    printf("Quasi-simmetrico - Caso 4 (atteso 1): %d\n", quasiSimmetrico(T4));
    printf("Quasi-simmetrico - Caso 5 (atteso 1): %d\n", quasiSimmetrico(T5));
    printf("Quasi-simmetrico - Caso 6 (atteso 0): %d\n", quasiSimmetrico(T6));

    /* libero memoria */
    freeTree(T1);
    freeTree(T2);
    freeTree(T3);
    freeTree(T4);
    freeTree(T6);

    return 0;
}
/*
   Un albero è "quasi-simmetrico" se i suoi due sottoalberi (sinistro e destro)
   hanno la STESSA STRUTTURA in modo speculare.
   I valori dei nodi possono essere diversi: conta SOLO la forma.
*/
int f(Tree albero1, Tree albero2)
    {
        if(albero1==NULL && albero2==NULL)
            return 1;
        if(albero1==NULL || albero2==NULL)
            return 0;
    
//        if(albero1->left==NULL && albero2->left!=NULL)
//            return 0;
//        if(albero1->left!=NULL && albero2->right==NULL)
//            return 0;
    return f(albero1->left, albero2->right)&&f(albero1->right, albero2->left);
    }
int quasiSimmetrico(Tree albero1)
    {
    if(albero1==NULL)
        return 1;
    return f(albero1->left, albero1->right);
    }
