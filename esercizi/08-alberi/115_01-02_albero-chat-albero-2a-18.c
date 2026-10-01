//
//  main.c
//  albero chat albero 2A -18
//
//  Created by Francesco Roscio Ricon on 01/02/26.
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

typedef Node* Albero;

/* =======================
   UTILITY
   ======================= */

static Node* newNode(int v, Node* l, Node* r) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->val = v;
    n->left = l;
    n->right = r;
    return n;
}

static void stampaPreorder(Albero t) {
    if (t == NULL) return;
    printf("%d ", t->val);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

static void freeTree(Albero t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =======================
   PROTOTIPI ESERCIZIO
   ======================= */

/*
  violazioni = quante violazioni della crescita sono già state usate (0 o 1)
  somma = somma dei valori sul cammino
*/
int cammino(Albero tree, int somma, int count);

int esisteCammino(Albero t) {
    return cammino(t, 0, 0);
}

/* =======================
   MAIN DI TEST
   ======================= */

int main(void) {
    /*
            10
           /  \
          12   9
         / \    \
        13  8    15
               /
              14

      Cammini radice->foglia:

      10-12-13     (crescente, somma=35 -> NO)
      10-12-8      (violazione: 8<12, una sola, somma=30 -> multipla di 3 -> OK)
      10-9-15-14   (violazione: 9<10, una sola, ma 14<15 seconda violazione -> NO)

      Esiste quindi un cammino valido -> SI
    */

    Albero t =
        newNode(10,
            newNode(12,
                newNode(13, NULL, NULL),
                newNode(8, NULL, NULL)
            ),
            newNode(9,
                NULL,
                newNode(15,
                    newNode(14, NULL, NULL),
                    NULL
                )
            )
        );

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n");

    int ok = esisteCammino(t);

    printf("Esiste cammino quasi-crescente (max 1 violazione)\n");
    printf("con somma multipla di 3? %s\n", ok ? "SI" : "NO");

    freeTree(t);
    return 0;
}

/* =======================
   FUNZIONE DA SVOLGERE
   ======================= */


int cammino(Albero tree, int somma, int count)
    {
        if(tree==NULL)
            return 0;
    somma=somma+tree->val;
    int sx=0;
    int dx=0;
    if(tree->left!=NULL)
    {
        if(tree->left->val>tree->val)
        {
            sx=cammino(tree->left, somma, count);
        }
        else
            sx=cammino(tree->left, somma, count+1);
    }
    if(tree->right!=NULL)
    {
        if(tree->right->val>tree->val)
        {
            dx=cammino(tree->right, somma, count);
        }
        else
            dx=cammino(tree->right, somma, count+1);
    }
    if(tree->left==NULL && tree->right==NULL)
        {
            if(somma%3==0 && count<=1)
                return 1;
            return 0;
        }
    return sx||dx;
    }
