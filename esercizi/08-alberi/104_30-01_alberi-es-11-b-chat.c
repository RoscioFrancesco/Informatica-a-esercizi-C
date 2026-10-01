//
//  main.c
//  alberi es 11 b chat
//
//  Created by Francesco Roscio Ricon on 30/01/26.
//


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

/* =======================
   PROTOTIPI
   ======================= */

Node* newNode(int v, Node* l, Node* r);
void freeTree(Albero t);


bool esisteCamminoDiffAlternate(Albero t);

/* helper consigliato:
   - t: nodo corrente
   - prev: valore del nodo precedente nel cammino
   - hasPrev: 0 se non c’è precedente (radice), 1 altrimenti
   - expSign: segno atteso della prossima differenza (+1 o -1); valido solo se hasPrev=1
   - hasExp: 0 se non ho ancora fissato il segno atteso (prima differenza), 1 altrimenti
*/
bool esisteCamminoDiffAlternateRec(Albero t, int prev, int hasPrev, int expSign, int hasExp);

/* =======================
   UTILITY
   ======================= */

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

/* =======================
   MAIN + ESEMPI
   ======================= */
int f(Albero tree, int expect, int prec, int *hasprec);
bool esisteCamminoDiffAlternate(Albero t);
int main(void)
{
    /*
      ESEMPIO 1 (atteso TRUE)
              5
             / \
            7   3
           /     \
          6       4

      Cammino valido: 5 -> 7 -> 6
      diff: +2, -1 (alterna)
      Anche 5 -> 3 -> 4 diff: -2, +1 (alterna)
    */
    Albero t1 =
        newNode(5,
            newNode(7,
                newNode(6, NULL, NULL),
                NULL
            ),
            newNode(3,
                NULL,
                newNode(4, NULL, NULL)
            )
        );

    printf("ESEMPIO 1 (atteso TRUE):  %s\n",
           esisteCamminoDiffAlternate(t1) ? "TRUE" : "FALSE");
    freeTree(t1);

    /*
      ESEMPIO 2 (atteso FALSE)
              5
             / \
            7   8
           /     \
          9       10

      Cammini:
      5->7->9  diff: +2, +2 (NON alterna)
      5->8->10 diff: +3, +2 (NON alterna)
      Nessun cammino valido => FALSE
    */
    Albero t2 =
        newNode(5,
            newNode(7,
                newNode(9, NULL, NULL),
                NULL
            ),
            newNode(8,
                NULL,
                newNode(10, NULL, NULL)
            )
        );

    printf("\nESEMPIO 2 (atteso FALSE): %s\n",
           esisteCamminoDiffAlternate(t2) ? "TRUE" : "FALSE");
    freeTree(t2);

    /*
      ESEMPIO 3 (atteso FALSE: differenza zero)
            5
           /
          5
         /
        6

      Cammino: 5->5->6 diff: 0, +1 (0 invalida) => nessun cammino valido => FALSE
    */
    Albero t3 =
        newNode(5,
            newNode(5,
                newNode(6, NULL, NULL),
                NULL
            ),
            NULL
        );

    printf("\nESEMPIO 3 (atteso FALSE): %s\n",
           esisteCamminoDiffAlternate(t3) ? "TRUE" : "FALSE");
    freeTree(t3);

    /*
      ESEMPIO 4 (atteso TRUE: un solo cammino)
          10
            \
             7
              \
               9
                \
                 6

      Cammino: 10->7->9->6
      diff: -3, +2, -3 (alterna) => TRUE
    */
    Albero t4 =
        newNode(10,
            NULL,
            newNode(7,
                NULL,
                newNode(9,
                    NULL,
                    newNode(6, NULL, NULL)
                )
            )
        );

    printf("\nESEMPIO 4 (atteso TRUE):  %s\n",
           esisteCamminoDiffAlternate(t4) ? "TRUE" : "FALSE");
    freeTree(t4);

    return 0;
}
int f(Albero tree, int expect, int prec, int *hasprec) // expect=1 mi aspetto differenza positiva, expect=-1 mi aspetto differenza negativa
    {
        if(tree==NULL)
            return 0;
        
        if(*hasprec==1)
            {
                if((tree->val-prec)*expect<=0)
                    return 0;
            }
        if(tree->left==NULL && tree->right==NULL)
            return 1;
        *hasprec=1;
        return  f(tree->left, -expect, tree->val, hasprec) || f(tree->right, -expect, tree->val, hasprec);
    }
bool esisteCamminoDiffAlternate(Albero t)
    {
    int flag=0;
    return  f(t, 1, 0, &flag) || f(t, -1, 0, &flag);
    }
