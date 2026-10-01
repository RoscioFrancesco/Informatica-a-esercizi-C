//
//  main.c
//  es 3 chat alberi  -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct node {
    char *parola;
    struct node *left, *right;
} Node;

typedef Node *Tree;

/* =========================
   PROTOTIPO RICHIESTO
   ========================= */
Tree eliminaDominati(Tree t);   

/* =========================
   UTILITY PER TEST
   ========================= */
static char *dupstr(const char *s) {
    char *p = (char*)malloc(strlen(s) + 1);
    if (!p) { perror("malloc"); exit(1); }
    strcpy(p, s);
    return p;
}

static Tree newNode(const char *w) {
    Tree n = (Tree)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->parola = dupstr(w);      /* alloco la stringa */
    n->left = n->right = NULL;
    return n;
}

static void freeTree(Tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t->parola);  /* importante */
    free(t);
}

static void stampaPreorder(Tree t) {
    if (!t) { printf("NULL "); return; }
    printf("\"%s\" ", t->parola);
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

/* stampa anche gli indirizzi dei nodi e delle stringhe (utile per debug) */
static void stampaPreorderAddr(Tree t) {
    if (!t) { printf("NULL "); return; }
    printf("(%s node@%p parola@%p) ", t->parola, (void*)t, (void*)t->parola);
    stampaPreorderAddr(t->left);
    stampaPreorderAddr(t->right);
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    /*
        Costruiamo un albero dove alcuni nodi sono dominati:

                 "art"
                /     \
            "car"    "bio"
             /  \       \
         "cart" "xx"   "biologia"

      - "car" è dominato da "cart" (discendente, contiene "car", più lunga)
      - "bio" è dominato da "biologia"
      - "art" NON è dominato (nessun discendente contiene "art" più lungo)
      - "xx" non è dominato
    */
    Tree t = newNode("art");
    t->left = newNode("car");
    t->right = newNode("bio");
    t->left->left = newNode("cart");
    t->left->right = newNode("xx");
    t->right->right = newNode("biologia");

    printf("=== PRIMA ===\n");
    printf("Preorder: ");
    stampaPreorder(t);
    printf("\n");

    printf("Preorder+addr: ");
    stampaPreorderAddr(t);
    printf("\n\n");

    /* chiamata funzione richiesta */
    t = eliminaDominati(t);

    printf("=== DOPO eliminaDominati ===\n");
    printf("Preorder: ");
    stampaPreorder(t);
    printf("\n");

    printf("Preorder+addr: ");
    stampaPreorderAddr(t);
    printf("\n");

    freeTree(t);
    return 0;
}

static int contieneSottostringaPiuLunga(Tree t, const char *pattern, int lenPattern) {
    if (!t) return 0;

    int lenT = (int)strlen(t->parola);
    if (lenT > lenPattern && strstr(t->parola, pattern) != NULL) {
        return 1;
    }

    return contieneSottostringaPiuLunga(t->left, pattern, lenPattern) ||
           contieneSottostringaPiuLunga(t->right, pattern, lenPattern);
}

/* n è dominato se esiste un discendente che contiene n->parola ed è più lungo */
static int nodoDominato(Tree n) {
    if (!n) return 0;
    int lenN = (int)strlen(n->parola);

    return contieneSottostringaPiuLunga(n->left,  n->parola, lenN) ||
           contieneSottostringaPiuLunga(n->right, n->parola, lenN);
}

/* =========================
   SUPPORTO: fusione sottoalberi
   ========================= */
/* Se elimino un nodo, devo tenere entrambi i sottoalberi.
   Strategia: promuovo LEFT; attacco RIGHT al nodo più a destra di LEFT. */
static Tree mergeSubtrees(Tree left, Tree right) {
    if (!left) return right;
    if (!right) return left;

    Tree p = left;
    while (p->right != NULL) p = p->right;
    p->right = right;
    return left;
}

/* =========================
   1 passata di potatura (postorder)
   ========================= */
static Tree eliminaDominati_pass(Tree t, int *changed) {
    if (!t) return NULL;

    /* prima sistema i figli */
    t->left  = eliminaDominati_pass(t->left, changed);
    t->right = eliminaDominati_pass(t->right, changed);

    /* poi valuta il nodo con i figli già “puliti” */
    if (nodoDominato(t)) {
        Tree res = mergeSubtrees(t->left, t->right);

        /* libera memoria del nodo eliminato */
        free(t->parola);
        free(t);

        *changed = 1;
        return res;   /* “collasso” il nodo */
    }

    return t;
}

/* =========================
   FUNZIONE RICHIESTA
   ========================= */
Tree eliminaDominati(Tree t) {
    int changed;
    do {
        changed = 0;
        t = eliminaDominati_pass(t, &changed);
    } while (changed);  /* iterazione logica: ripeti finché stabilizza */

    return t;
}

