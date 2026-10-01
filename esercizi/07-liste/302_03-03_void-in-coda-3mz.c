//
//  main.c
//  void in coda 3mz
//
//  Created by Francesco Roscio Ricon on 03/03/26.
//

#include <stdio.h>
#include <stdlib.h>
typedef struct EL{
    int x;
    struct EL *next;
}Elem;
typedef Elem *Lista;

void stampa(Lista l);
void inserisci_incoda(Lista *head, int x);

int main() {
    Lista l=NULL;
    inserisci_incoda(&l, 5);
    inserisci_incoda(&l, 6);
    inserisci_incoda(&l, 7);
    stampa(l);
}
void inserisci_incoda(Lista *head, int x)
    {
        if(*head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                (*head)=new;
                new->x=x;
                new->next=NULL;
                return;
            }
    inserisci_incoda(&(*head)->next, x);
    }
void stampa(Lista l)
    {
        while(l!=NULL)
            {
                printf("%d-->", l->x);
                l=l->next;
            }
    }
