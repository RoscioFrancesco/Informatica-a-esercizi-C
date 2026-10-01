//
//  main.c
//  albero chat albero 4A  -17
//
//  Created by Francesco Roscio Ricon on 02/02/26.
//
#include <stdio.h>
#include <stdlib.h>
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
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->left = l;
    n->right = r;
    return n;
}

static void stampaPreorder(Albero t) {
    if (!t) return;
    printf("%d ", t->val);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

static void freeTree(Albero t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =======================
   PROTOTIPI ESERCIZIO
   ======================= */

void f(Albero t, int somma, int *max, int len);
int lunghezzaMax(Albero t) {
    int max=0;
    f(t, 0, &max, 0);
    return max;
}

/* =======================
   MAIN DI TEST
   ======================= */

int main(void) {
    /*
            5
           / \
          7   6
         / \   \
        9   8   10
       /
      12

      Cammini radice->foglia:
      5-7-9-12  (crescente: sì) somma=33 dispari -> NO
      5-7-8     (crescente: sì) somma=20 pari   -> OK (len=3)
      5-6-10    (crescente: sì) somma=21 dispari -> NO

      Risposta attesa: 3
    */

    Albero t =
        newNode(5,
            newNode(7,
                newNode(9,
                    newNode(12, NULL, NULL),
                    NULL
                ),
                newNode(8, NULL, NULL)
            ),
            newNode(6,
                NULL,
                newNode(10, NULL, NULL)
            )
        );

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n");

    int ans = lunghezzaMax(t);

    printf("Lunghezza massima di un cammino radice->foglia crescente con somma pari: %d\n", ans);

    freeTree(t);
    return 0;
}

/* =======================
   FUNZIONE DA SVOLGERE
   ======================= */


void f(Albero t, int somma, int *max, int len)
    {
        if(t==NULL)
            return;
        somma=somma+t->val;
    len++;
        if(t->left!=NULL && t->left->val>t->val)
            f(t->left, somma, max, len);
        if(t->right!=NULL && t->right->val>t->val)
            f(t->right, somma, max, len);
        if(t->left==NULL && t->right==NULL)
        {
            if(somma%2==0 && len>*max)
                {
                    *max=len;
                }
            return;
        }
    }
