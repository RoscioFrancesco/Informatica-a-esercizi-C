//
//  main.c
//  tde 1 liste -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct B {
    char titolo[50];
    char genere[50];
    struct B *next; // Puntatore al prossimo brano
} Brano;


typedef Brano *ListaBrani;


// Struttura per la lista composta (genere con sottolista di brani)
typedef struct C {
    char genere[50];
    ListaBrani brani;
    struct C *next; // Puntatore alla prossima playlist
} ListaComposta;


typedef ListaComposta *ListaGeneri;


// Funzioni
ListaBrani aggiungiBrano(ListaBrani lista, const char *titolo, const char *genere);
void stampaListaBrani(ListaBrani lista);
ListaGeneri trovato(ListaGeneri head, char genere[]);
ListaGeneri organizza(ListaBrani head);
void stampaListaGeneri(ListaGeneri head);
int main() {
    // Creazione della lista di generi con brani
    ListaGeneri risultato = NULL;
    ListaBrani lista = NULL;
    lista = aggiungiBrano(lista, "Bohemian Rhapsody", "Rock");
    lista = aggiungiBrano(lista, "Black Hole Sun", "Grunge");
    lista = aggiungiBrano(lista, "Stairway to Heaven", "Rock");
    lista = aggiungiBrano(lista, "Thriller", "Pop");
    lista = aggiungiBrano(lista, "Like a Prayer", "Pop");
    lista = aggiungiBrano(lista, "Four Seasons", "Classica");
    lista = aggiungiBrano(lista, "Clair de Lune", "Classica");
    lista = aggiungiBrano(lista, "Smells Like Teen Spirit", "Grunge");
    lista = aggiungiBrano(lista, "Hotel California", "Rock");
    lista = aggiungiBrano(lista, "Billie Jean", "Pop");
    lista = aggiungiBrano(lista, "Come As You Are", "Grunge");
    lista = aggiungiBrano(lista, "Moonlight Sonata", "Classica");


    stampaListaBrani(lista);


    ListaGeneri new=organizza(lista);
    stampaListaGeneri(new);

    return 0;
}


ListaBrani aggiungiBrano(ListaBrani lista, const char *titolo, const char *genere) {
    ListaBrani nuovo = (ListaBrani)malloc(sizeof(Brano));
    strcpy(nuovo->titolo, titolo);strcpy(nuovo->genere, genere);
    nuovo->next = lista;
    return nuovo;
}


void stampaListaBrani(ListaBrani l) {
    while(l!=NULL) {
        printf("%s - %s\n",l->titolo,l->genere);
        l=l->next;
    }
}
ListaBrani inserisciincoda(ListaBrani head, Brano x)
    {
        if(head==NULL)
            {
                ListaBrani new=(ListaBrani)malloc(sizeof(Brano));
                *new=x;
                new->next=NULL;
                return new;
            }
    head->next=inserisciincoda(head->next, x);
    return head;
    }
ListaGeneri trovato(ListaGeneri head, char genere[])
    {
        if(head==NULL)
            return 0;
    ListaGeneri scorri=head;
    while (scorri!=NULL) {
        if(strcmp(scorri->genere, genere)==0)
            return scorri;
        scorri=scorri->next;
        }
    return NULL;
    }
ListaGeneri nuovoGenere(ListaGeneri head, Brano x)
    {
        if(head==NULL)
            {
                ListaGeneri new=(ListaGeneri)malloc(sizeof(ListaComposta));
                strcpy(new->genere, x.genere);
                new->brani=inserisciincoda(new->brani, x);
                new->next=NULL;
                return new;
            }
        head->next=nuovoGenere(head->next, x);
        return head;
    }
ListaGeneri organizza(ListaBrani head)
    {
        if(head==NULL)
            return NULL;
        ListaBrani scorri=head;
    ListaGeneri new=NULL;
    while (scorri!=NULL) {
        ListaGeneri punt=trovato(new, scorri->genere);
        if(punt==NULL)
            {
                new=nuovoGenere(new, *scorri);
            }
        else
            {
                punt->brani=inserisciincoda(punt->brani, *scorri);
            }
        scorri=scorri->next;
        }
    return new;
    }
void stampaListaGeneri(ListaGeneri head)
    {
        if(head==NULL)
            return;
    while (head!=NULL) {
        printf("\ngenere: %s\n", head->genere);
        ListaBrani scorribrani=head->brani;
        while(scorribrani!=NULL)
            {
                printf("-%s\n", scorribrani->titolo);
                scorribrani=scorribrani->next;
            }
        head=head->next;
    }
    }
