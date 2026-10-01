//
//  main.c
//  tde 8 alberi -11
//
//  Created by Francesco Roscio Ricon on 08/02/26.
//


#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct nodeS {
    int v;
    struct nodeS *left, *right;
} node;

typedef node *tree;

/* =========================
   PROTOTIPO FUNZIONE ESERCIZIO (DA FARE)
   ========================= */
int sommaPesata(tree t);




/* =========================
   UTILITY: creazione nodi
   ========================= */
static tree nuovoNodo(int valore) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) { perror("malloc"); exit(1); }
    n->v = valore;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/* =========================
   STAMPA ALBERO (preorder)
   ========================= */
static void stampaPreorder(tree t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }
    printf("%d ", t->v);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

/* =========================
   FREE
   ========================= */
static void freeTree(tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =========================
   MAIN DI TEST
   ========================= */
void f(tree albero, int *num, int *den, int livello);
int main(void) {
    /*
            5          livello 1
          /   \
         3     8        livello 2
        / \     \
       1   4     2      livello 3

    Somma pesata attesa:
    5*1 + 3*2 + 8*2 + 1*3 + 4*3 + 2*3
    = 5 + 6 + 16 + 3 + 12 + 6
    = 48
    */

    tree t = nuovoNodo(5);
    t->left = nuovoNodo(3);
    t->right = nuovoNodo(8);
    t->left->left = nuovoNodo(1);
    t->left->right = nuovoNodo(4);
    t->right->right = nuovoNodo(2);

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n");

    int ris = sommaPesata(t);
    printf("sommaPesata(t) = %d\n", ris);
    printf("(atteso: 48 se implementata correttamente)\n");

    freeTree(t);
    return 0;
}
void f(tree albero, int *num, int *den, int livello)
    {
        if(albero==NULL)
            return;
        *num=((livello)*albero->v)+(*num);
        *den=(*den)+livello;
    f(albero->left, num, den, livello+1);
    f(albero->right, num, den, livello+1);
    }
int sommaPesata(tree t) // pensavo di dover fare la media pesata
    {
    int num=0;
    int den=0;
    f(t, &num, &den, 1);
    return num;
    }
