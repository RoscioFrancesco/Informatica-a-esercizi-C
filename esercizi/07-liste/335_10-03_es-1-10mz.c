//
//  main.c
//  es 1 10mz
//
//  Created by Francesco Roscio Ricon on 10/03/26.
//

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
typedef Vagone * L_mia;


Lista inseriscincoda(Lista head, int x);
void distruggi(L_mia head);
void stampa(L_mia head);
L_mia f(Lista head, int k);

int main() {
    Lista new=NULL;
    new=inseriscincoda(new, 9);
    new=inseriscincoda(new, 1);
    new=inseriscincoda(new, 2);
    new=inseriscincoda(new, 1);
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 5);
    new=inseriscincoda(new, 6);
    new=inseriscincoda(new, 7);
    new=inseriscincoda(new, 7);
    new=inseriscincoda(new, 9);
    new=inseriscincoda(new, 9);
    new=inseriscincoda(new, 9);
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 1);
    L_mia head=f(new, 20);
    stampa(head);
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
L_mia inseriscidietromia(L_mia head, int x ,int occ)
    {
        if(head==NULL || head->occ<occ)
            {
                L_mia new=(L_mia)malloc(sizeof(*new));
                new->x=x;
                new->occ=occ;
                new->next=head;
                return new;
            }
    head->next=inseriscidietromia(head->next, x, occ);
    return head;
    }
L_mia trova(L_mia head, int x)
    {
        while(head!=NULL)
            {
                if(head->x==x)
                    return head;
                head=head->next;
            }
    return NULL;
    }

int conta(Lista head, int x)
    {
        if(head==NULL)
            return 0;
    int count=0;
        while(head!=NULL)
            {
                if(head->x==x)
                    count++;
                head=head->next;
            }
    return count;
    }
L_mia f(Lista head, int k)
    {
    L_mia new=NULL;
    Lista scorri=head;
    while(scorri!=NULL)
        {
            L_mia punt=trova(new, scorri->x);
            int num=conta(head, scorri->x);
            if(punt==NULL)
                {
                    new=inseriscidietromia(new, scorri->x, num);
                }
            scorri=scorri->next;
        }
    L_mia temp=new;
    L_mia finale=NULL;
    for(int i=0; i<k && new!=NULL; i++)
        {
            finale=inseriscidietromia(finale, new->x, new->occ);
            new=new->next;
        }
    distruggi(temp);
    return finale;
    }
void distruggi(L_mia head)
    {
        if(head==NULL)
            return;
    L_mia temp=head->next;
    free(head);
    head=temp;
    distruggi(head);
    }
void stampa(L_mia head)
    {
        if(head==NULL)
            return;
        while(head!=NULL)
            {
                printf("(valore: %d,occ: %d)\n", head->x, head->occ);
                head=head->next;
            }
    }
