//
//  main.c
//  liste tde 5 albero -12
//
//  Created by Francesco Roscio Ricon on 07/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node* tree;


int artussiano(tree t);

/* =========================
   UTILITY PER TEST
   ========================= */
static tree nuovoNodo(int v) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

static void stampaPreorder(tree t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }
    printf("%d ", t->dato);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

static void freeTree(tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =========================
   MAIN (runnabile)
   ========================= */
int f(tree albero);
int main(void) {

    /* Caso 1: albero artussiano (esempio ragionevole) */
    tree T1 = nuovoNodo(1);
    T1->left = nuovoNodo(2);                 /* nodo con 1 figlio */
    T1->left->left = nuovoNodo(3);           /* foglia */
    T1->right = nuovoNodo(4);                /* foglia */

    /* Caso 2: albero NON artussiano (esempio ragionevole) */
    tree T2 = nuovoNodo(10);
    T2->left = nuovoNodo(20);
    T2->right = nuovoNodo(30);
    /* creo più discendenti a sinistra che a destra */
    T2->left->left = nuovoNodo(40);
    T2->left->right = nuovoNodo(50);
    T2->left->left->left = nuovoNodo(60);

    printf("Albero T1 (preorder): ");
    stampaPreorder(T1);
    printf("\n");

    printf("Albero T2 (preorder): ");
    stampaPreorder(T2);
    printf("\n\n");

    printf("T1 artussiano? %d (ATTESO: 1 se la funzione e' corretta)\n", f(T1));
    printf("T2 artussiano? %d (ATTESO: 0 se la funzione e' corretta)\n", f(T2));

    freeTree(T1);
    freeTree(T2);

    return 0;
}

/* =========================
   STUB: NON SVOLGE L'ESERCIZIO
   ========================= */

int contadiscendenti(tree albero)
    {
        if(albero==NULL)
            return 0;
    return 1+contadiscendenti(albero->left)+contadiscendenti(albero->right);
    }
int f(tree albero)
    {
        if(albero==NULL)
            return 1;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
        int sx=1;
        int dx=1;
        if(albero->left!=NULL)
            sx= f(albero->left);
        if(albero->right!=NULL)
            dx=f(albero->right);
        if(albero->left!=NULL && albero->right!=NULL)
        {
            if(contadiscendenti(albero->left)!=contadiscendenti(albero->right))
                return 0;
        }
    return sx &&dx;
}
