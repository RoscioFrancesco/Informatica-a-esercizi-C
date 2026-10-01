//  Created by Francesco Roscio Ricon on 01/03/26.

#include <stdio.h>
#include <stdlib.h>
typedef struct EL{
    int x;
    struct EL *next;
}Elem;
typedef Elem *Lista;

typedef struct ES{
    Lista head;
    struct ES *succ;
}Vagone;
typedef Vagone *LdL;
Lista inserisciincoda(Lista head, int x);
Lista copiaK(Lista head, int k);
LdL inseriscincoda(Lista scorri, int k, LdL head);
int blocco(Lista head);

void stampa(LdL head);
LdL f(Lista head);
int main()
    {
    Lista new=NULL;
    new=inserisciincoda(new, 3);
    new=inserisciincoda(new,4);
    new=inserisciincoda(new,4);
    new=inserisciincoda(new,2);
    new=inserisciincoda(new,7);
    new=inserisciincoda(new,9);
    new=inserisciincoda(new,1);
    new=inserisciincoda(new,1);
    new=inserisciincoda(new,5);
    LdL l=NULL;
    l=f(new);
    stampa(l);
}

Lista inserisciincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=malloc(sizeof(*new));
                new->next=NULL;
                new->x=x;
                return new;
            }
    head->next=inserisciincoda(head->next, x);
    return head;
    }
Lista copiaK(Lista head, int k)
    {
    Lista new=NULL;
    for(int i=0; i<k && head!=NULL; i++)
        {
            new=inserisciincoda(new, head->x);
            head=head->next;
        }
    return new;
    }
    
LdL inseriscincoda(Lista scorri, int k, LdL head)
    {
        if(head==NULL)
            {
                LdL new=malloc(sizeof(*new));
                new->head=copiaK(scorri, k);
                new->succ=NULL;
                return new;
            }
    head->succ=inseriscincoda(scorri, k, head->succ);
    return head;
    }
int blocco(Lista head)
    {
        if(head==NULL)
            return 0;
    int count=1;
    while(head!=NULL && head->next!=NULL)
        {
            if(head->next->x<head->x)
                break;
            count++;
            head=head->next;
        }
    return count;
    }
LdL f(Lista head)
    {
    Lista scorri=head;
    LdL new=NULL;
        while(scorri!=NULL)
            {
                int num=blocco(scorri);
                new=inseriscincoda(scorri, num, new);
                printf("\n%d", num);
                for(int i=0; i<num; i++)
                    {
                        scorri=scorri->next;
                    }
            }
    return new;
    }
void stampa(LdL head)
    {
        while(head!=NULL)
            {
                Lista punt=head->head;
                printf("\n");
                while(punt!=NULL)
                    {
                        printf("%d", punt->x);
                        punt=punt->next;
                    }
                head=head->succ;
            }
    }

