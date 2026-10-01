//
//  main.c
//  es 14 7mz
//
//  Created by Francesco Roscio Ricon on 07/03/26.
//

#include <stdio.h>



typedef struct C{
    int valore;
    int occorrenze;
    struct C *next;
}NodoC;
typedef NodoC* ListaC;

typedef struct EL{
    int x;
    struct EL *next;
}Nodo;
typedef Nodo *Lista;
#include <stdlib.h>
int trova(ListaC head, int x);
Lista inseriscincoda(Lista head, int x);
void stampa(ListaC head);
ListaC f(Lista head);
int main() {
    Lista l=NULL;
    l=inseriscincoda(l, 3);
    l=inseriscincoda(l, 3);
    l=inseriscincoda(l, 5);
    l=inseriscincoda(l, 3);
    l=inseriscincoda(l, 5);
    l=inseriscincoda(l, 5);
    l=inseriscincoda(l, 3);
    ListaC L=f(l);
    stampa(L);
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
int contaocc(Lista head, int x)
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
int trova(ListaC head, int x)
    {
        if(head==NULL)
            return 0;
        while(head!=NULL)
            {
                if(head->valore==x)
                    return 1;
                head=head->next;
            }
    return 0;
    }
ListaC inserimento_coda(ListaC head, int x, int occ)
    {
        if(head==NULL || occ>head->occorrenze)
            {
                ListaC new=(ListaC)malloc(sizeof(*new));
                new->occorrenze=occ;
                new->valore=x;
                new->next=head;
                return new;
            }
    head->next=inserimento_coda(head->next, x, occ);
    return head;
    }
ListaC f(Lista head)
    {
        if(head==NULL)
            return NULL;
    Lista scorri=head;
    ListaC new=NULL;
        while(scorri!=NULL)
            {
                if(trova(new, scorri->x)==0)
                    {
                        int num=contaocc(head, scorri->x);
                        new=inserimento_coda(new, scorri->x, num);
                    }
                scorri=scorri->next;
            }
    return new;
    }
void stampa(ListaC head)
    {
        if(head==NULL)
            return;
        while(head!=NULL)
            {
                printf("(occ:%d, val:%d)", head->occorrenze, head->valore);
                head=head->next;
            }
    }
