//
//  main.c
//  8A -17
//
//  Created by Francesco Roscio Ricon on 02/02/26.
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
   STAMPE UTILI (DEBUG)
   ======================= */

static void printInorder(Albero t) {
    if (!t) return;
    printInorder(t->left);
    printf("%d ", t->val);
    printInorder(t->right);
}

static int isLeaf(Albero t) {
    return (t && !t->left && !t->right);
}

/* =======================
   ESERCIZIO 8A (STUB)
   ======================= */
int f(Albero t, int livello, int max);

int esisteCamminoVincolato(Albero t);
/* Se preferisci, puoi anche dichiarare una ausiliaria:
   int aux(Albero t, int livello, int maxFinora);
*/

int esisteCamminoVincolato(Albero t) {
    int livello=0;
    return f(t, 0, 0);
}

/* =======================
   MAIN DI TEST
   ======================= */
int èpari(int x);
int main(void) {
    /* Albero 1: costruito “a mano” */
    Albero t1 =
        newNode(4,
            newNode(3,
                newNode(8, NULL, NULL),
                newNode(5, NULL, NULL)
            ),
            newNode(7,
                NULL,
                newNode(10, NULL, NULL)
            )
        );

    /* Albero 2: un altro esempio */
    Albero t2 =
        newNode(2,
            newNode(6,
                newNode(1, NULL, NULL),
                NULL
            ),
            newNode(9,
                newNode(4, NULL, NULL),
                newNode(12, NULL, NULL)
            )
        );

    /* Albero 3: caso piccolo */
    Albero t3 =
        newNode(1,
            newNode(2, NULL, NULL),
            NULL
        );

    Albero tests[] = { t1, t2, t3 };
    const char* names[] = { "t1", "t2", "t3" };

    for (int i = 0; i < 3; i++) {
        printf("====================================\n");
        printf("Test %s\n", names[i]);
        printf("Inorder: ");
        printInorder(tests[i]);
        printf("\n");

        int ok = esisteCamminoVincolato(tests[i]);
        printf("Risultato esisteCamminoVincolato(%s) = %d\n", names[i], ok);
    }
    printf("====================================\n");

    freeTree(t1);
    freeTree(t2);
    freeTree(t3);
    return 0;
}


int f(Albero t, int livello, int max)
    {
        if(t==NULL)
            return 0;
        if(èpari(livello)!=èpari(t->val))
            return 0;
        int sx=0;
        int dx=0;
        if(t->left==NULL && t->right==NULL && èpari(livello)==èpari(t->val))
            {
                if(t->val>max)
                    return 1;
                return 0;
            }
        if(t->val>max)
            {
                max=t->val;
            }
        if(t->left!=NULL && èpari(livello)==èpari(t->val))
            {
                sx=f(t->left, livello+1, max);
            }
        if(t->right!=NULL && èpari(livello)==èpari(t->val))
            {
                dx=f(t->right, livello+1, max);
            }
        return sx||dx;
    }
int èpari(int x)
    {
    if(x%2==0)
        return 1;
    return 0;
    }
