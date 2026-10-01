//
//  main.c
//  es2  prima
//
//  Created by Francesco Roscio Ricon on 19/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA LISTA
   ========================= */

typedef struct nodo {
    int valore;
    struct nodo *next;
} nodo;

typedef nodo* lista;


/* =========================
   FUNZIONI DI SUPPORTO
   ========================= */

// Inserimento in coda
lista inserisciInCoda(lista L, int x) {
    if (L == NULL) {
        lista nuovo = (lista)malloc(sizeof(nodo));
        nuovo->valore = x;
        nuovo->next = NULL;
        return nuovo;
    }

    L->next = inserisciInCoda(L->next, x);
    return L;
}

// Stampa lista
void stampaLista(lista L) {
    while (L != NULL) {
        printf("%d", L->valore);
        if (L->next != NULL)
            printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

// Libera memoria
void liberaLista(lista L) {
    while (L != NULL) {
        lista temp = L;
        L = L->next;
        free(temp);
    }
}


/* =========================
   FUNZIONE RICHIESTA
   ========================= */

// Elimina tutti gli elementi pari (ricorsiva)
lista eliminaPari(lista L) {
    if(L==NULL)
        return L;
    if(L->valore%2==0)
        {
            lista temp=L->next;
            free(L);
            L=temp;
            return eliminaPari(L);
        }
    L->next=eliminaPari(L->next);
    return L;
}


/* =========================
   MAIN DI TEST
   ========================= */

int main() {

    lista L = NULL;

    // Costruzione lista esempio
    L = inserisciInCoda(L, 4);
    L = inserisciInCoda(L, 7);
    L = inserisciInCoda(L, 2);
    L = inserisciInCoda(L, 9);
    L = inserisciInCoda(L, 6);
    L = inserisciInCoda(L, 3);

    printf("Lista iniziale:\n");
    stampaLista(L);

    // Eliminazione pari
    L = eliminaPari(L);

    printf("\nLista dopo eliminazione dei pari:\n");
    stampaLista(L);

    liberaLista(L);

    return 0;
}
