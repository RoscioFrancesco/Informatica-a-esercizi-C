//
//  main.c
//  alberi es 8 b chat
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
/* crea un nodo (utility per i test) */
Node* newNode(int v, Node* l, Node* r);

/* libera l'albero (ricorsivo) */
void freeTree(Albero t);


bool camminoMaxKRec(Albero t, int maxCorr, int countMax, int hasMax, int K);

/* wrapper richiesto dall’esercizio */
bool esisteCamminoMaxEsattamenteK(Albero t, int K);

/* =======================
   MAIN + ESEMPI
   ======================= */
int f(Albero tree, int max, int occ_max, int K);
bool esisteCamminoMaxEsattamenteK(Albero t, int K);


/* crea un nodo (utility per i test) */
Node* newNode(int v, Node* l, Node* r);

/* libera l'albero (ricorsivo) */
void freeTree(Albero t);

/*
  helper ricorsivo:
  - t: nodo corrente
  - maxCorr: massimo visto finora lungo il cammino
  - countMax: quante volte compare maxCorr nel cammino finora
  - hasMax: 0 se maxCorr non inizializzato (inizio), 1 altrimenti
  - K: target
  ritorna true se ESISTE almeno un cammino valido nel sottoalbero
*/

int main(void)
{
    /*
      ESEMPIO 1 (TRUE per K=1)
             5
           /   \
          3     8
         / \     \
        2   4     9

      Cammini:
      5-3-2 : max=5 compare 1 volta  => valido per K=1
      5-3-4 : max=5 compare 1 volta  => valido per K=1
      5-8-9 : max=9 compare 1 volta  => valido per K=1
      Quindi esiste sicuramente un cammino con max che compare esattamente 1 volta.
    */
    Albero t1 =
        newNode(5,
            newNode(3,
                newNode(2, NULL, NULL),
                newNode(4, NULL, NULL)
            ),
            newNode(8,
                NULL,
                newNode(9, NULL, NULL)
            )
        );

    printf("ESEMPIO 1, K=1 (atteso TRUE):  %s\n",
           esisteCamminoMaxEsattamenteK(t1, 1) ? "TRUE" : "FALSE");
    printf("ESEMPIO 1, K=2 (atteso FALSE): %s\n",
           esisteCamminoMaxEsattamenteK(t1, 2) ? "TRUE" : "FALSE");

    freeTree(t1);

    /*
      ESEMPIO 2 (TRUE per K=2)
             7
           /   \
          7     3
         / \
        2   7

      Cammini:
      7-7-2 : max=7 compare 2 volte => valido per K=2
      7-7-7 : max=7 compare 3 volte => NON valido per K=2 (ma esiste l'altro)
      7-3   : max=7 compare 1 volta => valido per K=1
    */
    Albero t2 =
        newNode(7,
            newNode(7,
                newNode(2, NULL, NULL),
                newNode(7, NULL, NULL)
            ),
            newNode(3, NULL, NULL)
        );

    printf("\nESEMPIO 2, K=2 (atteso TRUE):  %s\n",
           esisteCamminoMaxEsattamenteK(t2, 2) ? "TRUE" : "FALSE");
    printf("ESEMPIO 2, K=3 (atteso TRUE):  %s\n",
           esisteCamminoMaxEsattamenteK(t2, 3) ? "TRUE" : "FALSE");
    printf("ESEMPIO 2, K=4 (atteso FALSE): %s\n",
           esisteCamminoMaxEsattamenteK(t2, 4) ? "TRUE" : "FALSE");

    freeTree(t2);

    /*
      ESEMPIO 3 (FALSE per K=2)
             4
           /   \
          1     2
               / \
              3   0

      Cammini:
      4-1   : max=4 compare 1 volta
      4-2-3 : max=4 compare 1 volta
      4-2-0 : max=4 compare 1 volta
      Qui il massimo lungo ogni cammino è sempre 4 e compare sempre 1 volta,
      quindi per K=2 deve essere FALSE.
    */
    Albero t3 =
        newNode(4,
            newNode(1, NULL, NULL),
            newNode(2,
                newNode(3, NULL, NULL),
                newNode(0, NULL, NULL)
            )
        );

    printf("\nESEMPIO 3, K=1 (atteso TRUE):  %s\n",
           esisteCamminoMaxEsattamenteK(t3, 1) ? "TRUE" : "FALSE");
    printf("ESEMPIO 3, K=2 (atteso FALSE): %s\n",
           esisteCamminoMaxEsattamenteK(t3, 2) ? "TRUE" : "FALSE");

    freeTree(t3);

    /*
      ESEMPIO 4 (TRUE per K=2, massimo compare in posizioni "arbitrarie")
             6
           /   \
          1     6
               /
              2
             /
            6

      Cammino destro: 6-6-2-6 (attenzione: non è un cammino perché 2 è sotto 6->left->left,
      qui invece è: 6 (root) -> 6 (right) -> 2 (left) -> 6 (left)
      Massimo del cammino è 6 e compare 3 volte => K=3 TRUE
      Ma esiste anche cammino 6-1: massimo 6 compare 1 volta => K=1 TRUE
      Quindi:
      K=2 FALSE, K=3 TRUE, K=1 TRUE
    */
    Albero t4 =
        newNode(6,
            newNode(1, NULL, NULL),
            newNode(6,
                newNode(2,
                    newNode(6, NULL, NULL),
                    NULL
                ),
                NULL
            )
        );

    printf("\nESEMPIO 4, K=1 (atteso TRUE):  %s\n",
           esisteCamminoMaxEsattamenteK(t4, 1) ? "TRUE" : "FALSE");
    printf("ESEMPIO 4, K=2 (atteso FALSE): %s\n",
           esisteCamminoMaxEsattamenteK(t4, 2) ? "TRUE" : "FALSE");
    printf("ESEMPIO 4, K=3 (atteso TRUE):  %s\n",
           esisteCamminoMaxEsattamenteK(t4, 3) ? "TRUE" : "FALSE");

    freeTree(t4);

    return 0;
}
/* wrapper richiesto dall’esercizio */
bool esisteCamminoMaxEsattamenteK(Albero t, int K)
    {
    return f(t, t->val, 0, K);
    }

int f(Albero tree, int max, int occ_max, int K)
    {
        if(tree==NULL)
            return 0;
        if(max==tree->val)
            {
                occ_max++;
            }
        if(max<tree->val)
            {
                max=tree->val;
                occ_max=1;
            }
        if(tree->left==NULL && tree->right==NULL)
            {
                if(occ_max==K)
                    return 1;
                return 0;
            }
    return f(tree->left, max, occ_max, K) || f(tree->right, max, occ_max, K);
    }
void freeTree(Albero t)
{
    if (t == NULL)
        return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}
Node* newNode(int v, Node* l, Node* r)
{
    Node* n = (Node*)malloc(sizeof(*n));
    n->val = v;
    n->left = l;
    n->right = r;
    return n;
}
