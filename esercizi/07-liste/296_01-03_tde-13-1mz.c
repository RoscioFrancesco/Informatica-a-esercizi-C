//
//  main.c
//  tde 13 1mz
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
typedef struct Date { int giorno; int mese; int anno; } Data;

typedef struct { char cognome[N], nome[N];
                 int eta; /* età della persona */ } Persona;

typedef struct Item { Persona p;
    int punti;
    struct Item * next;
} Socio;

typedef Socio * ListaDiSoci;

typedef struct Node { Data d;
                      Persona * ordineDiArrivo; /* la lista contiene i
                                                concorrenti in ordine
                                                di arrivo al traguardo */ // è una lista? + un array? cosa è???
                      struct Node * next; } Maratona;

typedef Maratona * ListaDiMaratone;

ListaDiSoci aggiungipunti(ListaDiSoci head, int p_da_aggiungere, Persona P)
    {
    if(head==NULL)
        return head;
    ListaDiSoci scorri=head;
    while(head!=NULL)
        {
            if(strcmp(head->p.cognome,P.cognome)==0 && strcmp(head->p.nome, P.nome)==0)
                {
                    head->punti=head->punti+p_da_aggiungere;
                    return scorri;
                }
            head=head->next;
        }
    return scorri;
    }
ListaDiSoci f(ListaDiMaratone head, ListaDiSoci soci)
    {
    ListaDiMaratone scorri_maratone=head;
    while(scorri_maratone!=NULL)
        {
            Persona * arrivo=scorri_maratone->ordineDiArrivo;
            int j=10;
            for(int i=0; i<10; i++)
                {
                    soci=aggiungipunti(soci, j-i, *arrivo);
                    arrivo++;
                }
            scorri_maratone=scorri_maratone->next;
        }
        return soci;
    }
