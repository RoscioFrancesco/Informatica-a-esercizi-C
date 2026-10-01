//
//  main.c
//  albero chat es7
//
//  Created by Francesco Roscio Ricon on 31/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <limits.h>

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

int isBST(Tree t);

/* =======================
   MAIN + ESEMPI
   ======================= */

int main() {

    /* ============================================================
       CASO 1: VERO (atteso 1) - BST classico

               8
              / \
             3   10
            / \    \
           1   6    14
              / \   /
             4   7 13
       ============================================================ */
    Tree T1 = newNode(8,
                newNode(3,
                    newNode(1, NULL, NULL),
                    newNode(6,
                        newNode(4, NULL, NULL),
                        newNode(7, NULL, NULL)
                    )
                ),
                newNode(10,
                    NULL,
                    newNode(14,
                        newNode(13, NULL, NULL),
                        NULL
                    )
                )
            );

    /* ============================================================
       CASO 2: FALSO (atteso 0) - errore "profondo" (tipica trappola)

               8
              / \
             3   10
              \
               9

       9 è nel sottoalbero sinistro di 8 ma 9 > 8 => NON BST
       (chi controlla solo i figli immediati sbaglia e lo dà per vero)
       ============================================================ */
    Tree T2 = newNode(8,
                newNode(3,
                    NULL,
                    newNode(9, NULL, NULL)
                ),
                newNode(10, NULL, NULL)
            );

    /* ============================================================
       CASO 3: FALSO (atteso 0) - violazione nel sottoalbero destro

               8
              / \
             3   10
                /
               7

       7 è nel sottoalbero destro di 8 ma 7 < 8 => NON BST
       ============================================================ */
    Tree T3 = newNode(8,
                newNode(3, NULL, NULL),
                newNode(10,
                    newNode(7, NULL, NULL),
                    NULL
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
       CASO 6: DIPENDE dalla tua scelta sui duplicati
       (se BST stretta < e >, allora è FALSO; se permetti = da un lato, cambia)

               5
              / \
             3   5
       ============================================================ */
    Tree T6 = newNode(5,
                newNode(3, NULL, NULL),
                newNode(5, NULL, NULL)
            );

    /* =======================
       PRINTF
       ======================= */

    printf("BST - Caso 1 (atteso 1): %d\n", isBST(T1));
    printf("BST - Caso 2 (atteso 0): %d\n", isBST(T2));
    printf("BST - Caso 3 (atteso 0): %d\n", isBST(T3));
    printf("BST - Caso 4 (atteso 1): %d\n", isBST(T4));
    printf("BST - Caso 5 (atteso 1): %d\n", isBST(T5));
    printf("BST - Caso 6 (duplicati: atteso 0 se BST stretta): %d\n", isBST(T6));

    /* libero memoria */
    freeTree(T1);
    freeTree(T2);
    freeTree(T3);
    freeTree(T4);
    freeTree(T6);

    return 0;
}

int f(Tree albero, int max, int min)
    {
        if(albero==NULL)
            return 1;
    if (albero->val <= min || albero->val >= max)
           return 0;
//        if(albero->left!=NULL &&(albero->left->val>albero->val || albero->left->val>max))
//            return 0;
//        if(albero->right!=NULL &&(albero->right->val<albero->val || albero->right->val<min))
//            return 0;
    return f(albero->left, albero->val, min) && f(albero->right, max, albero->val);
    }
int isBST(Tree t)
    {
    if(t==NULL)
        return 1;
    return f(t, INT_MAX, INT_MIN);
    }
/* ============================================================
   CASO 1: VERO (atteso 1) - BST classico

           8
          / \
         3   10
        / \    \
       1   6    14
          / \   /
         4   7 13
   ============================================================ */
