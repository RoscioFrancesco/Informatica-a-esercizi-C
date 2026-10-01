//
//  main.c
//  9B -17
//
//  Created by Francesco Roscio Ricon on 02/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA DELL'ALBERO
   ========================= */
typedef struct Nodo {
    int valore;
    struct Nodo *sx;
    struct Nodo *dx;
} Nodo;
typedef Nodo * Albero;
/* =========================
   PROTOTIPI (DA SVOLGERE)
   ========================= */
/*
 * 9B – Regole diverse per sinistra e destra

 * Domanda: esiste un cammino valido?
 */
int esisteCamminoValido(Nodo *radice);


int dfsCammino(Nodo *nodo);

/* =========================
   UTILITY: CREAZIONE + STAMPA
   ========================= */
Nodo* nuovoNodo(int v, Nodo *sx, Nodo *dx) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->valore = v;
    n->sx = sx;
    n->dx = dx;
    return n;
}

/* stampa leggibile: v(sx,dx) */
void stampaPreorder(Nodo *r) {
    if (!r) { printf("NULL"); return; }
    printf("%d(", r->valore);
    stampaPreorder(r->sx);
    printf(",");
    stampaPreorder(r->dx);
    printf(")");
}

int èpari(int x);
int f(Albero tree, int expected_pari);
int funz(Albero t);
int main(void) {
    
    Nodo *radice =
        nuovoNodo(7,
            nuovoNodo(2,
                nuovoNodo(4, NULL, NULL),
                nuovoNodo(11, NULL, NULL)
            ),
            nuovoNodo(9,
                nuovoNodo(6, NULL, NULL),
                nuovoNodo(13, NULL, NULL)
            )
        );

    printf("Albero (preorder con struttura):\n");
    stampaPreorder(radice);
    printf("\n\n");
    printf("\n%d", funz(radice));
    
}
int f(Albero tree, int expected_pari)
    {
        if(tree==NULL)
            return 0;
        if(èpari(tree->valore)!=expected_pari)
            return 0;
        int sx=0;
        int dx=0;
        if(tree->dx==NULL && tree->sx==NULL)
            return 1;
        if(tree->sx!=NULL)
            {
                sx=f(tree->sx, 1);
            }
        if(tree->dx!=NULL)
            {
                dx=f(tree->dx, -1);
            }
        return sx||dx;
    }

int èpari(int x)
    {
        if(x%2==0)
            return 1;
        return -1;
    }
int funz(Albero t)
    {
    return f(t->sx, 1)||f(t->dx, -1);
    }
