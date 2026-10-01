//
//  main.c
//  tde 1 es 3 -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node* tree;

int alberiIdentici(tree t1, tree t2);

tree creaNodo(int x) {
    tree n = (tree)malloc(sizeof(node));
    n->dato = x;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void stampaPreOrder(tree t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }

    printf("%d ", t->dato);
    stampaPreOrder(t->left);
    stampaPreOrder(t->right);
}

int main() {

    tree A1 = creaNodo(1);
    A1->left = creaNodo(2);
    A1->right = creaNodo(3);

    tree A2 = creaNodo(1);
    A2->left = creaNodo(2);
    A2->right = creaNodo(3);

    printf("=== TEST 1 ===\n");
    printf("Albero 1 (preorder): ");
    stampaPreOrder(A1);
    printf("\n");

    printf("Albero 2 (preorder): ");
    stampaPreOrder(A2);
    printf("\n");

    printf("Identici? %d\n\n", alberiIdentici(A1, A2));


    /* ===== TEST 2: stessa forma, valore diverso ===== */

    tree B1 = creaNodo(1);
    B1->left = creaNodo(2);
    B1->right = creaNodo(3);

    tree B2 = creaNodo(1);
    B2->left = creaNodo(2);
    B2->right = creaNodo(4);  // diverso

    printf("=== TEST 2 ===\n");
    printf("Albero 1 (preorder): ");
    stampaPreOrder(B1);
    printf("\n");

    printf("Albero 2 (preorder): ");
    stampaPreOrder(B2);
    printf("\n");

    printf("Identici? %d\n\n", alberiIdentici(B1, B2));


    /* ===== TEST 3: stessa valori ma struttura diversa ===== */

    tree C1 = creaNodo(1);
    C1->left = creaNodo(2);
    C1->left->left = creaNodo(3);

    tree C2 = creaNodo(1);
    C2->right = creaNodo(2);
    C2->right->right = creaNodo(3);

    printf("=== TEST 3 ===\n");
    printf("Albero 1 (preorder): ");
    stampaPreOrder(C1);
    printf("\n");

    printf("Albero 2 (preorder): ");
    stampaPreOrder(C2);
    printf("\n");

    printf("Identici? %d\n\n", alberiIdentici(C1, C2));


    /* ===== TEST 4: entrambi NULL ===== */

    tree D1 = NULL;
    tree D2 = NULL;

    printf("=== TEST 4 ===\n");
    printf("Albero 1: NULL\n");
    printf("Albero 2: NULL\n");
    printf("Identici? %d\n\n", alberiIdentici(D1, D2));

    return 0;
}


int alberiIdentici(tree t1, tree t2)
    {
        if(t1==NULL && t2==NULL)
            return 1;
        if(t1==NULL || t2==NULL)
            return 0;
        if(t1->dato!=t2->dato)
            return 0;
    return alberiIdentici(t1->left, t2->left) && alberiIdentici(t1->right, t2->right);
    }
