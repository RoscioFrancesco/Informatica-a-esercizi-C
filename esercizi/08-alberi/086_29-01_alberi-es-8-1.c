//
//  main.c
//  alberi es 8.1
//
//  Created by Francesco Roscio Ricon on 29/01/26.
//
#include <stdio.h>
#include <stdlib.h>
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
int tuttiCamminiPositiviDaOgniNodo(Tree t);


/* ===== ALBERI DI TEST ===== */

/* t1 (valido): tutti i cammini da ogni nodo sono >0
        5
       / \
      2   1
     / \   \
    1  1    2
   - Da 5: 5-2-1=8, 5-2-1=8, 5-1-2=8
   - Da 2: 2-1=3, 2-1=3
   - Da 1: 1 (foglia) >0
*/
Tree crea_valido1(void) {
    return nn(5,
              nn(2, nn(1,NULL,NULL), nn(1,NULL,NULL)),
              nn(1, NULL, nn(2,NULL,NULL)));
}

/* t2 (NON valido): root->foglia è >0, ma da un nodo interno no
        10
       /
     -5
   Cammino da 10 a foglia: 10 + (-5) = 5  (positivo)
   Ma da nodo -5 a foglia: -5 (NON positivo) => deve dare 0
*/
Tree crea_nonvalido1(void) {
    return nn(10,
              nn(-5, NULL, NULL),
              NULL);
}

/* t3 (NON valido): esiste cammino da nodo interno con somma 0
        6
       /
     -2
     /
     2
   Da 6: 6-2+2 = 6 (ok)
   Da -2: -2 + 2 = 0 (NON >0) => 0
*/
Tree crea_nonvalido2(void) {
    return nn(6,
              nn(-2, nn(2,NULL,NULL), NULL),
              NULL);
}

/* t4 (NON valido): una foglia negativa basta a fallire (perché cammino foglia->foglia)
        3
       / \
      2  -1
*/
Tree crea_nonvalido3(void) {
    return nn(3,
              nn(2,NULL,NULL),
              nn(-1,NULL,NULL));
}

/* t5 (valido con negativi): possibili negativi, ma ogni cammino da ogni nodo resta >0
        4
       / \
     -1   3
     /
    5
   Da 4: 4-1+5=8 e 4+3=7
   Da -1: -1+5=4
   Da 5: 5
*/
Tree crea_valido2(void) {
    return nn(4,
              nn(-1, nn(5,NULL,NULL), NULL),
              nn(3, NULL, NULL));
}

/* t6: singolo nodo positivo -> valido */
Tree crea_singolo_pos(void) {
    return nn(7,NULL,NULL);
}

/* t7: singolo nodo zero -> non valido (cammino nodo->nodo somma 0) */
Tree crea_singolo_zero(void) {
    return nn(0,NULL,NULL);
}

/* t8: albero vuoto -> convenzione: 1 (vacuamente vero) */
Tree crea_vuoto(void) {
    return NULL;
}

/* ===== MAIN DI TEST ===== */
int funz(Tree albero, int somma);
int main(void) {

    struct {
        Tree t;
        int atteso;
        const char *nome;
    } tests[] = {
        {crea_valido1(),      1, "valido1: tutte le somme da ogni nodo sono >0"},
        {crea_nonvalido1(),   0, "nonvalido1: root ok ma foglia -5 fallisce"},
        {crea_nonvalido2(),   0, "nonvalido2: da nodo -2 esiste cammino somma 0"},
        {crea_nonvalido3(),   0, "nonvalido3: foglia negativa (-1)"},
        {crea_valido2(),      1, "valido2: negativi ammessi ma tutte le somme >0"},
        {crea_singolo_pos(),  1, "singolo positivo"},
        {crea_singolo_zero(), 0, "singolo zero"},
        {crea_vuoto(),        1, "albero vuoto (vacuamente vero)"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("Test %d: %s\n", i+1, tests[i].nome);
        printf("  inorder: ");
        stampa_inorder(tests[i].t);
        int res = tuttiCamminiPositiviDaOgniNodo(tests[i].t);
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
int tuttiCamminiPositiviDaOgniNodo(Tree t)
    {
        if(t==NULL)
            return 1;
        if(funz(t, 0)==0)
            return 0;
    return tuttiCamminiPositiviDaOgniNodo(t->left)&& tuttiCamminiPositiviDaOgniNodo(t->right);
    }
