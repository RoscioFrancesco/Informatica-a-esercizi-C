//
//  main.c
//  tde 2 liste -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//
#include <stdio.h>
#include <stdlib.h>


typedef struct nodo {
    int dato;
    struct nodo *next;
} Nodo;


typedef Nodo* Lista;


typedef struct EL{
    Lista head;
    struct EL *next;
}vagone;
typedef vagone * ListaDiListe;

Lista costruisci();
Lista IIT(Lista l,int e);
Lista FL(int v[],int l);
void stampaLista(Lista lista);
ListaDiListe f(Lista head, int s1, int s2);
ListaDiListe inizializza();
void stampa(ListaDiListe t);
int main() {
    int s1=10,s2=20;
    Lista Lis = costruisci();
    stampaLista(Lis);
    ListaDiListe new=f(Lis, s1, s2);
    stampa(new);
}
//INSERIRE QUI LE PROPRIE FUNZIONI


Lista costruisci(){int v[]={2,4,7,21,9,11,5,1,3,4,
                             12,6,23,11,8,12,7,11,4,100,
                             6,22,8,89,10,4,12,22,8,89,
                             10,4,12,16,65,1,-8,-6,4,2};return FL(v,40);}
Lista IIT(Lista l,int e){Lista p=(Lista)malloc(sizeof(Nodo));p->dato=e;p->next=l;return p;}
Lista FL(int v[],int l){Lista lis=NULL;for(l=l-1;l>=0;l--)lis=IIT(lis,v[l]);return lis;}


void stampaLista(Lista lis) {
    while(lis!=NULL) {
        printf("%d->",lis->dato);
        lis=lis->next;
    }
    printf("---|\n");
}

Lista inserisciincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(Nodo));
                new->next=NULL;
                new->dato=x;
                return new;
            }
        head->next=inserisciincoda(head->next, x);
        return head;
    }
ListaDiListe inseriscincodaLDL(ListaDiListe head, int x)
    {
        if(head==NULL)
            {
                ListaDiListe new=(ListaDiListe)malloc(sizeof(vagone));
                new->head=inserisciincoda(new->head, x);
                new->next=NULL;
                return new;
            }
        head->next=inseriscincodaLDL(head->next, x);
        return head;
    }

ListaDiListe inizializza()
    {
    ListaDiListe new=NULL;
    for(int i=0; i<3; i++)
        {
            new=inseriscincodaLDL(new, 0);
        }
    return new;
    }
ListaDiListe f(Lista head, int s1, int s2)
    {
    ListaDiListe new=inizializza();
    Lista scorri=head;
    while (scorri!=NULL) {
        if(scorri->dato<s1)
            {
                new->head=inserisciincoda(new->head, scorri->dato);
            }
        if(scorri->dato<s2 && scorri->dato>s1)
            {
                new->next->head=inserisciincoda(new->next->head, scorri->dato);
            }
        if(scorri->dato>s2)
            {
                new->next->next->head=inserisciincoda(new->next->next->head, scorri->dato);
            }
        scorri=scorri->next;
    }
    ListaDiListe p=new;
    while(p!=NULL)
        {
            Lista singola=p->head;
            Lista temp=singola->next;
            free(singola);
            singola=temp;
            p->head=singola;
            p=p->next;
        }
    return new;
    }
void stampa(ListaDiListe t)
    {
        if(t==NULL)
            return;
    while (t!=NULL) {
        Lista punt=t->head;
        printf("\n");
        while(punt!=NULL)
            {
                printf("%d-->", punt->dato);
                punt=punt->next;
            }
        t=t->next;
    }
    }
