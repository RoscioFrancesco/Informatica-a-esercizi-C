//  Created by Francesco Roscio Ricon on 22/01/26.

#include <stdio.h>
#include <stdlib.h>

typedef struct EL {
    int dato;
    struct EL *next;
} nodo;

typedef nodo *lista;


void stampaLista(lista l) {
    printf("[ ");
    while (l != NULL) {
        printf("%d --> ", l->dato);
        l = l->next;
    }
    printf("]\n");
}

lista inserisciInTesta(lista l, int x) {
    nodo *nuovo = (nodo *)malloc(sizeof(nodo));
    nuovo->dato = x;
    nuovo->next = l;
    return nuovo;
}

lista funzione(lista head1, lista head2);
int contaoccorrenze(lista head, int valore);
int compare(lista head, int valore);

int main() {
    lista l1 = NULL;
    lista l2 = NULL;

    /* l1 = [3, 5, 3, 7, 7, 7, 9] */
    l1 = inserisciInTesta(l1, 9);
    l1 = inserisciInTesta(l1, 7);
    l1 = inserisciInTesta(l1, 7);
    l1 = inserisciInTesta(l1, 7);
    l1 = inserisciInTesta(l1, 3);
    l1 = inserisciInTesta(l1, 5);
    l1 = inserisciInTesta(l1, 3);

    /* l2 = [7, 3, 3, 5, 7, 7, 10] */
    l2 = inserisciInTesta(l2, 10);
    l2 = inserisciInTesta(l2, 7);
    l2 = inserisciInTesta(l2, 7);
    l2 = inserisciInTesta(l2, 5);
    l2 = inserisciInTesta(l2, 3);
    l2 = inserisciInTesta(l2, 3);
    l2 = inserisciInTesta(l2, 7);

    printf("Lista 1: ");
    stampaLista(l1);

    printf("Lista 2: ");
    stampaLista(l2);
    
    lista new=funzione(l1, l2);

    printf("Risultato: ");
    stampaLista(new);
 
}


int contaoccorrenze(lista head, int valore)
    {
    int contatore=0;
    lista scorrilista=head;
    while(scorrilista!=NULL)
        {
            if(scorrilista->dato==valore)
                contatore++;
            scorrilista=scorrilista->next;
        }
    return contatore;
    }

int compare(lista head, int valore)
    {
    if(head==NULL)
        return 0;
    lista scorrilista=head;
    while(scorrilista!=NULL)
        {
            if(scorrilista->dato==valore)
                return 1;
            scorrilista=scorrilista->next;
        }
    return 0;
    }

lista inserisciintesta(lista head, int valore)
    {
    lista new=(lista)malloc(sizeof(nodo));
    new->dato=valore;
    new->next=head;
    return new;
    }

lista funzione(lista head1, lista head2)
    {
    lista scorri1=head1;
    lista scorri2=head2;
    lista new=NULL;
    while (scorri1!=NULL) {
        if(compare(scorri2, scorri1->dato))
            {
                if(compare(new, scorri1->dato))
                {
                    scorri1=scorri1->next;
                    continue;
                }
                else {
                    int occorrenzein1=contaoccorrenze(head1, scorri1->dato);
                    int occorrenzein2=contaoccorrenze(head2, scorri1->dato);
                    
                    if(occorrenzein1==occorrenzein2)
                        new=inserisciintesta(new, scorri1->dato);
                    scorri1=scorri1->next;
                }
            }
        else{
            scorri1=scorri1->next;
        }
        
    }
    return new;
    }
