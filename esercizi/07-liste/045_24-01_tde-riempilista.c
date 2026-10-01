//
//  main.c
//  tde riempilista
//
//  Created by Francesco Roscio Ricon on 24/01/26.
//
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
lista riempilista(lista head);

int main() {
    lista lis = costruisci();
    VisualizzaLista(lis);
     
    lis=riempilista(lis);
    printf("\n");
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

lista riempilista(lista head)
    {
    lista scorrilista=head;
    while (scorrilista->next!=NULL) {
        lista succ=scorrilista->next;
        if(succ->valore-scorrilista->valore>1)
            {
                lista new=(lista)malloc(sizeof(nodo));
                new->valore=scorrilista->valore+1;
                new->next=succ;
                scorrilista->next=new;
                scorrilista=new;
            }
        else
        {
            scorrilista=succ;
        }
        }
    return head;
    }

