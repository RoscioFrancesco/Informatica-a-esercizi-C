//
//  main.c
//  eliminaz con punt 3mz
//
//  Created by Francesco Roscio Ricon on 03/03/26.
// elimina tutti i blocchi di elementi pari

#include <stdio.h>
#include <stdlib.h>

typedef struct EL{
    int num;
    struct EL *next;
}Nodo;
typedef Nodo* Lista;


void elimina(Lista *l);
Lista inseriscincoda(Lista head ,int x);
int blocco(Lista head);
void stampa(Lista l);
Lista eliminaK(Lista head, int k);
int main() {
    Lista l=NULL;
    l=inseriscincoda(l, 2);
    l=inseriscincoda(l, 2);
    l=inseriscincoda(l, 3);
    l=inseriscincoda(l, 4);
    l=inseriscincoda(l, 5);
    elimina(&l);
    stampa(l);
}
Lista inseriscincoda(Lista head ,int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->num=x;
                new->next=NULL;
                return new;
            }
    head->next=inseriscincoda(head->next, x);
    return head;
    }
void elimina(Lista *l)
    {
        if(*l==NULL)
            return;
        Lista *pp=l;
        while(*pp!=NULL)
            {
                int num=blocco(*pp);
                if(num>0)
                    {
                        (*pp)=eliminaK((*pp), num);
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
void stampa(Lista l)
    {
        if(l==NULL)
            return;
        while(l!=NULL)
            {
                printf("%d-->", l->num);
                l=l->next;
            }
    }
int blocco(Lista head)
    {
        if(head==NULL)
            return 0;
        int count=0;
        while(head!=NULL)
            {
                if(head->num%2==1)
                    break;
                count++;
                head=head->next;
            }
    return count;
    }
Lista eliminaK(Lista head, int k)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<k && head!=NULL; i++)
        {
            Lista temp=head->next;
            free(head);
            head=temp;
        }
        return head;
    }
