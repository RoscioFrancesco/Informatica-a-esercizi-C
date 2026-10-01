//
//  main.c
//  alberi es 14
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



int zigZagValoriACoppie(Tree t);


/* ===== ALBERI DI TEST ===== */

/*
 t1 (VALI DO): esiste cammino a sinistra-destra alternato e valori a coppie
 Cammino scelto: 1 -> 3 -> 5 -> 4 -> 2
 Direzioni:      dx, sx, dx, sx  (zig-zag)
 Confronti:      1<3 (up #1), 3<5 (up #2), 5>4 (down #1), 4>2 (down #2)
 Quindi: 2 up poi 2 down => OK
 Struttura albero:
          1
           \
            3
           /
          5
           \
            4
           /
          2
*/
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

/*
 t2 (NON valido): zig-zag ok ma pattern valori sbagliato (3 up di fila)
 Cammino: 1 -> 3 -> 5 -> 7 -> 6
 Confronti: 1<3 (up1), 3<5 (up2), 5<7 (up3)  -> doveva iniziare down al 3° passo
 Struttura:
          1
           \
            3
           /
          5
           \
            7
           /
          6
*/
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

/*
 t3 (NON valido): valori a coppie ok ma direzione NON zig-zag (due sx di fila)
 Cammino: 8 -> 10 -> 12 -> 11 -> 9
 Confronti: up, up, down, down ok
 Direzioni in questo albero: sx,sx,? (non alterna) -> deve fallire
 Struttura:
          8
         /
       10
      /
    12
     \
     11
    /
   9
*/
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

/*
 t4 (VALI DO): cammino valido parte a sinistra (zig-zag sx,dx,sx,dx)
 Cammino: -2 -> 0 -> 4 -> 3 -> 1
 Confronti: -2<0 (up1), 0<4 (up2), 4>3 (down1), 3>1 (down2) OK
 Struttura:
          -2
         /
        0
         \
          4
         /
        3
         \
          1
*/
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

/*
 t5 (NON valido): uguaglianza rompe (strettamente richiesto)
 Cammino: 1 -> 3 -> 3 -> 2 -> 0 (anche se zig-zag)
 C'è un passo con 3 == 3 => fail
 Struttura:
          1
           \
            3
           /
          3
           \
            2
           /
          0
*/
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

/* t6: singolo nodo (cammino di 0 passi) -> considerato valido (non può violare) */
Tree crea_singolo(void) { return nn(7,NULL,NULL); }

/* t7: albero vuoto -> 0 (non esiste cammino) */
Tree crea_vuoto(void) { return NULL; }

/* ===== MAIN DI TEST ===== */

int main(void) {

    struct {
        Tree t;
        int atteso;
        const char *nome;
    } tests[] = {
        {crea_valido1(),    1, "valido1: esiste 1-3-5-4-2 (2 up poi 2 down, zig-zag)"},
        {crea_nonvalido1(), 0, "nonvalido1: zig-zag ok ma 3 up di fila (coppie violate)"},
        {crea_nonvalido2(), 0, "nonvalido2: valori ok ma direzione non alterna"},
        {crea_valido2(),    1, "valido2: esiste -2-0-4-3-1 (sx/dx alternato, coppie)"},
        {crea_nonvalido3(), 0, "nonvalido3: uguaglianza 3==3"},
        {crea_singolo(),    1, "singolo nodo (cammino vuoto valido)"},
        {crea_vuoto(),      0, "albero vuoto (nessun cammino)"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("Test %d: %s\n", i+1, tests[i].nome);
        printf("  inorder: ");
        stampa_inorder(tests[i].t);
        int res = zigZagValoriACoppie(tests[i].t);
        printf("\n  -> %d (atteso %d)\n\n", res, tests[i].atteso);
    }

    return 0;
}


int f(Tree albero, int dir, int count, int cresce, int prec) // se cresc==1 allora cresce, altrimenti -1, se dir=0 alla prossima a sx altirmenti 1=dx
    {
        if(albero==NULL)
            return 0;
        if(prec==albero->val)
            return 0;
        if(count==1)
            {
                if(cresce==1)
                    {
                        if(prec>albero->val)
                            return 0;
                        if(dir==0)
                            {
                                return f(albero->left, 1, 2, 1, albero->val);
                            }
                        else
                            {
                                return f(albero->right, 0, 2, 1, albero->val);
                            }
                    }
                if(cresce==-1)
                    {
                        if(prec<albero->val)
                            return 0;
                        if(dir==0)
                            {
                                return f(albero->left, 1, 2, -1, albero->val);
                            }
                        else
                            {
                                return f(albero->right, 0, 2, -1, albero->val);
                            }
                    }
            }
        if(count==2)
            {
                if(cresce==1)
                    {
                        if(prec>albero->val)
                            return 0;
                        if(dir==0)
                            {
                                return f(albero->left, 1, 1, -1, albero->val);
                            }
                        else
                            {
                                return f(albero->right, 0, 1, -1, albero->val);
                            }
                    }
                if(cresce==-1)
                    {
                        if(prec<albero->val)
                            return 0;
                        if(dir==0)
                            {
                                return f(albero->left, 1, 1, 1, albero->val);
                            }
                        else
                            {
                                return f(albero->right, 0, 1, 1, albero->val);
                            }
                    }
            }
        if(albero->left==NULL && albero->right==NULL)
            return 1;
        return 0;
    }
int zigZagValoriACoppie(Tree t)
    {
    int cresce=1;
    return f(t, 1, 1, cresce, t->val) || f(t, 0, 1, cresce, t->val) || f(t, 1, 1, -cresce, t->val) || f(t, 0, 1, -cresce, t->val);
    }
