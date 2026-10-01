//
//  main.c
//  tde alberi  -2
//
//  Created by Francesco Roscio Ricon on 17/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct ET {
    int dato;
    struct ET *left, *center, *right;
} treeNode;

typedef treeNode *tree;

/* =========================
   PROTOTIPO ESERCIZIO
   ========================= */
int f(tree t);

/* =========================
   SUPPORTO PER TEST
   ========================= */
static treeNode *newNode(int x) {
    treeNode *n = (treeNode*)malloc(sizeof(treeNode));
    n->dato = x;
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

/* stampa preorder con parentesi: dato(L,C,R) */
static void printShape(tree t) {
    if (!t) { printf("NULL"); return; }
    printf("%d(", t->dato);
    printShape(t->left);
    printf(",");
    printShape(t->center);
    printf(",");
    printShape(t->right);
    printf(")");
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {

    

    /*
                 10
            /      |      \
          11       12      10
         / | \             |
        12 13 11           12

      Controlli (figlio <= padre+2):
      11 <= 12 OK
      12 <= 12 OK
      10 <= 12 OK
      12 <= 13 OK
      13 <= 13 OK
      11 <= 13 OK
      12 <= 12 OK
    */
    tree T1 = newNode(10);
    T1->left   = newNode(11);
    T1->center = newNode(12);
    T1->right  = newNode(10);

    T1->left->left   = newNode(12);
    T1->left->center = newNode(13);
    T1->left->right  = newNode(11);

    T1->right->center = newNode(12);

    printf("===== TEST 1 (atteso: 1) =====\n");
    printf("Struttura: ");
    printShape(T1);
    printf("\n");
    printf("f(T1) = %d\n\n", f(T1));

    /* =========================================================
       TEST 2: atteso f(T2) = 0 (violazione)
       ========================================================= */

    
    tree T2 = newNode(8);
    T2->left   = newNode(9);
    T2->center = newNode(7);
    T2->right  = newNode(8);

    T2->left->left = newNode(12);  /* VIOLAZIONE qui */

    T2->right->left   = newNode(9);
    T2->right->center = newNode(11);
    T2->right->right  = newNode(8);

    printf("===== TEST 2 (atteso: 0) =====\n");
    printf("Struttura: ");
    printShape(T2);
    printf("\n");
    printf("f(T2) = %d\n\n", f(T2));

    freeTree(T1);
    freeTree(T2);
    return 0;
}
/*
int f(tree t) {
    // TODO: tua soluzione
}
*/

int funz(tree t, int prec)
    {
        if(t==NULL)
            return 1;
        if(t->dato>2+prec)
            return 0;
        if(t->left==NULL && t->right==NULL && t->center==NULL)
            return 1;
        int sx=funz(t->left, t->dato);
        int dx=funz(t->right, t->dato);
        int mid=funz(t->center, t->dato);
        return sx &&  dx &&  mid;
    }
int f(tree t) {
    if(t==NULL)
        return 1;
    return funz(t->center, t->dato) && funz(t->left, t->dato) && funz(t->right, t->dato);
}
