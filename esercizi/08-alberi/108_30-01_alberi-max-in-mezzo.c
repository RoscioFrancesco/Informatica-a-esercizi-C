//
//  main.c
//  alberi max in mezzo
//
//  Created by Francesco Roscio Ricon on 30/01/26.
//
#include <stdio.h>
#include <stdlib.h>

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
int f(Albero tree, Albero root, int max, int occ_max, int *has_max);
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

static int max(int a, int b) { return (a > b) ? a : b; }

static int height(Albero t) {
    if (!t) return 0;
    return 1 + max(height(t->left), height(t->right));
}

/* =======================
   STAMPA CAMMINI RADICE-FOGLIA
   (solo per aiutarti a controllare a mano)
   ======================= */

static void printPath(int path[], int len) {
    printf("Cammino: ");
    for (int i = 0; i < len; i++) {
        printf("%d", path[i]);
        if (i + 1 < len) printf(" -> ");
    }
    printf("\n");
}

static void printAllPathsAux(Albero t, int path[], int depth) {
    if (!t) return;

    path[depth] = t->val;
    depth++;

    if (!t->left && !t->right) {
        printPath(path, depth);
        return;
    }

    printAllPathsAux(t->left, path, depth);
    printAllPathsAux(t->right, path, depth);
}

static void printAllPaths(Albero t) {
    if (!t) {
        printf("(albero vuoto) nessun cammino.\n");
        return;
    }
    int h = height(t);
    int *path = (int*)malloc(sizeof(int) * h);
    if (!path) { perror("malloc"); exit(1); }

    printf("\nCammini radice->foglia:\n");
    printAllPathsAux(t, path, 0);

    free(path);
}

/* =======================
   ESEMPI DI TEST
   ======================= */

/*
  ESEMPIO 1: vari cammini, massimo ripetuto in alcuni rami
              5
            /   \
           2     4
          / \     \
         9   1     9
            /
           3

  Stampa i cammini e verifica a mano:
  - max compare una sola volta?
  - max è interno (non primo, non ultimo)?
*/
static Albero esempio1(void) {
    return newNode(5,
        newNode(2,
            newNode(9, NULL, NULL),
            newNode(1,
                newNode(3, NULL, NULL),
                NULL)),
        newNode(4,
            NULL,
            newNode(9, NULL, NULL)));
}

/*
  ESEMPIO 2: massimo alla radice (caso da scartare)
          10
         /  \
        3    4
*/
static Albero esempio2(void) {
    return newNode(10,
        newNode(3, NULL, NULL),
        newNode(4, NULL, NULL));
}

/*
  ESEMPIO 3: massimo spesso in foglia (caso da scartare per quei cammini)
            1
           / \
          2   3
             / \
            4   9
*/
static Albero esempio3(void) {
    return newNode(1,
        newNode(2, NULL, NULL),
        newNode(3,
            newNode(4, NULL, NULL),
            newNode(9, NULL, NULL)));
}

/*
  ESEMPIO 4: catena (un solo cammino)
      2
       \
        7
         \
          5
           \
            1
*/
static Albero esempio4(void) {
    return newNode(2, NULL,
        newNode(7, NULL,
            newNode(5, NULL,
                newNode(1, NULL, NULL))));
}

/*
  ESEMPIO 5: massimo ripetuto (max compare più volte lungo lo stesso cammino)
            1
             \
              8
               \
                8
                 \
                  0
*/
static Albero esempio5(void) {
    return newNode(1, NULL,
        newNode(8, NULL,
            newNode(8, NULL,
                newNode(0, NULL, NULL))));
}

/*
  ESEMPIO 6: valori negativi e massimo interno possibile
             -5
            /  \
          -2   -7
           \
           -1
*/
static Albero esempio6(void) {
    return newNode(-5,
        newNode(-2,
            NULL,
            newNode(-1, NULL, NULL)),
        newNode(-7, NULL, NULL));
}

/* =======================
   MAIN
   ======================= */

static void run(const char* nome, Albero t) {
    printf("\n==================== %s ====================\n", nome);
    printTree(t);
    printAllPaths(t);
    int hasmax=0;
    printf("\n%d", f(t, t, 0, 0, &hasmax));
}
int f(Albero tree, Albero root, int max, int occ_max, int *has_max);

int main(void) {
    Albero t1 = esempio1();
    Albero t2 = esempio2();
    Albero t3 = esempio3();
    Albero t4 = esempio4();
    Albero t5 = esempio5();
    Albero t6 = esempio6();

    run("ESEMPIO 1", t1);
    run("ESEMPIO 2 (max in radice)", t2);
    run("ESEMPIO 3 (max spesso in foglia)", t3);
    run("ESEMPIO 4 (catena)", t4);
    run("ESEMPIO 5 (max ripetuto)", t5);
    run("ESEMPIO 6 (negativi)", t6);

    freeTree(t1);
    freeTree(t2);
    freeTree(t3);
    freeTree(t4);
    freeTree(t5);
    freeTree(t6);

    return 0;
}
/*
  Qui NON stampo TRUE/FALSE.
  Tu guardi ogni cammino e controlli a mano:
  - trova il massimo del cammino
  - verifica che compaia una sola volta
  - verifica che NON sia il primo (radice) né l’ultimo (foglia)
*/

int f(Albero tree, Albero root, int max, int occ_max, int *has_max)
    {
        if(tree==NULL)
            return 0;
        if(*has_max==0)
            {
                max=root->val;
                *has_max=1;
            }
        if(max==tree->val)
            occ_max++;
        if(tree->val>max)
            {
                max=tree->val;
                occ_max=1;
            }
        if(tree->left==NULL && tree->right==NULL)
            {
                if(occ_max>1)
                    return 0;
                if(tree->val==max)
                    return 0;
                if(root->val==max)
                    return 0;
                return 1;
            }
    return f(tree->left, root, max, occ_max, has_max) || f(tree->right, root, max, occ_max, has_max);
    }
