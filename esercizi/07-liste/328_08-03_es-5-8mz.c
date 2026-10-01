//  Created by Francesco Roscio Ricon on 08/03/26.


#include <stdio.h>
#include <stdlib.h>
typedef struct EL{
    int x;
    struct EL *next;
}Nodo;
typedef Nodo *Lista;

typedef struct C{
    int x;
    int occ;
    struct C *next;
}Vagone;
typedef Vagone *Treno;

void stampa(Treno head);
Lista inseriscincoda(Lista head, int x);
Treno f(Lista head);
int main() {
    Lista new=NULL;
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 2);
    new=inseriscincoda(new, 2);
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 5);
    new=inseriscincoda(new, 5);
    new=inseriscincoda(new, 5);
    Treno t=f(new);
    stampa(t);
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
int conta(Lista head, int x)
    {
    int count=0;
    while(head!=NULL)
        {
            if(head->x==x)
                count++;
            head=head->next;
        }
    return count;
    }
Treno inserimento_ord(Treno head, int x, int occ)
    {
        if(head==NULL || head->x>x)
            {
                Treno new=(Treno)malloc(sizeof(*new));
                new->x=x;
                new->occ=occ;
                new->next=head;
                return new;
            }
    head->next=inserimento_ord(head->next, x, occ);
    return head;
    }
int trova(Treno head, int x)
    {
    if(head==NULL)
        return 0;
        while(head!=NULL)
            {
                if(head->x==x)
                    return 1;
                head=head->next;
            }
    return 0;
    }


Treno f(Lista head)
    {
    Lista scorri=head;
    Treno new=NULL;
    while(scorri!=NULL)
        {
            int num=conta(head, scorri->x);
            if(trova(new, scorri->x)==0)
                {
                    new=inserimento_ord(new, scorri->x, num);
                }
            scorri=scorri->next;
        }
    return new;
    }
void stampa(Treno head)
    {
        if(head==NULL)
            return;
        while(head!=NULL)
            {
                printf("(%d,%d)", head->x, head->occ);
                head=head->next;
            }
    }
