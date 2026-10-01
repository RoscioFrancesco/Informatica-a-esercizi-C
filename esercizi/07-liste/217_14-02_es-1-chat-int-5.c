//
//  main.c
//  es 1 chat int -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int valore;
    struct nodo *next;
} Nodo;

typedef Nodo* lista;


lista eliminaBlocchiDominati(lista L);
/*
Elimina tutti i blocchi dominati da sinistra:

Blocco dominato da sinistra:
- è preceduto da nodo X
- tutti i nodi del blocco hanno valore < X
- termina prima del primo nodo >= X
- X NON viene eliminato
- il nodo >= X NON fa parte del blocco
*/

/* ===== helper ===== */

Nodo* newNode(int v) {
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    n->valore = v;
    n->next = NULL;
    return n;
}

lista buildList(int v[], int n) {
    if (n == 0) return NULL;
    Nodo* head = newNode(v[0]);
    Nodo* tail = head;

    for (int i = 1; i < n; i++) {
        tail->next = newNode(v[i]);
        tail = tail->next;
    }
    return head;
}

void printList(const char* msg, lista L) {
    printf("%s", msg);
    if (!L) {
        printf("NULL\n");
        return;
    }
    while (L) {
        printf("%d", L->valore);
        if (L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

void freeList(lista L) {
    while (L) {
        Nodo* tmp = L->next;
        free(L);
        L = tmp;
    }
}

int main() {

    /* T1: esempio del testo */
    int v1[] = {10,3,4,2,12,5,1,9};
    lista L1 = buildList(v1, 8);

    printList("T1 prima : ", L1);
    L1 = eliminaBlocchiDominati(L1);
    printList("T1 dopo  : ", L1);
    printf("\n");

    /* T2: nessun blocco */
    int v2[] = {1,5,7,10};
    lista L2 = buildList(v2, 4);

    printList("T2 prima : ", L2);
    L2 = eliminaBlocchiDominati(L2);
    printList("T2 dopo  : ", L2);
    printf("\n");

    /* T3: blocco fino a fine lista */
    int v3[] = {20,5,3,1};
    lista L3 = buildList(v3, 4);

    printList("T3 prima : ", L3);
    L3 = eliminaBlocchiDominati(L3);
    printList("T3 dopo  : ", L3);
    printf("\n");

    /* T4: blocchi consecutivi */
    int v4[] = {8,2,1,9,4,3,10,7};
    lista L4 = buildList(v4, 8);

    printList("T4 prima : ", L4);
    L4 = eliminaBlocchiDominati(L4);
    printList("T4 dopo  : ", L4);
    printf("\n");

    /* T5: lista vuota */
    lista L5 = NULL;

    printList("T5 prima : ", L5);
    L5 = eliminaBlocchiDominati(L5);
    printList("T5 dopo  : ", L5);
    printf("\n");

    freeList(L1);
    freeList(L2);
    freeList(L3);
    freeList(L4);

    return 0;
}
//Elimina tutti i blocchi dominati da sinistra:
//
//Blocco dominato da sinistra:
//- è preceduto da nodo X
//- tutti i nodi del blocco hanno valore < X
//- termina prima del primo nodo >= X
//- X NON viene eliminato
//- il nodo >= X NON fa parte del blocco
//*/
int bloccoK(lista head, int X)
    {
        if(head==NULL)
            return 0;
        int count=0;
        while(head!=NULL && head->next!=NULL)
            {
                if(head->next->valore>=X)
                    break;
                count++;
                head=head->next;
            }
        return count;
    }
lista distruggiK(lista head, int K)
    {
        if(head==NULL)
            return head;
        head=head->next;
        for(int i=0; i<K && head!=NULL; i++)
            {
                lista succ=head->next;
                free(head);
                head=succ;
            }
    return head;
    }
void f(lista *l, int X)
    {
        if(*l==NULL)
            return;
        lista *pp=l;
        while(*pp!=NULL)
            {
                if((*pp)->valore==X)
                    {
                        int num=bloccoK((*pp)->next, X);
                        (*pp)->next=distruggiK((*pp)->next, num);
                        pp = &(*pp)->next;
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
lista eliminaBlocchiDominati(lista L)
    {
    f(&L, 12);
    return L;
    }
