//
//  main.c
//  es 1.2 chat alberi  2 -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct nodeS {
    int v;
    struct nodeS *left, *right;
} node;

typedef node* tree;

/* =========================
   PROTOTIPO RICHIESTO
   ========================= */
int esisteCamminataBuona(tree T, int K);   

/* =========================
   UTILITY PER TEST
   ========================= */
static tree newNode(int v) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) { perror("malloc"); exit(1); }
    n->v = v;
    n->left = n->right = NULL;
    return n;
}

static void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

static int isLeaf(tree t) {
    return t && t->left == NULL && t->right == NULL;
}

static void stampaPreorder(tree t) {
    if (!t) { printf("NULL "); return; }
    printf("%d ", t->v);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

/* stampa valore+indirizzo e indica se foglia (debug) */
static void stampaPreorderAddr(tree t) {
    if (!t) { printf("NULL "); return; }
    printf("(%d@%p%s) ", t->v, (void*)t, isLeaf(t) ? ",leaf" : "");
    stampaPreorderAddr(t->left);
    stampaPreorderAddr(t->right);
}

/* =========================
   MAIN DI TEST
   ========================= */
int depth(tree albero);
int wrapper(tree albero, int K);
int main(void) {
    /*
            5
          /   \
         3     8
        / \   / \
       2   4 7   1
          /     /
         6     9

    Foglie: 2, 6, 7, 9
    Esempi di camminate a salti (da un nodo qualunque a foglia):
    - salti di 1 livello: X->figlio
    - salti di 2 livelli: X->nipote (LL, LR, RL, RR)
      con vincolo: NON due salti da 2 consecutivi
    */
    tree T = newNode(5);
    T->left = newNode(3);
    T->right = newNode(8);

    T->left->left = newNode(2);
    T->left->right = newNode(4);
    T->right->left = newNode(7);
    T->right->right = newNode(1);

    T->left->right->left = newNode(6);
    T->right->right->left = newNode(9);

    printf("Albero (preorder): ");
    stampaPreorder(T);
    printf("\n");

    printf("Albero (preorder con indirizzi): ");
    stampaPreorderAddr(T);
    printf("\n\n");
    /* TEST K */
    int Ks[] = { 2, 3, 5, 7, 10 };
    int nk = (int)(sizeof(Ks) / sizeof(Ks[0]));

    for (int i = 0; i < nk; i++) {
        int K = Ks[i];
        int ris = esisteCamminataBuona(T, K);
        printf("esisteCamminataBuona(T, K=%d) = %d\n", K, ris);
    }

    freeTree(T);
    return 0;
}

/* =========================
   PLACEHOLDER (così compila)
   ========================= */
int esisteCamminataBuona(tree T, int K) {
    return wrapper(T, K);
}

int f(tree albero, int somma, int K, int lastDouble)
    {
       if(albero==NULL)
           return 0;
        somma=somma+albero->v;
        if(albero->left==NULL && albero->right==NULL)
            return ((somma)%K==0);
        if(f(albero->left, somma, K, 0)) return 1;
        if(f(albero->right,somma, K, 0)) return 1;
        
        if(lastDouble==1)
            {
                if(!albero->left)
                    {
                        if(f(albero->left->left, somma, K, 1)) return 1;
                        if(f(albero->left->right, somma, K, 1)) return 1;
                    }
                if(!albero->right)
                    {
                        if(f(albero->right->left, somma, K, 1)) return 1;
                        if(f(albero->right->right, somma, K, 1)) return 1;
                    }
            }
    return 0;
    }
int wrapper(tree albero, int K)
    {
        if(albero==NULL)
            return 0;
        if(f(albero, 0, K, 0))
            return 1;
    return wrapper(albero->left, K) || wrapper(albero->right, K);
    }
