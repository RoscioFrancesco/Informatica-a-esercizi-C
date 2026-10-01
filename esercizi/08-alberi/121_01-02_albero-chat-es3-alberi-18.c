//
//  main.c
//  albero chat es3 alberi -18
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

int simmetricoSelettivo(Tree t);

/* =======================
   MAIN + ESEMPI
   ======================= */

int main() {

    /* ============================================================
       CASO 1: VERO (atteso 1)
       Dopo aver ignorato i dispari, rimane una struttura speculare.

                 9
                / \
               2   2
              /     \
             7       7

       Ignorando i dispari (9 e 7), restano solo i due "2"
       come figli speculari della radice "vuota" (ignorata).
       ============================================================ */
    Tree T1 = newNode(9,
                newNode(2,
                    newNode(7, NULL, NULL),
                    NULL),
                newNode(2,
                    NULL,
                    newNode(7, NULL, NULL))
            );

    /* ============================================================
       CASO 2: FALSO (atteso 0)
       Ignorando i dispari, resta una struttura NON speculare.

                 9
                / \
               2   2
              /    /
             8    8

       Ignorando 9, restano:
           2 con figlio sinistro 8
           2 con figlio sinistro 8
       NON sono speculari (dovrebbe essere sx vs dx).
       ============================================================ */
    Tree T2 = newNode(9,
                newNode(2,
                    newNode(8, NULL, NULL),
                    NULL),
                newNode(2,
                    newNode(8, NULL, NULL),
                    NULL)
            );

    /* ============================================================
       CASO 3: VERO (atteso 1)
       Molti dispari “in mezzo” da saltare.

                    11
                   /  \
                  5    7
                 /      \
                2        2
                 \      /
                  9    9
                 /      \
                4        4

       Ignorando i dispari (11,5,7,9,9), restano due catene speculari:
         sinistra: 2 -> (figlio sinistro 4)  [per via dei salti]
         destra:   2 -> (figlio destro 4)
       ============================================================ */
    Tree T3 = newNode(11,
                newNode(5,
                    newNode(2,
                        NULL,
                        newNode(9,
                            newNode(4, NULL, NULL),
                            NULL)),
                    NULL),
                newNode(7,
                    NULL,
                    newNode(2,
                        newNode(9,
                            NULL,
                            newNode(4, NULL, NULL)),
                        NULL))
            );

    /* ============================================================
       CASO 4: FALSO (atteso 0)
       Dopo i salti, un lato ha un pari in più.

                 1
                / \
               2   3
              /
             4

       Ignorando dispari (1 e 3), rimane:
       sinistra: 2 con figlio 4
       destra:   NULL
       quindi NON simmetrico.
       ============================================================ */
    Tree T4 = newNode(1,
                newNode(2,
                    newNode(4, NULL, NULL),
                    NULL),
                newNode(3, NULL, NULL)
            );

    /* ============================================================
       CASO 5: VERO (atteso 1)
       Tutti dispari -> ignorandoli resta "vuoto" -> simmetrico.

                 7
                / \
               5   9
       ============================================================ */
    Tree T5 = newNode(7,
                newNode(5, NULL, NULL),
                newNode(9, NULL, NULL)
            );

    /* ============================================================
       CASO 6: VERO (atteso 1)
       Albero vuoto.
       ============================================================ */
    Tree T6 = NULL;

    /* =======================
       PRINTF
       ======================= */

    printf("Simmetrico selettivo - Caso 1 (atteso 1): %d\n", simmetricoSelettivo(T1));
    printf("Simmetrico selettivo - Caso 2 (atteso 0): %d\n", simmetricoSelettivo(T2));
    printf("Simmetrico selettivo - Caso 3 (atteso 1): %d\n", simmetricoSelettivo(T3));
    printf("Simmetrico selettivo - Caso 4 (atteso 0): %d\n", simmetricoSelettivo(T4));
    printf("Simmetrico selettivo - Caso 5 (atteso 1): %d\n", simmetricoSelettivo(T5));
    printf("Simmetrico selettivo - Caso 6 (atteso 1): %d\n", simmetricoSelettivo(T6));

    /* libero memoria */
    freeTree(T1);
    freeTree(T2);
    freeTree(T3);
    freeTree(T4);
    freeTree(T5);

    return 0;
}

int f(Tree albero1, int livello, Tree albero2)
    {
        if(albero1==NULL && albero2==NULL)
            return 1;
        if(albero1==NULL || albero2==NULL)
            return 0;
        if(albero1->val%2==0 && albero2->val%2==0)
            {
                if(albero1->left==NULL && albero2->right!=NULL)
                    return 0;
                if(albero1->right==NULL && albero2->left!=NULL)
                    return 0;
            }
    return f(albero1->left, livello+1, albero2->right) && f(albero1->right, livello+1, albero2->left);
    }
int simmetricoSelettivo(Tree t)
    {
        if(t==NULL)
            return 1;
        if(t->left==NULL && t->right==NULL)
            return 1;
    return f(t->left, 1, t->right);
    }
