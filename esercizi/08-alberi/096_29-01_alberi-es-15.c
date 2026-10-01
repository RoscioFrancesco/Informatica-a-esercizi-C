//
//  main.c
//  alberi es 15
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



int bilanciatoPerSomma(Tree t, int K);


/* ===== ALBERI DI TEST ===== */

/*
 t1 (bilanciato per K=0):
        0
       / \
      1  -1
  somma sx = 1, somma dx = -1 => diff=2 (NON per K=0)
  Quindi: per K=2 è bilanciato, per K=1 no.
*/
Tree crea_t1(void) {
    return nn(0,
              nn(1,NULL,NULL),
              nn(-1,NULL,NULL));
}

/*
 t2 (bilanciato per K=1):
          5
         / \
        2   1
       / \
      1   1

  Somme:
   nodo 2: sx=1 dx=1 diff=0
   nodo 5: sx=(2+1+1)=4 dx=1 diff=3  -> serve K>=3
*/
Tree crea_t2(void) {
    return nn(5,
              nn(2, nn(1,NULL,NULL), nn(1,NULL,NULL)),
              nn(1,NULL,NULL));
}

/*
 t3 (molto sbilanciato):
        10
       /
      5
     /
    2

  somma sx di 10 = 7, dx = 0 diff=7
  somma sx di 5  = 2, dx = 0 diff=2
*/
Tree crea_t3(void) {
    return nn(10,
              nn(5, nn(2,NULL,NULL), NULL),
              NULL);
}

/*
 t4 (bilanciato anche con negativi):
         3
        / \
      -2   1
      /     \
     1      -1

  Somme:
   nodo -2: sx=1 dx=0 diff=1
   nodo  1 (dx): sx=0 dx=-1 diff=1
   nodo  3: sx=(-2+1)=-1 dx=(1-1)=0 diff=1
  => bilanciato per K>=1
*/
Tree crea_t4(void) {
    return nn(3,
              nn(-2, nn(1,NULL,NULL), NULL),
              nn(1, NULL, nn(-1,NULL,NULL)));
}

/*
 t5 (trucco: root sembra ok ma un nodo interno NO):
           0
          / \
         4   4
        /
      10

  Somme:
   root 0: sx=14 dx=4 diff=10
   nodo 4(sx): sx=10 dx=0 diff=10
  => per K=10 ok, per K=9 no
*/
Tree crea_t5(void) {
    return nn(0,
              nn(4, nn(10,NULL,NULL), NULL),
              nn(4,NULL,NULL));
}

/* t6: albero vuoto (vacuamente bilanciato) */
Tree crea_vuoto(void) { return NULL; }

/* t7: singolo nodo (sempre bilanciato) */
Tree crea_singolo(void) { return nn(7,NULL,NULL); }

/* ===== MAIN DI TEST ===== */

int main(void) {

    struct {
        Tree t;
        int K;
        int atteso;
        const char *nome;
    } tests[] = {
        {crea_t1(), 1, 0, "t1 con K=1 (diff root=2)"},
        {crea_t1(), 2, 1, "t1 con K=2 (diff root=2)"},
        {crea_t2(), 2, 0, "t2 con K=2 (root diff=3)"},
        {crea_t2(), 3, 1, "t2 con K=3 (root diff=3)"},
        {crea_t3(), 6, 0, "t3 con K=6 (root diff=7)"},
        {crea_t3(), 7, 1, "t3 con K=7 (root diff=7)"},
        {crea_t4(), 0, 0, "t4 con K=0 (diff=1 in vari nodi)"},
        {crea_t4(), 1, 1, "t4 con K=1 (tutto diff<=1)"},
        {crea_t5(), 9, 0, "t5 con K=9 (diff=10 interno e root)"},
        {crea_t5(),10, 1, "t5 con K=10 (diff=10 interno e root)"},
        {crea_vuoto(), 0, 1, "vuoto (vacuamente bilanciato)"},
        {crea_singolo(), 0, 1, "singolo (sempre bilanciato)"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("Test %d: %s\n", i+1, tests[i].nome);
        printf("  inorder: ");
        stampa_inorder(tests[i].t);
        int res = bilanciatoPerSomma(tests[i].t, tests[i].K);
        printf("\n  -> %d (atteso %d)\n\n", res, tests[i].atteso);
    }

    return 0;
}

int bilanciatoPerSomma(Tree t, int K);


// t1 (bilanciato per K=0):
//        0
//       / \
//      1  -1
//  somma sx = 1, somma dx = -1 => diff=2 (NON per K=0)
//  Quindi: per K=2 è bilanciato, per K=1 no.

int sommaalbero(Tree albero)
    {
        if(albero==NULL)
            return 0;
    return albero->val+sommaalbero(albero->left)+sommaalbero(albero->right);
    }
int bilanciatoPerSomma(Tree t, int K)
    {
        if(t==NULL)
            return 1;
        if(abs(sommaalbero(t->left)-sommaalbero(t->right))>K)
            return 0;
    return bilanciatoPerSomma(t->left, K) && bilanciatoPerSomma(t->right, K);
    }
