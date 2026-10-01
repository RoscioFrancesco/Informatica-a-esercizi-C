//
//  main.c
//  alberi es 5 chat
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
int quasiZigZag(Tree t);


/* ===== ALBERI DI TEST ===== */

/*
  t1 (zig-zag PERFETTO, quindi anche quasi zig-zag):
        0
       / \
      1   9
       \
        2
       /
      3

  Cammino: 0 -> 1 -> 2 -> 3
  Dir: sx, dx, sx   (0 violazioni) => 1
*/
Tree crea_t1(void) {
    return nn(0,
              nn(1, NULL, nn(2, nn(3, NULL, NULL), NULL)),
              nn(9, NULL, NULL));
}

/*
  t2 (1 SOLA violazione ammessa):
        0
       /
      1
     /
    2
     \
      3

  Cammino: 0 -> 1 -> 2 -> 3
  Dir: sx, sx, dx  (una violazione: sx,sx) => 1
*/
Tree crea_t2(void) {
    return nn(0,
              nn(1,
                 nn(2, NULL, nn(3, NULL, NULL)),
                 NULL),
              NULL);
}

/*
  t3 (DUE violazioni -> NO):
        0
       /
      1
     /
    2
   /
  3

  Cammino: 0->1->2->3
  Dir: sx,sx,sx  (violazioni: 0->1 e 1->2) = 2 => 0
*/
Tree crea_t3(void) {
    return nn(0,
              nn(1,
                 nn(2,
                    nn(3, NULL, NULL),
                    NULL),
                 NULL),
              NULL);
}

/*
  t4 (solo un ramo è valido: deve trovare "esiste"):
            0
           / \
          1   9
         /     \
        2       8
         \     /
          3   7

  Ramo sinistro: 0->1->2->3 : sx,sx,dx (1 violazione) => valido
  Ramo destro : 0->9->8->7 : dx,dx,sx (1 violazione) => valido
  => 1
*/
Tree crea_t4(void) {
    return nn(0,
              nn(1,
                 nn(2, NULL, nn(3, NULL, NULL)),
                 NULL),
              nn(9, NULL,
                 nn(8, nn(7, NULL, NULL), NULL)));
}

/*
  t5 (nessun cammino valido):
        0
       / \
      1   2
     /     \
    3       4
   /         \
  5           6

  Cammino sx: 0-1-3-5: sx,sx,sx (>=2 violazioni) => no
  Cammino dx: 0-2-4-6: dx,dx,dx (>=2 violazioni) => no
  => 0
*/
Tree crea_t5(void) {
    return nn(0,
              nn(1, nn(3, nn(5, NULL, NULL), NULL), NULL),
              nn(2, NULL, nn(4, NULL, nn(6, NULL, NULL))));
}

/*
  t6 (singolo nodo): cammino di lunghezza 0 => 1 (nessuna violazione)
*/
Tree crea_t6(void) {
    return nn(7, NULL, NULL);
}

/* ===== MAIN DI TEST ===== */

int main(void) {

    struct {
        Tree t;
        int atteso;
        const char *nome;
    } tests[] = {
        {crea_t1(), 1, "t1: zig-zag perfetto (0 violazioni)"},
        {crea_t2(), 1, "t2: una violazione (sx,sx,dx)"},
        {crea_t3(), 0, "t3: due violazioni (sx,sx,sx)"},
        {crea_t4(), 1, "t4: esiste un cammino valido (anche due)"},
        {crea_t5(), 0, "t5: nessun cammino valido"},
        {crea_t6(), 1, "t6: singolo nodo (0 mosse)"},
        {NULL,      0, "albero vuoto (nessun cammino)"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("Test %d: %s\n", i+1, tests[i].nome);
        printf("  inorder: ");
        stampa_inorder(tests[i].t);
        int res = quasiZigZag(tests[i].t);
        printf("\n  -> %d (atteso %d)\n\n", res, tests[i].atteso);
    }

    return 0;
}

int quasiZigZag(Tree t);

int f(Tree t, int dir, int count) // dir=1 vado a sx, dir=0 vado a dx
    {
        if(t==NULL)
            return 0;
        if(t->left==NULL && t->right==NULL)
            return 1;
        if(count==1)
        {
            if(dir==1)
            {
                if(t->left==NULL)
                    return 0;
                return f(t->left, 0, count);
            }
            if(dir==0)
            {
                if(t->right==NULL)
                    return 0;
                return f(t->right, 1, count);
            }
        }
        else
        {
            if(dir==1)
            {
                return f(t->left, 0, count) || f(t->right, 1, count+1);
            }
            if(dir==0)
                return f(t->right, 1, count) || f(t->left, 0, count+1);
        }
        return 0;
    }
int quasiZigZag(Tree t)
    {
    return f(t, 0, 0)||f(t, 1, 0);
    }
