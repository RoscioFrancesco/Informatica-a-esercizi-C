//
//  main.c
//  alberi es 3 chat
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



int camminoCrescenteZigZag(Tree t);


/* ===== ALBERI DI TEST ===== */

/*
  v1 (VALIDO):
          5
         / \
        2   6
         \  /
          4 7
           \  \
            8  9

  Cammino valido: 5 -> 2 -> 4 -> 8
   direzioni: sx, dx, dx  (ATTENZIONE: questo non è zig-zag perfetto)
  Quindi ne mettiamo uno zig-zag vero:

  Cammino valido reale: 5 -> 6 -> 7 -> 9
   direzioni: dx, sx, dx  (zig-zag)
   valori:   5 < 6 < 7 < 9 (crescente)
*/
Tree crea_valido1(void) {
    return nn(5,
              nn(2, NULL, nn(4, NULL, nn(8, NULL, NULL))),
              nn(6,
                 nn(7, NULL, nn(9, NULL, NULL)),
                 NULL));
}

/*
  n1 (NON valido): cresce ma non zig-zag
      1
       \
        2
         \
          3
           \
            4
  direzioni: dx,dx,dx (no zig-zag)
*/
Tree crea_nonvalido1(void) {
    return nn(1, NULL,
              nn(2, NULL,
                 nn(3, NULL,
                    nn(4, NULL, NULL))));
}

/*
  n2 (NON valido): zig-zag c'è, ma non è crescente
        5
       / \
      8   2
     /     \
    7       3
     \     /
      6   4

  Cammino zig-zag: 5->8->7->6 (sx,sx? no) / 5->2->3->4 (dx,dx? no)
  Qui costruito per non avere nessun cammino che soddisfa entrambe.
*/
Tree crea_nonvalido2(void) {
    return nn(5,
              nn(8, nn(7, NULL, nn(6, NULL, NULL)), NULL),
              nn(2, NULL, nn(3, nn(4, NULL, NULL), NULL)));
}

/*
  v2 (VALIDO): cammino minimo di lunghezza 2 (radice->foglia)
      1
     /
    2
  - Crescente: 1<2
  - Zig-zag: con 1 solo passo è sempre ok (nessuna alternanza da violare)
*/
Tree crea_valido2(void) {
    return nn(1, nn(2, NULL, NULL), NULL);
}

/*
  n3 (NON valido): un solo passo ma non crescente
      2
     /
    1
*/
Tree crea_nonvalido3(void) {
    return nn(2, nn(1, NULL, NULL), NULL);
}

/*
  n4 (NON valido): zig-zag perfetto esiste ma cresce non sempre
        3
       / \
      4   5
       \   \
        2   6
       /   /
      7   1
  Qui ci sono zig-zag ma sempre con una discesa nei valori.
*/
Tree crea_nonvalido4(void) {
    return nn(3,
              nn(4, NULL, nn(2, nn(7, NULL, NULL), NULL)),
              nn(5, NULL, nn(6, nn(1, NULL, NULL), NULL)));
}

/* ===== MAIN DI TEST ===== */

int main(void) {

    struct {
        Tree t;
        int atteso;
        const char *nome;
    } tests[] = {
        {crea_valido1(),    1, "valido1: esiste cammino crescente zig-zag"},
        {crea_nonvalido1(), 0, "nonvalido1: cresce ma non zig-zag (dx dx dx)"},
        {crea_nonvalido2(), 0, "nonvalido2: nessun cammino soddisfa entrambe"},
        {crea_valido2(),    1, "valido2: un passo crescente (considerato zig-zag)"},
        {crea_nonvalido3(), 0, "nonvalido3: un passo ma decrescente"},
        {crea_nonvalido4(), 0, "nonvalido4: zig-zag ma non crescente"},
        {NULL,              0, "albero vuoto (nessun cammino)"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("Test %d: %s\n", i+1, tests[i].nome);
        printf("  inorder: ");
        stampa_inorder(tests[i].t);
        int res = camminoCrescenteZigZag(tests[i].t);
        printf("\n  -> %d (atteso %d)\n\n", res, tests[i].atteso);
    }

    return 0;
}


int f(Tree root, int dir, int prec) // dir=0 vado a dx all prossima, dir==1 vado a sx alla prossima
    {
        if(root==NULL)
            return 0;
        if(prec==0)
            prec=root->val;
        if(root->val<prec)
            return 0;
        if(root->left==NULL && root->right==NULL)
            return 1;
        prec=root->val;
        if(dir==0)
            {
                if(root->right==NULL)
                    return 0;
                return f(root->right, 1, prec);
            }
        if(dir==1)
            {
                if(root->left==NULL)
                    return 0;
                return f(root->left, 0, prec);
            }
        return 0;
    }
int camminoCrescenteZigZag(Tree albero)
    {
    return f(albero,1, 0)|| f(albero, 0, 0);
    }
