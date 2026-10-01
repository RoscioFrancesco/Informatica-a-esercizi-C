//
//  main.c
//  albero chat es1
//
//  Created by Francesco Roscio Ricon on 31/01/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =======================
   STRUTTURE DATI
   ======================= */

typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;

typedef Node* Tree;

/* =======================
   FUNZIONI DI SUPPORTO
   ======================= */

/* crea un nuovo nodo */
Tree newNode(int val, Tree left, Tree right) {
    Tree t = (Tree)malloc(sizeof(Node));
    t->val = val;
    t->left = left;
    t->right = right;
    return t;
}



/*
   Un albero è lionesE se:
   - tutti i figli sinistri hanno valore DISPARI
   - tutti i figli destri hanno valore PARI
   - la radice può avere qualsiasi valore
*/
int lionese(Tree albero);
int unità(Tree albero);
/* =======================
   MAIN DI TEST
   ======================= */

int main() {

    /* Albero lionesE (atteso: 1)
            10
           /  \
          3    8
         /    / \
        5    6   4
    */
    Tree t1 = newNode(10,
                newNode(3,
                    newNode(5, NULL, NULL),
                    NULL),
                newNode(8,
                    newNode(6, NULL, NULL),
                    newNode(4, NULL, NULL))
            );

    /* Albero NON lionesE (atteso: 0)
            7
           / \
          4   9
    */
    Tree t2 = newNode(7,
                newNode(4, NULL, NULL),
                newNode(9, NULL, NULL)
            );

    /* Albero con sola radice (atteso: 1)
            42
    */
    Tree t3 = newNode(42, NULL, NULL);

    /* Albero con errore profondo (atteso: 0)
            10
           /  \
          3    8
           \
            4
    */
    Tree t4 = newNode(10,
                newNode(3,
                    NULL,
                    newNode(4, NULL, NULL)),
                newNode(8, NULL, NULL)
            );

    printf("t1 (atteso 1): %d\n", lionese(t1));
    printf("t2 (atteso 0): %d\n", lionese(t2));
    printf("t3 (atteso 1): %d\n", lionese(t3));
    printf("t4 (atteso 0): %d\n", lionese(t4));

    return 0;
}

int èpari(int a)
    {
        if(a%2==0)
            return 1;
    return 0;
    }
int verifica(Tree albero, int padre) // 1 padre ari, 0 padre dispari
    {
        if(albero==NULL)
            return 1;
        int sx=1;
        int dx=1;
        if(albero->left!=NULL)
            {
                if(èpari(albero->left->val)!=padre)
                    sx=0;
            }
        if(albero->right!=NULL)
            {
                if(èpari(albero->right->val)!=padre)
                    dx=0;
            }
        if(sx&&dx)
            {
                return verifica(albero->left, padre) && verifica(albero->right, padre);
            }
        return 0;
    }
int lionese(Tree albero)
    {
        if(albero==NULL)
            return 1;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
        if(albero->left->val%2==1 && albero->right->val%2==0)
            return verifica(albero->left, 0)  && verifica(albero->right, 1);
        else
            return 0;
    }
