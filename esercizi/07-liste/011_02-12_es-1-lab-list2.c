//
//  main.c
//  es 1 lab list2
//
//  Created by Francesco Roscio Ricon on 02/12/25.
//
#include <stdio.h>
#include <stdlib.h>





typedef struct nodo{
    int valore;
    struct nodo* next;
} nodo;
typedef nodo* lista;


lista InsInFondo(lista lis, int elem);
void VisualizzaLista(lista lis);
lista costruisci();
int sonopicchi(lista a, lista b, lista c);
lista funzione(lista lista1, lista *lista2);
lista funzione_iter(lista lista1, lista lista2);


int main(){
    lista lis = costruisci();
    lista lis2=NULL;
    VisualizzaLista(lis);
    lis2=funzione_iter(lis, lis2);
    VisualizzaLista(lis2);
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
        printf(" %d ---> ", lis->valore);
        VisualizzaLista( lis->next );
    }
}


lista costruisci(){
    // 1 -> 5 -> 16 -> 11 -> 12 -> 4 -> 5 -> 5 -> 3 -> 1 -> 5
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

lista funzione(lista lista1, lista *lista2)
    {
    if (lista1 == NULL)
        return lista1;

    if (lista1->next == NULL)
        return lista1;

    if (lista1->next->next == NULL)
        return lista1;
    
    funzione(lista1->next, lista2);
    
    if(sonopicchi(lista1, lista1->next, lista1->next->next))
    {
        *lista2 = InsInFondo(*lista2, lista1->next->valore);
    }
    
    return lista1;
        
    }
int sonopicchi(lista a, lista b, lista c)
    {
        if(b->valore>c->valore && b->valore>a->valore)
            return 1;
    return 0;
    }
// iterativamente era più semplice
// lo faccio in modo iterativo
lista funzione_iter(lista lista1, lista lista2)
    {
    if (lista1 == NULL)
        return lista1;

    if (lista1->next == NULL)
        return lista1;

    if (lista1->next->next == NULL)
        return lista1;
    lista temp=lista1->next;
    lista head2=NULL;
    while(temp->next->next != NULL)
        {
            if(sonopicchi(temp, temp->next, temp->next->next))
                {
                    head2=InsInFondo(head2, temp->next->valore);
                }
            temp=temp->next;
        }
    return head2;
    }
