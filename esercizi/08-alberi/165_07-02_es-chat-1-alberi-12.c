//
//  main.c
//  es chat 1 alberi -12
//
//  Created by Francesco Roscio Ricon on 07/02/26.


#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE
   ========================= */
typedef struct N {
    int v;                 /* può essere negativo */
    struct N *left, *right;
} Node;

typedef Node* tree;


int percorsoAlternatoMaxDaQualunqueNodo(tree t);  /* TODO */

/* =========================
   UTILITY CREAZIONE / STAMPA / FREE
   ========================= */
static tree newNode(int v) {
    tree n = (tree)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->v = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

static void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

static void printPreorder(tree t) {
    if (!t) { printf("NULL "); return; }
    printf("%d ", t->v);
    printPreorder(t->left);
    printPreorder(t->right);
}

/* =========================
   ALBERI DI TEST (con negativi)
   ========================= */

/* Test 1: misto, con cammini alternati che possono partire "dentro"
   Esempio:
              -5 (odd)
             /        \
         2 (even)     -8 (even)
         /    \          \
      -9(o)   7(o)       3(o)
       /
     -4(e)

   Qui ci sono cammini validi:
   -5 -> 2 -> -9 -> -4  (o-e-o-e) somma = -16
   2 -> 7               (e-o)     somma = 9
   -8 -> 3              (e-o)     somma = -5
   7 (da solo)          somma = 7
*/
static tree buildTest_MIX(void) {
    tree r = newNode(-5);
    r->left = newNode(2);
    r->right = newNode(-8);

    r->left->left = newNode(-9);
    r->left->right = newNode(7);
    r->left->left->left = newNode(-4);

    r->right->right = newNode(3);

    return r;
}

/* Test 2: tutto pari (nessun arco valido, ma cammini di lunghezza 1 sì)
              4
             / \
           -2   6
              /
             0
*/
static tree buildTest_ALL_EVEN(void) {
    tree r = newNode(4);
    r->left = newNode(-2);
    r->right = newNode(6);
    r->right->left = newNode(0);
    return r;
}

/* Test 3: struttura a zig-zag con negativi
         1(o)
          \
          -2(e)
           \
            -3(o)
             \
              10(e)
*/
static tree buildTest_ZIGZAG(void) {
    tree r = newNode(1);
    r->right = newNode(-2);
    r->right->right = newNode(-3);
    r->right->right->right = newNode(10);
    return r;
}

/* Test 4: singolo nodo negativo */
static tree buildTest_SINGLE_NEG(void) {
    return newNode(-7);
}

/* =========================
   MAIN DI TEST
   ========================= */
void f(tree albero, int *max);
void fromhere(tree albero, int expected, int somma, int *max);
int èpari(int x);

int main(void) {
    tree t1 = buildTest_MIX();
    tree t2 = buildTest_ALL_EVEN();
    tree t3 = buildTest_ZIGZAG();
    tree t4 = buildTest_SINGLE_NEG();
    tree t5 = NULL;

    printf("=== TEST 1 (MIX) ===\n");
    printf("Preorder: ");
    printPreorder(t1);
    printf("\n");
    printf("Risultato percorsoAlternatoMaxDaQualunqueNodo(t1) = %d\n\n",
           percorsoAlternatoMaxDaQualunqueNodo(t1));

    printf("=== TEST 2 (ALL EVEN) ===\n");
    printf("Preorder: ");
    printPreorder(t2);
    printf("\n");
    printf("Risultato percorsoAlternatoMaxDaQualunqueNodo(t2) = %d\n\n",
           percorsoAlternatoMaxDaQualunqueNodo(t2));

    printf("=== TEST 3 (ZIGZAG) ===\n");
    printf("Preorder: ");
    printPreorder(t3);
    printf("\n");
    printf("Risultato percorsoAlternatoMaxDaQualunqueNodo(t3) = %d\n\n",
           percorsoAlternatoMaxDaQualunqueNodo(t3));

    printf("=== TEST 4 (SINGLE NEG) ===\n");
    printf("Preorder: ");
    printPreorder(t4);
    printf("\n");
    printf("Risultato percorsoAlternatoMaxDaQualunqueNodo(t4) = %d\n\n",
           percorsoAlternatoMaxDaQualunqueNodo(t4));

    printf("=== TEST 5 (NULL) ===\n");
    printf("Preorder: ");
    printPreorder(t5);
    printf("\n");
    printf("Risultato percorsoAlternatoMaxDaQualunqueNodo(t5) = %d\n\n",
           percorsoAlternatoMaxDaQualunqueNodo(t5));

    freeTree(t1);
    freeTree(t2);
    freeTree(t3);
    freeTree(t4);

    return 0;
}
int èpari(int x)
    {
        if(x%2==0)
            return 1;
    return -1;
    }
void fromhere(tree albero, int expected, int somma, int *max)
    {
        if(albero==NULL)
            return;
        if(expected!=èpari(albero->v))
            return;
        somma=somma+albero->v;
        if(somma>*max)
            *max=somma;
        int new_expected=-èpari(albero->v);
        fromhere(albero->left, new_expected, somma, max);
        fromhere(albero->right, new_expected, somma, max);
    }
void f(tree albero, int *max)
    {
        if(albero==NULL)
            return;
        int stato_now=èpari(albero->v);
        fromhere(albero, stato_now, 0, max);
        f(albero->left, max);
        f(albero->right, max);
    }
int percorsoAlternatoMaxDaQualunqueNodo(tree t)
    {
    if(t==NULL)
        return 0;
    int somma=t->v;
    f(t, &somma);
    return somma;
    }
