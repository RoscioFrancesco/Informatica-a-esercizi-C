//
//  main.c
//  tde carta tde 3 alberi -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct EL {
    int dato;
    struct EL *left, *right;
} node;

typedef node *tree;


void f(tree TA, tree TB, tree TRES);

/* =========================
   UTILITY: creazione / stampa / free
   ========================= */
static tree newNode(int dato, tree left, tree right) {
    tree t = (tree)malloc(sizeof(node));
    if (!t) { perror("malloc"); exit(1); }
    t->dato = dato;
    t->left = left;
    t->right = right;
    return t;
}

/* stampa pre-order con parentesi, comoda per vedere la struttura */
static void printTree(tree t) {
    if (t == NULL) {
        printf("NULL");
        return;
    }
    printf("%d(", t->dato);
    printTree(t->left);
    printf(", ");
    printTree(t->right);
    printf(")");
}

/* stampa per livelli (solo se albero completo fino a una certa profondità) */
static int height(tree t) {
    if (!t) return 0;
    int hl = height(t->left);
    int hr = height(t->right);
    return 1 + (hl > hr ? hl : hr);
}
static void printLevel(tree t, int level) {
    if (level == 1) {
        if (t) printf("%d ", t->dato);
        else   printf("_ ");
        return;
    }
    if (!t) {
        /* per mantenere l’allineamento: espando NULL */
        printLevel(NULL, level - 1);
        printLevel(NULL, level - 1);
        return;
    }
    printLevel(t->left, level - 1);
    printLevel(t->right, level - 1);
}
static void printTreeByLevels(tree t) {
    int h = height(t);
    for (int i = 1; i <= h; i++) {
        printf("Livello %d: ", i);
        printLevel(t, i);
        printf("\n");
    }
}

static void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =========================
   MAIN DI TEST
   ========================= */
void inizializza_TRES(tree t);
void riempi(tree TRES, tree albero2);

int main(void) {
    /*
      Costruiamo TA e TB con la stessa profondità di TRES.
      Esempio: profondità 3 (radice + 2 livelli sotto).

      Mettiamo alcuni NULL per simulare "nodo non esiste" in TA/TB.
      TRES invece è COMPLETO (tutti i nodi interni hanno 2 figli).
    */

    /* TA (profondità 3, ma con buchi) */
    tree TA =
        newNode(10,
            newNode(5,
                newNode(1, NULL, NULL),
                NULL /* qui manca un nodo */
            ),
            newNode(7,
                NULL, /* qui manca un nodo */
                newNode(3, NULL, NULL)
            )
        );

    /* TB (profondità 3, ma con buchi diversi) */
    tree TB =
        newNode(20,
            newNode(2,
                NULL, /* manca */
                newNode(4, NULL, NULL)
            ),
            NULL /* manca tutto il sottoalbero destro */
        );

    /* TRES completo (stessa profondità 3) - valori iniziali "spazzatura" */
    tree TRES =
        newNode(-1,
            newNode(-1,
                newNode(-1, NULL, NULL),
                newNode(-1, NULL, NULL)
            ),
            newNode(-1,
                newNode(-1, NULL, NULL),
                newNode(-1, NULL, NULL)
            )
        );

    printf("TA (preorder):   ");
    printTree(TA);
    printf("\n");

    printf("TB (preorder):   ");
    printTree(TB);
    printf("\n");

    printf("TRES prima (preorder): ");
    printTree(TRES);
    printf("\n\n");

    printf("TA (livelli):\n");
    printTreeByLevels(TA);
    printf("\n");

    printf("TB (livelli):\n");
    printTreeByLevels(TB);
    printf("\n");

    printf("TRES prima (livelli):\n");
    printTreeByLevels(TRES);
    printf("\n");

    /* ======= CHIAMATA ALLA TUA FUNZIONE ======= */
    f(TA, TB, TRES);

    printf("TRES dopo f (preorder): ");
    printTree(TRES);
    printf("\n\n");

    printf("TRES dopo f (livelli):\n");
    printTreeByLevels(TRES);

    /* cleanup */
    freeTree(TA);
    freeTree(TB);
    freeTree(TRES);

    return 0;
}
void f(tree TA, tree TB, tree TRES)
    {
    inizializza_TRES(TRES);
    riempi(TRES, TA);
    riempi(TRES, TB);
    }
void inizializza_TRES(tree t)
    {
        if(t==NULL)
            return;
        t->dato=0;
        inizializza_TRES(t->left);
        inizializza_TRES(t->right);
    }
void riempi(tree TRES, tree albero2)
    {
        if(albero2==NULL)
            return;
        TRES->dato=TRES->dato+albero2->dato;
    riempi(TRES->left, albero2->left);
    riempi(TRES->right, albero2->right);
    }
