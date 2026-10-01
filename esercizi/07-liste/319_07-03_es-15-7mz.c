//  Created by Francesco Roscio Ricon on 07/03/26.
#include <stdio.h>
#include <stdlib.h>
typedef struct G{
    char nome[50];
    int numero;
    struct G *next;
}Giocatore;
typedef Giocatore* ListaGiocatori;

typedef struct S{
    char nome[50];
    int punti[10][5];
    ListaGiocatori giocatori;
    struct S *next;
}Squadra;
typedef Squadra* ListaSquadre;
int almeno10(Squadra x, int c);
int main() {

}
ListaGiocatori inseriscincoda(ListaGiocatori head, Giocatore x)
    {
        if(head==NULL)
            {
                ListaGiocatori new=(ListaGiocatori)malloc(sizeof(*new));
                *new=x;
                new->next=NULL;
                return new;
            }
    head->next=inseriscincoda(head->next, x);
    return head;
    }
ListaGiocatori copiaLista(ListaGiocatori head, Squadra x)
    {
    ListaGiocatori new=NULL;
    int count=0;
    while(head!=NULL)
        {
            if(almeno10(x, count))
            {
                new=inseriscincoda(new, *head);
            }
            count++;
            head=head->next;
        }
    return new;
    }
ListaSquadre inserisciincoda(ListaSquadre head, Squadra x)
    {
        if(head==NULL)
            {
                ListaSquadre new=(ListaSquadre)malloc(sizeof(*new));
                *new=x;
                new->giocatori=copiaLista(x.giocatori, x);
                new->next=NULL;
                return new;
            }
    head->next=inserisciincoda(head->next, x);
    return head;
    }
int ver(Squadra x)
    {
    int count=0;
    for(int c=0; c<5; c++)
        {
            int somma=0;
            for(int r=0; r<10; r++)
                {
                    somma=somma+x.punti[r][c];
                }
            if(somma>50)
                count++;
        }
    if(count>=3)
        return 1;
    return 0;
    }
ListaSquadre squadreForti(ListaSquadre L)
    {
        if(L==NULL)
            return NULL;
    ListaSquadre new=NULL;
        while(L!=NULL)
            {
                if(ver(*L))
                    {
                        new=inserisciincoda(new, *L);
                    }
                L=L->next;
            }
    return new;
    }
int almeno10(Squadra x, int c)
{
        int somma=0;
    for(int r=0; r<10; r++)
        {
            somma=somma+x.punti[r][c];
        }
    if(somma>=10)
        return 1;
    return 0;
    }
