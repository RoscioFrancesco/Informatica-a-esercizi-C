//  Created by Francesco Roscio Ricon on 21/01/26.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct nodo{
    int valore;
    struct nodo* next;
} nodo;
typedef nodo* lista;

lista InsInFondo(lista lis, int elem);
void VisualizzaLista(lista lis);
lista costruisci();
void stampalista(lista head);
lista funzione(lista start);

int main(){
    lista lis = costruisci();
    lista new=NULL;
    stampalista(lis);
    new=funzione(lis);
    printf("\n");
    stampalista(new);
}


lista InsInFondo(lista lis, int elem) {
    lista punt;
    if(lis == NULL){
        punt = malloc(sizeof(nodo));
        punt->next   = NULL;
        punt->valore = elem;
        return punt;
    }
    else {
        lis->next = InsInFondo(lis->next, elem);
        return lis;
    }
}


void VisualizzaLista( lista lis ) {
    if ( lis == NULL )
        printf(" ---| \n");
    else {
        printf(" %d\n ---> ", lis->valore);
        VisualizzaLista( lis->next );
    }
}

lista costruisci(){
    // 1 -> 9 -> 4 -> 7 -> 7 -> 1 -> 11 -> 5 -> 7 -> 1 -> 5
    lista lis = NULL;
    lis = InsInFondo(lis, 1);
    lis = InsInFondo(lis, 5);
    lis = InsInFondo(lis, 16);
    lis = InsInFondo(lis, 11);
    lis = InsInFondo(lis, 12);
    lis = InsInFondo(lis, 4);
    lis = InsInFondo(lis, 5);
    lis = InsInFondo(lis, 5);
    lis = InsInFondo(lis, 3);
    lis = InsInFondo(lis, 1);
    lis = InsInFondo(lis, 5);

    return lis;
}

lista funzione(lista start)
    {
    lista prec=start;
    lista scorri_lista=start->next;
    lista succ=scorri_lista->next;
    lista head=NULL;
    while(succ!=NULL)
        {
            if(prec->valore<scorri_lista->valore && scorri_lista->valore>succ->valore)
                {
                    head=InsInFondo(head, scorri_lista->valore);
                }
            scorri_lista=scorri_lista->next;
            prec=prec->next;
            succ=succ->next;
        }
    return head;
}

void stampalista(lista head)
    {
    lista scorrilista=head;
    while (scorrilista!=NULL) {
        printf("%d -->", scorrilista->valore);
        scorrilista=scorrilista->next;
    }
    }
