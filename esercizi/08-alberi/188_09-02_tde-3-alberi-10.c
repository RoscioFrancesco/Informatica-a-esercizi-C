//  Created by Francesco Roscio Ricon on 09/02/26.

#include <stdio.h>
#include <stdlib.h>

/* =====================
   STRUTTURE DATI (corrette)
   ===================== */
typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node *tree;

/* =====================
   PROTOTIPO FUNZIONE (DA SVOLGERE)
   ===================== */
int f(tree t);

/* =====================
   UTILITY PER TEST
   ===================== */
static tree nuovoNodo(int v) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

static void stampaPreorder(tree t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }
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

/* =====================
   MAIN DI TEST
   ===================== */
void funzica(tree albero, int *somma_interni, int *somma_foglie);
int main() {
    /* Albero 1 (esempio)
           5
          / \
         2   7
        / \   \
       4   6   8

       NODI INTERNI: 5,2,7  -> dispari interni = 5+7 = 12
       FOGLIE: 4,6,8        -> pari foglie = 4+6+8 = 18
       quindi dovrebbe tornare 0 (se interpretazione standard)
    */
    tree t1 = nuovoNodo(5);
    t1->left = nuovoNodo(2);
    t1->right = nuovoNodo(7);
    t1->left->left = nuovoNodo(4);
    t1->left->right = nuovoNodo(6);
    t1->right->right = nuovoNodo(8);

    printf("Albero t1 (preorder): ");
    stampaPreorder(t1);
    printf("\n");
    printf("f(t1) = %d\n\n", f(t1));

    /* Albero 2 (più piccolo)
           9
          / \
         2   3

       INTERNI: 9 (dispari) -> 9
       FOGLIE: 2 (pari), 3 (dispari) -> pari foglie = 2
       quindi dovrebbe tornare 0
    */
    tree t2 = nuovoNodo(9);
    t2->left = nuovoNodo(2);
    t2->right = nuovoNodo(3);

    printf("Albero t2 (preorder): ");
    stampaPreorder(t2);
    printf("\n");
    printf("f(t2) = %d\n\n", f(t2));

    freeTree(t1);
    freeTree(t2);
    return 0;
}

/* =====================
   STUB (NON SVOLTO)
   ===================== */
int f(tree t) {
    int interni=0;
    int foglie=0;
    funzica(t, &interni, &foglie);
    if(interni==foglie)
        return 1;
    return 0;
}
int èfoglia(tree albero)
    {
        if(albero->left==NULL && albero->right==NULL)
            return 1;
        return 0;
    }

void funzica(tree albero, int *somma_interni, int *somma_foglie)
    {
        if(albero==NULL)
            return;
        if(èfoglia(albero) && albero->dato%2==0)
            *somma_foglie=*somma_foglie+albero->dato;
        if(èfoglia(albero)==0 && albero->dato%2==1)
            *somma_interni=*somma_interni+albero->dato;
    funzica(albero->left, somma_interni, somma_foglie);
    funzica(albero->right, somma_interni, somma_foglie);
    }

