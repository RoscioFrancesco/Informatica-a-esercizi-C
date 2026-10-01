//
//  main.c
//  chat ricorsione es 1 -14
//
//  Created by Francesco Roscio Ricon on 05/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   STRUTTURE DATI
   ========================================================= */
typedef struct nodo {
    int valore;
    struct nodo* next;
} nodo;

typedef nodo* Lista;

/* =========================================================
   PROTOTIPO (DA SVOLGERE)
   Esercizio 1: Prodotto a coppie simmetriche (ricorsivo)
   - il primo diventa (primo * ultimo)
   - il secondo diventa (secondo * penultimo)
   - ...
   - se lunghezza dispari, il centrale resta invariato
   - vietati cicli nella soluzione
   ========================================================= */
void prodottoCoppieSimmetriche(Lista head);   /* TODO */

/* =========================================================
   UTILITY PER TEST (qui i cicli sono OK)
   ========================================================= */
static Lista nuovoNodo(int val, Lista next) {
    Lista n = (Lista)malloc(sizeof(nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->valore = val;
    n->next = next;
    return n;
}

static Lista creaListaDaArray(const int a[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; i--) {
        l = nuovoNodo(a[i], l);
    }
    return l;
}

static void stampaLista(Lista l) {
    printf("[ ");
    while (l != NULL) {
        printf("%d ", l->valore);
        l = l->next;
    }
    printf("]\n");
}

static void liberaLista(Lista l) {
    while (l != NULL) {
        Lista tmp = l;
        l = l->next;
        free(tmp);
    }
}

/* =========================================================
   MAIN DI TEST
   ========================================================= */
int main(void) {
    int a1[] = {1, 2, 3, 4, 5};
    int n1 = (int)(sizeof(a1) / sizeof(a1[0]));
    Lista L1 = creaListaDaArray(a1, n1);

    printf("Lista iniziale (dispari):\n");
    stampaLista(L1);

    prodottoCoppieSimmetriche(L1);

    printf("Lista dopo la modifica:\n");
    stampaLista(L1);

    printf("Output atteso:\n");
    printf("[ 5 8 3 8 5 ]\n\n");

    liberaLista(L1);

    /* Secondo test: lunghezza pari */
    int a2[] = {2, 3, 4, 5};
    int n2 = (int)(sizeof(a2) / sizeof(a2[0]));
    Lista L2 = creaListaDaArray(a2, n2);

    printf("Lista iniziale (pari):\n");
    stampaLista(L2);

    prodottoCoppieSimmetriche(L2);

    printf("Lista dopo la modifica:\n");
    stampaLista(L2);

    printf("Output atteso (pari):\n");
    /* 2*5=10, 3*4=12, 4*3=12, 5*2=10 */
    printf("[ 10 12 12 10 ]\n");

    liberaLista(L2);

    return 0;
}
static int helper(Lista dx, Lista *psx) {
    if (dx == NULL) return 0;

    /* vado fino in fondo */
    if (helper(dx->next, psx)) return 1;  /* se sotto ha detto STOP, propago */

    /* ora dx è in risalita (ultimo, penultimo, ...) */

    /* Caso dispari: nodo centrale -> non modificare */
    if (*psx == dx) return 1;

    /* Caso pari: i due centrali -> li modifico e stoppo */
    if ((*psx)->next == dx) {
        int a = (*psx)->valore;
        int b = dx->valore;
        (*psx)->valore = a * b;
        dx->valore     = a * b;
        return 1;
    }

    /* Caso normale: coppia simmetrica */
    {
        int a = (*psx)->valore;
        int b = dx->valore;
        (*psx)->valore = a * b;
        dx->valore     = a * b;
        *psx = (*psx)->next;   /* avanzo sx */
    }

    return 0; /* continua */
}

void prodottoCoppieSimmetriche(Lista head) {
    if (head == NULL || head->next == NULL) return;
    Lista sx = head;
    helper(head, &sx);
}
