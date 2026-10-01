//
//  main.c
//  albero chat albero 7 -18
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

void stampaPreorder(Albero t) {
    if (t == NULL) return;
    printf("%d ", t->val);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

void freeTree(Albero t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =======================
   UTILITY: PRIMO
   ======================= */

int isPrime(int x) {
    if (x < 2) return 0;
    if (x == 2) return 1;
    if (x % 2 == 0) return 0;
    for (int d = 3; d * d <= x; d += 2) {
        if (x % d == 0) return 0;
    }
    return 1;
}

/* =======================
   ESERCIZIO 1A
   ======================= */

int cammino(Albero tree, int count_primi, int somma);
int isPrime(int x);
int esisteCammino(Albero t) {
    return cammino(t, 0, 0);
}

/* =======================
   MAIN DI TEST
   ======================= */

int main(void) {
    /*
        Costruiamo un albero con almeno un cammino valido.

                    10
                  /    \
                 11     12
                /  \      \
               14  13      20
              /          /   \
             17         21    22

      Cammini radice->foglia:
      10-11-14-17   (crescente: sì) somma=52 pari, primi: 11 e 17 => 2 primi  ✅ VALIDO
      10-11-13      (crescente: sì) somma=34 pari, primi: 11 e 13 => 2 primi  ✅ valido (anche questo)
      10-12-20-21   (crescente: sì) somma=63 dispari => NO
      10-12-20-22   (crescente: sì) somma=64 pari, primi: nessuno => NO (0 primi)

      Quindi deve stampare: SI
    */

    Albero t =
        newNode(10,
            newNode(11,
                newNode(14,
                    newNode(17, NULL, NULL),
                    NULL
                ),
                newNode(13, NULL, NULL)
            ),
            newNode(12,
                NULL,
                newNode(20,
                    newNode(21, NULL, NULL),
                    newNode(22, NULL, NULL)
                )
            )
        );

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n");

    int ok = esisteCammino(t);

    printf("Esiste cammino radice->foglia crescente con somma pari e 2 primi? %s\n",
           ok ? "SI" : "NO");

    freeTree(t);
    return 0;
}

/* =======================
   SOLUZIONE (DA SCRIVERE)
   ======================= */

int èprimo(int x)
    {
    int i=x-1;
        while(i>0)
            {
                if(x%i==0)
                    return 0;
            }
        return 1;
    }
/*
  Ritorna 1 se esiste un cammino radice->foglia tale che:
  - è strettamente crescente (ogni figlio sul cammino > padre)
  - la somma dei valori sul cammino è pari
  - il numero di valori primi sul cammino è esattamente 2
*/
int cammino(Albero tree, int count_primi, int somma)
    {
        if(tree==NULL)
            return 0;
        if(isPrime(tree->val))
            count_primi++;
        somma=somma+tree->val;
        if(tree->left==NULL && tree->right==NULL)
            {
                if(somma%2==0 && count_primi==2)
                    return 1;
                return 0;
            }
        int sx=0;
        int dx=0;
        if(tree->left!=NULL && tree->left->val>tree->val)
            sx=cammino(tree->left, count_primi, somma);
        if(tree->right!=NULL && tree->right->val>tree->val)
            dx=cammino(tree->right, count_primi, somma);
    return sx || dx;
    }
