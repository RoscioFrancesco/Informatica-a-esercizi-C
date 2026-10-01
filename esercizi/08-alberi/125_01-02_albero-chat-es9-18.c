//
//  main.c
//  albero chat es9 -18
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

int esisteNodoSpeciale(Tree t);
int sommaalbero(Tree albero);
/* =======================
   MAIN + ESEMPI
   ======================= */

int main() {

    /* ============================================================
       CASO 1: VERO (atteso 1)

                10
               /  \
              3    4
                  / \
                 6   7

       Foglie sotto la radice 10: 3 + 6 + 7 = 16 > 10  => radice speciale
       ============================================================ */
    Tree T1 = newNode(10,
                newNode(3, NULL, NULL),
                newNode(4,
                    newNode(6, NULL, NULL),
                    newNode(7, NULL, NULL))
            );

    /* ============================================================
       CASO 2: FALSO (atteso 0)

                20
               /  \
              3    4
                  / \
                 6   7

       Foglie sotto 20: 3 + 6 + 7 = 16, non > 20 => nessun nodo speciale
       (anche 4: foglie 6+7=13 > 4 -> ATTENZIONE: qui sarebbe speciale!
        quindi per renderlo davvero falso facciamo 4 con una sola foglia 1)
       ------------------------------------------------------------
       Variante davvero FALSA:

                20
               /  \
              3    4
                  /
                 1

       Foglie:
       - sotto 20: 3+1=4  (non >20)
       - sotto 4: 1       (non >4)
       - 3 e 1 sono foglie (non contano come "nodi da verificare" se vuoi)
       ============================================================ */
    Tree T2 = newNode(20,
                newNode(3, NULL, NULL),
                newNode(4,
                    newNode(1, NULL, NULL),
                    NULL)
            );

    /* ============================================================
       CASO 3: VERO (atteso 1) - nodo speciale non è la radice

                50
               /  \
              2    10
                  /  \
                 30   25

       Radice 50: foglie 2+30+25 = 57 > 50 -> in realtà sarebbe speciale.
       Per farla "speciale solo sotto", rendiamo la radice più grande:
                100
               /   \
              2     10
                   /  \
                  30   25

       - 10: foglie 30+25=55 > 10 => speciale
       - 100: foglie 2+30+25=57 non > 100 => non speciale
       ============================================================ */
    Tree T3 = newNode(100,
                newNode(2, NULL, NULL),
                newNode(10,
                    newNode(30, NULL, NULL),
                    newNode(25, NULL, NULL))
            );

    /* ============================================================
       CASO 4: albero con un solo nodo (atteso 0 o 1 a seconda della convenzione)
       Di solito: nessuna foglia discendente "sotto" il nodo (solo se stesso),
       quindi non speciale -> atteso 0.
       ============================================================ */
    Tree T4 = newNode(7, NULL, NULL);

    /* ============================================================
       CASO 5: albero vuoto (atteso 0)
       ============================================================ */
    Tree T5 = NULL;

    /* =======================
       PRINTF
       ======================= */

    printf("Nodo speciale - Caso 1 (atteso 1): %d\n", esisteNodoSpeciale(T1));
    printf("Nodo speciale - Caso 2 (atteso 0): %d\n", esisteNodoSpeciale(T2));
    printf("Nodo speciale - Caso 3 (atteso 1): %d\n", esisteNodoSpeciale(T3));
    printf("Nodo speciale - Caso 4 (atteso 0): %d\n", esisteNodoSpeciale(T4));
    printf("Nodo speciale - Caso 5 (atteso 0): %d\n", esisteNodoSpeciale(T5));

    /* libero memoria */
    freeTree(T1);
    freeTree(T2);
    freeTree(T3);
    freeTree(T4);

    return 0;
}


int sommaalbero(Tree albero)
    {
        if(albero==NULL)
            return 0;
    return albero->val+sommaalbero(albero->right)+sommaalbero(albero->left);
    }
int esisteNodoSpeciale(Tree t)
    {
        if(t==NULL)
            return 0;
        if(sommaalbero(t)>t->val)
            return 1;
    return esisteNodoSpeciale(t->left)||esisteNodoSpeciale(t->right);
    }
