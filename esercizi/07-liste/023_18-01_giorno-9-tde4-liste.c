//  Created by Francesco Roscio Ricon on 18/01/26.

#include <stdlib.h>
#include <stdio.h>


typedef struct nodo {
    int valore;
    struct nodo *next;
} nodo;


typedef nodo *lista;


lista InsInFondo(lista lis, int elem);
void VisualizzaLista(lista lis);
lista costruisci();
lista wrapper(lista head);
lista funzione(lista head, lista scorrilista, lista scorrilista_succ);

int main() {
    lista lis = costruisci();
    VisualizzaLista(lis);
     
    lis=wrapper(lis);
    VisualizzaLista(lis);


    return 0;
}


lista InsInFondo(lista lis, int elem) {
    lista punt;
    if (lis == NULL) {
        punt = malloc(sizeof(nodo));
        punt->next = NULL;
        punt->valore = elem;
        return punt;
    } else {
        lis->next = InsInFondo(lis->next, elem);
        return lis;
    }
}


void VisualizzaLista(lista lis) {
    if (lis == NULL)
        printf(" ---| \n");
    else {
        printf(" %d ---> ", lis->valore);
        VisualizzaLista(lis->next);
    }
}


lista costruisci() {
    // 1 -> 2 -> 5 -> 7 -> 8
    lista lis = NULL;
    lis = InsInFondo(lis, 1);
    lis = InsInFondo(lis, 2);
    lis = InsInFondo(lis, 5);
    lis = InsInFondo(lis, 7);
    lis = InsInFondo(lis, 8);


    return lis;
}
lista funzione(lista head, lista scorrilista, lista scorrilista_succ)
    {
    if(head==NULL)
        return head;
    if(scorrilista_succ==NULL)
        return head;
    if(scorrilista_succ->valore-scorrilista->valore!=1)
        {
            lista new=malloc(sizeof(nodo));
            scorrilista->next=new;
            new->next=scorrilista_succ;
            new->valore=scorrilista->valore+1;
            scorrilista=new;
            return funzione(head, new, new->next);
        }
    else{
        
        return funzione(head, scorrilista_succ, scorrilista_succ->next);
    }
    }

lista wrapper(lista head)
    {
    if(head==NULL)
        return head;
    return funzione(head, head, head->next);
    }
