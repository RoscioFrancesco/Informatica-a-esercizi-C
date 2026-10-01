//
//  main.c
//  alberi es 9 b chat
//
//  Created by Francesco Roscio Ricon on 30/01/26.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* =======================
   STRUTTURE DATI
   ======================= */

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

typedef Node* Albero;



/* Utility per costruire alberi nei test */
Node* newNode(int v, Node* l, Node* r);

/* Utility per liberare memoria (ricorsiva, no cicli) */
void freeTree(Albero t);
bool sommaAlternata(Albero t);
int f(Albero t, int somma, int exp) ;
int main(void)
{
    /*
      ESEMPIO 1 (atteso TRUE)
               5
             /   \
           -8     -7
           /        \
          2          3

      Cammini:
      5, -8, 2:
        S0 = 5   ( + )
        S1 = -3  ( - )  alterna
        S2 = -1  ( - )  <-- qui NON alterna (da - a -) ... aspetta!
      Questo esempio così NON va bene per TRUE.

      Costruiamo invece:
               5
             /   \
           -9     -7
           /        \
          4          3

      Cammino sinistro: 5, -9, 4
        S0 = 5   (+)
        S1 = -4  (-) alterna
        S2 = 0   (0) -> VIOLA (0 non è né + né -)

      Ok, allora facciamo un vero TRUE:
               4
             /   \
           -7     -6
           /        \
          5          1

      Cammino sinistro: 4, -7, 5
        S0=4 (+), S1=-3 (-), S2=2 (+)  alterna OK
      Cammino destro: 4, -6, 1
        S0=4 (+), S1=-2 (-), S2=-1 (-) NON alterna

      Serve che anche il destro alterni:
               4
             /   \
           -7     -6
           /        \
          5          3

      Destro: 4, -6, 3 => S0=4(+), S1=-2(-), S2=1(+) OK
    */
    Albero t1 =
        newNode(4,
            newNode(-7,
                newNode(5, NULL, NULL),
                NULL
            ),
            newNode(-6,
                NULL,
                newNode(3, NULL, NULL)
            )
        );

    printf("ESEMPIO 1 (atteso TRUE):  %s\n", sommaAlternata(t1) ? "TRUE" : "FALSE");
    freeTree(t1);

    /*
      ESEMPIO 2 (atteso FALSE: un cammino viola)
               4
             /   \
           -7     -6
           /        \
          5          1

      Cammino destro: 4, -6, 1
        S0=4(+), S1=-2(-), S2=-1(-)  -> NON alterna => FALSE
    */
    Albero t2 =
        newNode(4,
            newNode(-7,
                newNode(5, NULL, NULL),
                NULL
            ),
            newNode(-6,
                NULL,
                newNode(1, NULL, NULL)
            )
        );

    printf("\nESEMPIO 2 (atteso FALSE): %s\n", sommaAlternata(t2) ? "TRUE" : "FALSE");
    freeTree(t2);

    /*
      ESEMPIO 3 (atteso FALSE: somma parziale 0)
               2
             /
           -2
           /
          5

      Cammino: 2, -2, 5
        S0=2(+)
        S1=0(0) -> viola subito
    */
    Albero t3 =
        newNode(2,
            newNode(-2,
                newNode(5, NULL, NULL),
                NULL
            ),
            NULL
        );

    printf("\nESEMPIO 3 (atteso FALSE): %s\n", sommaAlternata(t3) ? "TRUE" : "FALSE");
    freeTree(t3);

    /*
      ESEMPIO 4 (atteso TRUE: albero con una sola foglia)
          -3

      Cammino: -3
        S0=-3 (negativa) -> ok
    */
    Albero t4 = newNode(-3, NULL, NULL);
    printf("\nESEMPIO 4 (atteso TRUE):  %s\n", sommaAlternata(t4) ? "TRUE" : "FALSE");
    freeTree(t4);

    return 0;
}
/*
  ESERCIZIO 9 - Albero con somma alternata

  Wrapper:
  ritorna true se e solo se lungo OGNI cammino radice-foglia
  la somma parziale alterna segno (+/-) a ogni livello.
*/
int f(Albero t, int somma, int exp) // exp=1 mi aspetto una somma positiva, -1 mi aspetto somma negativa
    {
        if(t==NULL)
            return 1;
        somma=somma+t->val;
        if(exp*somma<=0)
            return 0;
        int new_exp=-exp;
        return f(t->left, somma, new_exp) && f(t->right, somma, new_exp);
    }
bool sommaAlternata(Albero t)
    {
    return f(t,0, 1)|| f(t, 0, -1);
    }
Node* newNode(int v, Node* l, Node* r)
{
    Node* n = (Node*)malloc(sizeof(*n));
    n->val = v;
    n->left = l;
    n->right = r;
    return n;
}

void freeTree(Albero t)
{
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}
