//
//  main.c
//  lista_bubble 6mz
//
//  Created by Francesco Roscio Ricon on 06/03/26.
//

#include <stdio.h>
#include <stdlib.h>
typedef struct EL{
    int x;
    struct EL *next;
}Nodo;
typedef Nodo *Lista;
Lista inserisci_in_coda(Lista head, int x);
Lista ordina(Lista head);
void stampa(Lista head);
int main() {
    Lista new=NULL;
    new=inserisci_in_coda(new, 2);
    new=inserisci_in_coda(new, 5);
    new=inserisci_in_coda(new, 1);
    new=inserisci_in_coda(new, 4);
    new=inserisci_in_coda(new, 3);
    stampa(new);
    new=ordina(new);
    printf("\n");
    stampa(new);
}
Lista inserisci_in_coda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->x=x;
                new->next=NULL;
                return new;
            }
    head->next=inserisci_in_coda(head->next, x);
    return head;
    }
Lista ordina(Lista head)
    {
    Lista t=head;
    Lista t1=head;
    int num=0;
    while(t1!=NULL)
    {
        head=t;
        num=0;
        while(head!=NULL && head->next!=NULL)
        {
            if(head->x>head->next->x)
            {
                int temp=head->next->x;
                head->next->x=head->x;
                head->x=temp;
                num++;
            }
            head=head->next;
        }
        if(num==0)
            break;
        t1=t1->next;
    }
    return t;
    }
void stampa(Lista head)
    {
        while(head!=NULL)
            {
                printf("%d-->", head->x);
                head=head->next;
            }
    }
