//
//  main.c
//  9A -17
//
//  Created by Francesco Roscio Ricon on 02/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA DELL'ALBERO
   ========================= */

struct Nodo {
    int valore;
    struct Nodo *sx;
    struct Nodo *dx;
};



/*
 * Scarto parziale dei rami:
 * esiste un cammino valido in cui i valori rispettano la crescita.
 * Se un ramo viola la crescita, viene eliminato SOLO quel ramo.
 */
struct Nodo* scartaRami(struct Nodo *radice, int valorePrecedente);

/* =========================
   STAMPA (printf)
   ========================= */

void stampaPreorder(struct Nodo *radice) {
    if (radice == NULL)
        return;

    printf("%d ", radice->valore);
    stampaPreorder(radice->sx);
    stampaPreorder(radice->dx);
}

/* =========================
   MAIN
   ========================= */

int main() {

    /* Albero di esempio */
    struct Nodo *radice = malloc(sizeof(struct Nodo));
    struct Nodo *n1 = malloc(sizeof(struct Nodo));
    struct Nodo *n2 = malloc(sizeof(struct Nodo));

    radice->valore = 10;
    radice->sx = n1;
    radice->dx = n2;

    n1->valore = 12;   // ramo che rispetta la crescita
    n1->sx = NULL;
    n1->dx = NULL;

    n2->valore = 5;    // ramo che viola la crescita
    n2->sx = NULL;
    n2->dx = NULL;

    printf("Albero originale (preorder):\n");
    stampaPreorder(radice);

    /*
     * Qui verrebbe applicato lo scarto parziale dei rami:
     * solo il ramo che rispetta la crescita viene mantenuto.
     *
     * radice = scartaRami(radice, radice->valore);
     */

    printf("\n\nAlbero dopo lo scarto parziale dei rami:\n");
    stampaPreorder(radice);

    return 0;
}

