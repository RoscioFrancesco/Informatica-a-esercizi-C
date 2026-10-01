//
//  main.c
//  es tde 7 27
//
//  Created by Francesco Roscio Ricon on 27/02/26.
//


#include <stdio.h>
#include <stdlib.h>

typedef struct EL{
    int num;
    int occ;
    struct EL* next;
}Elemento;
typedef Elemento *Lista;

Lista trova(Lista head, int num);
Lista inserisci_in_coda(Lista head, int x);
void lancia(int x);

int main()
    {
    lancia(8);
    }
Lista inserisci_in_coda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->occ=1;
                new->num=x;
                new->next=NULL;
                return new;
            }
    head->next=inserisci_in_coda(head->next, x);
    return head;
    }
Lista trova(Lista head, int num)
    {
        if(head==NULL)
            return NULL;
    Lista scorri=head;
    while(scorri!=NULL)
        {
            if(scorri->num==num)
                {
                    return scorri;
                }
            scorri=scorri->next;
        }
    return NULL;
    }

void lancia(int x)
    {
    Lista head=NULL;
    for(int i=0; i<x; i++)
        {
            int num=rand() % 6 + 1;   // valori 1..6
            Lista punt=trova(head, num);
            if(punt==NULL)
                {
                    head=inserisci_in_coda(head, num);
                }
            else
                {
                    (punt->occ)++;
                }
        }
    for(Lista i=head; i!=NULL; i=i->next)
        {
            for(Lista j=head->next; j!=NULL; j=j->next)
                {
                    if(i->occ>j->occ)
                        {
                            int temp_occ=i->occ;
                            int temp_num=i->num;
                            i->num=j->num;
                            i->occ=j->occ;
                            j->num=temp_num;
                            j->occ=temp_occ;
                        }
                }
        }
        while(head!=NULL)
            {
                printf("Il numero %d è uscito %d volte\n", head->num, head->occ);
                head=head->next;
            }
    }
