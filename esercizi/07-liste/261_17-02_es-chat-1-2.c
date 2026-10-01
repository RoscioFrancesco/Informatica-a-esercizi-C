//
//  main.c
//  es chat 1  -2
//
//  Created by Francesco Roscio Ricon on 17/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int v;
    struct nodo *next;
} nodo;

typedef nodo* lista;

int correggi(lista l);            // <-- DA SCRIVERE TU
int sommaCifre(int x);            // <-- ti serve quasi sicuramente

lista newNode(int x) {
    lista n = (lista)malloc(sizeof(nodo));
    if (!n) {
        printf("Errore malloc\n");
        exit(1);
    }
    n->v = x;
    n->next = NULL;
    return n;
}

lista pushBack(lista l, int x) {
    if (l == NULL) return newNode(x);
    lista cur = l;
    while (cur->next != NULL) cur = cur->next;
    cur->next = newNode(x);
    return l;
}

void printList(lista l) {
    while (l != NULL) {
        printf("%d", l->v);
        if (l->next != NULL) printf(" -> ");
        l = l->next;
    }
    printf("\n");
}

void freeList(lista l) {
    while (l != NULL) {
        lista tmp = l;
        l = l->next;
        free(tmp);
    }
}

lista f(lista head, int *aumento);
int main(void) {

    /* =========================
       TEST 1: già valida
       Vincolo: next >= prev + sommaCifre(prev)
       Lista: 10 -> 11 -> 13
       sommaCifre(10)=1  => 11 >= 10+1 OK
       sommaCifre(11)=2  => 13 >= 11+2 OK
       Incrementi totali attesi: 0
       ========================= */
    lista L1 = NULL;
    L1 = pushBack(L1, 10);
    L1 = pushBack(L1, 11);
    L1 = pushBack(L1, 13);

    printf("=== TEST 1 ===\n");
    printf("Prima:  ");
    printList(L1);

    int inc1 = correggi(L1);

    printf("Dopo:   ");
    printList(L1);
    printf("Somma incrementi restituita: %d\n\n", inc1);

    /* =========================
       TEST 2: correzione semplice (senza grande domino)
       Lista: 9 -> 10
       sommaCifre(9)=9 => next deve essere >= 18
       Quindi 10 diventa 18 (incremento 8)
       Incrementi totali attesi: 8
       ========================= */
    lista L2 = NULL;
    L2 = pushBack(L2, 9);
    L2 = pushBack(L2, 10);

    printf("=== TEST 2 ===\n");
    printf("Prima:  ");
    printList(L2);

    int inc2 = correggi(L2);

    printf("Dopo:   ");
    printList(L2);
    printf("Somma incrementi restituita: %d\n\n", inc2);

    /* =========================
       TEST 3: domino evidente
       Lista: 19 -> 20 -> 21
       sommaCifre(19)=10 => 20 deve diventare 29 (+9)
       Ora prev=29, sommaCifre(29)=11 => 21 deve diventare 40 (+19)
       Incrementi totali attesi: 9+19 = 28
       Output finale atteso: 19 -> 29 -> 40
       ========================= */
    lista L3 = NULL;
    L3 = pushBack(L3, 19);
    L3 = pushBack(L3, 20);
    L3 = pushBack(L3, 21);

    printf("=== TEST 3 ===\n");
    printf("Prima:  ");
    printList(L3);

    int inc3 = correggi(L3);

    printf("Dopo:   ");
    printList(L3);
    printf("Somma incrementi restituita: %d\n\n", inc3);

    /* cleanup */
    freeList(L1);
    freeList(L2);
    freeList(L3);

    return 0;
}
int sommaCifre(int x) {
    int somma = 0;
    while (x > 0) {
        somma += x % 10;
        x /= 10;
    }
    return somma;
}
// per ogni coppia consecutiva vale: next->v >= prev->v + sommaCifre(prev->v)

lista f(lista head, int *aumento)
    {
        if(head==NULL || head->next==NULL)
            return head;
        if(!(head->next->v>=head->v+sommaCifre(head->v)))
            {
                int val=head->next->v;
                head->next->v=head->v+sommaCifre(head->v);
                *aumento=(*aumento)+head->next->v-val;
            }
    return f(head->next, aumento);
    }
int correggi(lista l)
    {
    int aumento=0;
    l=f(l, &aumento);
    return aumento;
    }
