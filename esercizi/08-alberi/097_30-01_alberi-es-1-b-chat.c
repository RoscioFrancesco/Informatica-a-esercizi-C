//  Created by Francesco Roscio Ricon on 30/01/26.

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

/* Altezza/profondità massima: serve solo per stampare range di D nei test */
static int max(int a, int b) { return (a > b) ? a : b; }

static int altezza(Albero t) {
    if (!t) return 0;
    return 1 + max(altezza(t->left), altezza(t->right));
}




bool esisteNodoProfSommaPositiva(Albero t, int D);


/* =======================
   ESEMPI DI ALBERI
   ======================= */

/*
  ESEMPIO 1 (molto misto)
              5
            /   \
          -10     3
          / \    / \
         4  -2 -1  10

  Somme su profondità 0: [5] -> positiva => D=0 TRUE
  Profondità 1: cammini [5-10=-5], [5+3=8] => esiste somma positiva => D=1 TRUE
  Profondità 2: cammini [5-10+4=-1], [5-10-2=-7], [5+3-1=7], [5+3+10=18]
                => esiste positiva => D=2 TRUE
*/
static Albero esempio1(void) {
    return newNode(5,
        newNode(-10,
            newNode(4, NULL, NULL),
            newNode(-2, NULL, NULL)),
        newNode(3,
            newNode(-1, NULL, NULL),
            newNode(10, NULL, NULL)));
}

/*
  ESEMPIO 2 (tutto negativo)
            -2
           /  \
         -3   -4
        /
      -5

  D=0: somma=-2 (non positiva) => FALSE
  D=1: somma -2-3=-5, -2-4=-6 => FALSE
  D=2: somma -2-3-5=-10 => FALSE
*/
static Albero esempio2(void) {
    return newNode(-2,
        newNode(-3,
            newNode(-5, NULL, NULL),
            NULL),
        newNode(-4, NULL, NULL));
}

/*
  ESEMPIO 3 (radice negativa ma recupero sotto)
             -5
            /   \
           10    -1
          /  \
        -3    2

  D=0: -5 => FALSE
  D=1: -5+10=5 (positiva), -5-1=-6 => TRUE
  D=2: -5+10-3=2 (pos), -5+10+2=7 (pos) => TRUE
*/
static Albero esempio3(void) {
    return newNode(-5,
        newNode(10,
            newNode(-3, NULL, NULL),
            newNode(2, NULL, NULL)),
        newNode(-1, NULL, NULL));
}

/*
  ESEMPIO 4 (molti zeri, soglia “>0”)
             0
            / \
           0   1
              /
             0

  D=0: somma 0 => FALSE (serve positiva, non >=0)
  D=1: cammini 0+0=0 (no), 0+1=1 (si) => TRUE
  D=2: cammino 0+1+0=1 (si) => TRUE
*/
static Albero esempio4(void) {
    return newNode(0,
        newNode(0, NULL, NULL),
        newNode(1,
            newNode(0, NULL, NULL),
            NULL));
}

/*
  ESEMPIO 5 (nodo singolo)
        7

  D=0: 7 => TRUE
  D>=1: non esistono nodi a quella profondità => FALSE
*/
static Albero esempio5(void) {
    return newNode(7, NULL, NULL);
}

/*
  ESEMPIO 6 (nodo singolo negativo)
       -7

  D=0: -7 => FALSE
*/
static Albero esempio6(void) {
    return newNode(-7, NULL, NULL);
}

/* =======================
   MAIN DI TEST
   ======================= */

static void testAlbero(const char* nome, Albero t, int maxD_da_testare) {
    printf("\n==================== %s ====================\n", nome);
    printTree(t);

    for (int D = 0; D <= maxD_da_testare; D++) {
        bool ans = esisteNodoProfSommaPositiva(t, D);
        printf("D=%d -> %s\n", D, ans ? "TRUE" : "FALSE");
    }
}
int f(Albero t, int profondità, int K, int somma);

int main(void) {
    Albero t1 = esempio1();
    Albero t2 = esempio2();
    Albero t3 = esempio3();
    Albero t4 = esempio4();
    Albero t5 = esempio5();
    Albero t6 = esempio6();

    /* scegliamo quanti D provare in base all'altezza (profondità max = altezza-1) */
    testAlbero("ESEMPIO 1 (misto)", t1, altezza(t1));  // provo anche un D oltre la profondità max
    testAlbero("ESEMPIO 2 (tutto negativo)", t2, altezza(t2));
    testAlbero("ESEMPIO 3 (recupero sotto)", t3, altezza(t3));
    testAlbero("ESEMPIO 4 (zeri e positivi)", t4, altezza(t4));
    testAlbero("ESEMPIO 5 (singolo positivo)", t5, 2);
    testAlbero("ESEMPIO 6 (singolo negativo)", t6, 2);

    freeTree(t1);
    freeTree(t2);
    freeTree(t3);
    freeTree(t4);
    freeTree(t5);
    freeTree(t6);

    return 0;
}

bool esisteNodoProfSommaPositiva(Albero t, int D)
    {
    return f(t, 0, D, 0);
    }

int f(Albero t, int profondità, int K, int somma)
    {
        if(t==NULL)
            return 0;
        somma=somma+t->val;
        if(profondità==K)
            {
                if(somma>0)
                    return 1;
                return 0;
            }
        return f(t->right, profondità+1, K, somma)|| f(t->left, profondità+1, K, somma);
    }
