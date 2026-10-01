//
//  main.c
//  es 7 8mz
//
//  Created by Francesco Roscio Ricon on 08/03/26.
//


#include <stdio.h>
#include <stdlib.h>
typedef struct EL{
    int x;
    struct EL *next;
}Nodo;
typedef Nodo *Lista;
void stampa(Lista head);
Lista inseriscincoda(Lista head, int x);
Lista f(Lista head);
void funz(Lista *l);
int main() {
    Lista new=NULL;
    new=inseriscincoda(new, 1);
    new=inseriscincoda(new, 40);
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 15);
    new=inseriscincoda(new, 5);
    new=inseriscincoda(new, 6);
    funz(&new);
    stampa(new);
}
Lista inseriscincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->x=x;
                new->next=NULL;
                return new;
            }
    head->next=inseriscincoda(head->next, x);
    return head;
    }
int somma(Lista head)
    {
        if(head==NULL || head->next==NULL)
            return 0;
        head=head->next;
        int sum=0;
        while(head!=NULL)
            {
                sum=sum+head->x;
                head=head->next;
            }
    return sum;
    }
void funz(Lista *l)
    {
        if(*l==NULL)
            {
                return;
            }
        Lista *pp=l;
        while((*pp)->next!=NULL)
            {
                int sum=somma(*pp);
                if((*pp)->x>sum)
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
            return;
        while(head!=NULL)
            {
                printf("%d-->", head->x);
                head=head->next;
            }
    }
