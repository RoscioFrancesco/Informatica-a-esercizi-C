//
//  main.c
//  es 5 chat alberi  -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
    char c;
    struct node *left, *right;
} Node;

typedef Node *Tree;

/* =========================
   PROTOTIPO RICHIESTO
   ========================= */
int matchVincolato(Tree t, char *s, int K);
static Tree newNode(char c) {
    Tree n = (Tree)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->c = c;
    n->left = n->right = NULL;
    return n;
}

static void freeTree(Tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* Preorder semplice */
static void stampaPreorder(Tree t) {
    if (!t) { printf("NULL "); return; }
    printf("%c ", t->c);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

/* Preorder con indirizzi (utile per capire i nodi “unici” nel vincolo) */
static void stampaPreorderAddr(Tree t) {
    if (!t) { printf("NULL "); return; }
    printf("(%c@%p) ", t->c, (void*)t);
    stampaPreorderAddr(t->left);
    stampaPreorderAddr(t->right);
}

/* =========================
   MAIN DI TEST
   ========================= */
int compareKvolte(int K, char parola[]);
int wrapper( char parola[], Tree albero, int K);
int main(void) {
    /*
              a
            /   \
           b     a
          / \     \
         c   b     d
            /
           a

    Percorsi possibili (esempi):
    - da b (sx) -> b (dx) -> a (sx) ...
    - da a (radice) -> b -> c ...
    Serve matchVincolato: può partire da qualsiasi nodo, no ripetere nodo,
    e ogni lettera max K volte.
    */

    Tree t = newNode('a');
    t->left = newNode('b');
    t->right = newNode('a');

    t->left->left = newNode('c');
    t->left->right = newNode('b');
    t->left->right->left = newNode('a');

    t->right->right = newNode('d');

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n");

    printf("Albero (preorder con indirizzi): ");
    stampaPreorderAddr(t);
    printf("\n\n");

    /* TEST */
    struct {
        char *s;
        int K;
    } tests[] = {
        {"a", 1},        /* dovrebbe essere 1 (esiste nodo 'a') */
        {"ab", 1},       /* dipende dai percorsi, utile per debug */
        {"aba", 1},      /* con K=1 forse 0 (a ripetuta) */
        {"aba", 2},      /* con K=2 potrebbe diventare 1 */
        {"bb", 1},       /* con K=1 forse 0, con K=2 potrebbe 1 se esiste b->b senza ripetere nodo */
        {"ad", 1},       /* dovrebbe essere 1 (a -> ... -> d nel ramo destro) */
        {"aaaa", 2},     /* quasi sicuramente 0 per vincolo frequenza e/o nodi */
        {"", 1}          /* caso base: stringa vuota (decidi tu: spesso 1) */
    };

    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    for (int i = 0; i < nt; i++) {
        int ris = matchVincolato(t, tests[i].s, tests[i].K);
        printf("matchVincolato(t, \"%s\", K=%d) = %d\n", tests[i].s, tests[i].K, ris);
    }

    freeTree(t);
    return 0;
}

/* =========================
   PLACEHOLDER (così compila)
   ========================= */
int matchVincolato(Tree t, char *s, int K) {
    if(compareKvolte(K, s))
        return 0;
    return wrapper(s, t, K);
    }
int f(int len, int segna, char parola[], Tree albero, int K)
    {
        if(albero==NULL)
            return 0;
        if(parola[segna]!=albero->c)
            return 0;
        segna++;
        if(segna==strlen(parola))
            return 1;
        if(compareKvolte(K, parola))
            return 0;
    return f(len, segna, parola, albero->left, K) || f(len, segna, parola, albero->right, K);
    }
int compareKvolte(int K, char parola[]) // mi da 1 se sfora
    {
    for(int i=0; i<strlen(parola); i++)
        {
            int count=1;
            for(int j=i+1; j<strlen(parola); j++)
                {
                    if(parola[i]==parola[j])
                        count++;
                }
            if(count>K)
                return 1;
        }
    return 0;
    }
int wrapper( char parola[], Tree albero, int K)
    {
        if(albero==NULL)
            return 0;
        if(f(strlen(parola), 0, parola, albero, K))
            return 1;
    return wrapper(parola, albero->left, K) || wrapper(parola, albero->right, K);
    }
