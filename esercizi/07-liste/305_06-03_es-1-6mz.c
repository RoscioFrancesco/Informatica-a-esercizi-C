//
//  main.c
//  es 1 6mz
//
//  Created by Francesco Roscio Ricon on 06/03/26.
//  Esercizio 1 — Reparti e pazienti critici

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct EL{
    char nome[100];
    int codice;
    int età;
    int gravità;
    int giorni_ricovero;
    struct EL *next;
}Paziente;
typedef Paziente *Lista_paz;

typedef struct ES{
    char nomeReparto[100];
    int piano;
    Lista_paz head;
    struct ES*next;
}Reparto;
typedef Reparto *Lista_reparti;
Lista_reparti incodareparti(Lista_reparti head, int soglia, Lista_reparti x);
int main() {
    
}
//ListaReparti estraiRepartiCritici(ListaReparti reparti, int soglia);

Lista_paz inseriscincoda(Lista_paz head, Paziente x)
    {
        if(head==NULL)
            {
                Lista_paz new=(Lista_paz)malloc(sizeof(*new));
                *new=x;
                new->next=NULL;
                return new;
            }
    head->next=inseriscincoda(head->next, x);
    return head;
    }
int ver(Lista_paz head, int soglia)
    {
        if(head==NULL)
            return 0;
    float count_giorni=0;
    int somma_giorni=0;
    int grav=0;
        while(head!=NULL)
            {
                if(head->codice>soglia)
                    {
                        grav++;
                        somma_giorni=somma_giorni+head->giorni_ricovero;
                        count_giorni++;
                    }
                head=head->next;
            }
        if(somma_giorni/count_giorni>7 && grav>=2)
            return 1;
    return 0;
    }
Lista_reparti incodareparti(Lista_reparti head, int soglia, Lista_reparti x)
    {
        if(head==NULL)
            {
                Lista_reparti new=(Lista_reparti)malloc(sizeof(*new));
                new->piano=x->piano;
                strcpy(x->nomeReparto, x->nomeReparto);
                Lista_paz scorri=x->head;
                new->head=NULL;
                new->next=NULL;
                while(scorri!=NULL)
                    {
                        if(scorri->gravità>soglia)
                            {
                                new->head=inseriscincoda(new->head, *scorri);
                            }
                        scorri=scorri->next;
                    }
                return new;
            }
    head->next=incodareparti(head->next, soglia, x);
    return head;
    }

Lista_reparti estraiRepartiCritici(Lista_reparti reparti, int soglia)
    {
        if(reparti==NULL)
            return NULL;
    Lista_reparti new=NULL;
        while(reparti!=NULL)
            {
                if(ver(reparti->head, soglia))
                    {
                        new=incodareparti(new, soglia, reparti);
                    }
                reparti=reparti->next;
            }
    return new;
    }
