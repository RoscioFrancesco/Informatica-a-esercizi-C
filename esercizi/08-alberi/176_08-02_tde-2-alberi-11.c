//  Created by Francesco Roscio Ricon on 08/02/26.
#include <stdio.h>
#include <stdlib.h>

typedef struct ET {
    int dato;
    struct ET *left, *center, *right;
} treeNode;

typedef treeNode* tree;


int f(tree t);   /* TODO */

/* =========================
   UTILITY PER TEST
   ========================= */
static tree newNode(int v) {
    tree n = (tree)malloc(sizeof(treeNode));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = v;
    n->left = n->center = n->right = NULL;
    return n;
}

static void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->center);
    freeTree(t->right);
    free(t);
}

/* Stampa in preorder per vedere la struttura */
static void printPreorder(tree t) {
    if (!t) {
        printf("NULL");
        return;
    }
    printf("%d(", t->dato);
    printPreorder(t->left);
    printf(",");
    printPreorder(t->center);
    printf(",");
    printPreorder(t->right);
    printf(")");
}

/* =========================
   ALBERI DI TEST
   ========================= */

/*
Test 1 (dovrebbe essere 1 se f è corretta):
Tutti i figli rispettano figlio <= padre + 2

            10
        /    |     \
      11     12     9
     / | \           \
   12 13 11           11
*/
static tree buildTest_OK(void) {
    tree r = newNode(10);

    r->left = newNode(11);
    r->center = newNode(12);
    r->right = newNode(9);

    r->left->left = newNode(12);
    r->left->center = newNode(13);  /* 13 <= 11+2 ok */
    r->left->right = newNode(11);

    r->right->right = newNode(11);  /* 11 <= 9+2 ok */

    return r;
}

/*
Test 2 (dovrebbe essere 0 se f è corretta):
C'è almeno una violazione: figlio > padre + 2

            10
        /    |     \
      11     12     9
     / | \
   15 12 11

Violazione: 15 > 11+2
*/
static tree buildTest_NO(void) {
    tree r = newNode(10);

    r->left = newNode(11);
    r->center = newNode(12);
    r->right = newNode(9);

    r->left->left = newNode(15);    /* viola: 15 > 13 */
    r->left->center = newNode(12);
    r->left->right = newNode(11);

    return r;
}


static tree buildTest_SINGLE(void) {
    return newNode(7);
}

/* =========================
   MAIN DI TEST
   ========================= */
int funzione(tree albero);
int f(tree albero);
int main(void) {
    tree t1 = buildTest_OK();
    tree t2 = buildTest_NO();
    tree t3 = buildTest_SINGLE();
    tree t4 = NULL;

    printf("=== TEST 1 (OK) ===\n");
    printf("Preorder: ");
    printPreorder(t1);
    printf("\n");
    printf("f(t1) = %d\n\n", f(t1));

    printf("=== TEST 2 (NO) ===\n");
    printf("Preorder: ");
    printPreorder(t2);
    printf("\n");
    printf("f(t2) = %d\n\n", f(t2));

    printf("=== TEST 3 (SINGLE) ===\n");
    printf("Preorder: ");
    printPreorder(t3);
    printf("\n");
    printf("f(t3) = %d\n\n", f(t3));

    printf("=== TEST 4 (NULL) ===\n");
    printf("Preorder: ");
    printPreorder(t4);
    printf("\n");
    printf("f(t4) = %d\n\n", f(t4));

    freeTree(t1);
    freeTree(t2);
    freeTree(t3);

    return 0;
}
//nodo figlio minore di 2+valore nodopadre

int funzione(tree albero)
    {
        if(albero==NULL)
            return 1;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
        int sx=1;
        int dx=1;
        if(albero->left!=NULL)
            {
                if(albero->left->dato>2+albero->dato)
                    return 0;
                sx=funzione(albero->left);
            }
        if(albero->right!=NULL)
            {
                if(albero->right->dato>2+albero->dato)
                    return 0;
                dx=funzione(albero->right);
            }
    return sx&&dx;
    }
int f(tree albero)
    {
        if(albero==NULL)
            return 1;
        int ris=funzione(albero);
        if(ris==0)
            return 0;
    return ris&&f(albero->left)&&f(albero->right);
    }
