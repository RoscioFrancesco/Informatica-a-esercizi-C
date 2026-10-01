//
//  main.c
//  alberi sett 24
//
//  Created by Francesco Roscio Ricon on 26/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct El {
    char ruolo[50];
    char nome[50];
    int stipendioAnnuo;
    struct El *left,*right;
} Nodo;


typedef Nodo *Albero;


Nodo* nuovoNodo(char nome[],char ruolo[],int stipendio);
void in(Albero* T,char nome[],char ruolo[],int stipendio);
void sommaStipendi(Albero T,char ruolo[],int* somma,int* conteggio);
float mediaGerarchia(Albero T,char ruolo[]);
Albero creaAlbero();
void stampaAlbero(Albero T,int livello);
void f(Albero t, char stringa[], int*contatore, float *somma);
float mediaGerarchia(Albero t, char stringa[]);

int main() {
    float media;
    char ruolo1[]="Ingegnere Software",ruolo2[]="Team Leader";
    Albero azienda=creaAlbero();
    printf("Struttura aziendale:\n");
    stampaAlbero(azienda,0);


    media=mediaGerarchia(azienda,ruolo1);
    printf("\nMedia degli stipendi per il ruolo '%s': %.2f\n",ruolo1,media);
    media=mediaGerarchia(azienda,ruolo2);
    printf("\nMedia degli stipendi per il ruolo '%s': %.2f\n",ruolo2,media);


    return 0;
}

Albero creaAlbero(){Albero t=NULL;in(&t,"Mario Rossi","CEO",120000);in(&t,"Luca Bianchi","Direttore Finanziario",90000);in(&t,"Alessandra Verdi","Direttore Tecnico",85000);in(&t,"Giovanni Neri","Responsabile Marketing",70000);in(&t,"Chiara Esposito","Responsabile HR",65000);in(&t,"Francesco Ricci","Analista Finanziario",55000);in(&t,"Marco Gallo","Ingegnere Software",60000);in(&t,"Paola D'Angelo","Ingegnere Software",62000);in(&t,"Stefania Ferrari","Amministrazione",45000);in(&t,"Simone Pini","Amministrazione",46000);in(&t,"Giorgio Leone","Progettista",55000);in(&t,"Angela Moretti","Progettista",56000);in(&t,"Luca Colombo","Tecnico",48000);in(&t,"Sara Romano","Tecnico",49000);in(&t,"Matteo Fontana","Team Leader",70000);in(&t,"Federica Parisi","Team Leader",71000);in(&t,"Davide Sartori","Analista",50000);in(&t,"Valentina Caruso","Analista",52000);in(&t,"Giulia Greco","Segretaria",35000);in(&t,"Carlo De Luca","Segretaria",36000);return t;}
Nodo* nuovoNodo(char nome[],char ruolo[],int stipendio){Nodo* nuovo=(Nodo*)malloc(sizeof(Nodo));strcpy(nuovo->nome,nome);strcpy(nuovo->ruolo,ruolo);nuovo->stipendioAnnuo=stipendio;nuovo->left=nuovo->right=NULL;return nuovo;}
void in(Albero* T,char nome[],char ruolo[],int stipendio){if(*T==NULL)*T=nuovoNodo(nome,ruolo,stipendio);else if(rand() % 2)in(&((*T)->left),nome,ruolo,stipendio);else in(&((*T)->right),nome,ruolo,stipendio);}
void stampaAlbero(Albero T,int livello){int i;if(T==NULL) return;for(i=0;i<livello;i++)printf("    ");printf("%s - %s - Stipendio: %d\n",T->nome,T->ruolo,T->stipendioAnnuo);stampaAlbero(T->left,livello+1);stampaAlbero(T->right,livello+1);}


void f(Albero t, char stringa[], int*contatore, float *somma)
    {
        if(t==NULL)
            return;
        if(strcmp(stringa, t->ruolo)==0)
        {
            *somma=*somma+t->stipendioAnnuo;
            (*contatore)++;
        }
    f(t->left, stringa, contatore, somma);
    f(t->right, stringa, contatore, somma);
    }
float mediaGerarchia(Albero t, char stringa[])
    {
    float somma=0;
    int contatore=0;
    f(t, stringa, &contatore, &somma);
    float media=(somma+0.0)/contatore;
    return media;
    }
