//
//  main.c
//  funzione stampa lista
//
//  Created by Francesco Roscio Ricon on 23/11/25.
//

#include <stdio.h>
#include <stdlib.h>
//come prima cosa definisco il tipo strutturato nodo
typedef struct el
{
    int x;
    struct el *next;
}Nodo;
void stampalista(Nodo *l);
int lunghezzalista(Nodo *l);
int main() {
    Nodo *t; // inizializzo e popolo i nodi della lista
    t=(Nodo*)malloc(sizeof(Nodo));
    t->x=7;
    t->next=NULL;
//  quella sopra è una lista con un solo nodo e la messa a terra;
    Nodo *b;
    b=(Nodo*)malloc(sizeof(Nodo));
    b->x=8;
    b->next=NULL;
    t->next=b;
    stampalista(t);
    int len;
    len=lunghezzalista(t);
    printf("\n%d", len);
}
void stampalista(Nodo *l) //indirizzo passato per copia non sotfacendo garbage pk non sto perdendo l'indirizzo della testa
    {
        while(l!=NULL)
        {
            printf("%d-->", l->x);
            l=l->next;
        }
    }
// ora faccio la funzione lunghezza lista
int lunghezzalista(Nodo *l)
    {
    int len=0;
    while(l!=NULL)
        {
            l=l->next;
            len++;
        }
        return len;
    }
