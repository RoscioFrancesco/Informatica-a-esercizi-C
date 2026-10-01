//
//  main.c
//  tde
//
//  Created by Francesco Roscio Ricon on 26/01/26.
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
typedef struct Risultato {
    char matricola[20];
    int totaleMillisecondi;
    struct Risultato* next;
} Risultato;
Timbratura* a(Timbratura* head, const char* matricola, int ingresso, int uscita);
typedef struct Timbratura* e_timb;
typedef struct Risultato* e_ris;
void stampaRisultati(Risultato* risultati);
e_ris f(e_timb start);
e_ris trova_matr(e_ris head, char mat[]);
int calcolatempo(e_timb a);
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
int calcolatempo(e_timb a)
    {
    return a->uscita-a->ingresso;
    }
e_ris trova_matr(e_ris head, char mat[])
    {
        if(head==NULL)
            return NULL;
    e_ris scorri=head;
    while(scorri!=NULL)
        {
            if(strcmp(scorri->matricola, mat)==0)
                return scorri;
            scorri=scorri->next;
        }
    return NULL;
    }
e_ris f(e_timb start)
    {
    e_ris head=NULL;
    e_timb scorritimb=start;
    while (scorritimb!=NULL)
        {
            e_ris pos=trova_matr(head, scorritimb->matricola);
            if(pos==NULL) // in questo caso devo creare il nuovo nodo
                {
                    e_ris new=(e_ris)malloc(sizeof(Risultato));
                    strcpy(new->matricola,scorritimb->matricola);
                    new->next=head;
                    new->totaleMillisecondi=calcolatempo(scorritimb);
                    head=new;
                }
            else
                {
                    pos->totaleMillisecondi=pos->totaleMillisecondi+calcolatempo(scorritimb);
                }
            scorritimb=scorritimb->next;
        }
    return head;
    }
