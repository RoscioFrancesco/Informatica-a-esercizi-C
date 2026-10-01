//
//  main.c
//  tde liste alberi 4-14
//
//  Created by Francesco Roscio Ricon on 05/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct n {
    int dato;
    struct n *left;
    struct n *right;
} Node;

typedef Node* Tree;

/* =========================
   PROTOTIPO DELLA FUNZIONE
   ========================= */
float media(Tree t);   /* DA SVOLGERE */

/* =========================
   FUNZIONI DI SUPPORTO
   (solo per il main)
   ========================= */
Tree newNode(int val, Tree sx, Tree dx) {
    Tree n = (Tree)malloc(sizeof(Node));
    n->dato = val;
    n->left = sx;
    n->right = dx;
    return n;
}

/* =========================
   MAIN DI TEST
   ========================= */
float media(Tree albero);
void dati_interni(Tree albero, float *somma, float *count);
int èinterno(Tree albero);
int main() {
    /*
           10
          /  \
         5    20
             /  \
            15   30

       Foglie: 5, 15, 30
       Media attesa: (5 + 15 + 30) / 3
    */

    Tree t = newNode(10,
                newNode(5, NULL, NULL),
                newNode(20,
                    newNode(15, NULL, NULL),
                    newNode(30, NULL, NULL)
                )
            );

    float m = media(t);

    printf("Media dei valori nei nodi foglia: %.2f\n", m);

    return 0;
}
int èinterno(Tree albero)
    {
        if(albero==NULL)
            return 0;
        if(albero->left==NULL && albero->right==NULL)
            return 0;
    return 1;
    }
void dati_interni(Tree albero, float *somma, float *count)
    {
        if(albero==NULL)
            return;
        if(èinterno(albero)==0)
            {
                *somma=*somma+albero->dato;
                (*count)++;
            }
    dati_interni(albero->left, somma, count);
    dati_interni(albero->right, somma, count);
    }
float media(Tree albero)
    {
    float somma=0;
    float count=0;
    dati_interni(albero, &somma, &count);
    return somma/count;
    }
