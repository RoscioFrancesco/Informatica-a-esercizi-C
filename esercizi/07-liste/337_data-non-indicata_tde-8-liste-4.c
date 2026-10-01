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
ListaT organizzaPerTavoli(ListaP head);
void visualizzatavoli(ListaT head);
int main()
{
    ListaP ordini = costruisci();
    ListaP temp;
    ListaT tavoli = NULL;
    VisualizzaListaP(ordini);
    tavoli=organizzaPerTavoli(ordini);
    visualizzatavoli(tavoli);
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

ListaT trovato(ListaT head, int tavolo)
    {
        if(head==NULL)
            return NULL;
    ListaT scorri=head;
        while(scorri!=NULL)
            {
                if(scorri->tavolo==tavolo)
                    return scorri;
                scorri=scorri->next;
            }
        return NULL;
    }
ListaP inseriscincoda(ListaP head, Piatto x)
    {
        if(head==NULL)
            {
                ListaP new=(ListaP)malloc(sizeof(*new));
                *new=x;
                new->next=NULL;
                return new;
            }
        head->next=inseriscincoda(head->next, x);
        return head;
    }
ListaT inseriscitavolo(ListaT head, Piatto x, int tavolo)
    {
        if(head==NULL)
            {
                ListaT new=(ListaT)malloc(sizeof(*new));
                new->next=NULL;
                new->tavolo=tavolo;
                new->ordiniTavolo=inseriscincoda(new->ordiniTavolo, x);
                return new;
            }
        head->next=inseriscitavolo(head->next, x, tavolo);
        return head;
    }

ListaT organizzaPerTavoli(ListaP head)
    {
        if(head==NULL)
            return NULL;
    ListaP scorri=head;
    ListaT new=NULL;
    while (scorri!=NULL) {
        ListaT punt=trovato(new, scorri->tavolo);
        if(punt==NULL)
            {
                new=inseriscitavolo(new, *scorri, scorri->tavolo);
            }
        else
            {
                punt->ordiniTavolo=inseriscincoda(punt->ordiniTavolo, *scorri);
            }
        scorri=scorri->next;
    }
    return new;
    }
void visualizzatavoli(ListaT head)
    {
        if(head==NULL)
            return;
    ListaT scorri=head;
    while (scorri!=NULL) {
        ListaP punt=scorri->ordiniTavolo;
        printf("tavolo: %d:\n", scorri->tavolo);
        while(punt!=NULL)
            {
                printf("piatto %s,  costo: %f\n", punt->nome, punt->costo);
                punt=punt->next;
            }
        scorri=scorri->next;
    }
    }
