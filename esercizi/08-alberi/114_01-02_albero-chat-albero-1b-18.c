//
//  main.c
//  albero chat albero 1B -18
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

int cammino(Albero t);
int cammino(Albero t);
int esisteCammino(Albero t) {
    if (t == NULL) return 0;
    return cammino(t);
}

/* =======================
   MAIN DI TEST
   ======================= */
int èpari(int x);

int main(void) {
    

    Albero t =
        newNode(6,
            newNode(9,
                newNode(8, NULL, NULL),
                newNode(5,
                    newNode(10, NULL, NULL),
                    newNode(0, NULL, NULL)
                )
            ),
            newNode(4,
                NULL,
                newNode(7, NULL, NULL)
            )
        );

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n");

    int ok = esisteCammino(t);

    printf("Esiste cammino con alternanza pari/dispari, prodotto != 0 e foglia multipla di 5? %s\n",
           ok ? "SI" : "NO");

    freeTree(t);
    return 0;
}




int cammino(Albero t) // se expect=2 allora mi aspetto pari, se expect=1 allora mi aspetto dispari
    {
        if(t==NULL)
            return 0;
        int padre=èpari(t->val);
        if(t->val==0)
            return 0; // tutto il cammino bocciato
        int sx=0;
        int dx=0;
        if(t->left!=NULL && padre!=èpari(t->left->val))
            sx= cammino(t->left);
        if(t->right!=NULL && padre!=èpari(t->right->val))
            dx=cammino(t->right);

        if(t->left==NULL && t->right==NULL)
            {
                if(t->val%5==0)
                    return 1;
                return 0;
            }
        return sx|| dx;
    }
int èpari(int x)
    {
        if(x%2==0)
            return 1;
    return 0;
    }
