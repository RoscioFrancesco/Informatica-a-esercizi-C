//  Created by Francesco Roscio Ricon on 29/01/26.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

static int iabs(int x) { return (x < 0) ? -x : x; }

void stampa_inorder(Tree t) {
    if (!t) return;
    printf("(");
    stampa_inorder(t->left);
    printf(" %d ", t->val);
    stampa_inorder(t->right);
    printf(")");
}



int segniAlternatiAssolutiCrescenti(Tree t);


/* ===== ALBERI DI TEST ===== */

/*
  v1 (VALIDO):
          2
         /
       -3
       /
       5

  Cammino: 2, -3, 5
  segni: +, -, + (alternanza ok)
  |.|:  2 < 3 < 5 (crescente stretta) => 1
*/
Tree crea_valido1(void) {
    return nn(2,
              nn(-3, nn(5, NULL, NULL), NULL),
              NULL);
}

/*
  n1 (NON valido): segni alternano ma assoluti non crescono
        2
         \
         -3
           \
           3

  segni: +, -, + ok
  |.|: 2 < 3 ma 3 !< 3 (non strettamente) => 0
*/
Tree crea_nonvalido1(void) {
    return nn(2, NULL,
              nn(-3, NULL,
                 nn(3, NULL, NULL)));
}

/*
  n2 (NON valido): assoluti crescono ma segni non alternano
        1
       /
      2
     /
     3

  segni: +,+,+ (no) => 0
*/
Tree crea_nonvalido2(void) {
    return nn(1,
              nn(2, nn(3, NULL, NULL), NULL),
              NULL);
}

/*
  n3 (NON valido): contiene 0 (qui 0 rompe alternanza)
        1
       /
      0
     /
    -2

  0 non è + né -, quindi cammino non valido => 0
*/
Tree crea_nonvalido3(void) {
    return nn(1,
              nn(0, nn(-2, NULL, NULL), NULL),
              NULL);
}

/*
  v2 (VALIDO): cammino valido in un ramo, altri no
             -1
            /   \
           2     -2
          /       \
        -4         3
        /
       7

  Cammino valido: -1, 2, -4, 7
  segni: -, +, -, + ok
  |.|:  1 < 2 < 4 < 7 ok => 1
*/
Tree crea_valido2(void) {
    return nn(-1,
              nn(2, nn(-4, nn(7, NULL, NULL), NULL), NULL),
              nn(-2, NULL, nn(3, NULL, NULL)));
}

/*
  n4 (NON valido): max cammino alterna segni ma assoluti non crescono
         -2
         / \
        3  -3

  Cammini:
   -2->3: segni -,+ ok, |.| 2<3 ok (lunghezza 2) => sarebbe valido
  Per renderlo NON valido devo fare assoluti uguali:
         -2
           \
            2
  segni: -,+ ok, |.| 2 !< 2 => 0
*/
Tree crea_nonvalido4(void) {
    return nn(-2, NULL, nn(2, NULL, NULL));
}

/*
  v3 (VALIDO): due nodi possono essere validi se:
    segni alternano e |.| cresce
      -1
        \
         2
  => 1
*/
Tree crea_valido3(void) {
    return nn(-1, NULL, nn(2, NULL, NULL));
}

/*
  n5 (NON valido): singolo nodo non può alternare? (convenzione qui: cammino di lunghezza 1 è valido
  perché non viola alternanza e assoluti sono "vacuamente" crescenti).
  Se nel tuo corso vogliono almeno 2 nodi, cambia atteso a 0.
*/
Tree crea_singolo(void) {
    return nn(5, NULL, NULL);
}

/* ===== MAIN DI TEST ===== */
int f(Tree albero, int expect, int prev) ;
int main(void) {

    struct {
        Tree t;
        int atteso;
        const char *nome;
    } tests[] = {
        {crea_valido1(),    1, "valido1: +,-,+ e |.| crescente"},
        {crea_nonvalido1(), 0, "nonvalido1: segni ok ma |.| non stretta (..3,3)"},
        {crea_nonvalido2(), 0, "nonvalido2: |.| cresce ma segni non alternano"},
        {crea_nonvalido3(), 0, "nonvalido3: contiene 0 (rompe alternanza)"},
        {crea_valido2(),    1, "valido2: esiste un ramo valido lungo"},
        {crea_nonvalido4(), 0, "nonvalido4: segni ok ma |.| non cresce (2,2)"},
        {crea_valido3(),    1, "valido3: due nodi validi"},
        {crea_singolo(),    1, "singolo nodo (vacuamente valido)"},
        {NULL,              0, "albero vuoto: nessun cammino"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("Test %d: %s\n", i+1, tests[i].nome);
        printf("  inorder: ");
        stampa_inorder(tests[i].t);
        int res = segniAlternatiAssolutiCrescenti(tests[i].t);
        printf("\n  -> %d (atteso %d)\n\n", res, tests[i].atteso);
    }

    return 0;
}



int segniAlternatiAssolutiCrescenti(Tree t)
    {
    if(t==NULL)
        return 0;
    if(t->left==NULL && t->right==NULL)
        return 1;
    int expect;
    if(t->val>0)
    {
        expect=-1;
    }
    else
    {
        expect=1;
    }
    return f(t->left, expect, t->val)||f(t->right, expect, t->val);
    }

int f(Tree albero, int expect, int prev) // expect=1 ci si aspetta psozitivo, expect=-1 ci si apsetaa negativo
    {
        if(albero==NULL)
            return 0;
        if(albero->val*expect<=0)
            return 0;
        if(abs(prev)>=abs(albero->val))
            return 0;
        expect=-expect;
        prev=albero->val;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
        return f(albero->left, expect, prev) || f(albero->right, expect, prev);
    }

