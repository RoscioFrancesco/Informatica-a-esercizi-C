//
//  main.c
//  tde 2 liste -1
//
//  Created by Francesco Roscio Ricon on 18/02/26.
//

#include <stdio.h>
#include <stdlib.h>
typedef struct nodo {
    int dato;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

typedef struct EL{
    Lista L;
    struct EL* next;
}Vagone;
typedef Vagone* lDl;

Lista costruisci();
Lista IIT(Lista l,int e);
Lista FL(int v[],int l);
void stampaLista(Lista lista);
Lista inseriscincoda(Lista head, int x);
lDl inizializza(lDl primo);
void stampa(lDl head);
lDl f(Lista head, int s1, int s2);
lDl pulisci(lDl head);
int main() {
    int s1=10,s2=20;
    Lista Lis = costruisci();
    stampaLista(Lis);
    
    lDl new=f(Lis, s1, s2);
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


Lista inseriscincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=NULL;
                new->dato=x;
                return new;
            }
        head->next=inseriscincoda(head->next, x);
        return head;
    }
lDl inserisciLDL(lDl head, int x)
    {
        if(head==NULL)
            {
                lDl new=malloc(sizeof(*new));
                new->next=NULL;
                new->L=inseriscincoda(new->L, x);
                return new;
            }
    head->next=inserisciLDL(head->next, x);
    return head;
    }
lDl f(Lista head, int s1, int s2)
    {
        if(head==NULL)
            return NULL;
        lDl primo=NULL;
        primo=inizializza(primo);
        while(head!=NULL)
            {
                if(head->dato<s1)
                    {
                        primo->L=inseriscincoda(primo->L, head->dato);
                    }
                if(head->dato>s2)
                    {
                        primo->next->next->L=inseriscincoda(primo->next->next->L, head->dato);
                    }
                if(head->dato>=s1 && head->dato<=s2)
                    {
                        primo->next->L=inseriscincoda(primo->next->L, head->dato);
                    }
                head=head->next;
            }
    primo=pulisci(primo);
    return primo;
    }
lDl inizializza(lDl primo)
    {
    for(int i=0; i<3; i++)
        {
            primo=inserisciLDL(primo, 0);
        }
    return primo;
    }
void stampa(lDl head)
    {
    if(head==NULL) return;
    while(head!=NULL)
        {
            Lista punt=head->L;
            printf("\n");
            while(punt!=NULL)
                {
                    printf("%d-->", punt->dato);
                    punt=punt->next;
                }
            head=head->next;
        }
    printf("\n");
    }
lDl pulisci(lDl head)
    {
    lDl scorri=head;
        while(scorri!=NULL)
            {
                Lista punt=scorri->L;
                Lista temp=punt->next;
                free(punt);
                scorri->L=temp;
                scorri=scorri->next;
            }
        return head;
    }
