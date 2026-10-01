//
//  main.c
//  tde 1 alberi -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int dato;
    struct NO *next;
} nodo;
typedef nodo *lista;

typedef struct EL {
    int dato;
    struct EL *left, *right;
} node;
typedef node *tree;
int f(lista l, tree albero);
/* ====== SUPPORTO: CREAZIONE / STAMPA ====== */
tree newTreeNode(int x) {
    tree t = (tree)malloc(sizeof(node));
    if (!t) exit(1);
    t->dato = x;
    t->left = t->right = NULL;
    return t;
}

lista pushBack(lista L, int x) {
    nodo *n = (nodo*)malloc(sizeof(nodo));
    if (!n) exit(1);
    n->dato = x;
    n->next = NULL;

    if (L == NULL) return n;

    nodo *cur = L;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return L;
}

void printList(lista L) {
    printf("[");
    while (L) {
        printf("%d", L->dato);
        if (L->next) printf(" -> ");
        L = L->next;
    }
    printf("]");
}

void freeList(lista L) {
    while (L) {
        nodo *tmp = L;
        L = L->next;
        free(tmp);
    }
}

void freeTree(tree T) {
    if (!T) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* ====== MAIN DI TEST ====== */
int main(void) {
    /*
            1
          /   \
         2     3
        / \     \
       4   5     6
    Cammini root->leaf:
      1-2-4
      1-2-5
      1-3-6
    */
    tree T = newTreeNode(1);
    T->left = newTreeNode(2);
    T->right = newTreeNode(3);
    T->left->left = newTreeNode(4);
    T->left->right = newTreeNode(5);
    T->right->right = newTreeNode(6);

    lista L1 = NULL; L1 = pushBack(L1,1); L1 = pushBack(L1,2); L1 = pushBack(L1,5);   // match
    lista L2 = NULL; L2 = pushBack(L2,1); L2 = pushBack(L2,3); L2 = pushBack(L2,6);   // match
    lista L3 = NULL; L3 = pushBack(L3,1); L3 = pushBack(L3,2);                         // NON match (non termina in foglia)
    lista L4 = NULL; L4 = pushBack(L4,1); L4 = pushBack(L4,2); L4 = pushBack(L4,7);   // NON match

    lista tests[] = {L1, L2, L3, L4};
    int ntests = 4;

    for (int i = 0; i < ntests; i++) {
        printList(tests[i]);
        printf("  ->  f = %d\n", f(tests[i], T));
    }

    freeList(L1); freeList(L2); freeList(L3); freeList(L4);
    freeTree(T);
    return 0;
}

int f(lista l, tree albero)
    {
        if(albero==NULL && l==NULL)
            return 1;
        if(l==NULL || albero==NULL)
            return 0;
        if(l->dato!=albero->dato)
            return 0;
        l=l->next;
        if(albero->left==NULL && albero->right==NULL && l==NULL)
            return 1;
        int sx=0;
        int dx=0;
        if(albero->left!=NULL)
            {
                sx=f(l, albero->left);
            }
        if(albero->right!=NULL)
            {
                dx=f(l, albero->right);
            }
    return sx || dx;
    }
