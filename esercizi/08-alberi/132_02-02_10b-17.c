//
//  main.c
//  10B -17
//
//  Created by Francesco Roscio Ricon on 02/02/26.
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

typedef Node* Albero;

/* =======================
   UTILITY
   ======================= */

static Node* newNode(int v, Node* l, Node* r) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->left = l;
    n->right = r;
    return n;
}

static void freeTree(Albero t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

static int isEven(int x) {
    return (x % 2 == 0);
}

static void printInorder(Albero t) {
    if (!t) return;
    printInorder(t->left);
    printf("%d ", t->val);
    printInorder(t->right);
}

/* Stampa cammini root->leaf con parità (E/O) */
static void printPathsAux(Albero t, int path[], char parity[], int len) {
    if (!t) return;

    path[len] = t->val;
    parity[len] = isEven(t->val) ? 'E' : 'O';
    len++;

    if (t->left == NULL && t->right == NULL) {
        printf("Cammino: ");
        for (int i = 0; i < len; i++) {
            printf("%d(%c)%s", path[i], parity[i], (i == len - 1) ? "" : " -> ");
        }
        printf("\n");
        return;
    }

    printPathsAux(t->left,  path, parity, len);
    printPathsAux(t->right, path, parity, len);
}

static void printPathsWithParity(Albero t) {
    int path[128];
    char parity[128];
    printPathsAux(t, path, parity, 0);
}

/* =======================
   ESERCIZIO 10B (STUB)
   ======================= */

int maxCamminoResetPariDispari(Albero t);

/* =======================
   MAIN DI TEST
   ======================= */
void f(Albero tree, int count, int *max, int prev, int hasprev);
int wrapper(Albero tree);
void funz(Albero tree, int *max);
void f(Albero tree, int count, int *max, int prev, int hasprev);
int èpari(int x);

int main(void) {
    /* t1: alternanze e rotture sparse */
    Albero t1 =
        newNode(5,  /* O */
            newNode(2, /* E */
                newNode(7, NULL, NULL),  /* O */
                newNode(4, NULL, NULL)   /* E */
            ),
            newNode(9, /* O */
                newNode(8, NULL, NULL),  /* E */
                newNode(6, NULL, NULL)   /* E (qui rompe rispetto a 9->6? no: O->E ok, ma poi è foglia) */
            )
        );

    /* t2: catena con rottura in mezzo (serve “reset”) */
    Albero t2 =
        newNode(2,  /* E */
            newNode(4, /* E (rottura subito se venivi da 2) */
                newNode(7, /* O */
                    newNode(10, NULL, NULL), /* E */
                    NULL
                ),
                NULL
            ),
            NULL
        );

    /* t3: molti pari consecutivi, ma con un ramo che alterna */
    Albero t3 =
        newNode(8, /* E */
            newNode(6, /* E */
                newNode(5, /* O */
                    newNode(2, NULL, NULL), /* E */
                    NULL
                ),
                newNode(4, NULL, NULL) /* E */
            ),
            newNode(3, /* O */
                newNode(2, NULL, NULL),  /* E */
                newNode(1, NULL, NULL)   /* O (O->O rompe, ma reset conta) */
            )
        );

    printf("\n%d, %d, %d", wrapper(t1), wrapper(t2), wrapper(t3));
    freeTree(t1);
    freeTree(t2);
    freeTree(t3);
    return 0;
}

int èpari(int x)
    {
        if(x%2==0)
            return 1;
        return 0;
    }
void f(Albero tree, int count, int *max, int prev, int hasprev)
    {
        if(tree==NULL)
            return;
        if(hasprev==1 && èpari(prev)==èpari(tree->val))
            {
                count=0;
            }
    count++;
        if(*max<count)
            *max=count;
    f(tree->left, count, max, tree->val, 1);
    f(tree->right, count, max, tree->val, 1);
    }
void funz(Albero tree, int *max)
    {
    int max_nodo=0;
    f(tree, 0, &max_nodo, 0, 0);
    if(max_nodo>*max)
        *max=max_nodo;
    }

int wrapper(Albero tree)
    {
    int max=0;
    funz(tree, &max);
    return max;
    }
