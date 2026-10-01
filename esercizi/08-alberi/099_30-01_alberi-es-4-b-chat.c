//
//  main.c
//  alberi es 4 b chat
//
//  Created by Francesco Roscio Ricon on 30/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* =======================
   STRUTTURE DATI
   ======================= */

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
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

static void printTree2D(Albero t, int space) {
    if (!t) return;
    space += 6;
    printTree2D(t->right, space);
    for (int i = 6; i < space; i++) printf(" ");
    printf("%d\n", t->val);
    printTree2D(t->left, space);
}

static void printTree(Albero t) {
    printf("\n--- Albero (ruotato: destra in alto) ---\n");
    printTree2D(t, 0);
    printf("---------------------------------------\n");
}

static const char* parityStr(int x) {
    return (x % 2 == 0) ? "pari" : "dispari";
}

static void printPattern(const int* p, int len) {
    printf("Pattern (0=pari,1=dispari), len=%d: [", len);
    for (int i = 0; i < len; i++) {
        printf("%d", p[i]);
        if (i + 1 < len) printf(", ");
    }
    printf("]\n");
}




bool esisteCamminoPatternParita(Albero t, int pattern[], int len);


/* =======================
   ESEMPI DI ALBERI
   ======================= */

/*
  ESEMPIO A (molti cammini, varie parità)

               8(e)
             /      \
          3(o)      6(e)
          /  \        \
       4(e)  7(o)     5(o)

  Cammini radice-foglia (valori / parità):
  - 8-3-4 : e, o, e  -> [0,1,0]
  - 8-3-7 : e, o, o  -> [0,1,1]
  - 8-6-5 : e, e, o  -> [0,0,1]
*/
static Albero esempioA(void) {
    return newNode(8,
        newNode(3,
            newNode(4, NULL, NULL),
            newNode(7, NULL, NULL)),
        newNode(6,
            NULL,
            newNode(5, NULL, NULL)));
}

/*
  ESEMPIO B (catena unica)
     1(o)
      \
       2(e)
        \
         3(o)
          \
           4(e)

  Cammino unico: o,e,o,e -> [1,0,1,0]
*/
static Albero esempioB(void) {
    return newNode(1, NULL,
        newNode(2, NULL,
            newNode(3, NULL,
                newNode(4, NULL, NULL))));
}

/*
  ESEMPIO C (nodo singolo)
      10(e)
  Cammino unico di lunghezza 1: [0]
*/
static Albero esempioC(void) {
    return newNode(10, NULL, NULL);
}

/*
  ESEMPIO D (albero più “ampio” per test lunghezze e fallimenti)
              5(o)
            /     \
         2(e)     9(o)
        /   \     / \
     12(e)  3(o) 6(e) 7(o)

  Cammini (parità):
  5-2-12 : o,e,e -> [1,0,0]
  5-2-3  : o,e,o -> [1,0,1]
  5-9-6  : o,o,e -> [1,1,0]
  5-9-7  : o,o,o -> [1,1,1]
*/
static Albero esempioD(void) {
    return newNode(5,
        newNode(2,
            newNode(12, NULL, NULL),
            newNode(3, NULL, NULL)),
        newNode(9,
            newNode(6, NULL, NULL),
            newNode(7, NULL, NULL)));
}

/* =======================
   TEST CASES (pattern)
   ======================= */

static void runTest(const char* nomeAlbero, Albero t, int pattern[], int len) {
    printf("\n==================== %s ====================\n", nomeAlbero);
    printTree(t);

    printPattern(pattern, len);

    bool ans = esisteCamminoPatternParita(t, pattern, len);
    printf("Risultato esisteCamminoPatternParita -> %s\n", ans ? "TRUE" : "FALSE");
}

/* =======================
   MAIN
   ======================= */

int main(void) {
    Albero A = esempioA();
    Albero B = esempioB();
    Albero C = esempioC();
    Albero D = esempioD();

    /* Pattern di prova (0=pari, 1=dispari) */
    int p1[] = {0,1,0};      // in A esiste (8-3-4)
    int p2[] = {0,1,1};      // in A esiste (8-3-7)
    int p3[] = {0,0,1};      // in A esiste (8-6-5)
    int p4[] = {0,0,0};      // in A NON esiste
    int p5[] = {1,0,1,0};    // in B esiste (1-2-3-4)
    int p6[] = {1,0,1};      // in B NON esiste (lunghezza diversa)
    int p7[] = {0};          // in C esiste (10 pari)
    int p8[] = {1};          // in C NON esiste
    int p9[] = {1,0,1};      // in D esiste (5-2-3)
    int p10[] = {1,1,0};     // in D esiste (5-9-6)
    int p11[] = {1,1,1};     // in D esiste (5-9-7)
    int p12[] = {1,0,0,1};   // in D NON esiste (lunghezza e pattern)

    runTest("ALBERO A", A, p1, 3);
    runTest("ALBERO A", A, p2, 3);
    runTest("ALBERO A", A, p3, 3);
    runTest("ALBERO A", A, p4, 3);

    runTest("ALBERO B", B, p5, 4);
    runTest("ALBERO B", B, p6, 3);

    runTest("ALBERO C", C, p7, 1);
    runTest("ALBERO C", C, p8, 1);

    runTest("ALBERO D", D, p9, 3);
    runTest("ALBERO D", D, p10, 3);
    runTest("ALBERO D", D, p11, 3);
    runTest("ALBERO D", D, p12, 4);

    freeTree(A);
    freeTree(B);
    freeTree(C);
    freeTree(D);

    return 0;
}

int f(Albero t, int segna, int v[], int len) // 0 indica pari ,1 indica dispari
    {
        if(t==NULL)
            return 0;
        if (segna >= len) return 0;
        if(v[segna]!=t->val%2)
            return 0;
        segna++;
        if(t->left==NULL && t->right==NULL)
            {
                if(segna==len)
                    return 1;
                return 0;
            }
        return f(t->left, segna, v, len) || f(t->right, segna, v, len);
    }
bool esisteCamminoPatternParita(Albero t, int pattern[], int len)
    {
    
    return f(t, 0, pattern, len);
    }
