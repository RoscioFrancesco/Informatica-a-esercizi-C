//
//  main.c
//  alberi es 14 clean
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

/* ===== ESERCIZIO 14: ZIG-ZAG + VALORI A COPPIE ===== */

/* dir: 0 = devo andare a sx, 1 = devo andare a dx
   fase: +1 = crescente, -1 = decrescente
   cnt: 1 o 2 (posizione nella coppia)
   prev: valore precedente
//   has_prev: 0 solo alla radice, 1 altrimenti */
//int aux(Tree t, int dir, int fase, int cnt, int prev, int has_prev)
//{
//    if (t == NULL) return 0;
//
//    if (has_prev) {
//        if (fase == 1) {
//            if (t->val <= prev) return 0;
//        } else {
//            if (t->val >= prev) return 0;
//        }
//    }
//
//    if (t->left == NULL && t->right == NULL)
//        return 1;
//
//    int next_cnt = cnt;
//    int next_fase = fase;
//
//    if (has_prev) {
//        if (cnt == 1)
//            next_cnt = 2;
//        else {
//            next_cnt = 1;
//            next_fase = -fase;
//        }
//    }
//
//    int next_dir = 1 - dir;
//
//    if (dir == 0)
//        return aux(t->left, next_dir, next_fase, next_cnt, t->val, 1);
//    else
//        return aux(t->right, next_dir, next_fase, next_cnt, t->val, 1);
//}




/* valido: 1 -> 3 -> 5 -> 4 -> 2 */
Tree crea_valido1(void) {
    return nn(1,
              NULL,
              nn(3,
                 nn(5,
                    NULL,
                    nn(4,
                       nn(2,NULL,NULL),
                       NULL)),
                 NULL));
}

/* non valido: 3 salite consecutive */
Tree crea_nonvalido1(void) {
    return nn(1,
              NULL,
              nn(3,
                 nn(5,
                    NULL,
                    nn(7,
                       nn(6,NULL,NULL),
                       NULL)),
                 NULL));
}

/* non valido: direzione non zig-zag */
Tree crea_nonvalido2(void) {
    return nn(8,
              nn(10,
                 nn(12,
                    NULL,
                    nn(11,
                       nn(9,NULL,NULL),
                       NULL)),
                 NULL),
              NULL);
}

/* valido: parte a sinistra */
Tree crea_valido2(void) {
    return nn(-2,
              nn(0,
                 NULL,
                 nn(4,
                    nn(3,
                       NULL,
                       nn(1,NULL,NULL)),
                    NULL)),
              NULL);
}

/* non valido: uguaglianza */
Tree crea_nonvalido3(void) {
    return nn(1,
              NULL,
              nn(3,
                 nn(3,
                    NULL,
                    nn(2,
                       nn(0,NULL,NULL),
                       NULL)),
                 NULL));
}

Tree crea_singolo(void) { return nn(7,NULL,NULL); }
Tree crea_vuoto(void)   { return NULL; }
int zigZagValoriACoppie(Tree t);
/* ===== MAIN ===== */
int aux(Tree t, int dir, int fase, int cnt, int prev, int has_prev);
int main(void)
{
    struct {
        Tree t;
        int atteso;
        const char *nome;
    } tests[] = {
        {crea_valido1(),    1, "valido1: zig-zag e coppie OK"},
        {crea_nonvalido1(), 0, "nonvalido1: troppe salite"},
        {crea_nonvalido2(), 0, "nonvalido2: direzione non alterna"},
        {crea_valido2(),    1, "valido2: parte a sx"},
        {crea_nonvalido3(), 0, "nonvalido3: uguaglianza"},
        {crea_singolo(),    1, "singolo nodo"},
        {crea_vuoto(),      0, "albero vuoto"},
    };

    int n = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < n; i++) {
        printf("Test %d – %s\n", i+1, tests[i].nome);
        printf("  inorder: ");
        stampa_inorder(tests[i].t);
        int res = zigZagValoriACoppie(tests[i].t);
        printf("\n  risultato = %d (atteso %d)\n\n", res, tests[i].atteso);
    }

    return 0;
}
/* dir: 0 = devo andare a sx, 1 = devo andare a dx
   fase: +1 = crescente, -1 = decrescente
   cnt: 1 o 2 (posizione nella coppia)
   prev: valore precedente
//   has_prev: 0 solo alla radice, 1 altrimenti */
int aux(Tree t, int dir, int fase, int cnt, int prev, int has_prev)
{
    if(t==NULL)
        return 0;
    if(has_prev)
        {
            if(prev==t->val)
                return 0;
            if(fase==1)
                {
                    if(prev>t->val)
                        return 0;
                }
            else
                {
                    if(prev<t->val)
                        return 0;
                }
        }
    if (t->left == NULL && t->right == NULL)
          return 1;
    int next_count=cnt;
    int next_fase=fase;
    if(has_prev)
    {
        if(cnt==1)
        {
            next_fase=fase;
            next_count=2;
        }
        else
        {
            next_fase=-fase;
            next_count=1;
        }
    }
    int next_dir=1-dir;
    if(dir==0)
        return aux(t->left, next_dir, next_fase, next_count, t->val, 1);
    else
        return aux(t->right, next_dir, next_fase, next_count, t->val, 1);
}
int zigZagValoriACoppie(Tree t)
{
    if (t == NULL) return 0;

    return aux(t, 0,  1, 1, 0, 0) ||
           aux(t, 1,  1, 1, 0, 0) ||
           aux(t, 0, -1, 1, 0, 0) ||
           aux(t, 1, -1, 1, 0, 0);
}
