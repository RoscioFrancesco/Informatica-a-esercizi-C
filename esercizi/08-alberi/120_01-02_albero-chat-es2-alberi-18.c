//
//  main.c
//  albero chat es2 alberi -18
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

int dueFoglieSpeciali(Tree t);
void speciale(Tree t, int somma, int *count, Tree root);
/* =======================
   MAIN + ESEMPI
   ======================= */

int main() {

    /* ============================================================
       CASO 1: VERO (atteso 1)
       Due foglie speciali

                 10
                /  \
               5    3
              /      \
             5        9

       Cammini:
       - 10+5+5 = 20  → 20 % 5 == 0  (foglia speciale)
       - 10+3+9 = 22  → 22 % 9 != 0  (non speciale)

       Per renderlo VERO, modifichiamo leggermente:
                 10
                /  \
               5    3
              /      \
             5        11

       - 10+3+11 = 24 → 24 % 11 != 0 (ancora no)
       Quindi costruiamo un caso DAVVERO vero sotto.
       ============================================================ */

    Tree T1 = newNode(10,
                newNode(5,
                    newNode(5, NULL, NULL),
                    NULL),
                newNode(3,
                    NULL,
                    newNode(10, NULL, NULL))
            );
    /*
       Cammini:
       - 10+5+5 = 20 → 20 % 5 == 0
       - 10+3+10 = 23 → 23 % 10 != 0
       → una sola foglia speciale (quindi NON vero per l’esercizio)
       Questo serve per testare che NON basta una sola foglia.
    */

    /* ============================================================
       CASO 2: VERO (atteso 1)
       Esattamente due foglie speciali

                 6
                / \
               3   4
              /     \
             3       5

       Cammini:
       - 6+3+3 = 12 → 12 % 3 == 0
       - 6+4+5 = 15 → 15 % 5 == 0
       ============================================================ */

    Tree T2 = newNode(6,
                newNode(3,
                    newNode(3, NULL, NULL),
                    NULL),
                newNode(4,
                    NULL,
                    newNode(5, NULL, NULL))
            );

    /* ============================================================
       CASO 3: FALSO (atteso 0)
       Nessuna foglia speciale

                 10
                /  \
               4    6
              /      \
             3        7

       Cammini:
       - 10+4+3 = 17 → 17 % 3 != 0
       - 10+6+7 = 23 → 23 % 7 != 0
       ============================================================ */

    Tree T3 = newNode(10,
                newNode(4,
                    newNode(3, NULL, NULL),
                    NULL),
                newNode(6,
                    NULL,
                    newNode(7, NULL, NULL))
            );

    /* ============================================================
       CASO 4: FALSO (atteso 0)
       Una sola foglia (anche se speciale)

                 8
                  \
                   4

       Cammino: 8+4 = 12 → 12 % 4 == 0
       Ma c’è SOLO una foglia → deve tornare 0
       ============================================================ */

    Tree T4 = newNode(8,
                NULL,
                newNode(4, NULL, NULL)
            );

    /* ============================================================
       CASO 5: FALSO (atteso 0)
       Albero con una sola radice
       ============================================================ */

    Tree T5 = newNode(7, NULL, NULL);

    /* ============================================================
       CASO 6: FALSO (atteso 0)
       Albero vuoto
       ============================================================ */

    Tree T6 = NULL;

    /* =======================
       PRINTF
       ======================= */

    printf("Foglie speciali - Caso 1 (atteso 0): %d\n", dueFoglieSpeciali(T1));
    printf("Foglie speciali - Caso 2 (atteso 1): %d\n", dueFoglieSpeciali(T2));
    printf("Foglie speciali - Caso 3 (atteso 0): %d\n", dueFoglieSpeciali(T3));
    printf("Foglie speciali - Caso 4 (atteso 0): %d\n", dueFoglieSpeciali(T4));
    printf("Foglie speciali - Caso 5 (atteso 0): %d\n", dueFoglieSpeciali(T5));
    printf("Foglie speciali - Caso 6 (atteso 0): %d\n", dueFoglieSpeciali(T6));

    /* libero memoria */
    freeTree(T1);
    freeTree(T2);
    freeTree(T3);
    freeTree(T4);
    freeTree(T5);

    return 0;
}



void speciale(Tree t, int somma, int *count, Tree root)
    {
        if(t==NULL)
            return;
    somma=somma+t->val;
        if(somma%t->val==0 && somma!=0 && root!=t && t->left==NULL && t->right==NULL)
            ( *count)++;
        speciale(t->left, somma, count, root);
        speciale(t->right, somma, count, root);
    }
int dueFoglieSpeciali(Tree t)
    {
        int somma=0;
    int count=0;
    speciale(t, somma, &count, t);
    if(count>=2)
        return 1;
    return 0;
    }
