//  Created by Francesco Roscio Ricon on 19/01/26.

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
}Vagone;
typedef Vagone* LdL;

Lista inserisci_in_coda(Lista head, int val);
Lista costruisci();
Lista IIT(Lista l,int e);
Lista FL(int v[],int l);
void stampaLista(Lista lista);
LdL costruisci_lista_di_liste(LdL listadiliste, int val, int s1, int s2);
LdL dividiListe (Lista inizio, int s1, int s2);
Lista inserisci_in_coda(Lista head, int val);
void stampa_lista_di_liste(LdL lista_di_liste);

int main() {
    int s1=10,s2=21;
    Lista Lis = costruisci();
    stampaLista(Lis);
    LdL mia=NULL;
    mia=dividiListe(Lis, s1, s2);
    stampa_lista_di_liste(mia);
    


    return 0;
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

LdL dividiListe (Lista inizio, int s1, int s2)
    {
    Lista scorrilista=inizio;
    LdL lista_di_liste=NULL;
    while(scorrilista!=NULL)
        {
            lista_di_liste=costruisci_lista_di_liste(lista_di_liste, scorrilista->dato, s1, s2);
            scorrilista=scorrilista->next;
        }
    return lista_di_liste;
    }
LdL costruisci_lista_di_liste(LdL listadiliste, int val, int s1, int s2)
    {
        if(val<s1)
            {
               if(listadiliste==NULL)
                {
                    LdL new=(LdL)malloc(sizeof(Vagone));
                    new->next=NULL;
                    new->head=NULL;
                    new->head=inserisci_in_coda(new->head, val);
                    return new;
                }
               else
                {
                    listadiliste->head=inserisci_in_coda(listadiliste->head, val);
                    return listadiliste;
                }
            }
        if(val>=s1 && val<=s2)
            {
                if (listadiliste == NULL) {
                        listadiliste = (LdL)malloc(sizeof(Vagone));
                        listadiliste->head = NULL;
                        listadiliste->next = NULL;
                    }
                LdL secondo=listadiliste->next;
                if(secondo==NULL)
                    {
                        LdL new=(LdL)malloc(sizeof(Vagone));
                        new->next=NULL;
                        new->head=NULL;
                        new->head=inserisci_in_coda(new->head, val);
                        listadiliste->next=new;
                    }
                else
                    {
                        secondo->head=inserisci_in_coda(secondo->head, val);
                        return listadiliste;
                    }
            }
        if(val>s2)
            {
                if (listadiliste == NULL) {
                        listadiliste = (LdL)malloc(sizeof(Vagone));
                        listadiliste->head = NULL;
                        listadiliste->next = NULL;
                    }
                if (listadiliste->next == NULL) {
                        listadiliste->next = (LdL)malloc(sizeof(Vagone));
                        listadiliste->next->head = NULL;
                        listadiliste->next->next = NULL;
                    }
                
                if(listadiliste->next->next==NULL)
                    {
                        LdL new=(LdL)malloc(sizeof(Vagone));
                        new->next=NULL;
                        new->head=NULL;
                        new->head=inserisci_in_coda(new->head, val);
                        listadiliste->next->next=new;
                    }
                else
                {
                        LdL terzo=listadiliste->next->next;
                        terzo->head=inserisci_in_coda(terzo->head, val);
                        return listadiliste;
                    }
            }
    return listadiliste;
    }
Lista inserisci_in_coda(Lista head, int val)
    {
        Lista new=(Lista)malloc(sizeof(Nodo));
        new->dato=val;
        new->next=NULL;
        if(head==NULL)
            return new;
    Lista scorri=head;
    while(scorri->next!=NULL)
        {
            scorri=scorri->next;
        }
    scorri->next=new;
    return head;
    }


void stampa_lista_di_liste(LdL lista_di_liste)
    {
        while(lista_di_liste!=NULL)
            {
                while(lista_di_liste->head!=NULL)
                    {
                        printf("%d-->",lista_di_liste->head->dato);
                        lista_di_liste->head=lista_di_liste->head->next;
                    }
                printf("\n");
                lista_di_liste=lista_di_liste->next;
            }
    }
// figa tosto
