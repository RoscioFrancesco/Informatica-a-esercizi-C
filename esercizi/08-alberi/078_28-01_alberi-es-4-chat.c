//
//  main.c
//  alberi es 4 chat
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



int zigZagACoppie(Tree t);


/* ===== ALBERI DI TEST ===== */

/*
  v1 (VALIDO):
          0
         / \
        1   9
       /
      2
       \
        3
         \
          4

  Cammino: 0 -> 1 -> 2 -> 3 -> 4
  Direzioni: sx, sx, dx, dx   (pattern a coppie OK)
*/
Tree crea_valido1(void) {
    return nn(0,
              nn(1,
                 nn(2, NULL,
                    nn(3, NULL,
                       nn(4, NULL, NULL))),
                 NULL),
              nn(9, NULL, NULL));
}

/*
  n1 (NON valido):
        0
       /
      1
       \
        2
         \
          3

  Direzioni: sx, dx, dx
  Non può essere sx,sx,dx,dx... (già alla seconda mossa rompe)
  Né dx,dx,sx,sx... (prima è sx)
*/
Tree crea_nonvalido1(void) {
    return nn(0,
              nn(1, NULL,
                 nn(2, NULL,
                    nn(3, NULL, NULL))),
              NULL);
}

/*
  v2 (VALIDO, parte con dx,dx,sx,sx):
        0
         \
          1
           \
            2
           /
          3
         /
        4

  Direzioni: dx, dx, sx, sx  (pattern a coppie OK)
*/
Tree crea_valido2(void) {
    return nn(0, NULL,
              nn(1, NULL,
                 nn(2,
                    nn(3,
                       nn(4, NULL, NULL),
                       NULL),
                    NULL)));
}

/*
  n2 (NON valido): solo catena a sinistra lunga, pattern richiede sx,sx poi dx,dx,
  ma qui hai sx,sx,sx,... senza possibilità di fare dx.
      0
     /
    1
   /
  2
 /
3
*/
Tree crea_nonvalido2(void) {
    return nn(0,
              nn(1,
                 nn(2,
                    nn(3, NULL, NULL),
                    NULL),
                 NULL),
              NULL);
}

/*
  v3 (VALIDO): albero singolo nodo (0 mosse)
*/
Tree crea_singolo(void) {
    return nn(7, NULL, NULL);
}

/*
  v4 (VALIDO): 1 sola mossa (qualunque direzione), considerata valida
      7
     /
    8
*/
Tree crea_due_nodi(void) {
    return nn(7, nn(8, NULL, NULL), NULL);
}

/* ===== MAIN DI TEST ===== */

int main(void) {

    struct {
        Tree t;
        int atteso;
        const char *nome;
    } tests[] = {
        {crea_valido1(),    1, "valido1: esiste cammino sx,sx,dx,dx"},
        {crea_nonvalido1(), 0, "nonvalido1: sx,dx,dx rompe subito"},
        {crea_valido2(),    1, "valido2: esiste cammino dx,dx,sx,sx"},
        {crea_nonvalido2(), 0, "nonvalido2: solo sx,sx,sx..."},
        {crea_singolo(),    1, "singolo nodo: valido (0 mosse)"},
        {crea_due_nodi(),   1, "due nodi: valido (1 mossa)"},
        {NULL,              0, "albero vuoto: nessun cammino"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("Test %d: %s\n", i+1, tests[i].nome);
        printf("  inorder: ");
        stampa_inorder(tests[i].t);
        int res = zigZagACoppie(tests[i].t);
        printf("\n  -> %d (atteso %d)\n\n", res, tests[i].atteso);
    }

    return 0;
}
int f(Tree albero, int dir, int count) // dir=1 vai a dx, dir=0 vai a sx
    {
        if(albero==NULL)
            return 0;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
        if(count==0 || count==1)
            {
                if(dir==1)
                    {
                        if(albero->right==NULL)
                            return 0;
                        return f(albero->right, 1, count+1);
                    }
                if(dir==0)
                    {
                        if(albero->left==NULL)
                            return 0;
                        return f(albero->left, 0, count+1);
                    }
            }
        if(count==2)
            {
                if(dir==1)
                    {
                        if(albero->left==NULL)
                            return 0;
                        return f(albero->left, 0, 0);
                    }
                if(dir==0)
                    {
                        if(albero->right==NULL)
                            return 0;
                        return f(albero->right, 1,0);
                    }
            }
        return 0;
    }
int zigZagACoppie(Tree t)
    {
    return f(t, 0, 0)||f(t, 1, 0);
    }
