//
//  main.c
//  tde 11 28
//
//  Created by Francesco Roscio Ricon on 28/02/26.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int giorno, mese, anno;
} data;

typedef struct {
    char codiceFiscale[100], cognome[100], nome[100];
    data DataNascita;
} persona;

typedef struct {
    persona docente, studente;
    data d;
} lezione;

typedef lezione ripetizioni[1000];

typedef struct EL{
    persona P;
    struct EL *next;
}Vagone;
typedef Vagone *Lista_persone;
#define MAXR 1000
#define NRIP 8   /* quante celle inizializzo davvero (il resto puoi ignorarlo o riempire tu) */

Lista_persone inseriscincoda(Lista_persone head, persona x);
int trova(Lista_persone head, persona x);
int f(ripetizioni R);

int main() {
    ripetizioni r = {
        /* 0) CF001 docente, STU001 studente: giorno dei 18 anni (2006-03-15 -> 2024-03-15) */
        {
            .docente = {"CF001", "Rossi",   "Marco", {1,1,1980}},
            .studente = {"STU001","Bianchi","Luca",  {15,3,2006}},
            .d = {15,3,2024}
        },

        /* 1) stesso docente/studente ma data non rilevante */
        {
            .docente = {"CF001", "Rossi",   "Marco", {1,1,1980}},
            .studente = {"STU001","Bianchi","Luca",  {15,3,2006}},
            .d = {14,3,2024}
        },

        /* 2) CF002 docente, STU002 studente: giorno dei 18 anni (2005-11-02 -> 2023-11-02) */
        {
            .docente = {"CF002", "Verdi",   "Anna",  {10,5,1975}},
            .studente = {"STU002","Neri",   "Sara",  {2,11,2005}},
            .d = {2,11,2023}
        },

        /* 3) CF003 docente, STU003: giorno prima dei 18 anni -> NO */
        {
            .docente = {"CF003", "Gallo",   "Paolo", {20,9,1988}},
            .studente = {"STU003","Russo",  "Marta", {30,6,2004}},
            .d = {29,6,2022}
        },

        /* 4) CF004 docente, STU004: studente già >18 (2000-01-10 -> 2019-01-10) ma lezione nel 2020 -> NO */
        {
            .docente = {"CF004", "Fontana", "Giulia",{3,3,1990}},
            .studente = {"STU004","Conti",  "Dario", {10,1,2000}},
            .d = {10,1,2020}
        },

        /* 5) CF002 docente di prima, STU005: anche qui giorno dei 18 anni (2006-07-01 -> 2024-07-01) */
        {
            .docente = {"CF002", "Verdi",   "Anna",  {10,5,1975}},
            .studente = {"STU005","Colombo","Elena", {1,7,2006}},
            .d = {1,7,2024}
        },

        /* 6) ripetizione “random” non rilevante */
        {
            .docente = {"CF005", "Sala",    "Irene", {8,8,1982}},
            .studente = {"STU006","Greco",  "Nico",  {12,12,2007}},
            .d = {12,12,2024} /* qui sarebbero 17 anni */
        },

        /* 7) CF006 docente, STU007: giorno dei 18 anni (2004-02-29 -> 2022-02-28/03-01 dipende da come gestisci bisestili)
              metto un caso bisestile apposta: nascita 29/2/2004, lezione 28/2/2022 (NON è il compleanno reale) */
        {
            .docente = {"CF006", "Riva",    "Stefano",{9,9,1970}},
            .studente = {"STU007","De Luca","Arianna",{29,2,2004}},
            .d = {28,2,2022}
        }
    };

    printf("%d", f(r));
}
int f(ripetizioni R)
    {
    Lista_persone new=NULL;
    for(int i=0; i<NRIP; i++)
        {
            if(R[i].d.anno==R[i].studente.DataNascita.anno+18 && R[i].d.giorno==R[i].studente.DataNascita.giorno && R[i].d.mese==R[i].studente.DataNascita.mese && trova(new, R[i].docente)==0)
                {
                    new=inseriscincoda(new, R[i].docente);
                }
        }
    int count=0;
    while(new!=NULL)
        {
            new=new->next;
            count++;
        }
    return count;
    }
Lista_persone inseriscincoda(Lista_persone head, persona x)
    {
        if(head==NULL)
            {
                Lista_persone new=malloc(sizeof(*new));
                new->P=x;
                new->next=NULL;
                return new;
            }
    head->next=inseriscincoda(head->next, x);
    return head;
    }
int trova(Lista_persone head, persona x)
    {
        while(head!=NULL)
            {
                if(strcmp(x.codiceFiscale,head->P.codiceFiscale)==0)
                    return 1;
                head=head->next;
            }
    return 0;
    }
