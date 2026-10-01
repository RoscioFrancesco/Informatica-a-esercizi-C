//
//  main.c
//  albero tde
//
//  Created by Francesco Roscio Ricon on 22/01/26.
//



#include <stdio.h>
#include <stdlib.h>

/* ====== STRUTTURE (corrette) ====== */
typedef struct nodeS {
    int v;
    struct nodeS *left, *right;
} node;

typedef node *tree;



/* ====== FUNZIONI DI SUPPORTO ====== */
tree newNode(int v, tree left, tree right) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) exit(1);
    n->v = v;
    n->left = left;
    n->right = right;
    return n;
}

void stampaPreorder(tree t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }
    printf("%d ", t->v);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}
int f(tree albero);
int funzione(tree albero, int livello, int *profondità_foglie);
int main(void) {
    /*
        t1 (foglie tutte allo stesso livello: profondità 2)
                 1
               /   \
              2     3
             / \   / \
            4  5  6  7
        Foglie: 4,5,6,7 (tutte a profondità 2) => f(t1) = 1
    */
    tree t1 =
        newNode(1,
            newNode(2,
                newNode(4, NULL, NULL),
                newNode(5, NULL, NULL)
            ),
            newNode(3,
                newNode(6, NULL, NULL),
                newNode(7, NULL, NULL)
            )
        );

    /*
        t2 (foglie a livelli diversi)
                 10
               /    \
              5      20
             /      /  \
            3      15   30
                     \
                      17

        Foglie: 3 (profondità 2), 17 (profondità 3), 30 (profondità 2) => f(t2) = 0
    */
    tree t2 =
        newNode(10,
            newNode(5,
                newNode(3, NULL, NULL),
                NULL
            ),
            newNode(20,
                newNode(15,
                    NULL,
                    newNode(17, NULL, NULL)
                ),
                newNode(30, NULL, NULL)
            )
        );

    printf("Albero t1 (preorder): ");
    stampaPreorder(t1);
    printf("\nRisultato f(t1): %d (atteso 1)\n\n", f(t1));

    printf("Albero t2 (preorder): ");
    stampaPreorder(t2);
    printf("\nRisultato f(t2): %d (atteso 0)\n", f(t2));

    return 0;
}


int funzione(tree albero, int livello, int *profondità_foglie)
    {
        if(albero==NULL)
            return 1;
        if(albero->left==NULL && albero->right==NULL)
            {
                if(*profondità_foglie==-1)
                    *profondità_foglie=livello;
                if(livello==*profondità_foglie)
                    return 1;
                else
                    return 0;
            }
    return funzione(albero->left, livello+1, profondità_foglie) &&funzione(albero->right, livello+1, profondità_foglie);
    }

int f(tree albero)
    {
    int profondità_foglie=-1;
    return funzione(albero, 0, &profondità_foglie);
    }



