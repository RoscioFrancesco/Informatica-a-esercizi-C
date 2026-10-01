//
//  main.c
//  8B -17
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

/* Stampa i cammini root->leaf con i livelli (utile per controllare le somme).
   NOTA: è solo debug, usa un buffer di dimensione fissa. */
static void printPathsAux(Albero t, int livello, int path[], int level[], int len) {
    if (!t) return;

    path[len] = t->val;
    level[len] = livello;
    len++;

    if (t->left == NULL && t->right == NULL) {
        printf("Cammino: ");
        for (int i = 0; i < len; i++) {
            printf("%d(L%d)%s", path[i], level[i], (i == len - 1) ? "" : " -> ");
        }
        printf("\n");
        return;
    }

    printPathsAux(t->left,  livello + 1, path, level, len);
    printPathsAux(t->right, livello + 1, path, level, len);
}

static void printPaths(Albero t) {
    int path[128];
    int level[128];
    printPathsAux(t, 0, path, level, 0);
}

/* =======================
   ESERCIZIO 8B (STUB)
   ======================= */

int f(Albero t, int depth, int somma_3, int sommaaltri);
int esisteCamminoSommeLivelli(Albero t);


int esisteCamminoSommeLivelli(Albero t) {
    return f(t, 0, 0, 0);
}
/* =======================
   MAIN DI TEST
   ======================= */

int main(void) {
    /* Albero 1 */
    Albero t1 =
        newNode(5,
            newNode(2,
                newNode(7, NULL, NULL),
                newNode(1, NULL, NULL)
            ),
            newNode(9,
                NULL,
                newNode(3, NULL, NULL)
            )
        );

    /* Albero 2 */
    Albero t2 =
        newNode(10,
            newNode(4,
                newNode(6, NULL, NULL),
                NULL
            ),
            newNode(8,
                newNode(2, NULL, NULL),
                newNode(12, NULL, NULL)
            )
        );

    /* Albero 3 (piccolo) */
    Albero t3 =
        newNode(1,
            newNode(2,
                newNode(3, NULL, NULL),
                NULL
            ),
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

        printf("Cammini (root->leaf):\n");
        printPaths(tests[i]);

        int ok = esisteCamminoSommeLivelli(tests[i]);
        printf("Risultato esisteCamminoSommeLivelli(%s) = %d\n", names[i], ok);
    }

    printf("====================================\n");

    freeTree(t1);
    freeTree(t2);
    freeTree(t3);
    return 0;
}

//8B – Somme per livelli
int f(Albero t, int depth, int somma_3, int sommaaltri)
    {
        if(t==NULL)
            return 0;
        if(depth%3==0)
            somma_3=somma_3+t->val;
        else
            sommaaltri=sommaaltri+t->val;
        int sx=0;
        int dx=0;
        if(t->left==NULL && t->right==NULL)
            {
                if(somma_3>sommaaltri)
                    return 1;
                return 0;
            }
        if(t->left!=NULL)
            {
                sx=f(t->left, depth+1,somma_3, sommaaltri);
            }
        if(t->right!=NULL)
            {
                dx=f(t->right, depth+1, somma_3, sommaaltri);
            }
    return sx||dx;
    }
