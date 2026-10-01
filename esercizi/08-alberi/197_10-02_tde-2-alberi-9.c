//
//  main.c
//  tde 2 alberi -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct n {
    char dato;
    struct n *left;
    struct n *right;
} Node;

typedef Node *Tree;


/* Stampa la frase formata dai caratteri sulle foglie da sinistra a destra */
void stampaFraseFoglie(Tree t);

/* =========================
   UTILITY PER CREARE / STAMPARE / LIBERARE ALBERO
   ========================= */
static Tree newNode(char c) {
    Tree n = (Tree)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = c;
    n->left = NULL;
    n->right = NULL;
    return n;
}

static void freeTree(Tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

static void printPreorder(Tree t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }
    printf("%c ", t->dato);
    printPreorder(t->left);
    printPreorder(t->right);
}

/* =========================
   STUB: FUNZIONE DELL'ESERCIZIO (NON RISOLVE)
   ========================= */
void stampaFraseFoglie(Tree t) {
    if(t==NULL)
        return;
    if(t->left==NULL && t->right==NULL)
        printf("%c", t->dato);
    stampaFraseFoglie(t->left);
    stampaFraseFoglie(t->right);
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    /*
        Esempio albero:

                'A'
               /   \
             'B'   'C'
             / \     \
           'd' 'e'   'f'

        Foglie da sinistra a destra: d e f  -> "def"
    */
    Tree t = newNode('A');
    t->left = newNode('B');
    t->right = newNode('C');
    t->left->left = newNode('d');
    t->left->right = newNode('e');
    t->right->right = newNode('f');

    printf("=== Albero (preorder) ===\n");
    printPreorder(t);
    printf("\n\n");

    printf("=== Frase dalle foglie (da sinistra a destra) ===\n");
    stampaFraseFoglie(t);     /* stub al momento */
    printf("\n\n");

    freeTree(t);
    return 0;
}
