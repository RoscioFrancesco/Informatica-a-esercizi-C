//
//  main.c
//  zig zag 2
//
//  Created by Francesco Roscio Ricon on 28/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===== STRUTTURE ===== */

typedef struct El {
    char c;
    struct El *left, *right;
} Nodo;

typedef Nodo *Tree;

/* ===== UTILITIES ===== */

Tree nn(char c, Tree l, Tree r) {
    Tree t = (Tree)malloc(sizeof(Nodo));
    if (!t) {
        perror("malloc");
        exit(1);
    }
    t->c = c;
    t->left = l;
    t->right = r;
    return t;
}

/*
                 c
               /   \
              i     s
             / \   / \
            a   p k   r
             \         \
              o         w
*/
Tree crea(void) {
    return nn('c',
              nn('i',
                 nn('a', NULL, nn('o', NULL, NULL)),
                 nn('p', NULL, NULL)),
              nn('s',
                 nn('k', NULL, NULL),
                 nn('r', NULL, nn('w', NULL, NULL))));
}

void stampa(Tree t) {
    if (!t) return;
    printf("(");
    if (t->left) stampa(t->left);
    printf(" %c ", t->c);
    if (t->right) stampa(t->right);
    printf(")");
}

/* ===== ZIG-ZAG (PAROLA) =====
   Zig-zag: ad ogni passo devi alternare la direzione.
   - dir = 0 => il PROSSIMO passo deve andare a sinistra
   - dir = 1 => il PROSSIMO passo deve andare a destra

   parolaZigZag(t, parola):
   ritorna 1 se esiste un cammino discendente che scrive tutta la parola
   rispettando lo zig-zag, partendo da QUALSIASI nodo e con entrambe le
   direzioni iniziali permesse.
*/

int matchZigZagFrom(Tree t, const char *p, int i, int dir) {
    if (!t) return 0;
    if (t->c != p[i]) return 0;

    if (p[i + 1] == '\0') return 1;

    if (dir == 0) {
        return matchZigZagFrom(t->left, p, i + 1, 1);
    } else {
        return matchZigZagFrom(t->right, p, i + 1, 0);
    }
}

int parolaZigZag(Tree t, const char *parola) {
    if (!parola) return 0;
    if (!t) return 0;

    /* Provo a far partire la parola da questo nodo, con entrambe le direzioni iniziali */
    if (matchZigZagFrom(t, parola, 0, 0) || matchZigZagFrom(t, parola, 0, 1))
        return 1;
    
    return parolaZigZag(t->left, parola) || parolaZigZag(t->right, parola);
}


int main(void) {
    Tree t = crea();

    printf("Albero: ");
    stampa(t);
    printf("\n\n");

    const char *tests[] = {
        "c",
        "ci",
        "cip",   /* c->i->p (sx,dx)  OK */
        "cia",   /* c->i->a (sx,sx)  NO */
        "ciao",  /* c->i->a->o (sx,sx,dx) NO */
        "iao",   /* i->a->o (sx,dx)  OK */
        "sr",    /* s->r (dx)        OK */
        "srw",   /* s->r->w (dx,dx)  NO */
        "ir",    /* non esiste       NO */
        NULL
    };

    for (int k = 0; tests[k] != NULL; k++) {
        printf("%s -> %d\n", tests[k], parolaZigZag(t, tests[k]));
    }

    return 0;
}
