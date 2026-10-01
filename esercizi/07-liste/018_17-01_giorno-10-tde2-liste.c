//  Created by Francesco Roscio Ricon on 17/01/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Struttura per il brano musicale
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
ListaGeneri inseriscibrano(ListaGeneri head, Brano brano);
ListaGeneri organizza(ListaBrani Elenco);
void stampaListaGeneri(ListaGeneri lista);

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
    risultato=organizza(lista);
    stampaListaGeneri(risultato);
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

ListaGeneri organizza(ListaBrani Elenco)
    {
    ListaGeneri head=NULL;
        if(Elenco==NULL)
            return head;
    ListaBrani scorribrani=Elenco;
    do {
            head=inseriscibrano(head, *scorribrani);
            scorribrani=scorribrani->next;
        } while (scorribrani!=NULL);
        return head;
    }
ListaGeneri inseriscibrano(ListaGeneri head, Brano brano)
    {
    if(head==NULL)
        {
            ListaGeneri new=(ListaGeneri)malloc(sizeof(ListaComposta));
            new->next=NULL;
            strcpy(new->genere,brano.genere);
            new->brani=NULL;
            new->brani=aggiungiBrano(new->brani, brano.titolo, brano.genere);
            return new;
        }
    ListaGeneri scorrilista=head;
    int flag=0;
        while (scorrilista!=NULL)
            {
            if(strcmp(scorrilista->genere, brano.genere)==0)
                {
                    flag=1;
                    scorrilista->brani=aggiungiBrano(scorrilista->brani, brano.titolo, brano.genere);
                    break;
                }
            scorrilista=scorrilista->next;
            }
    
    if(flag==0)
        {
            ListaGeneri new=(ListaGeneri)malloc(sizeof(ListaComposta));
            strcpy(new->genere,brano.genere);
            new->next=NULL;
            new->brani=NULL;
            new->brani=aggiungiBrano(new->brani, brano.titolo, brano.genere);;
            ListaGeneri scorrilista2=head;
            while(scorrilista2->next!=NULL)
                {
                    scorrilista2=scorrilista2->next;
                }
            scorrilista2->next=new;
        }
    return head;
    }



void stampaListaGeneri(ListaGeneri lista)
    {
    if(lista==NULL)
        return;
    ListaGeneri scorrilista=lista;
    while(scorrilista!=NULL)
        {
            ListaBrani scorribrani=scorrilista->brani;
            printf("\nGenere: %s\n", scorrilista->genere);
            while(scorribrani!=NULL)
                {
                    printf("-%s\n",scorribrani->titolo);
                    scorribrani=scorribrani->next;
                }
            scorrilista=scorrilista->next;
        }
    }
