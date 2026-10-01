//
//  main.c
//  es 1 9mz
//
//  Created by Francesco Roscio Ricon on 09/03/26.
//  fare il fold di una lista

#include <stdio.h>
#include <stdlib.h>

typedef struct EL{
    int x;
    struct EL *next;
}Nodo;
typedef Nodo *Lista;

Lista inverti(Lista head);
Lista inseriscincoda(Lista head, int x);
int len(Lista head);
Lista f(Lista head);
void stampa(Lista head);
int main() {
    Lista new=NULL;
    new=inseriscincoda(new, 1);
    new=inseriscincoda(new, 2);
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 4);
    new=inseriscincoda(new, 5);
    new=inseriscincoda(new, 6);
    Lista fin=f(new);
    stampa(fin);
}

Lista inseriscincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=malloc(sizeof(*new));
                new->x=x;
                new->next=NULL;
                return new;
            }
    head->next=inseriscincoda(head->next, x);
    return head;
    }
Lista inverti(Lista head)
    {
        if(head==NULL || head->next==NULL)
            {
                return head;
            }
    Lista temp=inverti(head->next);
    head->next->next=head;
    head->next=NULL;
    return temp;
    }
Lista copia(Lista head)
    {
    Lista new=NULL;
    while(head!=NULL)
        {
            new=inseriscincoda(new, head->x);
            head=head->next;
        }
    return new;
    }
int len(Lista head)
    {
    int count=0;
    while(head!=NULL)
        {
            count++;
            head=head->next;
        }
    return count;
    }
Lista f(Lista head)
    {
    int l=len(head);
    Lista c=copia(head);
    c=inverti(c);
    Lista new=NULL;
    Lista temp1=head;
    Lista temp2=c;
    for(int i=0; i<l/2; i++)
        {
            new=inseriscincoda(new, head->x);
            head=head->next;
            new=inseriscincoda(new, c->x);
            c=c->next;
        }
    free(temp2);
    return new;
    }
void stampa(Lista head)
    {
        while(head!=NULL)
            {
                printf("%d-->", head->x);
                head=head->next;
            }
    }
