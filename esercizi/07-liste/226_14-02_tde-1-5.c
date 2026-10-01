//
//  main.c
//  tde 1 -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//
#include <stdio.h>
#include <stdlib.h>


typedef struct nodo {
    int dato;
    struct nodo *next;
} Nodo;


typedef Nodo* Lista;


Lista costruisciA();
Lista costruisciB();
Lista costruisciC();
Lista costruisciD();
Lista costruisciE();
Lista costruisciF();
Lista IIT(Lista l,int e);
Lista FL(int v[],int l);
void stampaLista(Lista lista);

Lista mischia(Lista l1, Lista l2);
int main() {
    Lista ris;
    Lista LA = costruisciA();
    Lista LB = costruisciB();
    Lista LC = costruisciC();
    Lista LD = costruisciD();
    Lista LE = costruisciE();
    Lista LF = costruisciF();
    printf("LA:");stampaLista(LA);
    printf("LB:");stampaLista(LB);
    printf("LC:");stampaLista(LC);
    printf("LD:");stampaLista(LD);
    printf("LE:");stampaLista(LE);
    printf("LF:");stampaLista(LF);
    
    Lista AB=mischia(LA, LB);
    stampaLista(AB);


    return 0;
}
//INSERIRE QUI LE PROPRIE FUNZIONI


Lista costruisciA(){int v[]={2,4,7,21,9,11};return FL(v,6);}
Lista costruisciB(){int v[]={5,1,3,4,12,6};return FL(v,6);}
Lista costruisciC(){int v[]={23,11,8,12,7,11,4,100,6};return FL(v,9);}
Lista costruisciD(){int v[]={22,8,89,10,4,12};return FL(v,6);}
Lista costruisciE(){int v[]={23,8,4,12,7,11,4,100,6};return FL(v,9);}
Lista costruisciF(){int v[]={22,8,89,10,4,12};return FL(v,6);}
Lista IIT(Lista l,int e){Lista p=(Lista)malloc(sizeof(Nodo));p->dato=e;p->next=l;return p;}
Lista FL(int v[],int l){Lista lis=NULL;for(l=l-1;l>=0;l--)lis=IIT(lis,v[l]);return lis;}


void stampaLista(Lista lis) {
    while(lis!=NULL) {
        printf("%d->",lis->dato);
        lis=lis->next;
    }
    printf("---|\n");
}


int verifica(Lista l1, Lista l2)
    {
        if(l1==NULL || l2==NULL)
            return 0;
    int count=0;
        while(l1!=NULL && l2!=NULL)
            {
                if(l1->dato==l2->dato)
                    count++;
                l2=l2->next;
                l1=l1->next;
            }
    return count;
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
Lista mischia(Lista l1, Lista l2)
    {
        if(verifica(l1, l2)>0)
            return NULL;
    Lista scorril1=l1;
    Lista scorril2=l2;
    Lista new=NULL;
    while (scorril1!=NULL && scorril2!=NULL) {
        if(scorril1->dato<scorril2->dato)
            {
                new=inserisciincoda(new, scorril1->dato);
            }
        else
            {
                new=inserisciincoda(new, scorril2->dato);
            }
        scorril1=scorril1->next;
        scorril2=scorril2->next;
    }
    return new;
    }
