//
//  main.c
//  alberi es 8 chat
//
//  Created by Francesco Roscio Ricon on 29/01/26.
//
#include <stdio.h>
#include <stdlib.h>

/* ===== STRUTTURE ===== */

typedef struct nodo {
    int val;
    struct nodo *left, *right;
} Nodo;

typedef Nodo* Tree;

/* ===== UTILS ===== */

Tree nn(int v, Tree l, Tree r) {
    Tree t = malloc(sizeof(Nodo));
    if (!t) { perror("malloc"); exit(1); }
    t->val = v;
    t->left = l;
    t->right = r;
    return t;
}

void stampa_inorder(Tree t) {
    if (!t) return;
    printf("(");
    stampa_inorder(t->left);
    printf(" %d ", t->val);
    stampa_inorder(t->right);
    printf(")");
}



int tuttiCamminiPositivi(Tree t);


/* ===== ALBERI DI TEST ===== */

/* t1 (valido): tutti i cammini hanno somma > 0
        5
       / \
      2   1
     / \   \
    1  1    2
   Cammini:
    5-2-1 = 8
    5-2-1 = 8
    5-1-2 = 8
*/
Tree crea_valido1(void) {
    return nn(5,
              nn(2, nn(1,NULL,NULL), nn(1,NULL,NULL)),
              nn(1, NULL, nn(2,NULL,NULL)));
}

/* t2 (non valido): esiste un cammino con somma = 0
        2
       / \
     -2   5
    /
    0
   Cammini:
    2-(-2)-0 = 0  -> NON valido
    2-5 = 7        -> ok
*/
Tree crea_nonvalido1(void) {
    return nn(2,
              nn(-2, nn(0,NULL,NULL), NULL),
              nn(5, NULL, NULL));
}

/* t3 (non valido): esiste un cammino con somma negativa
       -1
       / \
      2  -3
         /
       -4
   Cammini:
    -1 + 2 = 1     -> ok
    -1-3-4 = -8    -> NON valido
*/
Tree crea_nonvalido2(void) {
    return nn(-1,
              nn(2,NULL,NULL),
              nn(-3, nn(-4,NULL,NULL), NULL));
}

/* t4 (valido con negativi): comunque tutte le somme > 0
        3
       / \
     -1   4
     /     \
    5      -1
   Cammini:
    3-1+5 = 7
    3+4-1 = 6
*/
Tree crea_valido2(void) {
    return nn(3,
              nn(-1, nn(5,NULL,NULL), NULL),
              nn(4, NULL, nn(-1,NULL,NULL)));
}

/* t5 (non valido): foglia con somma <= 0 su albero a catena
    1
     \
     -1
       \
       -1
   Cammino: 1-1-1 = -1 -> NON valido
*/
Tree crea_nonvalido3(void) {
    return nn(1, NULL,
              nn(-1, NULL,
                 nn(-1, NULL, NULL)));
}

/* t6: singolo nodo positivo (valido)
   [7] -> unico cammino somma 7 > 0
*/
Tree crea_singolo_pos(void) {
    return nn(7,NULL,NULL);
}

/* t7: singolo nodo zero (non valido)
   [0] -> unico cammino somma 0 (non strettamente positiva)
*/
Tree crea_singolo_zero(void) {
    return nn(0,NULL,NULL);
}

/* t8: albero vuoto (convenzione nei test: 1, vacuamente vero)
   Se il tuo prof vuole 0, cambia atteso nel main.
*/
Tree crea_vuoto(void) {
    return NULL;
}

/* ===== MAIN DI TEST ===== */

int main(void) {

    struct {
        Tree t;
        int atteso;
        const char *nome;
    } tests[] = {
        {crea_valido1(),      1, "valido1: tutte somme > 0"},
        {crea_nonvalido1(),   0, "nonvalido1: esiste cammino somma = 0"},
        {crea_nonvalido2(),   0, "nonvalido2: esiste cammino somma < 0"},
        {crea_valido2(),      1, "valido2: negativi ammessi ma somme > 0"},
        {crea_nonvalido3(),   0, "nonvalido3: catena con somma negativa"},
        {crea_singolo_pos(),  1, "singolo positivo"},
        {crea_singolo_zero(), 0, "singolo zero"},
        {crea_vuoto(),        1, "albero vuoto (vacuamente vero)"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("Test %d: %s\n", i+1, tests[i].nome);
        printf("  inorder: ");
        stampa_inorder(tests[i].t);
        int res = tuttiCamminiPositivi(tests[i].t);
        printf("\n  -> %d (atteso %d)\n\n", res, tests[i].atteso);
    }

    return 0;
}

int funz(Tree albero, int somma)
    {
        if(albero==NULL)
            return 1;
        somma=somma+albero->val;
        if(albero->left==NULL && albero->right==NULL)
        {
            if(somma>0)
                return 1;
            return 0;
        }
    return funz(albero->left, somma) &&funz(albero->right, somma);
    }
int tuttiCamminiPositivi(Tree t)
    {
    return funz(t, 0);
    }
