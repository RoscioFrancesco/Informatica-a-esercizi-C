//
//  main.c
//  aggiungi nodo in coda
//
//  Created by Francesco Roscio Ricon on 23/11/25.
// vogglio aggiungere un elemento in coda

#include <stdio.h>
#include <stdlib.h>
typedef struct el
{
    int x;
    struct el *next;
}Nodo;
typedef Nodo *Lista;
void stampalista(Nodo *l);;
Lista aggiungiincoda (Lista l, int num);
int main() {
    Lista l;
    int num;
    l=(Lista)malloc(sizeof(Nodo));
    l=NULL;
    printf("Inserire il valore da aggiungere");
    scanf("%d", &num);
    l = aggiungiincoda(l, num);
    stampalista(l);
}
Lista aggiungiincoda (Lista l, int num)
    {
    Lista pnew; //lista è un puntatore al tipo nodo
    pnew=(Lista)malloc(sizeof(Nodo));
    pnew->next=NULL;
    pnew->x=num;
    if(l==NULL) // se la lista è vuota
        return pnew;
    Lista temp=l; // salvo il puntatore alla testa
    while(l->next!=NULL)
        {
            l=l->next;
        }
    l->next=pnew; // adesso l->next punta
    return temp;
    }
void stampalista(Lista l) //indirizzo passato per copia non sotfacendo garbage pk non sto perdendo l'indirizzo della testa
    {
        while(l!=NULL)
        {
            printf("%d-->", l->x);
            l=l->next;
        }
        if(l==NULL)
            printf("NULL\n");
    }
