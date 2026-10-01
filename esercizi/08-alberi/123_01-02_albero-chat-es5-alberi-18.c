//
//  main.c
//  albero chat es5 alberi -18
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

int alberoCoerente(Tree t);
int tutteinterni(int x, Tree t);
int tuttefoglie(int x, Tree t);
int occorrenze(int val, Tree t);
void voidoccorrenze(int val, Tree t, int *count);
int f(Tree t, Tree root);


int main() {

    /* ============================================================
       CASO 1: VERO (atteso 1)
       Valori ripetuti ma ruoli coerenti

                 10
                /  \
               5    5
              / \
             3   7

       - valore 5: compare due volte, ENTRAMBI nodi interni
       - valore 3: una volta (foglia)
       - valore 7: una volta (foglia)
       ============================================================ */
    Tree T1 = newNode(10,
                newNode(5,
                    newNode(3, NULL, NULL),
                    newNode(7, NULL, NULL)),
                newNode(5, NULL, NULL)
            );

    /* ============================================================
       CASO 2: FALSO (atteso 0)  ★ TRAPPOLA CLASSICA ★
       Stesso valore come foglia e come nodo interno

                 8
                / \
               4   6
              /
             6

       - valore 6: una volta nodo interno, una volta foglia → NON coerente
       ============================================================ */
    Tree T2 = newNode(8,
                newNode(4,
                    newNode(6, NULL, NULL),
                    NULL),
                newNode(6, NULL, NULL)
            );

    /* ============================================================
       CASO 3: VERO (atteso 1)
       Stesso valore ripetuto SOLO come foglia

                 9
                / \
               2   3
              /     \
             5       5

       - valore 5: compare due volte, ENTRAMBE foglie
       ============================================================ */
    Tree T3 = newNode(9,
                newNode(2,
                    newNode(5, NULL, NULL),
                    NULL),
                newNode(3,
                    NULL,
                    newNode(5, NULL, NULL))
            );

    /* ============================================================
       CASO 4: FALSO (atteso 0)
       Valore ripetuto in profondità con ruoli diversi (TRAPPOLA)

                 10
                /  \
               4    7
              /      \
             2        4
                       \
                        3

       - valore 4:
           * a sinistra: nodo interno
           * a destra: nodo interno? NO → foglia con figlio? no → interno?
         Attenzione: qui è INTERNO (ha figlio 3)
       Modifichiamo per renderlo FALSO sotto.
       ============================================================ */

    Tree T4 = newNode(10,
                newNode(4,
                    newNode(2, NULL, NULL),
                    NULL),
                newNode(7,
                    NULL,
                    newNode(4, NULL, NULL))
            );
    /*
       - valore 4:
           * a sinistra: nodo interno
           * a destra: FOGLIA
       => NON coerente
    */

    /* ============================================================
       CASO 5: VERO (atteso 1)
       Albero con un solo nodo
       ============================================================ */
    Tree T5 = newNode(1, NULL, NULL);

    /* ============================================================
       CASO 6: VERO (atteso 1)
       Albero vuoto
       ============================================================ */
    Tree T6 = NULL;

    /* =======================
       PRINTF
       ======================= */

    printf("Albero coerente - Caso 1 (atteso 1): %d\n", alberoCoerente(T1));
    printf("Albero coerente - Caso 2 (atteso 0): %d\n", alberoCoerente(T2));
    printf("Albero coerente - Caso 3 (atteso 1): %d\n", alberoCoerente(T3));
    printf("Albero coerente - Caso 4 (atteso 0): %d\n", alberoCoerente(T4));
    printf("Albero coerente - Caso 5 (atteso 1): %d\n", alberoCoerente(T5));
    printf("Albero coerente - Caso 6 (atteso 1): %d\n", alberoCoerente(T6));

    /* libero memoria */
    freeTree(T1);
    freeTree(T2);
    freeTree(T3);
    freeTree(T4);
    freeTree(T5);

    return 0;
}

void voidoccorrenze(int val, Tree t, int *count)
    {
        if(t==NULL)
            return;
        if(t->val==val)
            (*count)++;
    voidoccorrenze(val, t->left, count);
    voidoccorrenze(val, t->right, count);
    }
int occorrenze(int val, Tree t)
    {
    int count=0;
    voidoccorrenze(val, t, &count);
    return count;
    }
int tuttefoglie(int x, Tree t)
    {
        if(t==NULL)
            return 1;
    if(t->val==x)
        {
        if(t->left!=NULL || t->right!=NULL)
            return 0;
        }
    return tuttefoglie(x, t->left) && tuttefoglie(x, t->right);
    }
int tutteinterni(int x, Tree t)
    {
    if(t==NULL)
        return 1;
    if(t->val==x)
    {
        if(t->left==NULL && t->right==NULL)
            return 0;
    }
return tutteinterni(x, t->left) && tutteinterni(x, t->right);
}
int f(Tree t, Tree root)
    {
        if(t==NULL)
            return 1;
        if(occorrenze(t->val, root)>1)
            {
                if(t->left==NULL && t->right==NULL)
                    {
                         if(tuttefoglie(t->val, root)==0)
                             return 0;
                    }
                else
                    {
                        if(tutteinterni(t->val, root)==0)
                            return 0;
                    }
            }
    return f(t->left, root) && f(t->right, root);
    }
int alberoCoerente(Tree t)
    {
    if(t==NULL)
        return 1;
    return f(t, t);
    }
