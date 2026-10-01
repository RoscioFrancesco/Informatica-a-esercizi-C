//
//  main.c
//  albero chat es4 alberi -18
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

int tuttiNodiDominanti(Tree t);
int contanodi(Tree t);
int wrapper(Tree t);
void containterni(Tree t, int *count);
int tuttiNodiDominanti(Tree t);
int contanodi(Tree t);
void èdominante(Tree t, int *count);

/* =======================
   MAIN + ESEMPI
   ======================= */

int main() {

    /* ============================================================
       CASO 1: VERO (atteso 1)
       Tutti i nodi interni sono dominanti

                 10
                /  \
               5    3
              / \
             2   4

       - Nodo 10: sx=3 nodi, dx=1 nodo → OK
       - Nodo 5:  sx=1 nodo,  dx=1 nodo → NON strettamente maggiore
         → quindi questo caso in realtà è FALSO.
       Correggiamo per avere un caso VERO sotto.
       ============================================================ */

    Tree T1 = newNode(10,
                newNode(5,
                    newNode(2,
                        newNode(1, NULL, NULL),
                        NULL),
                    NULL),
                newNode(3, NULL, NULL)
            );
    /*
       - Nodo 10: sx=4, dx=1 → OK
       - Nodo 5:  sx=2, dx=0 → OK
       - Nodo 2:  sx=1, dx=0 → OK
    */

    /* ============================================================
       CASO 2: FALSO (atteso 0)
       La radice NON è dominante

                 8
                / \
               4   6

       sx=1, dx=1 → NON sx > dx
       ============================================================ */

    Tree T2 = newNode(8,
                newNode(4, NULL, NULL),
                newNode(6, NULL, NULL)
            );

    /* ============================================================
       CASO 3: FALSO (atteso 0)
       Nodo interno profondo non dominante (TRAPPOLA)

                 10
                /  \
               5    1
              / \
             3   4

       - Nodo 10: sx=3, dx=1 → OK
       - Nodo 5:  sx=1, dx=1 → NON dominante ❌
       ============================================================ */

    Tree T3 = newNode(10,
                newNode(5,
                    newNode(3, NULL, NULL),
                    newNode(4, NULL, NULL)),
                newNode(1, NULL, NULL)
            );

    /* ============================================================
       CASO 4: VERO (atteso 1)
       Albero con un solo nodo (nessun nodo interno)

                 7

       Per convenzione: vero (non ci sono nodi interni che violano).
       ============================================================ */

    Tree T4 = newNode(7, NULL, NULL);

    /* ============================================================
       CASO 5: VERO (atteso 1)
       Albero vuoto
       ============================================================ */

    Tree T5 = NULL;

    /* =======================
       PRINTF
       ======================= */

    printf("Nodo dominante - Caso 1 (atteso 1): %d\n", tuttiNodiDominanti(T1));
    printf("Nodo dominante - Caso 2 (atteso 0): %d\n", tuttiNodiDominanti(T2));
    printf("Nodo dominante - Caso 3 (atteso 0): %d\n", tuttiNodiDominanti(T3));
    printf("Nodo dominante - Caso 4 (atteso 1): %d\n", tuttiNodiDominanti(T4));
    printf("Nodo dominante - Caso 5 (atteso 1): %d\n", tuttiNodiDominanti(T5));

    /* libero memoria */
    freeTree(T1);
    freeTree(T2);
    freeTree(T3);
    freeTree(T4);

    return 0;
}

void èdominante(Tree t, int *count)
    {
        if(t==NULL)
            return;
        if(contanodi(t->left)>contanodi(t->right) && !(t->left==NULL && t->right==NULL))
            (*count)++;
    èdominante(t->left, count);
    èdominante(t->right, count);
    }
int contanodi(Tree t)
    {
    if(t==NULL)
        return 0;
    return 1+contanodi(t->left)+contanodi(t->right);
    }
int tuttiNodiDominanti(Tree t)
    {
    if(t==NULL)
        return 1;
    int count=0;
    èdominante(t, &count);
    if(count==wrapper(t))
        return 1;
    return 0;
    }
void containterni(Tree t, int *count)
    {
        if(t==NULL)
            return;
        if(!(t->left==NULL && t->right==NULL))
            (*count)++;
    containterni(t->left, count);
    containterni(t->right, count);
    }
int wrapper(Tree t)
    {
        if(t==NULL)
            return 0;
    int count=0;
    containterni(t, &count);
    return count;
    }
