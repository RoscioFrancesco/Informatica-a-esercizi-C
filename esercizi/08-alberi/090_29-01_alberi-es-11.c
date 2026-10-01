//
//  main.c
//  alberi es 11
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
/* ===== ALBERI DI TEST ===== */

/*
  t1:
          0
         / \
        0   0
       /     \
      0       0
       \     /
        0   0

  Cammino A: root -> left -> left -> right
    direzioni: L, L, R
    cambi: tra L e L (0), tra L e R (1) => K=1

  Cammino B: root -> right -> right -> left
    direzioni: R, R, L
    cambi: 1
*/
Tree crea_t1(void) {
    return nn(0,
              nn(0,
                 nn(0, NULL, nn(0, NULL, NULL)),
                 NULL),
              nn(0,
                 NULL,
                 nn(0, nn(0, NULL, NULL), NULL)));
}

/*
  t2: linea tutta a sinistra (nessun cambio possibile)
      0
     /
    0
   /
  0
 /
0
  Ogni cammino ha direzioni: L,L,L => cambi = 0
*/
Tree crea_t2(void) {
    return nn(0,
              nn(0,
                 nn(0,
                    nn(0, NULL, NULL),
                    NULL),
                 NULL),
              NULL);
}

/*
  t3: zig-zag perfetto lungo un cammino
      0
       \
        0
       /
      0
       \
        0
  direzioni: R, L, R  => cambi = 2
*/
Tree crea_t3(void) {
    return nn(0,
              NULL,
              nn(0,
                 nn(0, NULL, nn(0, NULL, NULL)),
                 NULL));
}

/*
  t4: albero con cammini di lunghezza 1 (root->foglia)
      0
     / \
    0   0
  direzioni: L oppure R => cambi = 0 (primo passo non conta)
*/
Tree crea_t4(void) {
    return nn(0, nn(0, NULL, NULL), nn(0, NULL, NULL));
}

/*
  t5: un ramo ha 2 cambi, l'altro 0
          0
         / \
        0   0
         \
          0
         /
        0

  Cammino sinistro: L, R, L => cambi 2
  Cammino destro: R => cambi 0
*/
Tree crea_t5(void) {
    return nn(0,
              nn(0, NULL, nn(0, nn(0, NULL, NULL), NULL)),
              nn(0, NULL, NULL));
}

/* ===== MAIN DI TEST ===== */
int f(Tree t, int k, int somma, int exp);
int camminoConKCambi(Tree t, int K);
int main(void) {

    struct {
        Tree t;
        int K;
        int atteso;
        const char *nome;
    } tests[] = {
        {crea_t1(), 1, 1, "t1 con K=1 (esiste: L,L,R oppure R,R,L)"},
        {crea_t1(), 0, 0, "t1 con K=0 (tutti i cammini hanno almeno 1 cambio)"},
        {crea_t2(), 0, 1, "t2 con K=0 (linea sinistra: nessun cambio)"},
        {crea_t2(), 1, 0, "t2 con K=1 (impossibile)"},
        {crea_t3(), 2, 1, "t3 con K=2 (zig-zag: R,L,R => 2 cambi)"},
        {crea_t3(), 1, 0, "t3 con K=1 (no)"},
        {crea_t4(), 0, 1, "t4 con K=0 (un passo: 0 cambi)"},
        {crea_t4(), 1, 0, "t4 con K=1 (un passo non conta: 0 cambi)"},
        {crea_t5(), 2, 1, "t5 con K=2 (esiste nel ramo sinistro)"},
        {crea_t5(), 0, 1, "t5 con K=0 (esiste nel ramo destro)"},
        {NULL,      0, 0, "albero vuoto: nessun cammino"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("Test %d: %s\n", i+1, tests[i].nome);
        printf("  inorder: ");
        stampa_inorder(tests[i].t);
        int res = camminoConKCambi(tests[i].t, tests[i].K);
        printf("\n  -> %d (atteso %d)\n\n", res, tests[i].atteso);
    }

    return 0;
}


int camminoConKCambi(Tree t, int K)
    {
    if(t==NULL)
        return 0;
    return f(t->right, K, 0, 1)|| f(t->left, K, 0, -1);
    }


int f(Tree t, int k, int somma, int exp) // exp=1 mi aspetto di andare a destra, exp=-1 mi aspetto di andare a sinistra
{
    if(t==NULL)
        return 0;
    if(t->left==NULL && t->right==NULL)
            {
                if(somma==k)
                    return 1;
                return 0;
            }
    if(exp==1)
        {
            return f(t->left, k, somma+1, -1) || f(t->right, k, somma, 1);
        }
    else
        {
            return f(t->right,k,somma+1, 1) || f(t->left, k, somma, -1);
        }
    }
