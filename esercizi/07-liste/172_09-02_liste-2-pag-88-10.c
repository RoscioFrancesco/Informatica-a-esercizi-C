//
//  main.c
//  liste 2 pag 88 -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct EL {
    int dato;
    struct EL *next;
} nodo;

typedef nodo *lista;

lista differenzaSimmetrica(lista l1, lista l2);   

/* =========================
   UTILITY PER LE LISTE
   ========================= */
static lista nuovoNodo(int x) {
    lista n = (lista)malloc(sizeof(nodo));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->dato = x;
    n->next = NULL;
    return n;
}

static lista inserisciInCoda(lista head, int x) {
    lista n = nuovoNodo(x);
    if (head == NULL)
        return n;
    lista cur = head;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = n;
    return head;
}

static void stampaLista(lista l) {
    while (l != NULL) {
        printf("%d -> ", l->dato);
        l = l->next;
    }
    printf("NULL\n");
}

static void freeLista(lista l) {
    while (l != NULL) {
        lista tmp = l->next;
        free(l);
        l = tmp;
    }
}
lista inserisciincoda(lista head, int x);
int trova(lista head, int x);
int main(void) {

    /* Lista 1: 1 2 3 4 */
    lista l1 = NULL;
    l1 = inserisciInCoda(l1, 1);
    l1 = inserisciInCoda(l1, 2);
    l1 = inserisciInCoda(l1, 3);
    l1 = inserisciInCoda(l1, 4);

    /* Lista 2: 3 4 5 6 */
    lista l2 = NULL;
    l2 = inserisciInCoda(l2, 3);
    l2 = inserisciInCoda(l2, 4);
    l2 = inserisciInCoda(l2, 5);
    l2 = inserisciInCoda(l2, 6);

    printf("=== INPUT ===\n");
    printf("Lista 1: ");
    stampaLista(l1);
    printf("Lista 2: ");
    stampaLista(l2);


    
    lista ris = differenzaSimmetrica(l1, l2);
    printf("Lista risultato (elementi in una sola lista): ");
    stampaLista(ris);
    freeLista(ris);

    freeLista(l1);
    freeLista(l2);

    return 0;
}


lista differenzaSimmetrica(lista l1, lista l2) {
    lista new=NULL;
    lista scorril1=l1;
    while (scorril1!=NULL) {
        if(trova(l2, scorril1->dato)==0)
            {
                new=inserisciincoda(new, scorril1->dato);
            }
        scorril1=scorril1->next;
    }
    lista scorril2=l2;
    while (scorril2!=NULL) {
        if(trova(l1, scorril2->dato)==0)
            new=inserisciincoda(new, scorril2->dato);
        scorril2=scorril2->next;
    }
    return new;
}

int trova(lista head, int x)
    {
        if(head==NULL)
            return 0;
    while (head!=NULL) {
        if(head->dato==x)
            return 1;
        head=head->next;
    }
    return 0;
    }

lista inserisciincoda(lista head, int x)
    {
        if(head==NULL)
            {
                lista new=(lista)malloc(sizeof(*new));
                new->next=head;
                new->dato=x;
                return new;
            }
        head->next=inserisciincoda(head->next, x);
        return head;
    }
