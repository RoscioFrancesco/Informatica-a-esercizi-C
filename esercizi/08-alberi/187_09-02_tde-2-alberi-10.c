//
//  main.c
//  tde 2 alberi -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ET {
    char parola[1000];
    struct ET *left, *right;
} treeNode;

typedef treeNode *tree;


int f(tree t);

/* =====================
   UTILITY PER CREARE/TESTARE L'ALBERO
   ===================== */
static tree nuovoNodo(const char *s) {
    tree n = (tree)malloc(sizeof(treeNode));
    if (!n) { perror("malloc"); exit(1); }
    strncpy(n->parola, s, sizeof(n->parola) - 1);
    n->parola[sizeof(n->parola) - 1] = '\0';
    n->left = NULL;
    n->right = NULL;
    return n;
}

static void freeTree(tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* Stampa per livelli (BFS) giusto per vedere bene i livelli */
static int altezza(tree t) {
    if (t == NULL) return 0;
    int aL = altezza(t->left);
    int aR = altezza(t->right);
    return 1 + (aL > aR ? aL : aR);
}

static void stampaLivello(tree t, int livello) {
    if (t == NULL) return;
    if (livello == 1) {
        printf("\"%s\"  ", t->parola);
    } else {
        stampaLivello(t->left, livello - 1);
        stampaLivello(t->right, livello - 1);
    }
}

static void stampaPerLivelli(tree t) {
    int h = altezza(t);
    for (int i = 1; i <= h; i++) {
        printf("Livello %d: ", i);
        stampaLivello(t, i);
        printf("\n");
    }
}

/* =====================
   MAIN DI TEST
   ===================== */
int verifica(tree albero, char *lettera, int *hasprev, int livello, int livellodaverificare);
int main() {
    /* ESEMPIO 1 (pensato per essere "ok"):
       livello 1: A...
       livello 2: B..., B...
       livello 3: C..., C... (solo nodi esistenti)
    */
    tree t1 = nuovoNodo("alfa");
    t1->left  = nuovoNodo("beta");
    t1->right = nuovoNodo("barca");
    t1->left->left = nuovoNodo("casa");
    t1->right->right = nuovoNodo("cielo");

    printf("=== Albero t1 ===\n");
    stampaPerLivelli(t1);
    printf("f(t1) = %d\n\n", f(t1));

    /* ESEMPIO 2 (pensato per essere "ko"):
       livello 2: parole iniziano con lettere diverse (b... e d...)
    */
    tree t2 = nuovoNodo("albero");
    t2->left  = nuovoNodo("bar");
    t2->right = nuovoNodo("dado");   /* qui rompe la regola al livello 2 */
    t2->left->right = nuovoNodo("cane");

    printf("=== Albero t2 ===\n");
    stampaPerLivelli(t2);
    printf("f(t2) = %d\n\n", f(t2));

    freeTree(t1);
    freeTree(t2);

    return 0;
}

/* =====================
   STUB (NON SVOLTO)
   ===================== */
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int depth(tree albero)
    {
        if(albero==NULL)
            return 0;
    int sx=depth(albero->left);
    int dx=depth(albero->right);
    return 1+max(sx, dx);
    }
int verifica(tree albero, char *lettera, int *hasprev, int livello, int livellodaverificare)
    {
        if(albero==NULL)
            return 1;
        if(livello==livellodaverificare && *hasprev==1)
            {
                if(*lettera!=albero->parola[0])
                    return 0;
            }
        if(*hasprev==0 && livello==livellodaverificare)
            {
                *lettera=albero->parola[0];
                *hasprev=1;
            }
    return verifica(albero->left, lettera, hasprev, livello+1, livellodaverificare) && verifica(albero->right, lettera, hasprev, livello+1, livellodaverificare);
    }
int f(tree albero)
    {
        if(albero==NULL)
            return 1;
        int numlivelli=depth(albero);
        for(int i=0; i<numlivelli; i++)
            {
                int hasprev=0;
                char lettera='a';
                int val=0;
                val=verifica(albero, &lettera, &hasprev, 0, i);
                if(val==0)
                    return 0;
            }
    return 1;
    }
