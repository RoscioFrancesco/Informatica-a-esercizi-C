//
//  main.c
//  tde gen liste 2
//
//  Created by Francesco Roscio Ricon on 25/01/26.
//  Riferimento: Informatica A (061202), TDE gennaio 2026, a.a. 2025/26: https://forms.cloud.microsoft/e/U1bBujvcBe

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
int min(int a, int b);
Lista inserisciincoda(Lista head, int val);


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
    printf("\n");
    Lista newAB=mischia(LA, LB);
    Lista newBC=mischia(LB, LC);
    Lista newCD=mischia(LC, LD);
    Lista newEF=mischia(LE, LF);
    printf("AB:");stampaLista(newAB);
    printf("BC:");stampaLista(newBC);
    printf("CD:");stampaLista(newCD);
    printf("EF:");stampaLista(newEF);

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
    int somma=0;
    if(l1==NULL || l2==NULL)
        return 0;
    Lista scorril1=l1;
    Lista scorril2=l2;
    while(scorril1!=NULL && scorril2!=NULL)
        {
            if(scorril1->dato==scorril2->dato)
                somma++;
            scorril1=scorril1->next;
            scorril2=scorril2->next;
        }
    return somma;
    }


Lista mischia(Lista l1, Lista l2)
    {
    Lista scorril1=l1;
    Lista scorril2=l2;
        if(verifica(l1, l2)>0)
            return NULL;
    Lista head=NULL;
        while(scorril1!=NULL && scorril2!=NULL)
            {
                head=inserisciincoda(head, min(scorril1->dato,scorril2->dato));
                scorril1=scorril1->next;
                scorril2=scorril2->next;
            }
        return head;
    }
Lista inserisciincoda(Lista head, int val)
    {
    Lista new=(Lista)malloc(sizeof(Nodo));
    new->next=NULL;
    new->dato=val;
    Lista scorrilista=head;
    if(head==NULL) return new;
    while(scorrilista->next!=NULL)scorrilista=scorrilista->next;
    scorrilista->next=new;
    return head;
    }
int min(int a, int b)
    {
    if(b<a)
        return b;
    return a;
}
