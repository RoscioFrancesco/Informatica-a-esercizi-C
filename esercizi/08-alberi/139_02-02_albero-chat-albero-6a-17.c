//
//  main.c
//  albero chat albero 6A  -17
//
//  Created by Francesco Roscio Ricon on 02/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =======================
   STRUTTURA DATI
   ======================= */
typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

typedef Node* Albero;

/* =======================
   UTILITY
   ======================= */
static Node* newNode(int v, Node* l, Node* r) {
    Node* n = (Node*)malloc(sizeof(Node));
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

/* stampa ricorsiva (indentata) */
static void printTreeIndented(Albero t, int depth) {
    if (!t) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("%d\n", t->val);
    printTreeIndented(t->left, depth + 1);
    printTreeIndented(t->right, depth + 1);
}

/* =======================
   ALBERO RIDOTTO IN-PLACE
   Tiene solo nodi su cammini radice-foglia con somma pari.
   Ritorna 1 se nel sottoalbero esiste almeno un cammino valido,
   altrimenti 0 (e taglia/libera tutto quel sottoalbero).
   ======================= */
static int potaSommaPariRec(Albero *pt, int sumSoFar) {
    if (*pt == NULL) return 0;

    Albero t = *pt;
    int newSum = sumSoFar + t->val;

    /* caso foglia */
    if (t->left == NULL && t->right == NULL) {
        if (newSum % 2 == 0) {
            return 1;  // foglia valida: la tengo
        } else {
            free(t);   // foglia non valida: la elimino
            *pt = NULL;
            return 0;
        }
    }

    /* ricorsione sui figli: aggiorno direttamente i puntatori */
    int okL = potaSommaPariRec(&(t->left), newSum);
    int okR = potaSommaPariRec(&(t->right), newSum);

    /* se nessun figlio porta a cammino valido, elimino questo nodo */
    if (!okL && !okR) {
        // a questo punto t->left e t->right sono già NULL (o già potati)
        free(t);
        *pt = NULL;
        return 0;
    }

    /* altrimenti questo nodo sta su almeno un cammino valido: lo tengo */
    return 1;
}

/* =======================
   MAIN DI TEST
   ======================= */
int f2(Albero t, int sum);
void  f(Albero * t);
int main(void) {
    /*
        Albero di esempio:

                5
              /   \
             2     7
            / \     \
           1   4     3
                  \
                   6

      Cammini radice->foglia e somme:
      5-2-1   = 8  (pari)   => tieni 5,2,1
      5-2-4-6 = 17 (dispari)=> taglia ramo verso 6, quindi 4 diventa foglia (somma 11 dispari) -> taglia anche 4
      5-7-3   = 15 (dispari)=> taglia 3, poi 7 resta senza figli -> taglia anche 7
      Risultato atteso: 5-2-1
    */

    Albero t =
        newNode(5,
            newNode(2,
                newNode(1, NULL, NULL),
                newNode(4, NULL,
                    newNode(6, NULL, NULL)
                )
            ),
            newNode(7,
                NULL,
                newNode(3, NULL, NULL)
            )
        );

    printf("=== Albero originale ===\n");
    printTreeIndented(t, 0);
    f(&t);
    printf("\n=== Albero ridotto IN-PLACE (cammini con somma pari) ===\n");
    if (t == NULL) {
        printf("(albero vuoto)\n");
    } else {
        printTreeIndented(t, 0);
    }
    freeTree(t);
    return 0;
}

void  f(Albero * t){
    Albero a = *t;
    int ok = f2(a, 0);
    if(!ok) {
        free(a);
        *t=NULL;
    }
}

int f2(Albero t, int sum)
{
    if(t==NULL) return 0;
    if(t->left == NULL && t->right==NULL)
        return (sum+t->val+1)%2;
    int okdx=f2(t->right, sum+t->val);
    int oksx=f2(t->left, sum+t->val);
    if(!okdx && t->right!=NULL){
        free(t->right);
        t->right = NULL;
    }
    if(!oksx && t->left!=NULL){
        free(t->left);
        t->left = NULL;
    }
    return okdx || oksx;
}
