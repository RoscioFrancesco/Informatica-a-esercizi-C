//
//  main.c
//  alberi es 1 chat
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



int alternaPariDispari(Tree t);


/* ===== ALBERI DI TEST ===== */

// Valido: tutti i cammini alternano
//        2
//       / \
//      3   3
//     /     \
//    2       2
Tree crea_valido1(void) {
    return nn(2,
              nn(3, nn(2, NULL, NULL), NULL),
              nn(3, NULL, nn(2, NULL, NULL)));
}

// Non valido: cammino con due pari consecutivi (2 -> 4)
//    2
//     \
//      4
Tree crea_nonvalido1(void) {
    return nn(2, NULL, nn(4, NULL, NULL));
}

// Non valido: cammino con due dispari consecutivi (1 -> 3)
//    1
//   /
//  3
Tree crea_nonvalido2(void) {
    return nn(1, nn(3, NULL, NULL), NULL);
}

// Valido (inizia con dispari): tutti i cammini alternano
//      1
//     / \
//    2   2
//   /     \
//  3       3
Tree crea_valido2(void) {
    return nn(1,
              nn(2, nn(3, NULL, NULL), NULL),
              nn(2, NULL, nn(3, NULL, NULL)));
}

// Valido: foglia singola (nessuna coppia consecutiva da controllare)
// 7
Tree crea_singolo(void) {
    return nn(7, NULL, NULL);
}

// Valido: albero vuoto (convenzione tipica: vacuamente vero)
Tree crea_vuoto(void) {
    return NULL;
}

// Non valido: solo un cammino rompe (a sinistra), gli altri ok
//        2
//       / \
//      4   3
//         / \
//        2   2
// Qui il cammino 2->4 è (pari, pari) => invalido
Tree crea_nonvalido3(void) {
    return nn(2,
              nn(4, NULL, NULL),
              nn(3, nn(2, NULL, NULL), nn(2, NULL, NULL)));
}

/* ===== MAIN DI TEST ===== */

int main(void) {

    struct {
        Tree t;
        int atteso;
        const char *nome;
    } tests[] = {
        {crea_valido1(),    1, "valido1 (inizia pari, alterna sempre)"},
        {crea_nonvalido1(), 0, "nonvalido1 (2->4 pari-pari)"},
        {crea_nonvalido2(), 0, "nonvalido2 (1->3 dispari-dispari)"},
        {crea_valido2(),    1, "valido2 (inizia dispari, alterna sempre)"},
        {crea_singolo(),    1, "singolo nodo (vacuamente alterna)"},
        {crea_vuoto(),      1, "albero vuoto (vacuamente alterna)"},
        {crea_nonvalido3(), 0, "nonvalido3 (solo un cammino rompe)"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("Test %d: %s\n", i+1, tests[i].nome);
        printf("  inorder: ");
        stampa_inorder(tests[i].t);
        int res = alternaPariDispari(tests[i].t);
        printf("\n  -> %d (atteso %d)\n\n", res, tests[i].atteso);
    }

    return 0;
}


int èpari(int x)
    {
        if(x%2==0)
            return 1;
    return 0;
    }
int pari_fromhere(Tree albero, int exp) // exp=0 mi aspetto un pari, exp=1 mi aspetto un dispari
    {
        if(albero==NULL)
            return 1;
        if(exp==0)
            {
                if(albero->val%2==1)
                    return 0;
                return pari_fromhere(albero->left, 1) && pari_fromhere(albero->right, 1);
            }
        if(exp==1)
            {
                if(albero->val%2==0)
                    return 0;
                return pari_fromhere(albero->left, 0) && pari_fromhere(albero->right, 0);
            }
        return 0;
    }
int alternaPariDispari(Tree albero)
    {
        if(albero==NULL)
            return 1;
        if(albero->val%2==0)
        {
            if(pari_fromhere(albero->left, 1)==0 || pari_fromhere(albero->right, 1)==0)
                return 0;
        }
            else{
                if(pari_fromhere(albero->left, 0)==0 || pari_fromhere(albero->right, 0)==0)
                    return 0;
            }
    return 1;
//    return alternaPariDispari(albero->left)&&alternaPariDispari(albero->right); cosi controllo ogni nodo dell'albero
    }
