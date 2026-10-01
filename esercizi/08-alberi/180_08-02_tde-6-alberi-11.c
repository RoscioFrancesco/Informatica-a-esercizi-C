//  Created by Francesco Roscio Ricon on 08/02/26.
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node * tree;


int verificaProprieta(tree t);

/* =========================
   UTILITY PER CREARE / STAMPARE / LIBERARE
   ========================= */
static tree nuovoNodo(int v) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

static int isFoglia(tree t) {
    return (t != NULL && t->left == NULL && t->right == NULL);
}

static void stampaPreorder(tree t) {
    if (t == NULL) { printf("NULL "); return; }
    printf("%d ", t->dato);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

static void freeTree(tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =========================
   FUNZIONE RICHIESTA (STUB)
   ========================= */
int verificaProprieta(tree t);


/* =========================
   MAIN DI TEST
   ========================= */
int divisore(tree albero, int x);
int f(tree albero);
int main(void) {
    
    tree A = nuovoNodo(3);
    A->left = nuovoNodo(4);
    A->right = nuovoNodo(6);
    A->left->left = nuovoNodo(9);
    A->left->right = nuovoNodo(10);
    A->right->right = nuovoNodo(12);

    /*
      Albero B (altro test, con nodo interno che magari fallisce):
              5
             / \
            2   7
           /
          3
    */
    tree B = nuovoNodo(5);
    B->left = nuovoNodo(2);
    B->right = nuovoNodo(7);
    B->left->left = nuovoNodo(3);
    
    
    tree hc = nuovoNodo(3);
    hc->left = nuovoNodo(6);
    hc->right = nuovoNodo(9);
    
    printf("=== Albero A (preorder) ===\n");
    stampaPreorder(A);
    printf("\n");
    printf("Risultato verificaProprieta(A) = %d\n\n", verificaProprieta(A));

    printf("=== Albero B (preorder) ===\n");
    stampaPreorder(B);
    printf("\n");
    printf("Risultato verificaProprieta(B) = %d\n\n", verificaProprieta(B));

    /* Test limite: albero vuoto */
    tree C = NULL;
    printf("=== Albero C (vuoto) ===\n");
    printf("Risultato verificaProprieta(C) = %d\n\n", verificaProprieta(C));

    
    
    printf("Risultato verificaProprieta(hc) = %d\n\n", verificaProprieta(hc));
    freeTree(A);
    freeTree(B);
    return 0;
}
int divisore(tree albero, int x)
    {
        if(albero==NULL)
            return 0;
        if(albero->dato%x==0)
            return 1;
    return divisore(albero->left, x)|| divisore(albero->right, x);
    }
int verificaProprieta(tree albero)
    {
        if(albero==NULL)
            return 0;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
        if(albero->dato==0)
            return 0;
        if(divisore(albero->left, albero->dato)==0 && divisore(albero->right, albero->dato)==0)
            return 0;
    return verificaProprieta(albero->right)&&verificaProprieta(albero->left);
    }
