//
//  main.c
//  albero chat es1 alberi -18
//
//  Created by Francesco Roscio Ricon on 01/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

int quasiBSTalternato(Tree t);
int f(Tree t, int livello, int max, int min);
int quasiBSTalternato_f(Tree t, int livello);
/* =======================
   MAIN + ESEMPI
   ======================= */

int main() {

    /* ============================================================
       CASO 1: VERO (atteso 1) - piccolo e "normale"

                 10              livello 0: BST  (sx < 10 < dx)
                /  \
               5    20           livello 1: invertita
              / \   / \
            7  3  30  15         livello 2: BST

       Controlli chiave:
       - livello 0 (BST): 5 < 10 < 20 OK
       - livello 1 invertito:
           nodo 5:  left=7 > 5, right=3 < 5  OK
           nodo 20: left=30 > 20, right=15 < 20 OK
       - livello 2 (BST):
           7 è foglia ok, 3 foglia ok, 30 foglia ok, 15 foglia ok
       ============================================================ */
    Tree T1 = newNode(10,
                newNode(5,
                    newNode(7, NULL, NULL),
                    newNode(3, NULL, NULL)),
                newNode(20,
                    newNode(30, NULL, NULL),
                    newNode(15, NULL, NULL))
            );

    /* ============================================================
       CASO 2: FALSO (atteso 0) - errore a livello 1 (invertito rotto)

                 10
                /  \
               5    20
              / \
             4   3

       livello 1 su nodo 5 dovrebbe essere: left > 5 e right < 5
       ma left=4 NON è > 5 => fallisce
       ============================================================ */
    Tree T2 = newNode(10,
                newNode(5,
                    newNode(4, NULL, NULL),
                    newNode(3, NULL, NULL)),
                newNode(20, NULL, NULL)
            );

    /* ============================================================
       CASO 3: FALSO (atteso 0) - trappola "profonda" (vincolo non locale)
       Questo caso serve per beccare chi controlla solo i figli immediati.

                 10
                /  \
               5    20
              / \
             7   3
                /
               999

       A livello 2 (BST): nel sottoalbero destro di 5 (che vale 3),
       il valore 999 è nel suo sottoalbero sinistro, quindi deve essere < 3 (BST),
       ma 999 >> 3 => fallisce in profondità.
       ============================================================ */
    Tree T3 = newNode(10,
                newNode(5,
                    newNode(7, NULL, NULL),
                    newNode(3,
                        newNode(999, NULL, NULL),
                        NULL)),
                newNode(20, NULL, NULL)
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
       CASO 6: FALSO (atteso 0) - errore a livello 0 (BST rotto)

                 10
                /  \
              50    20

       livello 0 richiede 50 < 10, ma è falso
       ============================================================ */
    Tree T6 = newNode(10,
                newNode(50, NULL, NULL),
                newNode(20, NULL, NULL)
            );

    /* =======================
       PRINTF
       ======================= */

    printf("Quasi-BST alternato - Caso 1 (atteso 1): %d\n", quasiBSTalternato(T1));
    printf("Quasi-BST alternato - Caso 2 (atteso 0): %d\n", quasiBSTalternato(T2));
    printf("Quasi-BST alternato - Caso 3 (atteso 0): %d\n", quasiBSTalternato(T3));
    printf("Quasi-BST alternato - Caso 4 (atteso 1): %d\n", quasiBSTalternato(T4));
    printf("Quasi-BST alternato - Caso 5 (atteso 1): %d\n", quasiBSTalternato(T5));
    printf("Quasi-BST alternato - Caso 6 (atteso 0): %d\n", quasiBSTalternato(T6));

    /* libero memoria */
    freeTree(T1);
    freeTree(T2);
    freeTree(T3);
    freeTree(T4);
    freeTree(T6);

    return 0;
}

int f(Tree t, int livello, int max, int min)
    {
            if(livello%2==0)
                {
                    if(t==NULL)
                        return 1;
                    if(t->val<=min || t->val>=max)
                        return 0;
                return f(t->left,livello+1, t->val, min) && f(t->right,livello+1, max, t->val);

                }
            else
                {
                    if(t==NULL)
                        return 1;
                    if(t->val<=min || t->val>=max)
                        return 0;
                    return f(t->left, livello+1, max, t->val) && f(t->right, livello+1,t->val, min) ;
                }
    }
int quasiBSTalternato(Tree t)
    {
    return f(t, 0, INT_MAX, INT_MIN);
    }
