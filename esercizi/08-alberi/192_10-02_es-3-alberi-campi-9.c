//
//  main.c
//  es 3 alberi campi -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA (come da testo)
   ========================= */
typedef struct Elemento {
    int dato;
    struct Elemento *left, *center, *right;
} Nodo;

typedef Nodo * Tree;

/* =========================
   PROTOTIPO FUNZIONE RICHIESTA
   ========================= */

int isobatoTernario(Tree t);

/* =========================
   SUPPORTO (solo per costruire esempi)
   ========================= */
Tree nuovoNodo(int v) {
    Tree n = (Tree)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = v;
    n->left = NULL;
    n->center = NULL;
    n->right = NULL;
    return n;
}

/* =========================
   MAIN
   ========================= */
int isobatoTernario(Tree albero);
int f(Tree albero, int *depth);
int isobatoAux( Tree t, int * depth );
int main() {
    Tree T;
    int esito;

    /* Costruzione di un albero ternario di test */
    T = nuovoNodo(1);

    T->left   = nuovoNodo(2);
    T->center = nuovoNodo(3);
    T->right  = nuovoNodo(4);

    /* aggiungo un livello sotto ogni figlio (così, in questo esempio, i cammini hanno stessa lunghezza) */
    T->left->left       = nuovoNodo(5);
    T->center->center   = nuovoNodo(6);
    T->right->right     = nuovoNodo(7);
    esito = isobatoTernario(T);

    if (esito == 1)
        printf("Albero ternario ISOBATO (tutti i cammini radice->foglia hanno stessa lunghezza)\n");
    else
        printf("Albero ternario NON isobato\n");

    return 0;
}

//int f(Tree albero, int *depth)
//    {
//        if(albero==NULL)
//            {
//                *depth=0;
//                return 1;
//            }
//    if(albero->center==NULL && albero->left==NULL && albero->right==NULL)
//    {
//        *depth=1;
//        return 1;
//    }
//    int il, ir, ic, dl, dr, dc;
//    il=f(albero->left, &dl);
//    ir=f(albero->right, &dr);
//    ic=f(albero->center, &dc);
//    if(!il || ! ir|| !ic || dl!=dr || dr!=dc)
//        return 0;
//    *depth=dc+1;
//    return 1;
//    }
int isobatoTernario(Tree albero)
    {
    int depth=0;
    return isobatoAux(albero, &depth);
    
    }
// se non viene neanche al prof !!!
int isobatoAux( Tree t, int * depth ) {
int dl, dc, dr, il, ic, ir; /* 3 profondità per i rami e 3 booleani */
if ( t == NULL ) {
*depth = 0; /* Un albero vuoto è isobato di profondità 0 */
return 1;
}
il = isobatoAux(t->left, &dl); /* Controlliamo l'isobaticità dei rami */
ic = isobatoAux(t->center, &dc); /* Memorizzando le (eventuali) profondità */
ir = isobatoAux(t->right, &dr);
if ( !il || !ic || !ir || dl != dc || dc != dr )
return 0;
*depth = dl + 1; /* tanto le profondità sono tutte uguali */
return 1;
}
