//
//  main.c
//  albero chat albero 3A 2.0 -17
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
int esisteCammino(Albero t);
int f(Albero t, int dir, int mag);

int main(void) {
    

    Albero t =
        newNode(10,
            newNode(5,
                NULL,
                newNode(3,
                    NULL,
                    newNode(8, NULL, NULL)
                )
            ),
            newNode(15,
                NULL,
                newNode(12,
                    NULL,
                    newNode(9, NULL, NULL)
                )
            )
        );

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n");

    int ok = esisteCammino(t);

    printf("Esiste cammino con direzione alternata\n");
    printf("e confronto >/< alternato? %s\n", ok ? "SI" : "NO");

    freeTree(t);
    return 0;
}


int f(Albero t, int dir, int mag) // se mag=1 mi aspetto padre>figlio, se mag=-1 mi aspetto padre<figlio
//dir=1 allor dx, dir=-1 allora sx
    {
        if(t==NULL)
            return 0;
        int next_mag=-mag;
        int sx=0;
        int dx=0;
        if(t->right!=NULL && dir==1 && (t->val-t->right->val)*(mag)>0)
            {
                dx=f(t->right, -1, next_mag);
            }
        if(t->left!=NULL && dir==-1 && (t->val-t->left->val)*(mag)>0)
            {
                sx=f(t->left, 1, next_mag);
            }
        if(t->left==NULL && t->right==NULL)
            return 1;
        return sx||dx;
    }
int esisteCammino(Albero t)
    {
    if(t==NULL)
        return 0;
    return f(t, 1, 1) || f(t, 1, -1) || f(t, -1, 1) || f(t, -1, -1);
    }
