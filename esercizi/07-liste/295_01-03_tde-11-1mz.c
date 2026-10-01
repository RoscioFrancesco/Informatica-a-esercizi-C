//
//  main.c
//  tde 11 1mz
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct n {
int info;
struct n *next;
} nodo;

typedef  nodo * Lista;

typedef struct li {
Lista lis;
struct li *next;
} lisNodo;

typedef  lisNodo * ListaDiListe;
ListaDiListe inseriscincodaLDL(ListaDiListe head, Lista mia, int k);
Lista inseriscincoda(Lista head, int x);
ListaDiListe f(Lista head, int k);
void stampa(ListaDiListe head);
int main()
    {
    ListaDiListe new=NULL;
    Lista L=NULL;
    L=inseriscincoda(L, 3);
    L=inseriscincoda(L, 7);
    L=inseriscincoda(L, 1);
    L=inseriscincoda(L, 4);
    L=inseriscincoda(L, 2);
    L=inseriscincoda(L, 8);
    L=inseriscincoda(L, 4);
    L=inseriscincoda(L, 3);
    L=inseriscincoda(L, 2);
    int k=10;
    new=f(L, k);
    stampa(new);
    }

Lista inseriscincoda(Lista head, int x)
    {
    if(head==NULL)
        {
            Lista new=(Lista)malloc(sizeof(*new));
            new->next=NULL;
            new->info=x;
            return new;
        }
    head->next=inseriscincoda(head->next, x);
    return head;
    }
Lista inserisciK(Lista head, int k)
    {
    Lista new=NULL;
    for(int i=0; i<k && head!=NULL; i++)
        {
            new=inseriscincoda(new, head->info);
            head=head->next;
        }
    return new;
    }
int blocco(Lista head, int K)
    {
    int somma=0;
    int count=0;
    while(head!=NULL)
        {
            somma=somma+head->info;
            if(somma>K)
                break;
            count++;
            head=head->next;
        }
    return count;
    }
ListaDiListe inseriscincodaLDL(ListaDiListe head, Lista mia, int k)
    {
        if(head==NULL)
            {
                ListaDiListe new=(malloc(sizeof(lisNodo)));
                new->next=NULL;
                new->lis=inserisciK(mia, k);
                return new;
            }
    head->next=inseriscincodaLDL(head->next, mia, k);
    return head;
    }
ListaDiListe f(Lista head, int k)
    {
        if(head==NULL)
            return NULL;
        ListaDiListe new=NULL;
        Lista scorri=head;
        while(scorri!=NULL)
            {
                int q=blocco(scorri, k);
                printf("\n%d", q);
                new=inseriscincodaLDL(new, scorri, q);
                for(int i=0; i<q && scorri!=NULL; i++)
                    {
                        scorri=scorri->next;
                    }
            }
    return new;
    }
void stampa(ListaDiListe head)
    {
        while(head!=NULL)
            {
                Lista punt=head->lis;
                printf("\n");
                while(punt!=NULL)
                    {
                        printf("%d-->", punt->info);
                        punt=punt->next;
                    }
                head=head->next;
            }
    }
