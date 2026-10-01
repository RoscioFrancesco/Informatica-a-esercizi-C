//
//  main.c
//  chat es 3 liste -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//

#include <stdio.h>
#include <stdlib.h>
typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;
Lista f(Lista head, int k, int *somma);


/*
  Dato K, elimina ogni blocco MASSIMALE consecutivo
  la cui somma è esattamente K.

  Suggerimento interfaccia:
  - Lista* per poter cambiare la testa
  - ritorna quanti nodi hai eliminato (debug comodo)
*/
int eliminaBlocchiSommaK(Lista *L, int K);
int trovablocco(Lista head, int k);
Lista distruggiK(Lista head, int k);
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
    if (*L == NULL) { *L = n; return; }
    Lista cur = *L;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
}

Lista buildFromArray(const int a[], int n) {
    Lista L = NULL;
    for (int i = 0; i < n; i++) pushBack(&L, a[i]);
    return L;
}

void printList(const char *label, Lista L) {
    printf("%s[", label);
    for (Lista cur = L; cur != NULL; cur = cur->next) {
        printf("%d", cur->val);
        if (cur->next) printf(" -> ");
    }
    printf("]\n");
}

int length(Lista L) {
    int c = 0;
    while (L) { c++; L = L->next; }
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

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    /* Test 1: esempio del testo */
    int t1[] = {1, 2, 3, 4, 2, 3};
    int K1 = 6;

    /* Test 2: overlapping (greedy da sinistra, eliminazioni ripetute) */
    int t2[] = {1, 2, 1, 2};
    int K2 = 3;

    /* Test 3: blocco in testa e poi un altro che nasce dopo */
    int t3[] = {3, 3, 3};
    int K3 = 6;

    /* Test 4: blocco lungo (massimale) */
    int t4[] = {2, 1, 1, 2};
    int K4 = 4;

    struct {
        const char *name;
        int *arr;
        int n;
        int K;
    } tests[] = {
        {"T1", t1, 6, K1},
        {"T2", t2, 4, K2},
        {"T3", t3, 3, K3},
        {"T4", t4, 4, K4},
    };

    int nt = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < nt; i++) {
        Lista L = buildFromArray(tests[i].arr, tests[i].n);

        printf("\n==================== %s (K=%d) ====================\n", tests[i].name, tests[i].K);
        printList("Prima: ", L);
        printf("Lunghezza prima: %d\n", length(L));

        int removed = eliminaBlocchiSommaK(&L, tests[i].K);

        printList("Dopo:  ", L);
        printf("Lunghezza dopo:  %d\n", length(L));
        printf("Nodi rimossi (ritorno funzione): %d\n", removed);

        freeList(L);
    }

    return 0;
}
// elimina i primi k nodi della lista e ritorna la nuova testa
Lista distruggiK(Lista head, int k) {
    for (int i = 0; i < k && head != NULL; i++) {
        Lista tmp = head->next;
        free(head);
        head = tmp;
    }
    return head;
}

int trovablocco(Lista head, int K) {
    int somma = 0;
    int len = 0;
    while (head != NULL && somma < K) {
        somma = somma+head->val;
        head = head->next;
        len++;
    }
    return (somma == K) ? len : 0;
}

/*
  Versione semplice con soli contatori:
  - scorre da sinistra
  - se trova un blocco che parte da curr con somma K, lo elimina
  - dopo eliminazione riparte dallo stesso punto (perché la lista cambia)
  Ritorna il numero totale di nodi eliminati.
*/
int eliminaBlocchiSommaK(Lista *L, int K) {
    int eliminati = 0;

    Lista *pp = L; // puntatore al "link" che porta al nodo corrente (testa o next di un nodo)

    while (*pp != NULL) {
        int len = trovablocco(*pp, K);

        if (len == 0) {
            pp = &((*pp)->next);
        } else {
            *pp = distruggiK(*pp, len);
            eliminati =eliminati+ len;
        }
    }

    return eliminati;
}
