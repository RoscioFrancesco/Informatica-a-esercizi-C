//
//  main.c
//  chat es 2 liste -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA LISTA
   ========================= */
typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;


/*
   Elimina ogni nodo che ha alla sua destra
   un valore strettamente maggiore.

   Deve funzionare anche se cambia la testa.

   Versione bastarda: una sola scansione ricorsiva.
*/
int cancellaDominatiMaxFuturo(Lista *L);


/* =========================
   UTILITY LISTA
   ========================= */

Lista newNode(int v) {
    Lista n = (Lista)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->next = NULL;
    return n;
}

void pushBack(Lista *L, int v) {
    Lista n = newNode(v);
    if (*L == NULL) {
        *L = n;
        return;
    }
    Lista cur = *L;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = n;
}

Lista buildFromArray(const int a[], int n) {
    Lista L = NULL;
    for (int i = 0; i < n; i++)
        pushBack(&L, a[i]);
    return L;
}

void printList(const char *label, Lista L) {
    printf("%s[", label);
    while (L != NULL) {
        printf("%d", L->val);
        if (L->next) printf(" -> ");
        L = L->next;
    }
    printf("]\n");
}

int length(Lista L) {
    int c = 0;
    while (L) {
        c++;
        L = L->next;
    }
    return c;
}

void freeList(Lista L) {
    while (L) {
        Lista tmp = L;
        L = L->next;
        free(tmp);
    }
}

/* =========================
   STUB (NON RISOLVO)
   ========================= */
int cercamaggiore(int x, Lista head);
int cancellaDominatiMaxFuturo(Lista *L) {
    if(L==NULL || *L==NULL)
        return 0;
    if(cercamaggiore((*L)->val, *L))
        {
            Lista temp=*L;
            *L=(*L)->next;
            free(temp);
            return 1+cancellaDominatiMaxFuturo(L);
        }
    return cancellaDominatiMaxFuturo(&(*L)->next);
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {

    int a1[] = {5, 3, 8, 2, 7};      // esempio del testo → 8 -> 7
    int a2[] = {1, 2, 3, 4, 5};      // → 5
    int a3[] = {9, 8, 7, 6};         // → 9 8 7 6
    int a4[] = {4, 1, 4, 1, 4};      // → 4 4 4
    int a5[] = {10};                 // → 10
    int a6[] = {2, 2, 2};            // → 2 2 2 (non strettamente maggiore)

    Lista tests[6];
    const char *names[6] = {"T1", "T2", "T3", "T4", "T5", "T6"};

    tests[0] = buildFromArray(a1, 5);
    tests[1] = buildFromArray(a2, 5);
    tests[2] = buildFromArray(a3, 4);
    tests[3] = buildFromArray(a4, 5);
    tests[4] = buildFromArray(a5, 1);
    tests[5] = buildFromArray(a6, 3);

    for (int i = 0; i < 6; i++) {
        printf("\n==================== %s ====================\n", names[i]);
        printList("Prima: ", tests[i]);
        printf("Lunghezza prima: %d\n", length(tests[i]));

        int removed = cancellaDominatiMaxFuturo(&tests[i]);

        printList("Dopo:  ", tests[i]);
        printf("Lunghezza dopo:  %d\n", length(tests[i]));
        printf("Nodi rimossi: %d\n", removed);
    }

    for (int i = 0; i < 6; i++)
        freeList(tests[i]);

    return 0;
}
//Elimina ogni nodo che ha alla sua destra un valore strettamente maggiore.

int cercamaggiore(int x, Lista head)
    {
        if(head==NULL)
            return 0;
    while (head!=NULL) {
        if(x<head->val)
            return 1;
        head=head->next;
    }
    return 0;
    }
