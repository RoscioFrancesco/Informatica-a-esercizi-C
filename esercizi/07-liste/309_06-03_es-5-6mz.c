//
//  main.c
//  es 5 6mz
//
//  Created by Francesco Roscio Ricon on 06/03/26.
//  Esercizio 4 — Università e corsi con studenti promossi

//Una università è rappresentata da una lista di corsi.
//Ogni corso contiene:
//una matrice int voti[40][5] (studenti × prove)
//una lista di studenti iscritti
//Ogni studente contiene:
//matricola
//nome
//votoFinale
//Scrivi la funzione:
//ListaCorsi corsiValidi(ListaCorsi L);
//che costruisce una nuova lista contenente solo i corsi in cui:
//almeno 20 studenti hanno media dei voti nella matrice maggiore o uguale a 18.
//Nella nuova lista:
//la matrice voti viene copiata
//nella lista studenti vengono copiati solo quelli con votoFinale ≥ 18

#include <stdlib.h>
typedef struct EL{
    char nome[100];
    int matricola;
    int votoFinale;
    struct EL *next;
}Studente;
typedef Studente *Lista_studetni;

typedef struct C{
    int codice_corso;
    int voti[40][5];
    Lista_studetni iscritti;
    struct C*next;
}Corso;
typedef Corso *Lista_Corsi;

#include <stdio.h>
Lista_studetni inserisciincoda(Lista_studetni head, Studente x);
int main() {

}
int ver(Corso C)
    {
    int contastud=0;
    for(int r=0; r<40; r++)
        {
            int somma=0;
            int count=0;
            for(int c=0; c<5; c++)
                {
                    somma=somma+C.voti[r][c];
                    count++;
                }
            if(somma/count>=18)
            {contastud++;}
        }
    if(contastud>=20)
        return 1;
    return 0;
    }
Lista_studetni inserisciincoda(Lista_studetni head, Studente x)
    {
        if(head==NULL)
            {
                Lista_studetni new=(Lista_studetni)malloc(sizeof(*new));
                *new=x;
                new->next=NULL;
                return new;
            }
    head->next=inserisciincoda(head->next, x);
    return head;
    }
Lista_Corsi inseriscicorso(Lista_Corsi head, Corso x)
    {
        if(head==NULL)
            {
                Lista_Corsi new=(Lista_Corsi)malloc(sizeof(*new));
                *new=x;
                new->next=NULL;
                Lista_studetni punt=x.iscritti;
                while(punt!=NULL)
                    {
                        if(punt->votoFinale>=18)
                            {
                                new->iscritti=inserisciincoda(new->iscritti, *punt);
                            }
                        punt=punt->next;
                    }
                return new;
            }
    head->next=inseriscicorso(head->next, x);
    return head;
    }
Lista_Corsi f(Lista_Corsi head)
    {
        if(head==NULL)
            return NULL;
    Lista_Corsi new=NULL;
    new->iscritti=NULL;
    while(head!=NULL)
        {
            if(ver(*head))
                {
                    new=inseriscicorso(new, *head);
                }
            head=head->next;
        }
    return new;
    }
