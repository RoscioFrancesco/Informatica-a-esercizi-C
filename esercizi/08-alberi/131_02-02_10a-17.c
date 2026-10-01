//
//  main.c
//  10A -17
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
   COSTRUZIONE / DEALLOCAZIONE
   ======================= */

static Node* newNode(int v, Node* l, Node* r) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->left = l;
    n->right = r;
    return n;
}

static void freeTree(Albero t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =======================
   STAMPE DI DEBUG
   ======================= */

static void printInorder(Albero t) {
    if (!t) return;
    printInorder(t->left);
    printf("%d ", t->val);
    printInorder(t->right);
}

/* Stampa tutti i cammini root->leaf (solo debug per “vedere” l’albero) */
static void printPathsAux(Albero t, int path[], int len) {
    if (!t) return;

    path[len] = t->val;
    len++;

    if (t->left == NULL && t->right == NULL) {
        printf("Cammino: ");
        for (int i = 0; i < len; i++) {
            printf("%d%s", path[i], (i == len - 1) ? "" : " -> ");
        }
        printf("\n");
        return;
    }

    printPathsAux(t->left,  path, len);
    printPathsAux(t->right, path, len);
}

static void printPaths(Albero t) {
    int path[128];
    printPathsAux(t, path, 0);
}

/* =======================
   ESERCIZIO 10A (STUB)
   ======================= */
int maxSottocamminoCrescente(Albero t);
void max_fromhere(Albero t, int *max, int count, int prec, int hasprec);
int maxSottocamminoCrescente(Albero t) {
    /* TODO: NON svolgo l’esercizio come richiesto */
    (void)t;
    return -1;
}

/* =======================
   MAIN DI TEST
   ======================= */
int wrapper(Albero t);
void f(Albero t, int *max);
void max_fromhere(Albero t, int *max, int count, int prec, int hasprec);
int main(void) {
    /* t1: albero con tratti crescenti e non */
    Albero t1 =
        newNode(5,
            newNode(3,
                newNode(2, NULL, NULL),
                newNode(4, NULL, NULL)
            ),
            newNode(8,
                newNode(7, NULL, NULL),
                newNode(10, NULL, NULL)
            )
        );

    /* t2: albero “a catena” con salite/discese */
    Albero t2 =
        newNode(6,
            newNode(1,
                NULL,
                newNode(3,
                    NULL,
                    newNode(4, NULL, NULL)
                )
            ),
            newNode(2, NULL, NULL)
        );

    /* t3: albero piccolo */
    Albero t3 =
        newNode(1,
            newNode(2,
                newNode(0, NULL, NULL),
                NULL
            ),
            NULL
        );
    const char* names[] = { "t1", "t2", "t3" };

    printf("\n%d, %d, %d", wrapper(t1), wrapper(t2), wrapper(t3));
}


void max_fromhere(Albero t, int *max, int count, int prec, int hasprec)
    {
        if(t==NULL)
            return;
        if(hasprec && t->val<=prec)
            return;
        if(count>*max)
            *max=count;
        if(hasprec==1)
            {
                if(t->left!=NULL)
                    max_fromhere(t->left, max, count+1, t->val, 1);
                if(t->right!=NULL)
                    max_fromhere(t->right, max, count+1, t->val, 1);
            }
        else
            {
                max_fromhere(t->left, max, count+1, t->val, 1);
                max_fromhere(t->right, max, count+1, t->val, 1);
            }
    }
void f(Albero t, int *max)
    {
        if(t==NULL)
            {
                return;
            }
    int max_nodo=0;
    max_fromhere(t, &max_nodo, 1, 0, 0);
    if(max_nodo>*max)
        *max=max_nodo;
    f(t->left, max);
    f(t->right, max);
    }
int wrapper(Albero t)
    {
    int max=0;
    f(t, &max);
    return max;
    }
