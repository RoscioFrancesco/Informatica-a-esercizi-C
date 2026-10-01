//
//  main.c
//  es 15 esercitazione alessandrini
//
//  Created by Francesco Roscio Ricon on 24/01/26.
//


#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

/* Crea un nodo */
Lista newNode(int x) {
    Lista n = (Lista)malloc(sizeof(Nodo));
    if (n == NULL) {
        printf("Errore malloc\n");
        exit(1);
    }
    n->val = x;
    n->next = NULL;
    return n;
}


/* Stampa lista */
void stampaLista(Lista L) {
    while (L != NULL) {
        printf("%d -> ", L->val);
        L = L->next;
    }
    printf("NULL\n");
}

/* Libera lista */
void freeLista(Lista L) {
    while (L != NULL) {
        Lista tmp = L;
        L = L->next;
        free(tmp);
    }
}
Lista inserimento_ordinato_ricorsivo(Lista head, int val);
Lista inserimento_ordinato_iterativo(Lista head, int val);
int main() {


    /* inserisco valori NON in ordine (la funzione li ordinerà) */
    int valori[8] = {7, 3, 5, 3, 10, 1, 7, 2};

    printf("Inserimento ordinato ricorsivo (con ripetizioni):\n");
    Lista head=NULL;
    int i;
    for(i=0; i<8; i++)
        {
            head=inserimento_ordinato_iterativo(head, valori[i]);
        }
    
    Lista L=NULL;
    for(i=0; i<8; i++)
        {
            L=inserimento_ordinato_ricorsivo(L, valori[i]);
        }

    printf("\nLista finale ordinata:\n");
    stampaLista(head);
    printf("\n");
    stampaLista(L);
    freeLista(L);
    return 0;
}

Lista inserimento_ordinato_iterativo(Lista head, int val)
    {
    Lista new=(Lista)malloc(sizeof(Nodo));
    new->val=val;
    new->next=NULL;
        if(head==NULL || val<head->val)
            {
                new->next=head;
                return new;
            }
    Lista scorrilista=head;
    while(scorrilista->next!=NULL && scorrilista->next->val<val)
        {
            scorrilista=scorrilista->next;
        }
    new->next=scorrilista->next;
    scorrilista->next=new;
    return head;
    }

Lista inserimento_ordinato_ricorsivo(Lista head, int val)
    {
    if (head == NULL || val <= head->val) {
            Lista new = (Lista)malloc(sizeof(Nodo));
            new->val = val;
            new->next = head;
            return new;
        }
    head->next=inserimento_ordinato_ricorsivo(head->next, val);
    return head;
    }
