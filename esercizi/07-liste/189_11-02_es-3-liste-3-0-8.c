//
//  main.c
//  es 3 liste 3.0 -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct EL {
    int dato;
    struct EL *next;
} nodo;

typedef nodo *lista;

/*
  Rimuove dalla lista tutti i blocchi instabili (a blocchi),
  ritorna il numero totale di nodi eliminati.
*/
int ripulisciInstabili(lista *L);

/* =========================
   FUNZIONI DI SUPPORTO LISTA
   ========================= */
static nodo *newNode(int x) {
    nodo *n = (nodo *)malloc(sizeof(nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = x;
    n->next = NULL;
    return n;
}

static void pushBack(lista *L, int x) {
    nodo *n = newNode(x);
    if (*L == NULL) {
        *L = n;
        return;
    }
    nodo *cur = *L;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
}

static void printList(lista L) {
    printf("[ ");
    while (L != NULL) {
        printf("%d ", L->dato);
        L = L->next;
    }
    printf("]\n");
}

static void freeList(lista L) {
    while (L != NULL) {
        nodo *nx = L->next;
        free(L);
        L = nx;
    }
}

/* (facoltativo) costruisce una lista da array, utile per test */
static lista buildFromArray(const int *a, int n) {
    lista L = NULL;
    for (int i = 0; i < n; i++) pushBack(&L, a[i]);
    return L;
}

/* =========================
   MAIN DI TEST
   ========================= */
int èinsabile(int a, int b, int c);
float media(int a, int b);
lista f(lista head, int *count, lista root);

int main(void) {
    /*
      Metto una lista di test (puoi cambiarla).
      Nota: i primi due nodi non sono mai valutati.
    */
    int a[] = { 10, 8, 2, 1, 7, 3, 2, 9, 0, 0, 5 };
    int n = (int)(sizeof(a) / sizeof(a[0]));
    lista L = buildFromArray(a, n);

    printf("=== LISTA INIZIALE ===\n");
    printList(L);

    int eliminati = ripulisciInstabili(&L); /* stub */
    printf("\nNodi eliminati = %d (stub)\n", eliminati);

    printf("\n=== LISTA FINALE ===\n");
    printList(L);

    freeList(L);
    return 0;
}


int instabile(lista prev2, lista prev1, lista cur) {
    if (prev2 == NULL || prev1 == NULL || cur == NULL) return 0;
    float m = (prev2->dato + prev1->dato) / 2.0f;
    return (cur->dato < m);
}

int ripulisciRec(lista *pcurr, lista prev2, lista prev1) {
    if (pcurr == NULL || *pcurr == NULL) return 0;

    lista cur = *pcurr;

    /* Se cur è instabile: elimina tutto il blocco massimale */
    if (instabile(prev2, prev1, cur)) {
        int eliminati = 0;

        while (*pcurr != NULL && instabile(prev2, prev1, *pcurr)) {
            lista kill = *pcurr;
            *pcurr = (*pcurr)->next;
            free(kill);
            eliminati++;
        }

        /* Dopo la cancellazione, rivaluta da qui con gli stessi prev */
        return eliminati + ripulisciRec(pcurr, prev2, prev1);
    }

    return ripulisciRec(&cur->next, prev1, cur);
}

int ripulisciInstabili(lista *L) {
    if (L == NULL || *L == NULL) return 0;
    return ripulisciRec(L, NULL, NULL);
}
