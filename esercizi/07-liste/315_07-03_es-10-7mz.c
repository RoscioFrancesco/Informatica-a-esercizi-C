//  Created by Francesco Roscio Ricon on 07/03/26.
#include <stdio.h>
#include <stdlib.h>
typedef struct EL{
    int x;
    struct EL *next;
}Nodo;
typedef Nodo *Lista;
Lista inserisci_in_coda(Lista head, int x);
void stampa(Lista head);
void eliminaPari(Lista *l);

int main() {
    Lista l=NULL;
    l=inserisci_in_coda(l, 1);
    l=inserisci_in_coda(l, 2);
    l=inserisci_in_coda(l, 3);
    l=inserisci_in_coda(l, 4);
    l=inserisci_in_coda(l, 5);
    l=inserisci_in_coda(l, 6);
    eliminaPari(&l);
    stampa(l);
}

Lista inserisci_in_coda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(Nodo));
                new->next=NULL;
                new->x=x;
                return new;
            }
    head->next=inserisci_in_coda(head->next, x);
    return head;
    }
void eliminaPari(Lista *l)
    {
    Lista *pp=l;
    while(*pp!=NULL)
        {
            if((*pp)->x%2==0)
                {
                    Lista temp=*pp;
                    (*pp)=(*pp)->next;
                    free(temp);
                }
            else
                {
                    pp=&(*pp)->next;
                }
        }
    }
void stampa(Lista head)
    {
        if(head==NULL)
        {return;
            }
        while(head!=NULL)
            {
                printf("%d", head->x);
                head=head->next;
            }
    }
