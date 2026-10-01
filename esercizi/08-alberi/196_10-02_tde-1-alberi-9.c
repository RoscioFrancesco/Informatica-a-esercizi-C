//
//  main.c
//  tde 1 alberi -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */

typedef struct ET {
    char dato;
    struct ET *left;
    struct ET *right;
} treeNode;

typedef treeNode *tree;

typedef struct ch {
    char c;
    struct ch *next;
} carattere;

typedef carattere *parola;


int f(tree t, parola p);

/* (facoltativo) prototipo ausiliaria che potresti usare */
static int f_aux(tree t, parola p); /* TODO: puoi usarla nella tua soluzione */

/* =========================
   UTILITY: ALBERO
   ========================= */
static tree newNode(char x) {
    tree n = (tree)malloc(sizeof(treeNode));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = x;
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

static void printPreorder(tree t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }
    printf("%c ", t->dato);
    printPreorder(t->left);
    printPreorder(t->right);
}
int funz(tree albero ,parola p);
/* =========================
   UTILITY: LISTA (parola)
   ========================= */
static parola pushBack(parola head, char c) {
    carattere *n = (carattere *)malloc(sizeof(carattere));
    if (!n) { perror("malloc"); exit(1); }
    n->c = c;
    n->next = NULL;

    if (head == NULL) return n;

    carattere *cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return head;
}

static parola buildParolaFromString(const char *s) {
    parola p = NULL;
    for (int i = 0; s[i] != '\0'; i++) {
        p = pushBack(p, s[i]);
    }
    return p;
}

static void printParola(parola p) {
    while (p != NULL) {
        printf("%c", p->c);
        p = p->next;
    }
}

static void freeParola(parola p) {
    while (p != NULL) {
        carattere *nx = p->next;
        free(p);
        p = nx;
    }
}

/* =========================
   STUB: FUNZIONE DELL'ESERCIZIO (NON RISOLVE)
   ========================= */
int f(tree t, parola p) {
    return funz(t, p);
}

int main(void) {
    /*
       Costruisco un albero di esempio:

               a
             /   \
            b     x
           / \     \
          c   d     y

       Alcuni cammini radice-foglia:
       a-b-c
       a-b-d
       a-x-y
    */
    tree t = newNode('a');
    t->left = newNode('b');
    t->right = newNode('x');
    t->left->left = newNode('c');
    t->left->right = newNode('d');
    t->right->right = newNode('y');

    /* creo una parola (lista) da stringa */
    parola p1 = buildParolaFromString("abc");
    parola p2 = buildParolaFromString("abd");
    parola p3 = buildParolaFromString("axy");
    parola p4 = buildParolaFromString("ab");   /* non finisce su foglia */

    printf("=== Albero (preorder) ===\n");
    printPreorder(t);
    printf("\n\n");

    printf("=== Parole di test ===\n");
    printf("p1 = "); printParola(p1); printf("\n");
    printf("p2 = "); printParola(p2); printf("\n");
    printf("p3 = "); printParola(p3); printf("\n");
    printf("p4 = "); printParola(p4); printf("\n\n");

    /* Chiamo f (attualmente stub) */
    printf("f(t, p1) = %d (stub)\n", f(t, p1));
    printf("f(t, p2) = %d (stub)\n", f(t, p2));
    printf("f(t, p3) = %d (stub)\n", f(t, p3));
    printf("f(t, p4) = %d (stub)\n", f(t, p4));

    /* pulizia memoria */
    freeParola(p1);
    freeParola(p2);
    freeParola(p3);
    freeParola(p4);
    freeTree(t);

    return 0;
}
int funz(tree albero ,parola p)
    {
        if(albero==NULL || p==NULL)
            return 0;
        if(albero->dato!=p->c)
            return 0;
        if(albero->left==NULL && albero->right==NULL)
            {
                if(p->next==NULL)
                    return 1;
                return 0;
            }
    return funz(albero->left, p->next) || funz(albero->right, p->next);
    }
