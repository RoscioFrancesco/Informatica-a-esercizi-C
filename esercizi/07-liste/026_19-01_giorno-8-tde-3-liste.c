//  Created by Francesco Roscio Ricon on 19/01/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Timbratura {
    char matricola[20];
    int ingresso;
    int uscita;
    struct Timbratura* next;
} Timbratura;

typedef Timbratura *punt;

typedef struct Risultato {
    char matricola[20];
    int totaleMillisecondi;
    struct Risultato* next;
} Risultato;

typedef Risultato *punt_a_ris;

Timbratura* a(Timbratura* head, const char* matricola, int ingresso, int uscita);
void stampaRisultati(Risultato* risultati);
punt_a_ris inserisci_in_coda(punt_a_ris head, punt puntatore_a_timbratura);
punt_a_ris funzione(punt start);
int cerca(punt_a_ris risultato, punt matricola);
punt_a_ris trovaNodo(punt_a_ris head, punt timb);

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
    
    risultati=funzione(t);
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

punt_a_ris funzione(punt start)
    {
    punt scorri_matricole=start;
    punt_a_ris ris=NULL;
    while(scorri_matricole!=NULL)
        {
            if(ris==NULL)
            {
                ris=inserisci_in_coda(ris, scorri_matricole);
                scorri_matricole = scorri_matricole->next;
                continue;
            }
            if(cerca(ris,scorri_matricole))
                {
                    punt_a_ris dove=trovaNodo(ris, scorri_matricole);
                    
                    dove->totaleMillisecondi=dove->totaleMillisecondi+(scorri_matricole->uscita-scorri_matricole->ingresso);
                }
            else {
                ris=inserisci_in_coda(ris, scorri_matricole);
            }
            scorri_matricole=scorri_matricole->next;
        }
    return ris;
    }
punt_a_ris inserisci_in_coda(punt_a_ris head, punt puntatore_a_timbratura)
    {
        punt_a_ris scorri_ris=head;
        punt_a_ris new=(punt_a_ris)malloc(sizeof(Risultato));
        strcpy(new->matricola,puntatore_a_timbratura->matricola);
        new->next=NULL;
        new->totaleMillisecondi=(puntatore_a_timbratura->uscita-puntatore_a_timbratura->ingresso);
        if(head==NULL)
            {
                return new;
            }
        while(scorri_ris->next!=NULL)
            {
                scorri_ris=scorri_ris->next;
            }
        scorri_ris->next=new;
        return head;
    }
int cerca(punt_a_ris risultato, punt matricola)
    {
    punt_a_ris cerca=risultato;
        while(cerca!=NULL)
            {
                if(strcmp(cerca->matricola,matricola->matricola)==0)
                    {
                        return 1;
                    }
                cerca=cerca->next;
            }
        return 0;
    }

punt_a_ris trovaNodo(punt_a_ris head, punt timb)
{
    while (head != NULL) {
        if (strcmp(head->matricola, timb->matricola) == 0)
            return head;   // trovato
        head = head->next;
    }
    return NULL; // non trovato
}
