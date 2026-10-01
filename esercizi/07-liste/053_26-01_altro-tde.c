//  Created by Francesco Roscio Ricon on 26/01/26.

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
lista funz(lista head);

int main() {
    lista lis = costruisci();
    VisualizzaLista(lis);
    lis=funz(lis);
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
lista funz(lista head)
    {
        if(head==NULL)
            return head;
    lista scorri=head;
    while(scorri->next!=NULL)
        {
            lista succ=scorri->next;
            if(succ->valore-scorri->valore!=1)
                {
                    lista punt= malloc(sizeof(nodo));
                    punt->valore=(scorri->valore)+1;
                    scorri->next=punt;
                    punt->next=succ;
                    scorri=punt;
                }
            else
                {
                    scorri=succ;
                }
        }
    return head;
    }

