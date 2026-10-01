//
//  main.c
//  tde carta alberi -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//

typedef struct nodeS {
    int v;
    struct nodeS * left, *right; } node;
typedef node * tree;

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */

/* =========================
   PROTOTIPO (TU LA SCRIVI)
   ========================= */
int simmetrici(tree t1, tree t2);  /* TODO */

/* =========================
   UTILITY per creare / stampare / liberare alberi
   (qui i cicli sono ok, ma non servono)
   ========================= */
static tree newNode(int v, tree left, tree right) {
    tree t = (tree)malloc(sizeof(node));
    if (!t) { perror("malloc"); exit(1); }
    t->v = v;
    t->left = left;
    t->right = right;
    return t;
}

static void freeTree(tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* stampa semplice (preorder) per vedere la forma */
static void printTreePre(tree t) {
    if (t == NULL) { printf("NULL "); return; }
    printf("%d ", t->v);
    printTreePre(t->left);
    printTreePre(t->right);
}

/* =========================
   MAIN DI TEST
   ========================= */
int f(tree albero1, tree albero2);
int main(void) {
    /* -------------------------
       ESEMPIO 1: t1 e t2 SIMMETRICI
       t1:            1
                    / \
                   2   3
                  /     \
                 4       5

       t2:            1
                    / \
                   3   2
                  /     \
                 5       4
       (stessa struttura a specchio, e valori in posizioni specchiate)
       ------------------------- */
    tree t1 = newNode(1,
                newNode(2,
                    newNode(4, NULL, NULL),
                    NULL
                ),
                newNode(3,
                    NULL,
                    newNode(5, NULL, NULL)
                )
            );

    tree t2 = newNode(1,
                newNode(3,
                    newNode(5, NULL, NULL),
                    NULL
                ),
                newNode(2,
                    NULL,
                    newNode(4, NULL, NULL)
                )
            );

    /* -------------------------
       ESEMPIO 2: NON simmetrici
       Cambiamo un valore/ramo in t3
       ------------------------- */
    tree t3 = newNode(1,
                newNode(3,
                    newNode(999, NULL, NULL), /* diverso da 5 */
                    NULL
                ),
                newNode(2,
                    NULL,
                    newNode(4, NULL, NULL)
                )
            );

    printf("t1 (preorder): ");
    printTreePre(t1);
    printf("\n");

    printf("t2 (preorder): ");
    printTreePre(t2);
    printf("\n");

    printf("t3 (preorder): ");
    printTreePre(t3);
    printf("\n\n");

    printf("simmetrici(t1,t2) = %d  (atteso: 1)\n", f(t1, t2));
    printf("simmetrici(t1,t3) = %d  (atteso: 0)\n", f(t1, t3));

    freeTree(t1);
    freeTree(t2);
    freeTree(t3);

    return 0;
}
int f(tree albero1, tree albero2)
    {
        if(albero1==NULL && albero2==NULL)
            return 1;
        if(albero1==NULL || albero2==NULL)
            return 0;
        if(albero1->v!=albero2->v)
            return 0;
    return f(albero1->left, albero2->right) && f(albero1->right, albero2->left);
    }
