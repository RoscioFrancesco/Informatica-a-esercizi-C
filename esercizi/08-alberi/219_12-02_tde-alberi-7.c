//  Created by Francesco Roscio Ricon on 12/02/26.
#include <stdio.h>
#include <stdlib.h>

/* ====== Strutture date dal testo ====== */
typedef struct nodeS {
    int val;
    struct nodeS *left, *right;
} node;

typedef node* tree;

/* ====== Utility ====== */
int isEven(int x) {
    return (x % 2 == 0);
}

tree newNode(int v) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) {
        printf("Errore malloc\n");
        exit(1);
    }
    n->val = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}


/* ====== MAIN DI TEST + PRINTF ====== */
int f(tree albero, int prec);
int main(void) {
    /* Costruisco un albero di esempio:

              4
            /   \
           7     6
          / \     \
         2   9     5

       Percorso valido: 4(pari) -> 7(dispari) -> 2(pari)  => alterna ✓
       Anche:          4(pari) -> 6(pari) -> 5(dispari)   => NON alterna (4->6) ✗
    */
    tree T = newNode(4);
    T->left = newNode(7);
    T->right = newNode(6);
    T->left->left = newNode(2);
    T->left->right = newNode(9);
    T->right->right = newNode(5);

    int ris = f(T->left, T->val)|| f(T->right, T->val);
    printf("%d", ris);
}
int èpari(int x)
    {
        if(x%2==0)
            return 1;
        return 0;
    }
int f(tree albero, int prec)
    {
        if(albero==NULL)
            return 0;
    if(èpari(prec)==èpari(albero->val))
        return 0;
    if(albero->left==NULL && albero->right==NULL)
        return 1;
    int sx=0;
    int dx=0;
    if(albero->left!=NULL)
        sx=f(albero->left, albero->val);
    if(albero->right!=NULL)
        dx=f(albero->right, albero->val);
    return sx||dx;
    }
