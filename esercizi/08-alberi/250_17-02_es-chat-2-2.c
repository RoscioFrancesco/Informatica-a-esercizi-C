//
//  main.c
//  es chat 2  -2
//
//  Created by Francesco Roscio Ricon on 17/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA ALBERO BINARIO
   ========================= */
typedef struct node {
    int v;
    struct node *left, *right;
} node;

typedef node* tree;


int contaDominanti(tree T);

/* =========================
   FUNZIONI DI SUPPORTO
   ========================= */
tree newNode(int x) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) {
        printf("Errore malloc\n");
        exit(1);
    }
    n->v = x;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void printPreorder(tree T) {
    if (T == NULL) return;
    printf("%d ", T->v);
    printPreorder(T->left);
    printPreorder(T->right);
}

void freeTree(tree T) {
    if (T == NULL) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {

    /* =====================================
       TEST 1

               10
              /  \
             5    3
            / \
           2   1

       Somme:
       nodo 5:
           left = 2
           right = 1
           2 > 1  → dominante ✔

       nodo 10:
           left subtree = 5+2+1 = 8
           right subtree = 3
           8 > 3 → dominante ✔

       nodo 3,2,1:
           NON contano (non hanno entrambi i figli)

       Dominanti attesi: 2
       ===================================== */

    tree T1 = newNode(10);
    T1->left = newNode(5);
    T1->right = newNode(3);
    T1->left->left = newNode(2);
    T1->left->right = newNode(1);

    printf("=== TEST 1 ===\n");
    printf("Preorder: ");
    printPreorder(T1);
    printf("\n");

    int d1 = contaDominanti(T1);
    printf("Dominanti: %d\n\n", d1);



    /* =====================================
       TEST 2

               8
              / \
             4   6
                / \
               1   2

       nodo 6:
           left = 1
           right = 2
           1 > 2? NO

       nodo 8:
           left subtree = 4
           right subtree = 6+1+2 = 9
           4 > 9? NO

       Nessun dominante.

       Atteso: 0
       ===================================== */

    tree T2 = newNode(8);
    T2->left = newNode(4);
    T2->right = newNode(6);
    T2->right->left = newNode(1);
    T2->right->right = newNode(2);

    printf("=== TEST 2 ===\n");
    printf("Preorder: ");
    printPreorder(T2);
    printf("\n");

    int d2 = contaDominanti(T2);
    printf("Dominanti: %d\n\n", d2);



    /* =====================================
       TEST 3 (caso limite)

               5
              / \
             2   2

       nodo 5:
           left = 2
           right = 2
           2 > 2? NO (non strettamente)

       Atteso: 0
       ===================================== */

    tree T3 = newNode(5);
    T3->left = newNode(2);
    T3->right = newNode(2);

    printf("=== TEST 3 ===\n");
    printf("Preorder: ");
    printPreorder(T3);
    printf("\n");

    int d3 = contaDominanti(T3);
    printf("Dominanti: %d\n\n", d3);


    /* cleanup */
    freeTree(T1);
    freeTree(T2);
    freeTree(T3);

    return 0;
}
//Un nodo è “dominante” se: la somma dei valori nel suo sottoalbero sinistro è strettamente maggiore della somma nel suo sottoalbero destro
int sommavalori(tree t)
    {
        if(t==NULL)
            return 0;
    return t->v+sommavalori(t->right)+sommavalori(t->left);
    }
void f(tree t, int *count)
    {
        if(t==NULL)
            return;
    int sx=sommavalori(t->left);
    int dx=sommavalori(t->right);
    if(sx>dx)
        {
            (*count)++;
        }
    f(t->left, count);
    f(t->right, count);
    }
int contaDominanti(tree T)
    {
    int count=0;
    f(T, &count);
    return count;
    }
