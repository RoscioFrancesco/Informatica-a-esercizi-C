//
//  main.c
//  alberi es 10
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

/* ===== ESERCIZIO 10: ALBERO A FISARMONICA =====
   Un albero è "a fisarmonica" se lungo OGNI cammino radice-foglia:
   - i valori alternano tra crescere e decrescere rispetto al precedente
     (>,<,>,<,...) oppure (<,>,<,>,...)
   - il primo confronto può essere crescente o decrescente
   - uguaglianze NON ammesse
   La proprietà deve valere per TUTTI i cammini.
*/

int fisarmonica(Tree t);


/* ===== ALBERI DI TEST ===== */

/*
  v1 (VALIDO):
          5
         / \
        7   3
       /     \
      6       4

  Cammini:
   5->7->6 : (5<7) poi (7>6) alterna ok
   5->3->4 : (5>3) poi (3<4) alterna ok
*/
Tree crea_valido1(void) {
    return nn(5,
              nn(7, nn(6, NULL, NULL), NULL),
              nn(3, NULL, nn(4, NULL, NULL)));
}

/*
  n1 (NON valido): un cammino fa due crescite di fila
      1
       \
        3
         \
          5
  1<3 e 3<5 (crescente,crescente) => NO
*/
Tree crea_nonvalido1(void) {
    return nn(1, NULL, nn(3, NULL, nn(5, NULL, NULL)));
}

/*
  n2 (NON valido): uguaglianza (vietata)
      2
     /
    2
*/
Tree crea_nonvalido2(void) {
    return nn(2, nn(2, NULL, NULL), NULL);
}

/*
  v2 (VALIDO): un solo cammino, alterna decrescente/crescente
        10
       /
      5
       \
        7
       /
      6
  Confronti: 10>5, 5<7, 7>6 => alterna ok
*/
Tree crea_valido2(void) {
    return nn(10,
              nn(5, NULL,
                 nn(7, nn(6, NULL, NULL), NULL)),
              NULL);
}

/*
  n3 (NON valido): solo uno dei cammini rompe -> tutto l'albero NON è fisarmonica
          5
         / \
        7   8
       /     \
      6       9

  Cammino sx: 5<7, 7>6 ok
  Cammino dx: 5<8, 8<9 (due crescite) -> rompe => NO globale
*/
Tree crea_nonvalido3(void) {
    return nn(5,
              nn(7, nn(6, NULL, NULL), NULL),
              nn(8, NULL, nn(9, NULL, NULL)));
}

/*
  v3 (VALIDO): singolo nodo (nessun confronto -> vacuamente vero)
*/
Tree crea_singolo(void) {
    return nn(42, NULL, NULL);
}

/*
  v4 (VALIDO): albero vuoto (convenzione: vero)
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
        {crea_valido1(),    1, "valido1: tutti i cammini alternano"},
        {crea_nonvalido1(), 0, "nonvalido1: due crescite consecutive"},
        {crea_nonvalido2(), 0, "nonvalido2: uguaglianza vietata"},
        {crea_valido2(),    1, "valido2: cammino unico alterna"},
        {crea_nonvalido3(), 0, "nonvalido3: un cammino rompe => NO globale"},
        {crea_singolo(),    1, "singolo: vacuamente vero"},
        {crea_vuoto(),      1, "vuoto: convenzione vero"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("Test %d: %s\n", i+1, tests[i].nome);
        printf("  inorder: ");
        stampa_inorder(tests[i].t);
        int res = fisarmonica(tests[i].t);
        printf("\n  -> %d (atteso %d)\n\n", res, tests[i].atteso);
    }

    return 0;
}
/* ===== ESERCIZIO 10: ALBERO A FISARMONICA =====
   Un albero è "a fisarmonica" se lungo OGNI cammino radice-foglia:
   - i valori alternano tra crescere e decrescere rispetto al precedente
     (>,<,>,<,...) oppure (<,>,<,>,...)
   - il primo confronto può essere crescente o decrescente
   - uguaglianze NON ammesse
   La proprietà deve valere per TUTTI i cammini.
*/

int f(Tree albero, int expect, int prev) // expect=1 mi aspetto più grande, expect=-1 mi aspetto più piccolo
    {
        if(albero==NULL)
            return 1;
        if(prev==albero->val)
            return 0;
        if(expect==1)
            {
                if(prev<=albero->val)
                    return 0;
                return f(albero->left, -1, albero->val) && f(albero->right, -1, albero->val);
            }
        else
            {
                if(prev>=albero->val)
                    return 0;
                return f(albero->left, 1, albero->val) && f(albero->right, 1, albero->val);
            }
    }
int fisarmonica(Tree t)
    {
        if(t==NULL)
            return 1;
    int ris_1=1, ris_2=1;
    
    if(t->left!=NULL)
        {
            if(t->val>t->left->val)
                ris_1=f(t->left, 1, t->val);
            else
                ris_1=f(t->left, -1, t->val);
        }
    if(t->right!=NULL)
        {
            if(t->val>t->right->val)
                ris_2=f(t->right, 1, t->val);
            else
                ris_2=f(t->right, -1, t->val);
        }
    return ris_1 && ris_2;
    }
