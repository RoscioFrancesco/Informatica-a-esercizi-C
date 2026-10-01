//
//  main.c
//  tde ristorante
//
//  Created by Francesco Roscio Ricon on 24/01/26.



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
ListaP costruisci();
ListaT creatavolo(ListaP piatto, ListaT head, int numerotavolo);
int trovato(ListaT lista_tavoli, int numero_tavolo);
void stampa(ListaT head);
ListaT organizzaPerTavoli(ListaP start);

int main()
{
    ListaP ordini = costruisci();
    ListaP temp;
    ListaT tavoli = NULL;
    tavoli=organizzaPerTavoli(ordini);
    stampa(tavoli);
    return 0;
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


ListaT organizzaPerTavoli(ListaP start)
    {
    ListaP scorripiatti=start;
    ListaT head=NULL;
    while(scorripiatti!=NULL)
        {
            if(head==NULL)
                head=creatavolo(scorripiatti, head, scorripiatti->tavolo);
            else {
                if(trovato(head, scorripiatti->tavolo))
                {
                    ListaT scorritavoli=head;
                    while(scorritavoli!=NULL)
                    {
                        if(scorritavoli->tavolo==scorripiatti->tavolo)
                        {
                            scorritavoli->ordiniTavolo=InsInFondoPiatto(scorritavoli->ordiniTavolo, scorripiatti->costo, scorripiatti->tavolo, scorripiatti->nome);
                        }
                        scorritavoli=scorritavoli->next;
                    }
                }
                else
                {
                    head=creatavolo(scorripiatti, head, scorripiatti->tavolo);
                }
            }
            scorripiatti=scorripiatti->next;
        }
    return head;
}

ListaT creatavolo(ListaP piatto, ListaT head, int numerotavolo) // con inserimento in testa
    {
    ListaT new=(ListaT)malloc(sizeof(Tavolo));
    new->next=NULL;
    new->tavolo=numerotavolo;
    new->ordiniTavolo=InsInFondoPiatto(new->ordiniTavolo, piatto->costo, piatto->tavolo, piatto->nome);
    if(head==NULL)
    return new;
    ListaT scorrilista=head;
        while (scorrilista->next!=NULL) {
            scorrilista=scorrilista->next;
        }scorrilista->next=new;
        return head;
        
    }
int trovato(ListaT lista_tavoli, int numero_tavolo)
    {
    ListaT scorritavolo=lista_tavoli;
    while(scorritavolo!=NULL)
        {
            if(numero_tavolo==scorritavolo->tavolo)
                return 1;
            scorritavolo=scorritavolo->next;
        }
    return 0;
    }
void stampa(ListaT head)
    {
    ListaT scorritavoli=head;
    while(scorritavoli!=NULL)
        {
            printf("TAVOLO ID NUMERO: %d\n", scorritavoli->tavolo);
            ListaP scorripiatti=scorritavoli->ordiniTavolo;
            while(scorripiatti!=NULL)
                {
                    printf("%s, tavolo %d, costo:%f\n", scorripiatti->nome, scorripiatti->tavolo, scorripiatti->costo);
                    scorripiatti=scorripiatti->next;
                }
            scorritavoli=scorritavoli->next;
        }
}
