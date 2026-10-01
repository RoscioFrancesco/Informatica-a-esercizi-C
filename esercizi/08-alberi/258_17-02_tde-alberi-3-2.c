//
//  main.c
//  tde alberi 3  -2
//
//  Created by Francesco Roscio Ricon on 17/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct ET {
    int dato;
    struct ET *left, *center, *right;
} treeNode;

typedef treeNode *tree;

int cerca(tree t, int totale);

tree newNode(int x) {
    tree n = (tree)malloc(sizeof(treeNode));
    if (!n) {
        printf("Errore malloc\n");
        exit(1);
    }
    n->dato = x;
    n->left = n->center = n->right = NULL;
    return n;
}

void printPreorder(tree t) {
    if (t == NULL) return;
    printf("%d ", t->dato);
    printPreorder(t->left);
    printPreorder(t->center);
    printPreorder(t->right);
}

void freeTree(tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->center);
    freeTree(t->right);
    free(t);
}
void f(tree albero, int somma, int tot, int *count);
int main(void) {

    /* -------- TEST TREE 1 --------
            5
         /  |  \
        3   4   2
       / \       \
      7   1       8

      Cammini radice->foglia e somme:
      5-3-7 = 15
      5-3-1 = 9
      5-4   = 9
      5-2-8 = 15
    */
    tree T1 = newNode(5);
    T1->left = newNode(3);
    T1->center = newNode(4);
    T1->right = newNode(2);
    T1->left->left = newNode(7);
    T1->left->center = newNode(1);
    T1->right->right = newNode(8);

    printf("T1 preorder: ");
    printPreorder(T1);
    printf("\n");

    printf("cerca(T1, 15) = %d\n", cerca(T1, 15));
    printf("cerca(T1,  9) = %d\n", cerca(T1,  9));
    printf("cerca(T1, 10) = %d\n", cerca(T1, 10));

    printf("\n");

    /* -------- TEST TREE 2 --------
            1
          / | \
         2  3  4

      Cammini e somme:
      1-2 = 3
      1-3 = 4
      1-4 = 5

      Per totale=4 esiste UN SOLO cammino -> deve tornare 0 (non "almeno due").
    */
    tree T2 = newNode(1);
    T2->left = newNode(2);
    T2->center = newNode(3);
    T2->right = newNode(4);

    printf("T2 preorder: ");
    printPreorder(T2);
    printf("\n");

    printf("cerca(T2, 4) = %d\n", cerca(T2, 4));
    printf("cerca(T2, 3) = %d\n", cerca(T2, 3));
    printf("cerca(T2, 7) = %d\n", cerca(T2, 7));

    /* cleanup */
    freeTree(T1);
    freeTree(T2);

    return 0;
}


void f(tree albero, int somma, int tot, int *count)
    {
        if(albero==NULL)
            return;
        somma=somma+albero->dato;
        if(albero->center==NULL && albero->right==NULL && albero->left==NULL)
            {
                if(somma==tot)
                    {
                        (*count)++;
                    }
            }
    f(albero->center, somma, tot, count);
    f(albero->left, somma, tot, count);
    f(albero->right, somma, tot, count);
    }
int cerca(tree t, int totale)
    {
    int count=0;
    f(t, 0, totale, &count);
    if(count>=2)
        return 1;
    return 0;
    }
