//
//  main.c
//  tde carta tde 2 es alberi -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node* tree;

/* =========================
   PROTOTIPO (GIÀ DATO)
   ========================= */
int f(tree t, int livello);

/* =========================
   UTILITY (per test: OK usare cicli)
   ========================= */
static tree newNode(int x, tree l, tree r) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = x;
    n->left = l;
    n->right = r;
    return n;
}

static void freeTree(tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* stampa preorder con livello (per capire la struttura) */
static void printTree(tree t, int livello) {
    if (t == NULL) return;
    printf("livello %d -> %d\n", livello, t->dato);
    printTree(t->left, livello + 1);
    printTree(t->right, livello + 1);
}

/* =========================
   MAIN DI TEST
   ========================= */
int èpari(int x);
int main(void) {

    /*
        Albero di esempio (valido):

                2        livello 0 (pari)
               / \
              3   5      livello 1 (dispari)
             / \
            4   6        livello 2 (pari)

        Atteso: 1
    */
    tree t1 =
        newNode(2,
            newNode(3,
                newNode(4, NULL, NULL),
                newNode(6, NULL, NULL)
            ),
            newNode(5, NULL, NULL)
        );

    printf("ALBERO t1:\n");
    printTree(t1, 0);

    printf("\nRisultato f(t1,0) = %d (atteso: 1)\n", f(t1, 0));

    /*
        Albero NON valido:

                2
               / \
              4   5   <- 4 è pari ma livello 1 è dispari

        Atteso: 0
    */
    tree t2 =
        newNode(2,
            newNode(4, NULL, NULL),
            newNode(5, NULL, NULL)
        );

    printf("\nALBERO t2:\n");
    printTree(t2, 0);

    printf("\nRisultato f(t2,0) = %d (atteso: 0)\n", f(t2, 0));

    freeTree(t1);
    freeTree(t2);

    return 0;
}

int f(tree T, int livello)
    {
        if(T==NULL)
            return 1;
        if(èpari(livello)!=èpari(T->dato))
            return 0;
        if(T->left==NULL && T->right==NULL)
            return 1;
    return f(T->left, livello+1) && f(T->right, livello+1);
    }
int èpari(int x)
    {
        if(x%2==0)
            return 1;
        return 0;
    }
