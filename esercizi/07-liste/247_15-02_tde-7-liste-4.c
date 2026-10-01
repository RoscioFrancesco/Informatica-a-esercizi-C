//
//  main.c
//  tde 7 liste -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Timbratura {
    char matricola[20];
    int ingresso;
    int uscita;
    struct Timbratura* next;
} Timbratura;
typedef Timbratura *Lista_timbrature;
typedef struct Risultato {
    char matricola[20];
    int totaleMillisecondi;
    struct Risultato* next;
} Risultato;
typedef Risultato* Lista_ris;
Timbratura* a(Timbratura* head, const char* matricola, int ingresso, int uscita);
void stampaRisultati(Risultato* risultati);
Lista_ris f(Lista_timbrature head);

int main() {
    Timbratura* t = NULL;
    Risultato* risultati = NULL;
    t=a(t,"12345",554800,562000);
    t=a(t,"67890",554800,562000);
    t=a(t,"12345",576400,583600);
    t=a(t,"67890",576400,583600);
    t=a(t,"11111",598000,601600);
    t=a(t,"22222",605200,612400);
    t=a(t,"33333",616000,623200);
    t=a(t,"44444",626800,630400);
    t=a(t,"55555",634000,641200);
    t=a(t,"11111",644800,652000);
    t=a(t,"22222",655600,662800);
    t=a(t,"33333",666400,673600);
    t=a(t,"44444",677200,680800);
    t=a(t,"55555",684400,691600);
    t=a(t,"12345",695200,702400);
    t=a(t,"67890",706000,713200);
    t=a(t,"11111",716800,724000);
    t=a(t,"22222",727600,734800);
    t=a(t,"33333",738400,745600);
    t=a(t,"44444",749200,752800);
    t=a(t,"55555",756400,763600);
    t=a(t,"12345",767200,774400);
    t=a(t,"67890",778000,785200);
    t=a(t,"11111",788800,796000);

    risultati=f(t);
    stampaRisultati(risultati);


    return 0;
}


Timbratura* a(Timbratura* head, const char* matricola, int ingresso, int uscita) {
    Timbratura* newNode = (Timbratura*)malloc(sizeof(Timbratura));
    strcpy(newNode->matricola, matricola);
    newNode->ingresso = ingresso;
    newNode->uscita = uscita;
    newNode->next = head;
    return newNode;
}


void stampaRisultati(Risultato* risultati) {
    while (risultati != NULL) {
        printf("Matricola: %s, Totale millisecondi: %d\n", risultati->matricola, risultati->totaleMillisecondi);
        risultati = risultati->next;
    }
}


Lista_ris trova(Lista_ris head, char matricola[])
    {
        if(head==NULL)
            return 0;
    Lista_ris scorri=head;
    while (scorri!=NULL){
        if(strcmp(scorri->matricola, matricola)==0)
            return scorri;
        scorri=scorri->next;
    }
    return NULL;
    }

Lista_ris inserisciincoda(Lista_ris head, char matricola[], int millisecondi)
    {
        if(head==NULL)
            {
                Lista_ris new=(Lista_ris)malloc(sizeof(*new));
                new->totaleMillisecondi=millisecondi;
                strcpy(new->matricola, matricola);
                new->next=NULL;
                return new;
            }
    head->next=inserisciincoda(head->next, matricola, millisecondi);
    return head;
    }

Lista_ris f(Lista_timbrature head)
{
        if(head==NULL)
            return NULL;
    Lista_timbrature scorri=head;
    Lista_ris new=NULL;
    while (scorri!=NULL) {
        int len=(scorri->uscita-scorri->ingresso);
        Lista_ris punt=trova(new, scorri->matricola);
        if(punt==NULL)
            {
                new=inserisciincoda(new, scorri->matricola, len);
            }
        else
            {
                punt->totaleMillisecondi=punt->totaleMillisecondi+len;
            }
        scorri=scorri->next;
    }
    return new;
}
