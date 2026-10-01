//  Created by Francesco Roscio Ricon on 07/03/26.


typedef struct P{
    char codice[20];
    int prezzo;
    struct P *next;
}Prodotto;
typedef Prodotto* ListaProdotti;

typedef struct M{
    char nome[50];
    int qta[6][6];
    ListaProdotti prodotti;
    struct M *next;
}Magazzino;
typedef Magazzino* ListaMagazzini;

#include <stdio.h>
#include <stdlib.h>
ListaProdotti inseriscincoda(ListaProdotti head, Prodotto x);
ListaProdotti copialista(ListaProdotti head, Magazzino x);
int main() {

}

ListaProdotti inseriscincoda(ListaProdotti head, Prodotto x)
    {
        if(head==NULL)
            {
                ListaProdotti new=(ListaProdotti)malloc(sizeof(*new));
                *new=x;
                new->next=NULL;
                return new;
            }
    head->next=inseriscincoda(head->next, x);
    return head;
    }
int ver(Magazzino x)
    {
    for(int r=0; r<6; r++)
        {
            int somma=0;
            for(int c=0; c<6; c++)
                {
                    somma=somma+x.qta[r][c];
                }
            if(somma>=100)
                return 1;
        }
    return 0;
    }
int ver_prod(int c, Magazzino x)
    {
    for(int r=0; r<6; r++)
        {
            if(x.qta[r][c]==0)
                return 1;
        }
    return 0;
    }
ListaProdotti copialista(ListaProdotti head, Magazzino x)
    {
        if(head==NULL)
            return NULL;
        int count=0;
        ListaProdotti new=NULL;
        while(head!=NULL)
            {
                if(ver_prod(count, x))
                    {
                        new=inseriscincoda(new, *head);
                    }
                count++;
                head=head->next;
            }
    return new;
    }
ListaMagazzini inseriscimagazzini(ListaMagazzini head, Magazzino x)
    {
        if(head==NULL)
            {
                ListaMagazzini new=(ListaMagazzini)malloc(sizeof(*new));
                *new=x;
                new->prodotti=copialista(x.prodotti, x);
                new->next=NULL;
                return new;
            }
    head->next=inseriscimagazzini(head->next, x);
    return head;
    }


ListaMagazzini magazziniCritici(ListaMagazzini L)
    {
        if(L==NULL)
            return NULL;
        ListaMagazzini new=NULL;
        while(L!=NULL)
            {
                if(ver(*L))
                    {
                        new=inseriscimagazzini(new, *L);
                    }
                L=L->next;
            }
    return new;
    }
