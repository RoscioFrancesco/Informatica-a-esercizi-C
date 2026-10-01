//
//  main.c
//  es 18 7mz
//
//  Created by Francesco Roscio Ricon on 07/03/26.
//
//ListaListe split(Lista L, int k);
//che divide la lista L in sottoliste di lunghezza k.
//Esempio:
//Input
//1 2 3 4 5 6 7
//k=3
//Output
//(1 2 3) (4 5 6) (7)
//⚠️ non modificare la lista originale.

#include <stdio.h>
#include <stdlib.h>
typedef struct N{
    int x;
    struct N *next;
}Nodo;

typedef Nodo* Lista;

typedef struct LL{
    Lista l;
    struct LL *next;
}NodoLL;

typedef NodoLL* ListaListe;
Lista inseriscincoda(Lista head, int x);
void stampaLDL(ListaListe head);
ListaListe f(Lista head, int k);
int main() {
    Lista new=NULL;
    new=inseriscincoda(new, 1);
    new=inseriscincoda(new, 2);
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 4);
    new=inseriscincoda(new, 5);
    new=inseriscincoda(new, 6);
    new=inseriscincoda(new, 7);
    ListaListe head=NULL;
    head=f(new, 3);
    stampaLDL(head);
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
Lista copiak(Lista head, int k)
    {
    Lista new=NULL;
    for(int i=0; i<k && head!=NULL; i++)
        {
            new=inseriscincoda(new, head->x);
            head=head->next;
        }
    return new;
    }
ListaListe inseriscincodaLDL(ListaListe head, int k ,Lista lis)
    {
        if(head==NULL)
            {
                ListaListe new=(ListaListe)malloc(sizeof(*new));
                new->next=NULL;
                new->l=copiak(lis, k);
                return new;
            }
    head->next=inseriscincodaLDL(head->next, k, lis);
    return head;
    }
ListaListe f(Lista head, int k)
    {
        if(head==NULL)
            return NULL;
    ListaListe new=NULL;
        while(head!=NULL)
            {
                new=inseriscincodaLDL(new, k, head);
                for(int i=0; i<k && head!=NULL; i++)
                    {
                        head=head->next;
                    }
            }
    return new;
    }
void stampaLDL(ListaListe head)
    {
        while(head!=NULL)
            {
                printf("\n");
                Lista punt=head->l;
                while(punt!=NULL)
                    {
                        printf("%d", punt->x);
                        punt=punt->next;
                    }
                head=head->next;
            }
    }
