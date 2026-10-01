//
//  main.c
//  alberi es 7 b chat
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
   UTILITY: creazione nodi
   ======================= */

Node* newNode(int v, Node* l, Node* r)
{
    Node* n = (Node*)malloc(sizeof(*n));
    n->val = v;
    n->left = l;
    n->right = r;
    return n;
}

/* =======================
   FREE ALBERO (NO CICLI)
   ======================= */

void freeTree(Node* root)
{
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/* =======================
   ESERCIZIO 7:
   Foglie ordinate strettamente crescenti
   ======================= */
/* =======================
   MAIN + ESEMPI
   ======================= */
bool foglieOrdinate(Albero t);
int f(Albero t, int *last, int *flag);

int main(void)
{
    /*
      ESEMPIO 1 (TRUE)
              5
            /   \
           3     8
          / \     \
         1   4     10

      Foglie da sinistra a destra: 1, 4, 10  => strettamente crescente => TRUE
    */
    Albero t1 =
        newNode(5,
            newNode(3,
                newNode(1, NULL, NULL),
                newNode(4, NULL, NULL)
            ),
            newNode(8,
                NULL,
                newNode(10, NULL, NULL)
            )
        );

    printf("ESEMPIO 1 (atteso TRUE): %s\n", foglieOrdinate(t1) ? "TRUE" : "FALSE");
    freeTree(t1);

    /*
      ESEMPIO 2 (FALSE)
              5
            /   \
           3     8
          / \   / \
         1  7  6  10

      Foglie: 1, 7, 6, 10  => 7 -> 6 non cresce => FALSE
    */
    Albero t2 =
        newNode(5,
            newNode(3,
                newNode(1, NULL, NULL),
                newNode(7, NULL, NULL)
            ),
            newNode(8,
                newNode(6, NULL, NULL),
                newNode(10, NULL, NULL)
            )
        );

    printf("ESEMPIO 2 (atteso FALSE): %s\n", foglieOrdinate(t2) ? "TRUE" : "FALSE");
    freeTree(t2);

    /*
      ESEMPIO 3 (FALSE per uguaglianza: NON stretta)
              2
            /   \
           1     3
          /     / \
         1     4   5

      Foglie: 1, 4, 5? Attenzione: c'è anche la foglia 1 a sinistra.
      In realtà: foglie = 1 (sinistra-sinistra), 4, 5.
      Qui è crescente (1<4<5) => TRUE.
      Facciamo invece una uguaglianza:

              2
            /   \
           1     3
          /     / \
         4     4   5

      Foglie: 4, 4, 5 => 4 -> 4 non stretta => FALSE
    */
    Albero t3 =
        newNode(2,
            newNode(1,
                newNode(4, NULL, NULL),
                NULL
            ),
            newNode(3,
                newNode(4, NULL, NULL),
                newNode(5, NULL, NULL)
            )
        );

    printf("ESEMPIO 3 (atteso FALSE): %s\n", foglieOrdinate(t3) ? "TRUE" : "FALSE");
    freeTree(t3);

    /*
      ESEMPIO 4 (TRUE: albero con una sola foglia)
          7

      Foglie: 7 => sequenza vacuamente crescente => TRUE
    */
    Albero t4 = newNode(7, NULL, NULL);
    printf("ESEMPIO 4 (atteso TRUE): %s\n", foglieOrdinate(t4) ? "TRUE" : "FALSE");
    freeTree(t4);

    return 0;
}
/* =======================
   ESERCIZIO 7:
   Foglie ordinate strettamente crescenti
   ======================= */

int f(Albero t, int *last, int *flag)
    {
            if(t==NULL)
                return 1;
        if(t->left==NULL && t->right==NULL)
        {
            if(*flag==0)
            {
                *last=t->val;
                *flag=1;
            }
            else
                {
                    if(*last>=t->val)
                        return 0;
                    *last=t->val;
                }
        }
        return f(t->left, last, flag) && f(t->right, last, flag);
    }
bool foglieOrdinate(Albero t)
{
    int last = 0;
    int flag = 0;
    return f(t, &last, &flag);
}
