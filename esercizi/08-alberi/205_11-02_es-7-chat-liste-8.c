//
//  main.c
//  es 7 chat liste  -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct node {
    char c;
    struct node *left, *right;
} Node;

typedef Node *Tree;

/* =========================
   PROTOTIPO RICHIESTO
   ========================= */
int matchGlobale(Tree t, char *s);   

/* =========================
   UTILITY PER TEST
   ========================= */
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

static void stampaPreorder(Tree t) {
    if (!t) { printf("NULL "); return; }
    printf("%c ", t->c);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

/* Stampa anche gli indirizzi (utile per capire “quali nodi” vengono usati) */
static void stampaPreorderAddr(Tree t) {
    if (!t) { printf("NULL "); return; }
    printf("(%c@%p) ", t->c, (void*)t);
    stampaPreorderAddr(t->left);
    stampaPreorderAddr(t->right);
}

/* =========================
   MAIN DI TEST
   ========================= */
int parolafromhere(Tree t, char parola[], int *segna);
int main(void) {
    /*
            a
          /   \
         b     c
        / \   / \
       a   d b   a

    Preorder: a b a d c b a
    */
    Tree t = newNode('a');
    t->left = newNode('b');
    t->right = newNode('c');
    t->left->left = newNode('a');
    t->left->right = newNode('d');
    t->right->left = newNode('b');
    t->right->right = newNode('a');

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n");

    printf("Albero (preorder con indirizzi): ");
    stampaPreorderAddr(t);
    printf("\n\n");

    /* TEST STRINGHE */
    char *tests[] = {
        "a",      /* dovrebbe essere 1 (esiste un nodo 'a') */
        "ba",     /* 1: b->a (nel ramo sinistro) */
        "abd",    /* 1: a->b->d (radice->sinistra->destra) */
        "cb",     /* 1: c->b (ramo destro) */
        "aa",     /* 0 o 1 a seconda della tua interpretazione (serve a->a in un percorso) */
        "acb",    /* probabilmente 0 (non puoi “tornare su”) */
        "d",      /* 1 (nodo 'd') */
        "z",      /* 0 */
        ""
    };
    int nt = (int)(sizeof(tests) / sizeof(tests[0]));

    for (int i = 0; i < nt; i++) {
        printf("matchGlobale(t, \"%s\") = %d\n",
               tests[i], matchGlobale(t, tests[i]));
    }

    freeTree(t);
    return 0;
}


int matchGlobale(Tree t, char s[]) {
    if(t==NULL)
        return 0;
    if(t->c==s[0])
        {
            int segna=0;
            if(parolafromhere(t, s, &segna))
                return 1;
        }
    return matchGlobale(t->left, s)||matchGlobale(t->right, s);
}
int parolafromhere(Tree t, char parola[], int *segna)
    {
        if(t==NULL)
            return 0;
        if(parola[*segna]!=t->c)
            return 0;
        (*segna)++;
        if(*segna==strlen(parola))
            return 1;
    int sx=0;
    int dx=0;
        if(t->left!=NULL)
            sx=parolafromhere(t->left, parola, segna);
        if(t->right!=NULL)
            dx=parolafromhere(t->right, parola, segna);
    return sx || dx;
    }
