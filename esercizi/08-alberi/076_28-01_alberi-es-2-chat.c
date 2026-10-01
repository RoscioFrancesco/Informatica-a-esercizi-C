//
//  main.c
//  alberi es 2 chat
//
//  Created by Francesco Roscio Ricon on 28/01/26.
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
/* ===== ALBERI DI TEST ===== */

/*
  t1:
        5
       / \
      3   8
     / \   \
    2   4   9

  Cammini:
   5-3-2: max=5 min=2 diff=3
   5-3-4: max=5 min=3 diff=2
   5-8-9: max=9 min=5 diff=4
*/
Tree crea_t1(void) {
    return nn(5,
              nn(3, nn(2,NULL,NULL), nn(4,NULL,NULL)),
              nn(8, NULL, nn(9,NULL,NULL)));
}

/*
  t2:
        10
       /  \
      1    20
           /
          30

  Cammini:
    10-1:     diff=9
    10-20-30: max=30 min=10 diff=20
*/
Tree crea_t2(void) {
    return nn(10,
              nn(1,NULL,NULL),
              nn(20, nn(30,NULL,NULL), NULL));
}

/*
  t3 (tutto uguale):
        7
       / \
      7   7
         /
        7
  Tutti i cammini diff=0
*/
Tree crea_t3(void) {
    return nn(7,
              nn(7,NULL,NULL),
              nn(7, nn(7,NULL,NULL), NULL));
}

/*
  t4 (un solo cammino valido, gli altri no):
          50
         /  \
        49   10
       /       \
      48        100

  Cammini:
    50-49-48: diff=2  (valido per K>=2)
    50-10-100: max=100 min=10 diff=90 (quasi sempre non valido)
*/
Tree crea_t4(void) {
    return nn(50,
              nn(49, nn(48,NULL,NULL), NULL),
              nn(10, NULL, nn(100,NULL,NULL)));
}

/* ===== MAIN DI TEST ===== */

int esisteCamminoLimitato(Tree t, int K);
int f(Tree t, int K, int min, int max);
int main(void) {

    struct {
        Tree t;
        int K;
        int atteso;
        const char *nome;
    } tests[] = {
        {crea_t1(), 2, 1, "t1 con K=2 (esiste 5-3-4 diff=2)"},
        {crea_t1(), 1, 0, "t1 con K=1 (nessun cammino diff<=1)"},
        {crea_t2(), 9,  1, "t2 con K=9 (cammino 10-1 diff=9)"},
        {crea_t2(), 8,  0, "t2 con K=8 (10-1 diff=9, 10-20-30 diff=20)"},
        {crea_t3(), 0,  1, "t3 con K=0 (tutti diff=0)"},
        {crea_t3(), 5,  1, "t3 con K=5 (sempre 1)"},
        {crea_t4(), 2,  1, "t4 con K=2 (valido solo a sinistra)"},
        {crea_t4(), 1,  0, "t4 con K=1 (diff minimo è 2)"},
        {NULL,      0,  0, "albero vuoto (qui scegliamo 0: nessun cammino)"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("Test %d: %s\n", i+1, tests[i].nome);
        printf("  inorder: ");
        stampa_inorder(tests[i].t);
        int res = esisteCamminoLimitato(tests[i].t, tests[i].K);
        printf("\n  -> %d (atteso %d)\n\n", res, tests[i].atteso);
    }

    return 0;
}

int f(Tree t, int K, int min, int max)
    {
        if(t==NULL)
            return 0;
        if(max==0)
            max=t->val;
        if(min==0)
            min=t->val;
        if(t->val>max)
            max=t->val;
        if(min>t->val)
            min=t->val;
        if(t->left==NULL && t->right==NULL)
            {
                if(max-min<=K)
                    return 1;
                return 0;
            }
    return f(t->left, K, min, max) || f(t->right, K, min, max);
    }

int esisteCamminoLimitato(Tree t, int K)
    {
    return f(t, K, 0, 0);
    }
