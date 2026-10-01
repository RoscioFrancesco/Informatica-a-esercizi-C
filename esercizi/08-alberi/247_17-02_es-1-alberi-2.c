//
//  main.c
//  es 1 alberi  -2
//
//  Created by Francesco Roscio Ricon on 17/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
    char c;
    struct nodo *left;
    struct nodo *right;
} Nodo;

typedef Nodo* Tree;


int matchZigZag(Tree T, char *s);

/* =========================
   HELPER: CREAZIONE / STAMPA / FREE
   ========================= */
Tree newNode(char ch) {
    Tree n = (Tree)malloc(sizeof(Nodo));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->c = ch;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void freeTree(Tree T) {
    if (!T) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* Stampa semplice (preorder) per capire cosa hai costruito */
void printPreorder(Tree T) {
    if (!T) {
        printf("NULL");
        return;
    }
    printf("%c(", T->c);
    printPreorder(T->left);
    printf(",");
    printPreorder(T->right);
    printf(")");
}

/* =========================
   COSTRUZIONE DELL'ALBERO DELL'ESEMPIO
   Albero:
            a
           / \
          b   c
           \   \
            d   e
           /
          f
   ========================= */
Tree buildExampleTree(void) {
    Tree a = newNode('a');
    Tree b = newNode('b');
    Tree c = newNode('c');
    Tree d = newNode('d');
    Tree e = newNode('e');
    Tree f = newNode('f');

    a->left = b;
    a->right = c;

    b->right = d;
    d->left = f;

    c->right = e;

    return a; /* radice */
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    Tree T = buildExampleTree();

    printf("Albero (preorder): ");
    printPreorder(T);
    printf("\n\n");

    /* TEST 1 */
    char s1[] = "bdf";
    printf("Test 1: s = \"%s\"\n", s1);
    printf("matchZigZag(T, \"%s\") = %d\n\n", s1, matchZigZag(T, s1));
    /* Output atteso: 1 */

    /* TEST 2 */
    char s2[] = "bdfx";
    printf("Test 2: s = \"%s\"\n", s2);
    printf("matchZigZag(T, \"%s\") = %d\n\n", s2, matchZigZag(T, s2));
    /* Output atteso: 0 */

    /* TEST 3 */
    char s3[] = "acd";
    printf("Test 3: s = \"%s\"\n", s3);
    printf("matchZigZag(T, \"%s\") = %d\n\n", s3, matchZigZag(T, s3));
    /* Output atteso: 0 */

    /* TEST 4: stringa di 1 char (match da qualunque nodo) */
    char s4[] = "e";
    printf("Test 4: s = \"%s\"\n", s4);
    printf("matchZigZag(T, \"%s\") = %d\n\n", s4, matchZigZag(T, s4));
    /* Output atteso: 1 (perché esiste un nodo 'e') */

    /* TEST 5: stringa vuota (decidi tu la convenzione; spesso 0) */
    char s5[] = "";
    printf("Test 5: s = \"%s\" (stringa vuota)\n", s5);
    printf("matchZigZag(T, \"\") = %d\n\n", matchZigZag(T, s5));
    /* Output atteso: dipende dalla tua scelta (consiglio: 0) */

    freeTree(T);
    return 0;
}
int f(char parola[], Tree t, char prossima, int segna)
    {
        if(t==NULL)
            return 0;
        if(t->c!=parola[segna])
            return 0;
        segna++;
        if(parola[segna]=='\0')
            return 1;
        int sx=0;
        int dx=0;
        if(prossima=='s')
            {
                sx=f(parola, t->left, 'd', segna);
            }
        if(prossima=='d')
            {
                dx=f(parola, t->right, 's', segna);
            }
    return sx  ||  dx;
    }
int matchZigZag(Tree T, char *s)
    {
        if(T==NULL)
            return 0;
        if(f(s, T, 's', 0) || f(s, T, 'd', 0))
            return 1;
    return matchZigZag(T->left, s) || matchZigZag(T->right, s);
    }
