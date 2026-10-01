//
//  main.c
//  liste 2 pag 70 -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//




#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int numero;
    struct Node *next;
} Nodo;

typedef Nodo *Lista;

/* =========================
   PROTOTIPI FUNZIONI (ESERCIZIO)
   ========================= */
int ondulatoria(Lista lis);
int ondulatoriaCrescente(Lista lis);

/* =========================
   UTILITY PER CREARE LISTE
   ========================= */
static Lista nuovoNodo(int x) {
    Lista n = (Lista)malloc(sizeof(Nodo));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->numero = x;
    n->next = NULL;
    return n;
}

static Lista inserisciInCoda(Lista head, int x) {
    Lista n = nuovoNodo(x);
    if (head == NULL)
        return n;
    Lista cur = head;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = n;
    return head;
}

/* =========================
   STAMPA LISTA
   ========================= */
static void stampaLista(Lista l) {
    while (l != NULL) {
        printf("%d -> ", l->numero);
        l = l->next;
    }
    printf("NULL\n");
}

/* =========================
   FREE LISTA
   ========================= */
static void freeLista(Lista l) {
    while (l != NULL) {
        Lista tmp = l->next;
        free(l);
        l = tmp;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {

    Lista l1 = NULL;
    l1 = inserisciInCoda(l1, 5);
    l1 = inserisciInCoda(l1, 2);
    l1 = inserisciInCoda(l1, 6);
    l1 = inserisciInCoda(l1, 3);
    l1 = inserisciInCoda(l1, 7);

    Lista l2 = NULL;
    l2 = inserisciInCoda(l2, 1);
    l2 = inserisciInCoda(l2, 2);
    l2 = inserisciInCoda(l2, 3);
    l2 = inserisciInCoda(l2, 4);

    printf("Lista 1: ");
    stampaLista(l1);

    printf("Lista 2: ");
    stampaLista(l2);

    printf("\n=== TEST FUNZIONI (NON IMPLEMENTATE) ===\n");
    printf("ATTENZIONE: le funzioni ondulatoria e ondulatoriaCrescente NON sono implementate.\n");
    printf("Quando le implementi, scommenta le chiamate qui sotto.\n\n");

    
    printf("Lista 1 ondulatoria? %d\n", ondulatoria(l1));
    printf("Lista 1 ondulatoria crescente? %d\n", ondulatoriaCrescente(l1));
//
    printf("Lista 2 ondulatoria? %d\n", ondulatoria(l2));
    printf("Lista 2 ondulatoria crescente? %d\n", ondulatoriaCrescente(l2));


    freeLista(l1);
    freeLista(l2);

    return 0;
}

//int ondulatoriaCrescente(Lista lis) {
//    // TODO
//}

int ondulatoria(Lista lis)
    {
        if(lis==NULL || lis->next==NULL || lis->next->next==NULL)
            return 1;
    Lista prec=lis;
    Lista mid=lis->next;
    Lista succ=mid->next;
    if((prec->numero<mid->numero && mid->numero<succ->numero) ||(prec->numero>mid->numero && mid->numero>succ->numero ))
        return 0;
    return ondulatoria(mid);
    }

//Una lista è ondulatoria crescente se mai tre numeri consecutivi sono in
//ordine crescente o decrescente ma sempre il primo e il terzo di tre
//consecutivi sono in ordine crescente.
int ondulatoriaCrescente(Lista lis)
    {
    if(lis==NULL || lis->next==NULL || lis->next->next==NULL)
        return 1;
Lista prec=lis;
Lista mid=lis->next;
Lista succ=mid->next;
if((prec->numero<mid->numero && mid->numero<succ->numero) ||(prec->numero>mid->numero && mid->numero>succ->numero ))
    return 0;
if(prec->numero>=succ->numero)
    return 0;
return ondulatoriaCrescente(mid);
    }
