//
//  main.c
//  es8 6mz
//
//  Created by Francesco Roscio Ricon on 06/03/26.
//

#include <stdio.h>

int main() {

}
//Esercizio 4 — Campionato sportivo (lista + matrice)
//Un campionato è rappresentato da una lista di squadre.
//Ogni squadra contiene:
//nome
//una matrice 11x38 di prestazioni giocatori × partite
//Ogni cella è:

#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int gol;
    int minuti;
} Prestazione;
typedef struct S{
    char nome[50];
    Prestazione stat[11][38];
    struct S *next;
} Squadra;
typedef Squadra *ListaSquadre;
int ver(Squadra S)
    {
    int count=0;
    for(int r=0; r<11; r++)
        {
            for(int c=0; c<38; c++)
                {
                    count=count+S.stat[r][c].gol;
                }
        }
    if(count>=50)
        return 1;
    return 0;
    }
ListaSquadre inserisci_in_coda(ListaSquadre head, Squadra x)
    {
        if(head==NULL)
            {
                ListaSquadre new=(ListaSquadre)malloc(sizeof(*new));
                *new=x;
                new->next=NULL;
                return new;
            }
    head->next=inserisci_in_coda(head->next, x);
    return head;
    }
ListaSquadre f(ListaSquadre head)
    {
        if(head==NULL)
            return NULL;
        ListaSquadre new=NULL;
        while(head!=NULL)
            {
                if(ver(*head))
                    {
                        new=inserisci_in_coda(new, *head);
                    }
                head=head->next;
            }
    return new;
    }
