//
//  main.c
//  chat es 8 liste -6
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

/*
  Elimina tutti i nodi il cui valore ha frequenza dispari nella lista.

  Suggerito:
  - L puntatore alla testa (può cambiare la testa)
  - ritorna numero di nodi eliminati (debug comodo)
*/
int eliminaDispariOccorrenze(Lista *L);

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

int main(void) {

    int t1[] = {1, 2, 2, 3, 3, 3, 4, 4};       // 1x1 (odd) -> via; 2x2 (even)-> ok; 3x3 (odd)-> via; 4x2 (even)-> ok
    int t2[] = {5, 5, 5, 5};                   // 5x4 (even) -> resta tutto
    int t3[] = {7, 8, 7, 8, 9};                // 7x2 ok, 8x2 ok, 9x1 via
    int t4[] = {1, 1, 2, 2, 2, 3, 3, 3, 3};    // 1x2 ok, 2x3 via, 3x4 ok
    int t5[] = {10};                           // 10x1 via (lista diventa vuota)

    struct {
        const char *name;
        int *arr;
        int n;
    } tests[] = {
        {"T1", t1, 8},
        {"T2", t2, 4},
        {"T3", t3, 5},
        {"T4", t4, 9},
        {"T5", t5, 1},
    };

    int nt = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < nt; i++) {
        Lista L = buildFromArray(tests[i].arr, tests[i].n);

        printf("\n==================== %s ====================\n", tests[i].name);
        printList("Prima: ", L);
        printf("Lunghezza prima: %d\n", length(L));

        int removed = eliminaDispariOccorrenze(&L);

        printList("Dopo:  ", L);
        printf("Lunghezza dopo:  %d\n", length(L));
        printf("Nodi rimossi: %d\n", removed);

        freeList(L);
    }

    return 0;
}
int contaoccorrenze(Lista head, int x)
    {
    int count=0;
        if(head==NULL)
            return 0;
    while (head!=NULL) {
        if(head->val==x)
            count++;
        head=head->next;
    }
    return count;
    }
int ver(int x, Lista head)
    {
    int num=contaoccorrenze(head, x);
    if(num%2==0)
        return 0;
    return 1;
    }


int eliminaDispariOccorrenze(Lista *L)
    {
        if(*L==NULL)
            return 0;
    Lista *pp=L;
    int count=0;
    while (*pp!=NULL) {
        if((*pp)->val==3)
            {
                count++;
                Lista temp=*pp;
                *pp=(*pp)->next;
                free(temp);
            }
        else
            {
                pp=&(*pp)->next;
            }
    }
    return count;
    }
