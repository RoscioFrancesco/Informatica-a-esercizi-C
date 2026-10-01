//
//  main.c
//  tde liste 2024 gen
//
//  Created by Francesco Roscio Ricon on 30/11/25.
//
// Riferimento: Informatica A (061202), TDE gennaio 2024, a.a. 2023/24: https://forms.office.com/e/REVRfR3pbc
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
int verifica(Lista lis1, Lista lis2);

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


    //INSERIRE QUI INVOCAZIONI DI FUNZIONE E STAMPE


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

int verifica(Lista lis1, Lista lis2)
{
    int contatore=0;
        if(lis1==NULL && lis2==NULL)
            return 0;
        while(lis1!=NULL && lis2!=NULL)
            {
                if(lis1->dato==lis2->dato)
                    contatore++;
                lis1=lis1->next;
                lis2=lis2->next;
            }
    return contatore;
}
Lista mischia(Lista lis1, Lista lis2)
{
    int ris = verifica(lis1, lis2);
    if (ris > 0)
        return NULL;

    Lista head = NULL;
    Lista tail = NULL;

    while (lis1 != NULL && lis2 != NULL)
    {
        Lista nuovo = malloc(sizeof(Nodo));
        if (lis1->dato < lis2->dato)
            nuovo->dato = lis1->dato;
        else
            nuovo->dato = lis2->dato;

        nuovo->next = NULL;

        if (head == NULL) {   // primo nodo
            head = nuovo;
            tail = nuovo;
        } else {
            tail->next = nuovo;
            tail = nuovo;
        }

        lis1 = lis1->next;
        lis2 = lis2->next;
    }
    return head;
}
