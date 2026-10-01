//  Created by Francesco Roscio Ricon on 11/02/26.

#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int v;
    struct node *left, *right;
} Node;

typedef Node *Tree;

int esisteFirma(Tree t, int K);

static Tree newNode(int v) {
    Tree n = (Tree)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->v = v;
    n->left = n->right = NULL;
    return n;
}

static void freeTree(Tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

static void stampaPreorder(Tree t) {
    if (!t) { printf("NULL "); return; }
    printf("%d ", t->v);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

/* Stampa valore+indirizzo (utile nei debug) */
static void stampaPreorderAddr(Tree t) {
    if (!t) { printf("NULL "); return; }
    printf("(%d@%p) ", t->v, (void*)t);
    stampaPreorderAddr(t->left);
    stampaPreorderAddr(t->right);
}
int fromhere(Tree t, int stato, int K, int len, int somma);
int main(void) {
    /*
            5
          /   \
         2     7
        / \   / \
       1   4 6   3

    Alcuni percorsi dall’alto verso il basso (lunghezza>=2):
    5->2  firma = 5 - 2 = 3
    5->7  firma = 5 - 7 = -2
    5->2->4 firma = 5 - 2 + 4 = 7
    5->7->6 firma = 5 - 7 + 6 = 4
    5->7->3 firma = 5 - 7 + 3 = 1
    */
    Tree t = newNode(5);
    t->left = newNode(2);
    t->right = newNode(7);
    t->left->left = newNode(1);
    t->left->right = newNode(4);
    t->right->left = newNode(6);
    t->right->right = newNode(3);

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n");

    printf("Albero (preorder con indirizzi): ");
    stampaPreorderAddr(t);
    printf("\n\n");

    int tests[] = {
        3,   /* 1: 5->2 */
        -2,  /* 1: 5->7 */
        7,   /* 1: 5->2->4 */
        4,   /* 1: 5->7->6 */
        1,   /* 1: 5->7->3 */
        5,   /* probabilmente 0 (non basta lunghezza 1) */
        999  /* 0 */
    };
    int nt = (int)(sizeof(tests) / sizeof(tests[0]));

    for (int i = 0; i < nt; i++) {
        int K = tests[i];
        int ris = esisteFirma(t, K);
        printf("esisteFirma(t, K=%d) = %d\n", K, ris);
    }

    freeTree(t);
    return 0;
}


int esisteFirma(Tree t, int K) {
        if(t==NULL)
            return 0;
        if(fromhere(t, 1, K, 1, 0))
            return 1;
    return esisteFirma(t->left, K) || esisteFirma(t->right, K);
}
int fromhere(Tree t, int stato, int K, int len, int somma) // stato=1 sommo, altirmenti sottraggo
    {
        if(t==NULL)
            return 0;
        somma=somma+(stato)*t->v;
        if(somma==K && len>=2)
            return 1;
        int sx=0;
        int dx=0;
        if(t->left!=NULL)
            sx=fromhere(t->left, -stato, K, len+1, somma);
        if(t->right!=NULL)
            dx=fromhere(t->right, -stato, K, len+1, somma);
        return sx||dx;
    }
