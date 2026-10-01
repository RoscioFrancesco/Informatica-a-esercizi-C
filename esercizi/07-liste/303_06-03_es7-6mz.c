//
//  main.c
//  es7 6mz
//
//  Created by Francesco Roscio Ricon on 06/03/26.
//Esercizio 1 — Università con corsi e voti (lista + matrice)

//Una università è rappresentata da una lista di corsi.
//Ogni corso contiene:
//codice corso
//una matrice di strutture voti[30][3]
//una lista di studenti iscritti
//Ogni voto è:

//Ogni studente contiene:
//
//La struttura corso è:


#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int voto;
    char data[20];
} Voto;

typedef struct EL{
    int matricola;
    char nome[50];
    int media;
    struct EL *next;
} Studente;
typedef Studente *ListaStudenti;

typedef struct C{
    int codice;
    Voto voti[30][3];
    ListaStudenti iscritti;
    struct C *next;
} Corso;
typedef Corso *Lista_Corsi;
ListaStudenti inserisci_in_fondo(ListaStudenti head, Studente x);
int main() {
}
int ver(Corso C)
    {
    int num=0;
    for(int r=0; r<30; r++)
        {
            float somma=0;
            float count=0;
            for(int c=0; c<3; c++)
                {
                    somma=somma+C.voti[r][c].voto;
                    count++;
                }
            if(somma/count>=27)
                {
                    num++;
                }
            
        }
    if(num>=10)
        return 1;
    return 0;
    }
ListaStudenti inserisci_in_fondo(ListaStudenti head, Studente x)
    {
        if(head==NULL)
            {
                ListaStudenti new=(ListaStudenti)malloc(sizeof(*new));
                *new=x;
                new->next=NULL;
                return new;
            }
    head->next=inserisci_in_fondo(head->next, x);
    return head;
    }
ListaStudenti copialista(ListaStudenti head)
    {
    ListaStudenti new=NULL;
    while(head!=NULL)
        {
            new=inserisci_in_fondo(new, *head);
            head=head->next;
        }
    return new;
    }
Lista_Corsi inserisci_corso(Lista_Corsi head, Corso x)
    {
        if(head==NULL)
            {
                Lista_Corsi new=(Lista_Corsi)malloc(sizeof(*new));
                *new=x;
                new->iscritti=copialista(x.iscritti);
                new->next=NULL;
                return new;
            }
    head->next=inserisci_corso(head->next, x);
    return head;
    }
Lista_Corsi f(Lista_Corsi head)
    {
    Lista_Corsi new=NULL;
    while(head!=NULL)
        {
            if(ver(*head))
                {
                    new=inserisci_corso(new, *head);
                }
        }
    return new;
    }
