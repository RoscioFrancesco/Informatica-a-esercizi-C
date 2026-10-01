//  Created by Francesco Roscio Ricon on 30/01/26.

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

int camminoTreStatiPattern(Tree t);



/* ===== ALBERI DI TEST =====

   NOTA: i test sono costruiti in modo che tu possa verificare facilmente
   se la tua funzione trova (o non trova) almeno un cammino valido.
*/

/* ---------- t1: VALIDO ----------
   Costruisco un cammino valido con:
   - direzioni: dx, dx, sx, sx (zig-zag a coppie)
   - stati:     S0,S0,S1,S1,S2 (per livelli 0..4)
   - valori:    pari, pari, dispari, dispari, mult di 3

   Cammino scelto (radice->foglia):
     2  (S0 pari)
      \
       4 (S0 pari)      [dx #1]
        \
         7 (S1 dispari) [dx #2]
        /
       9  (S1 dispari)  [sx #1]   (9 è anche mult di 3 ma qui serve dispari)
      /
     12 (S2 mult di 3)  [sx #2]   foglia

   Albero:
        2
         \
          4
           \
            7
           /
          9
         /
        12
*/
Tree crea_valido1(void) {
    return nn(2,
              NULL,
              nn(4,
                 NULL,
                 nn(7,
                    nn(9,
                       nn(12,NULL,NULL),
                       NULL),
                    NULL)));
}

/* ---------- t2: NON valido ----------
   Stesso pattern di direzioni possibile, ma metto un valore che rompe lo stato:
   Al livello 2 (stato S1) metto un pari => fallisce.

   Cammino tentato:
     2 (S0 pari)
      \
       4 (S0 pari)
        \
         8 (S1 dovrebbe essere dispari) -> FAIL
*/
Tree crea_nonvalido1(void) {
    return nn(2,
              NULL,
              nn(4,
                 NULL,
                 nn(8,NULL,NULL)));
}

/* ---------- t3: NON valido ----------
   Valori ok, ma la direzione a coppie è impossibile (manca il ramo richiesto).
   Se parti con dx,dx,... il secondo dx non esiste; se parti con sx,sx,... non esiste proprio.

        2
       /
      4
       \
        7
*/
Tree crea_nonvalido2(void) {
    return nn(2,
              nn(4, NULL, nn(7,NULL,NULL)),
              NULL);
}

/* ---------- t4: VALIDO (parte a sinistra) ----------
   Pattern direzioni: sx,sx,dx,dx,...
   Stati: S0,S0,S1,S1,S2
   Valori: pari,pari,dispari,dispari,mult3

   Cammino:
        6 (S0 pari e anche mult3 va bene comunque)
       /
      2 (S0 pari)       [sx #1]
     /
    5 (S1 dispari)      [sx #2]
     \
      11 (S1 dispari)   [dx #1]
       \
        15 (S2 mult3)   [dx #2] foglia
*/
Tree crea_valido2(void) {
    return nn(6,
              nn(2,
                 nn(5,
                    NULL,
                    nn(11, NULL, nn(15,NULL,NULL))),
                 NULL),
              NULL);
}

/* ---------- t5: NON valido (stato S2 fallisce) ----------
   Arrivo allo stato S2 ma metto un valore non multiplo di 3.

   Cammino (direzione dx,dx,sx,sx):
     2 (S0 pari)
      \
       4 (S0 pari)
        \
         7 (S1 dispari)
        /
       9 (S1 dispari)
      /
     14 (S2 dovrebbe mult3) -> FAIL
*/
Tree crea_nonvalido3(void) {
    return nn(2,
              NULL,
              nn(4,
                 NULL,
                 nn(7,
                    nn(9,
                       nn(14,NULL,NULL),
                       NULL),
                    NULL)));
}

/* singolo nodo: può essere valido se esiste uno stato iniziale che lo accetta
   (qui 3 è dispari e mult di 3, quindi se permetti scegliere lo stato iniziale, dovrebbe dare 1) */
Tree crea_singolo3(void) { return nn(3,NULL,NULL); }

/* albero vuoto: nessun cammino */
Tree crea_vuoto(void) { return NULL; }


/* ===== MAIN DI TEST ===== */

int main(void) {

    struct {
        Tree t;
        int atteso;
        const char *nome;
        const char *nota;
    } tests[] = {
        {crea_valido1(),    1, "valido1",    "esiste cammino dx,dx,sx,sx con stati a coppie S0,S1,S2"},
        {crea_nonvalido1(), 0, "nonvalido1", "valori rompono lo stato S1 (pari al posto di dispari)"},
        {crea_nonvalido2(), 0, "nonvalido2", "pattern direzioni impossibile (rami mancanti)"},
        {crea_valido2(),    1, "valido2",    "esiste cammino sx,sx,dx,dx con stati a coppie"},
        {crea_nonvalido3(), 0, "nonvalido3", "stato S2 fallisce (14 non mult di 3)"},
        {crea_singolo3(),   1, "singolo3",   "se permetti scegliere stato iniziale, 3 soddisfa S1 o S2"},
        {crea_vuoto(),      0, "vuoto",      "nessun cammino"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("Test %d: %s\n", i+1, tests[i].nome);
        printf("  nota   : %s\n", tests[i].nota);
        printf("  inorder: ");
        stampa_inorder(tests[i].t);

        int res = camminoTreStatiPattern(tests[i].t);

        printf("\n  -> %d (atteso %d)\n\n", res, tests[i].atteso);
    }

    return 0;
}



int f(Tree albero, int dir, int stato_expect, int count_dir, int count_stato)
// stato=0 se è pari, stato=1 se è dispari, stato=2 se è multiplo di 3
// -1 allora vado a sx, 1 allora vado a dx
// coutn stato va da 1 a 6
{
    if(albero==NULL)
        return 0;
    
    int next_dir;
    int next_count_dir=1;
    int move_dir=dir;
    if(count_dir==1)
        {
            next_dir=dir;
            next_count_dir=2;
        }
    if(count_dir==2)
        {
            next_dir=-dir;
            next_count_dir=1;
        }
    int stato;
    if (albero->val % 3 == 0) {
        stato = 2;              // S2
    }
    else if (albero->val % 2 == 0) {
        stato = 0;              // S0
    }
    else {
        stato = 1;              // S1
    }
    if (stato!=stato_expect)
        return 0;
    int stato_expect_next;
    int next_count_stato;

    /* stato dura 2 livelli: S0,S0 poi S1,S1 poi S2,S2 poi S0,S0... */
    if (count_stato == 1) {
        stato_expect_next = stato_expect;      // seconda volta nello stesso stato
        next_count_stato = 2;
    } else { // count_stato == 2
        stato_expect_next = (stato_expect + 1) % 3; // passo allo stato successivo
        next_count_stato = 1;
    }
    if(albero->left==NULL && albero->right==NULL)
        return 1;
    if(move_dir==-1)
    {
        if(albero->left==NULL)
            return 0;
        return f(albero->left, next_dir, stato_expect_next, next_count_dir, next_count_stato);
    }
    else
    {
        if(albero->right==NULL)
            return 0;
        return f(albero->right, next_dir, stato_expect_next, next_count_dir, next_count_stato);
    }
}

int camminoTreStatiPattern(Tree t)
{
    if (!t) return 0;
    return f(t, -1, 0, 1, 1) || f(t,  1, 0, 1, 1);
}
