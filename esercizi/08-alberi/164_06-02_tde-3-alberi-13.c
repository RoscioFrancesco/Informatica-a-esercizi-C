//
//  main.c
//  tde 3 alberi -13
//
//  Created by Francesco Roscio Ricon on 06/02/26.
//


#include <stdio.h>
#include <stdlib.h>

#define N 100

/* =======================
   STRUTTURE DATI (DATE)
   ======================= */
typedef struct ET {
    int dati[N];
    struct ET *left, *right;
} treeNode;

typedef treeNode* tree;

/* =======================
   PROTOTIPO ESERCIZIO
   ======================= */
int f(tree t);   

/* =======================
   UTILITY PER TEST (OK usare cicli qui)
   ======================= */
static tree newNodeWithConst(int value) {
    tree n = (tree)malloc(sizeof(treeNode));
    if (!n) { perror("malloc"); exit(1); }
    for (int i = 0; i < N; i++) n->dati[i] = value;  /* array pieno di value */
    n->left = n->right = NULL;
    return n;
}

static tree newNodeWithFirstK(int k, int base) {
    /* primi k elementi: base, base+1, ...; resto 0 */
    tree n = (tree)malloc(sizeof(treeNode));
    if (!n) { perror("malloc"); exit(1); }
    for (int i = 0; i < N; i++) n->dati[i] = 0;
    for (int i = 0; i < k && i < N; i++) n->dati[i] = base + i;
    n->left = n->right = NULL;
    return n;
}

static double mediaArray(const int a[N]) {
    long long s = 0;
    for (int i = 0; i < N; i++) s += a[i];
    return (double)s / (double)N;
}

static void stampaNodo(tree t, const char *label) {
    if (!t) {
        printf("%s: NULL\n", label);
        return;
    }
    printf("%s: media = %.2f (primi 10: ", label, mediaArray(t->dati));
    for (int i = 0; i < 10; i++) printf("%d%s", t->dati[i], (i==9?")\n":" "));
}

static void stampaAlberoPreorder(tree t, int depth) {
    if (!t) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("- nodo (media=%.2f)\n", mediaArray(t->dati));
    stampaAlberoPreorder(t->left, depth + 1);
    stampaAlberoPreorder(t->right, depth + 1);
}

static void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =======================
   MAIN DI TEST
   ======================= */
int main(void) {
    /*
      Costruiamo un albero di esempio.

              root
             /    \
          sx        dx
         /  \      /  \
       ...  ...  ...  ...

      L'esercizio chiede: esistono almeno due figli dello stesso padre
      (fratelli) con la STESSA media dei rispettivi array?
    */

    tree root = newNodeWithConst(1);

    
    root->left  = newNodeWithConst(5);
    root->right = newNodeWithConst(5);

    /* Aggiungo altri nodi giusto per avere un albero non banale */
    root->left->left   = newNodeWithFirstK(5, 10);
    root->left->right  = newNodeWithConst(0);
    root->right->left  = newNodeWithFirstK(3, 7);
    root->right->right = newNodeWithConst(2);

    printf("=== STAMPA ALBERO (preorder) ===\n");
    stampaAlberoPreorder(root, 0);

    printf("\n=== ESEMPI DI NODI ===\n");
    stampaNodo(root, "root");
    stampaNodo(root->left, "root->left");
    stampaNodo(root->right, "root->right");
    printf("\n=== CHIAMATA ALLA FUNZIONE f(t) ===\n");
    int esito = f(root);   
    printf("f(root) = %d\n", esito);

    freeTree(root);
    return 0;
}




int  f(tree t)
    {
        if(t==NULL)
            return 0;
        int sx=0;
        int dx=0;
        if(t->left!=NULL && t->right!=NULL && mediaArray(t->left->dati)==mediaArray(t->right->dati))
            return 1;
        if(t->left!=NULL)
            {
                sx=f(t->left);
            }
        if(t->right!=NULL)
            {
                dx=f(t->right);
            }
        return sx|| dx;
    }
