//  Created by Francesco Roscio Ricon on 07/02/26.

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE DATI
   ========================= */
typedef struct EL {
    int dato;
    struct EL *next;
} nodo;

typedef nodo* Lista;


Lista Merge(Lista lista1, Lista lista2);   // DA SVOLGERE

/* =========================
   FUNZIONI DI SUPPORTO
   ========================= */
Lista inserisciInCoda(Lista head, int val)
{
    Lista nuovo = malloc(sizeof(nodo));
    nuovo->dato = val;
    nuovo->next = NULL;

    if(head == NULL)
        return nuovo;

    Lista temp = head;
    while(temp->next != NULL)
        temp = temp->next;

    temp->next = nuovo;
    return head;
}

void stampaLista(Lista l)
{
    while(l != NULL)
    {
        printf("%d ", l->dato);
        l = l->next;
    }
    printf("\n");
}

/* =========================
   MAIN DI TEST
   ========================= */
Lista inserisci_ordinata(Lista head, int x);
int main()
{
    Lista lista1 = NULL;
    Lista lista2 = NULL;
    Lista risultato = NULL;

    /* lista1: 1 3 5 7 */
    lista1 = inserisciInCoda(lista1, 1);
    lista1 = inserisciInCoda(lista1, 3);
    lista1 = inserisciInCoda(lista1, 5);
    lista1 = inserisciInCoda(lista1, 7);

    /* lista2: 2 3 6 8 */
    lista2 = inserisciInCoda(lista2, 2);
    lista2 = inserisciInCoda(lista2, 3);
    lista2 = inserisciInCoda(lista2, 6);
    lista2 = inserisciInCoda(lista2, 8);

    printf("Lista 1: ");
    stampaLista(lista1);

    printf("Lista 2: ");
    stampaLista(lista2);

    risultato = Merge(lista1, lista2);

    printf("Lista merge: ");
    stampaLista(risultato);

    return 0;
}


Lista Merge(Lista lista1, Lista lista2)
{
    Lista new=NULL;
    Lista scorri1=lista1;
    Lista scorri2=lista2;
    while (scorri1!=NULL) {
        new=inserisci_ordinata(new, scorri1->dato);
        scorri1=scorri1->next;
    }
    while (scorri2!=NULL) {
        new=inserisci_ordinata(new, scorri2->dato);
        scorri2=scorri2->next;
    }
    return new;
}
Lista inserisci_ordinata(Lista head, int x) // soto inserendo ordinato rispetto alla head
    {
        if(head==NULL || x<head->dato)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->dato=x;
                new->next=head;
                return new;
            }
        head->next=inserisci_ordinata(head->next, x);
        return head;
    }
