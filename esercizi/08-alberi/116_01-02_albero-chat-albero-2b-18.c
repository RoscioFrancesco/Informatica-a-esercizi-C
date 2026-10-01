//
//  main.c
//  albero chat albero 2B -18
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

/*
  stato: 0=S0 (pari), 1=S1 (multiplo di 3), 2=S2 (primo)
  len: lunghezza del cammino finora (numero di nodi)
*/
int cammino(Albero t, int stato, int len);
int f(Albero tree, int profondità);
int esisteCammino(Albero t) {
    return f(t, 0);
}

/* =======================
   MAIN DI TEST
   ======================= */

int main(void) {
    /*
        Albero costruito per contenere un cammino valido (lunghezza 5):

                 8
               /   \
              6     10
             / \
            4   9
               /
              12
             /
            5

        Cammino candidato: 8 -> 6 -> 9 -> 12 -> 5

        Pattern atteso:
        S0: pari        (8)
        S1: mult. 3     (6)
        S2: primo       (9? no, 9 non è primo)  <-- ramo-trappola

        Quindi questo test NON è “garantito SI”:
        serve solo per provare la tua logica e farti vedere subito
        se gestisci stati/len correttamente.

        Se vuoi un test “atteso SI”, modifica i valori del ramo
        in modo coerente col pattern (ma qui non svolgiamo).
    */

    Albero t =
        newNode(8,
            newNode(6,
                newNode(4, NULL, NULL),
                newNode(9,
                    newNode(12,
                        newNode(5, NULL, NULL),
                        NULL
                    ),
                    NULL
                )
            ),
            newNode(10, NULL, NULL)
        );

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n");

    int ok = esisteCammino(t);

    printf("Esiste cammino radice->foglia (len>=5) che segue S0(pari)->S1(mult3)->S2(primo)? %s\n",
           ok ? "SI" : "NO");

    freeTree(t);
    return 0;
}
int isPrime(int x)
{
    if (x < 2)
        return 0;

    if (x == 2)
        return 1;

    if (x % 2 == 0)
        return 0;

    for (int d = 3; d * d <= x; d += 2)
        if (x % d == 0)
            return 0;

    return 1;
}

int stato(int x)
    {
        if(x%2==0)
            return 0;
        if(x%3==0)
            return 1;
        if(isPrime(x))
            return 2;
    return 5;
    }
int f(Albero tree, int profondità)
    {
        if(tree==NULL)
            return 0;
        int stato_now=stato(tree->val);
    int stato_prox=0;
    switch (stato_now) {
        case 0:
            stato_prox=1;
            break;
        case 1:
            stato_prox=2;
            break;
        case 2:
            stato_prox=0;
            break;
            }
        int sx=0;
        int dx=0;
        if(tree->left!=NULL && stato_prox==stato(tree->left->val))
            {
                sx=f(tree->left, profondità+1);
            }
        if(tree->right!=NULL && stato_prox==stato(tree->right->val))
            {
            dx=f(tree->right, profondità+1);
            }
    
        if(tree->left==NULL && tree->right==NULL)
        {
            if(profondità+1>=5)
                return 1;
            return 0;
        }
    return sx|| dx;
    }
