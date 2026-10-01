//
//  main.c
//  void in coda ** 3mz
//
//  Created by Francesco Roscio Ricon on 03/03/26.
//

#include <stdio.h>
#include <stdlib.h>
typedef struct EL{
    int x;
    struct EL *next;
}Elem;

void inserisci_in_coda(Elem **head, int x);
void stampa(Elem *l);
int main() {
    Elem *l=NULL;
    inserisci_in_coda(&l, 5);
    inserisci_in_coda(&l, 6);
    inserisci_in_coda(&l, 7);
    stampa(l);
}
void stampa(Elem *l)
    {
        if(l==NULL)
            return;
        while(l!=NULL)
            {
                printf("%d-->", l->x);
                l=l->next;
            }
    }
void inserisci_in_coda(Elem **head, int x)
    {
        if(*head==NULL)
            {
                Elem *new=malloc(sizeof(Elem));
                new->next=NULL;
                new->x=x;
                (*head)=new;
                return;
            }
    inserisci_in_coda(&(*head)->next, x);
    }
