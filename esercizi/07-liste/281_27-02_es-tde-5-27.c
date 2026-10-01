//
//  main.c
//  es tde 5 27
//
//  Created by Francesco Roscio Ricon on 27/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;


int numSommaDiff(Lista head);

/* =========================
   FUNZIONI DI SUPPORTO (per il main)
   ========================= */
Nodo* newNode(int v) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    if(!n) { printf("Errore malloc\n"); exit(1); }
    n->val = v;
    n->next = NULL;
    return n;
}

Lista pushBack(Lista head, int v) {
    Nodo *n = newNode(v);
    if(head == NULL) return n;
    Nodo *cur = head;
    while(cur->next != NULL) cur = cur->next;
    cur->next = n;
    return head;
}

void printList(Lista head) {
    Nodo *cur = head;
    while(cur != NULL) {
        printf("%d", cur->val);
        if(cur->next) printf(" -> ");
        cur = cur->next;
    }
    printf(" -> NULL\n");
}

void freeList(Lista head) {
    while(head != NULL) {
        Nodo *tmp = head->next;
        free(head);
        head = tmp;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int sommaprec(Lista head, Lista mio);
int sommadopo(Lista head);
int main() {
    Lista A = NULL;
    Lista B = NULL;

    
    int vA[] = {1, 2, 1, 20, -6, 16, 14};
    int nA = sizeof(vA)/sizeof(vA[0]);
    for(int i=0; i<nA; i++) A = pushBack(A, vA[i]);

    
    int vB[] = {1, 2, 1, 20, -14, 20, 14};
    int nB = sizeof(vB)/sizeof(vB[0]);
    for(int i=0; i<nB; i++) B = pushBack(B, vB[i]);

    printf("=== TEST 1 ===\n");
    printf("Lista A: ");
    printList(A);
    printf("numSommaDiff(A) = %d (atteso: 1)\n\n", numSommaDiff(A));

    printf("=== TEST 2 ===\n");
    printf("Lista B: ");
    printList(B);
    printf("numSommaDiff(B) = %d (atteso: 0)\n\n", numSommaDiff(B));

    freeList(A);
    freeList(B);

    return 0;
}
int sommaprec(Lista head, Lista mio) // non conta l'elemento mio
    {
        if(head==NULL)
            return 0;
    Lista scorri=head;
    int somma=0;
    while(scorri!=mio)
        {
            somma=somma+scorri->val;
            scorri=scorri->next;
        }
    return somma;
    }
int sommadopo(Lista head)
    {
        if(head==NULL)
            return 0;
        int somma=0;
        if(head->next==NULL)
            return head->val;
        head=head->next;
        Lista scorri=head;
        while(scorri!=NULL)
            {
                somma=scorri->val+somma;
                scorri=scorri->next;
            }
    return somma;
    }
int scorri(Lista head, Lista mio)
    {
        if(head==NULL || mio==NULL)
            return 0;
        if(mio->val==sommadopo(mio)-sommaprec(head, mio))
            return 1;
    return scorri(head, mio->next);
    }
int numSommaDiff(Lista head)
    {
    return scorri(head, head);
    }
