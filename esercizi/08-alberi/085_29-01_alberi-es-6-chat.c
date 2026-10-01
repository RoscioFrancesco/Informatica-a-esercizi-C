//
//  main.c
//  alberi es 6 chat
//
//  Created by Francesco Roscio Ricon on 29/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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



/* ===== ALBERI DI TEST ===== */

/*
  v1 (VALIDO) - completo fino a livello 2:

            4
          /   \
         9     1
        / \   / \
       2  6  8  10

  Livello 0 (pari): [4] ok
  Livello 1 (dispari): [9,1] decrescente ok
  Livello 2 (pari): [2,6,8,10] crescente ok
*/
Tree crea_valido1(void) {
    return nn(4,
              nn(9, nn(2,NULL,NULL), nn(6,NULL,NULL)),
              nn(1, nn(8,NULL,NULL), nn(10,NULL,NULL)));
}

/*
  n1 (NON valido): livello 1 dovrebbe essere decrescente, ma è [1,9]
            4
          /   \
         1     9
*/
Tree crea_nonvalido1(void) {
    return nn(4,
              nn(1,NULL,NULL),
              nn(9,NULL,NULL));
}

/*
  n2 (NON valido): livello 2 pari dovrebbe essere crescente, ma è [2,8,6,10]
            4
          /   \
         9     1
        / \   / \
       2  8  6  10
*/
Tree crea_nonvalido2(void) {
    return nn(4,
              nn(9, nn(2,NULL,NULL), nn(8,NULL,NULL)),
              nn(1, nn(6,NULL,NULL), nn(10,NULL,NULL)));
}

/*
  v2 (VALIDO) - albero non completo, ma l'ordine per livello conta comunque.

            5
          /   \
         7     1
          \     \
           2     9

  Livello 0 pari: [5] ok
  Livello 1 dispari: [7,1] decrescente ok
  Livello 2 pari: nodi da sx a dx sono [2,9] crescente ok
*/
Tree crea_valido2(void) {
    return nn(5,
              nn(7, NULL, nn(2,NULL,NULL)),
              nn(1, NULL, nn(9,NULL,NULL)));
}

/*
  n3 (NON valido) - non completo, ma livello 2 pari è [9,2] non crescente

            5
          /   \
         7     1
          \     \
           9     2
*/
Tree crea_nonvalido3(void) {
    return nn(5,
              nn(7, NULL, nn(9,NULL,NULL)),
              nn(1, NULL, nn(2,NULL,NULL)));
}

/*
  v3 (VALIDO) - singolo nodo (solo livello 0)
*/
Tree crea_singolo(void) {
    return nn(42, NULL, NULL);
}

/*
  v4 (VALIDO) - albero vuoto: convenzione tipica -> vero
*/
Tree crea_vuoto(void) {
    return NULL;
}

/*
  n4 (NON valido) - uguaglianze (se richiediamo ordine stretto)
            4
          /   \
         9     9
  livello 1 dovrebbe essere strettamente decrescente, ma [9,9] no
*/
Tree crea_nonvalido4(void) {
    return nn(4, nn(9,NULL,NULL), nn(9,NULL,NULL));
}

/* ===== MAIN DI TEST ===== */
int checklivello_pari(Tree albero, int liv, int piano, int *val, int *sentinella);
int contalivello(Tree t);
int checklivello_dispari(Tree albero, int liv, int piano, int *val, int *sentinella);
int livelliAlternati(Tree t);
int main(void) {

    struct {
        Tree t;
        int atteso;
        const char *nome;
    } tests[] = {
        {crea_valido1(),    1, "valido1: livelli alternati su 0..2 (completo)"},
        {crea_nonvalido1(), 0, "nonvalido1: livello 1 non decrescente ([1,9])"},
        {crea_nonvalido2(), 0, "nonvalido2: livello 2 non crescente ([2,8,6,10])"},
        {crea_valido2(),    1, "valido2: non completo ma livelli ordinati"},
        {crea_nonvalido3(), 0, "nonvalido3: livello 2 [9,2] non crescente"},
        {crea_singolo(),    1, "singolo: solo livello 0"},
        {crea_vuoto(),      1, "vuoto: convenzione vero"},
        {crea_nonvalido4(), 0, "nonvalido4: uguaglianza rompe ordine stretto"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("Test %d: %s\n", i+1, tests[i].nome);
        printf("  inorder: ");
        stampa_inorder(tests[i].t);
        int res = livelliAlternati(tests[i].t);
        printf("\n  -> %d (atteso %d)\n\n", res, tests[i].atteso);
    }

    return 0;
}
/* ===== ESERCIZIO 6: LIVELLI ALTERNATI =====
   Un albero soddisfa la proprietà se, su ogni livello pari,
   i valori dei nodi sono in ordine crescente da sinistra a destra,
   mentre su ogni livello dispari sono in ordine decrescente.
   Livello 0 = radice.

   La proprietà deve valere per TUTTI i livelli.
*/
int checklivello_pari(Tree albero, int liv, int piano, int *val, int *sentinella)
    {
        if(albero==NULL)
            return 1;
        if(liv==piano)
            {
                if(*sentinella==0)
                {
                    *sentinella=1;
                    *val=albero->val;
                }
                else
                    {
                        if(*val>=albero->val)
                            return 0;
                        *val=albero->val;
                    }
            }
    return checklivello_pari(albero->left, liv, piano+1, val, sentinella) &&checklivello_pari(albero->right, liv, piano+1, val, sentinella);
    }
int checklivello_dispari(Tree albero, int liv, int piano, int *val, int *sentinella)
    {
    if(albero==NULL)
        return 1;
    if(liv==piano)
        {
            if(*sentinella==0)
            {
                *sentinella=1;
                *val=albero->val;
            }
            else
                {
                    if(*val<=albero->val)
                        return 0;
                    *val=albero->val;
                }
        }
return checklivello_dispari(albero->left, liv, piano+1, val, sentinella) &&checklivello_dispari(albero->right, liv, piano+1, val, sentinella);
    }
int max(int a, int b)
    {
    if(a>b)
        return a;
    return b;
}
int contalivello(Tree t)
    {
        if(t==NULL)
            return 0;
    int sx=contalivello(t->left);
    int dx=contalivello(t->right);
    return 1+max(sx, dx);
    }

int livelliAlternati(Tree t)
    {
    int prof=contalivello(t);
    for(int i=0; i<prof; i++)
        {
            if(i%2==0)
            {   int val=0;
                int sentinella=0;
                int p=checklivello_pari(t, i, 0, &val, &sentinella);
                if(p==0)
                    return 0;
            }
            if(i%2==1)
            {
                int val=0;
                int sentinella=0;
                int d=checklivello_dispari(t, i, 0, &val, &sentinella);
                if(d==0)
                    return 0;
            }
        }
    return 1;
    }
