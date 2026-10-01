//  Created by Francesco Roscio Ricon on 07/02/26.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* =========================================================
   STRUTTURE DATI (corrette)
   ========================================================= */
typedef struct EL {
    int dato;
    struct EL *left, *right;   /* <-- right deve essere un puntatore */
} node;

typedef node* tree;

/* =========================================================
   PROTOTIPI
   ========================================================= */
tree newNode(int value);
void freeTree(tree t);

void printInOrder(tree t);
void printTreePretty(tree t, int depth);

int gcd2(int a, int b);     /* ausiliaria classica MCD(a,b) */
int mcdAlbero(tree t);      

/* =========================================================
   MAIN DI TEST
   ========================================================= */
int f(tree albero);
int main(void) {
    /*
        Albero di esempio:

              48
             /  \
           18    30
          / \     \
        12  27     42
    */

    tree t = newNode(48);
    t->left = newNode(18);
    t->right = newNode(30);
    t->left->left = newNode(12);
    t->left->right = newNode(27);
    t->right->right = newNode(42);

    printf("Albero (pretty):\n");
    printTreePretty(t, 0);

    printf("\nVisita inorder: ");
    printInOrder(t);
    printf("\n");

    /* Chiamata alla funzione dell'esercizio (ancora TODO) */
    int ris = f(t);
    printf("\nMCD tra tutti gli elementi dell'albero = %d\n", ris);

    freeTree(t);
    return 0;
}

/* =========================================================
   UTILITY: CREAZIONE / DISTRUZIONE
   ========================================================= */
tree newNode(int value) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->dato = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void freeTree(tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =========================================================
   STAMPE (per debug)
   ========================================================= */
void printInOrder(tree t) {
    if (t == NULL) return;
    printInOrder(t->left);
    printf("%d ", t->dato);
    printInOrder(t->right);
}

void printTreePretty(tree t, int depth) {
    if (t == NULL) return;
    printTreePretty(t->right, depth + 1);
    for (int i = 0; i < depth; i++) printf("    ");
    printf("%d\n", t->dato);
    printTreePretty(t->left, depth + 1);
}

/* =========================================================
   AUSILIARIA MCD DI DUE NUMERI
   (questa può servirti per MCD(x,y,z)=MCD(MCD(x,y),z))
   ========================================================= */

int MCD(int a, int b)
{
    if (b == 0)
        return a;
    return MCD(b, a % b);
}
int f(tree albero)
    {
        if(albero==NULL)
            return 0;
        int sx=f(albero->left);
        int dx=f(albero->right);
        int m=MCD(sx, dx);
    return MCD(m, albero->dato);
    }
