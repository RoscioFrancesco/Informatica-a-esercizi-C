//
//  main.c
//  giorno -7 tde 3 liste
//
//  Created by Francesco Roscio Ricon on 20/01/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
typedef char Tipo[N];


typedef struct ndP{
    float costo;
    int tavolo;
    Tipo nome;
    struct ndP* next;
} Piatto;


typedef Piatto* ListaP;


typedef struct ndT{
    int tavolo;
    ListaP ordiniTavolo;
    struct ndT* next;
} Tavolo;
typedef Tavolo* ListaT;


ListaP InsInFondoPiatto(ListaP lista, float costo, int tavolo, Tipo nome);
void VisualizzaListaP(ListaP lista);
ListaP costruisci();
ListaT popola_tavoli(ListaT head, ListaP ordine);
ListaT organizzaPerTavoli(ListaP start);
void stampa_tavoli(ListaT head);


int main()
{
    ListaP ordini = costruisci();
    ListaP temp;
    ListaT tavoli = NULL;
    VisualizzaListaP(ordini);
    tavoli=organizzaPerTavoli(ordini);
    stampa_tavoli(tavoli);
}


// Sviluppare qui le funzioni richieste
ListaP costruisci()
{
ListaP lista = NULL;
lista = InsInFondoPiatto(lista, 10.5, 1, "Karelian Pie"); lista = InsInFondoPiatto(lista, 8.0, 1, "Makkara");lista = InsInFondoPiatto(lista, 12.0, 1, "Musta Makkara");lista = InsInFondoPiatto(lista, 20, 2, "Baltic Herrings");lista = InsInFondoPiatto(lista, 20, 2, "Pasta all'Amatriciana");lista = InsInFondoPiatto(lista, 20, 1, "Herrings");lista = InsInFondoPiatto(lista, 20, 4, "Sgombro al Limone");lista = InsInFondoPiatto(lista, 20, 4, "Tiramisu'");return lista;
}


ListaP InsInFondoPiatto(ListaP lista, float costo, int tavolo, Tipo nome)
{
    ListaP punt;
        if(lista==NULL) { punt = malloc( sizeof(Piatto) );
                     punt->next = NULL; punt->costo = costo; punt->tavolo = tavolo; strcpy(punt->nome,nome);return punt;
    }else{lista->next = InsInFondoPiatto(lista->next,costo, tavolo, nome); return lista;}
}


void VisualizzaListaP(ListaP lista)
{
  if (lista==NULL) printf(" ---| \n");
    else{printf("\n nome:%s, tav:%d (%.2f) ---> ", lista->nome, lista->tavolo, lista->costo);
     VisualizzaListaP(lista->next);}
}

ListaT organizzaPerTavoli(ListaP start)
    {
        if(start==NULL)
            return NULL;
    ListaP scorri_ordini=start;
    ListaT head=NULL;
        while(scorri_ordini!=NULL)
            {
                head=popola_tavoli(head, scorri_ordini);
                scorri_ordini=scorri_ordini->next;
            }
    return head;
    }

ListaT popola_tavoli(ListaT head, ListaP ordine)
    {
    ListaT scorritavoli=head;
    ListaT prev = NULL;
    if(head==NULL)
        {
            ListaT new=(ListaT)malloc(sizeof(Tavolo));
            new->next=NULL;
            new->tavolo=ordine->tavolo;
            ListaP nuovo_ordine=(ListaP)malloc(sizeof(Piatto));
            nuovo_ordine->next=NULL;
            nuovo_ordine->costo=ordine->costo;
            strcpy(nuovo_ordine->nome,ordine->nome);
            nuovo_ordine->tavolo=ordine->tavolo;
            new->ordiniTavolo=nuovo_ordine;
            return new;
        }
    while (scorritavoli!=NULL) {
        if(scorritavoli->tavolo==ordine->tavolo)
            {
                ListaP scorri_ordini=scorritavoli->ordiniTavolo;
                while(scorri_ordini->next!=NULL)
                    {
                        scorri_ordini=scorri_ordini->next;
                    }
                ListaP nuovo_ordine=(ListaP)malloc(sizeof(Piatto));
                nuovo_ordine->next=NULL;
                nuovo_ordine->costo=ordine->costo;
                strcpy(nuovo_ordine->nome,ordine->nome);
                nuovo_ordine->tavolo=ordine->tavolo;
                scorri_ordini->next=nuovo_ordine;
                return head;
            }
        prev = scorritavoli;
        scorritavoli=scorritavoli->next;
        } // all'uscita del while scorritavoli=NULL quindi serve un prev
    ListaT new=(ListaT)malloc(sizeof(Tavolo));
    new->next=NULL;
    new->tavolo=ordine->tavolo;
    ListaP nuovo_ordine=(ListaP)malloc(sizeof(Piatto));
    nuovo_ordine->next=NULL;
    nuovo_ordine->costo=ordine->costo;
    strcpy(nuovo_ordine->nome,ordine->nome);
    nuovo_ordine->tavolo=ordine->tavolo;
    new->ordiniTavolo=nuovo_ordine;
    prev->next = new;
    return head;
    }

void stampa_tavoli(ListaT head)
    {
    ListaT scorritavoli=head;
    while(scorritavoli!=NULL)
        {
            ListaP scorriordini=scorritavoli->ordiniTavolo;
            printf("TAVOLO ID NUMERO: %d\n", scorritavoli->tavolo);
            while (scorriordini!=NULL) {
                printf("%s, %d, %f\n", scorriordini->nome, scorriordini->tavolo, scorriordini->costo);
                scorriordini=scorriordini->next;
            }
            printf("\n");
            scorritavoli=scorritavoli->next;
        }
    }
