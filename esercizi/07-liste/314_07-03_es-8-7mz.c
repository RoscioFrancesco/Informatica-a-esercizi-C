//
//  main.c
//  es 8 7mz
//
//  Created by Francesco Roscio Ricon on 07/03/26.
//


#include <stdio.h>
#include <stdlib.h>
typedef struct nodo{
    int x;
    struct nodo *next;
}Nodo;
typedef Nodo* Lista;
void inserisciTesta(Lista *l, int valore);
void stampa(Lista head);
void inserisciincoda(Lista *l, int valore);
int main() {
    Lista l=NULL;
    inserisciincoda(&l, 1);
    inserisciincoda(&l, 2);
    inserisciincoda(&l, 3);
    stampa(l);
}
void inserisciTesta(Lista *l, int valore)
    {
        Lista new=(Lista)malloc(sizeof(Nodo));
        new->x=valore;
        new->next=*l;
        *l=new;
    }
void stampa(Lista head)
    {
    while (head!=NULL) {
        printf("%d-->", head->x);
        head=head->next;
    }
    }

void inserisciincoda(Lista *l, int valore)
    {
    Lista scorri=*l;
    if(scorri==NULL)
        {
            Lista new=(Lista)malloc(sizeof(*new));
            new->x=valore;
            new->next=NULL;
            *l=new;
            return;
        }
    while(scorri!=NULL && scorri->next!=NULL)
        {
            scorri=scorri->next;
        }
    Lista new=(Lista)malloc(sizeof(*new));
    new->x=valore;
    new->next=NULL;
    scorri->next=new;
    }
