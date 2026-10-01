//
//  main.c
//  albero chat es4
//
//  Created by Francesco Roscio Ricon on 31/01/26.
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
   Un albero è detto "ridotto" se OGNI nodo interno
   ha almeno un discendente (non necessariamente figlio diretto)
   il cui valore è divisibile per il valore del nodo.

   Le foglie non impongono vincoli.
   Nota: gestire bene il caso val==0 (se può comparire).
*/
int ridotto(Tree t);

/* =======================
   MAIN + ESEMPI NORMALI
   ======================= */

int main() {

    /* ============================================================
       CASO 1: VERO (atteso 1)

                6
               / \
              5   9
             /   /
           10   18

       - Nodo 6 ha discendenti 18 (18%6==0)
       - Nodo 5 ha discendente 10 (10%5==0)
       - Nodo 9 ha discendente 18 (18%9==0)
       Foglie: 10 e 18 (nessun vincolo)
       ============================================================ */

    Tree T1 = newNode(6,
                newNode(5,
                    newNode(10, NULL, NULL),
                    NULL),
                newNode(9,
                    newNode(18, NULL, NULL),
                    NULL)
            );

    /* ============================================================
       CASO 2: FALSO (atteso 0)

                6
               / \
              5   9
                 /
                10

       - Nodo 6: discendente 10 (10%6!=0) e 9 (9%6!=0) -> nessun discendente multiplo di 6
       Quindi NON ridotto.
       ============================================================ */

    Tree T2 = newNode(6,
                newNode(5, NULL, NULL),
                newNode(9,
                    newNode(10, NULL, NULL),
                    NULL)
            );

    /* ============================================================
       CASO 3: VERO (atteso 1) - albero con una sola radice
              42
       Nessun nodo interno -> vacuamente vero.
       ============================================================ */
    Tree T3 = newNode(42, NULL, NULL);

    /* ============================================================
       CASO 4: FALSO (atteso 0) - nodo interno senza discendenti validi

                4
               /
              3
             /
            5

       Nodo 4 ha discendenti {3,5}: 3%4!=0, 5%4!=0 -> fallisce.
       ============================================================ */
    Tree T4 = newNode(4,
                newNode(3,
                    newNode(5, NULL, NULL),
                    NULL),
                NULL
            );

    /* ============================================================
       CASO 5: (opzionale) VUOTO
       Per molti esercizi: albero NULL -> vero (nessun vincolo).
       ============================================================ */
    Tree T5 = NULL;

    /* =======================
       PRINTF
       ======================= */

    printf("Ridotto - Caso 1 (atteso 1): %d\n", ridotto(T1));
    printf("Ridotto - Caso 2 (atteso 0): %d\n", ridotto(T2));
    printf("Ridotto - Caso 3 (atteso 1): %d\n", ridotto(T3));
    printf("Ridotto - Caso 4 (atteso 0): %d\n", ridotto(T4));
    printf("Ridotto - Caso 5 (atteso 1): %d\n", ridotto(T5));

    /* libero memoria */
    freeTree(T1);
    freeTree(T2);
    freeTree(T3);
    freeTree(T4);

    return 0;
}
/*
   Un albero è detto "ridotto" se OGNI nodo interno
   ha almeno un discendente (non necessariamente figlio diretto)
   il cui valore è divisibile per il valore del nodo.

   Le foglie non impongono vincoli.
   Nota: gestire bene il caso val==0 (se può comparire).
*/
int ridottofromhere(int K, Tree albero)
    {
        if(albero==NULL)
            return 0;
        if(albero->val%K==0)
            return 1;
    return ridottofromhere(K, albero->left) || ridottofromhere(K, albero->right);
    }
int ridotto(Tree albero)
    {
        if(albero==NULL)
            return 1;
        if (albero->left==NULL && albero->right==NULL)
            return 1;
    return (ridottofromhere(albero->val, albero->left) || ridottofromhere(albero->val, albero->right)) && ridotto(albero->right) && ridotto(albero->left);
    }
