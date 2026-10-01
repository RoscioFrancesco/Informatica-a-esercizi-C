//  Created by Francesco Roscio Ricon on 19/01/26.


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct AP {
   int oraInizio, minutoInizio;
   int oraFine, minutoFine;
   struct AP *prox;
} appuntamento;


typedef appuntamento *ListaAppuntamenti;

typedef struct EL{
    int durata;
    struct EL *next;
}Vagone;
typedef Vagone *Treno;


ListaAppuntamenti costruisci();
ListaAppuntamenti InsInFondo(ListaAppuntamenti lista, int oraInizio, int minutoInizio, int oraFine, int minutoFine);
void VisualizzaLista(ListaAppuntamenti lista);
Treno inserisci_in_coda(ListaAppuntamenti appuntamento, Treno head);
Treno funzione(ListaAppuntamenti start);
int si_sovrappongono(ListaAppuntamenti prev, ListaAppuntamenti succ);
ListaAppuntamenti EliminaSovrapposti(ListaAppuntamenti head);


int main() {


    ListaAppuntamenti lista = costruisci();
    printf("Lista di partenza:\n");
    VisualizzaLista(lista);
    lista=EliminaSovrapposti(lista);
    printf("dopo");
    VisualizzaLista(lista);
    
}


// TODO DEFINIZIONI DI FUNZIONI




// FUNZIONI PER COSTRUIRE LISTA
ListaAppuntamenti costruisci() {
    int i, M[8][4] = {8, 20, 9, 56,
                     9, 30, 10, 20,
                     10, 30, 11, 45,
                     11, 57, 12, 20,
                     14, 40, 15, 20,
                     15, 20, 16, 12,
                     16, 30, 17, 15,
                     17, 10, 18, 30};


    ListaAppuntamenti lista = NULL;
    for (i = 0; i < 8; i++) {
        lista = InsInFondo(lista, M[i][0], M[i][1], M[i][2], M[i][3]);
    }


    return lista;
}


ListaAppuntamenti InsInFondo(ListaAppuntamenti lista, int oraInizio, int minutoInizio, int oraFine, int minutoFine){
    ListaAppuntamenti punt;
    if (lista == NULL) {
        punt = malloc(sizeof(appuntamento));
        punt->prox = NULL;
        punt->oraInizio = oraInizio;
        punt->minutoInizio = minutoInizio;
        punt->oraFine = oraFine;
        punt->minutoFine = minutoFine;
        return punt;
    } else {
        lista->prox = InsInFondo(lista->prox, oraInizio, minutoInizio, oraFine, minutoFine);
        return lista;
    }
}


void VisualizzaLista(ListaAppuntamenti lista) {
    while (lista != NULL) {
        printf("%02d:%02d - %02d:%02d\n", lista->oraInizio, lista->minutoInizio, lista->oraFine, lista->minutoFine);
        lista = lista->prox;
    }
}

Treno funzione(ListaAppuntamenti start)
    {
        if(start==NULL)
            return 0;
        Treno head=NULL;
    ListaAppuntamenti scorrilista=start;
        while(scorrilista!=NULL)
            {
                head=inserisci_in_coda(scorrilista, head);
                scorrilista=scorrilista->prox;
            }
        return head;
    }
Treno inserisci_in_coda(ListaAppuntamenti appuntamento, Treno head)
    {
        Treno new = (Treno)malloc(sizeof(Vagone));
        new->durata=appuntamento->minutoFine-appuntamento->minutoInizio+60*(appuntamento->oraFine-appuntamento->oraInizio);
        new->next=NULL;
        if(head==NULL)
            {
                return new;
            }
    Treno scorritreno=head;
    while(scorritreno->next!=NULL)
        {
            scorritreno=scorritreno->next;
        }
    scorritreno->next=new;
    return head;
            
    }

// EliminaSovrapposti che, presa una lista di appuntamenti, controlla se due appuntamenti si sovrappongono, e in tal caso elimina il secondo dalla lista.

ListaAppuntamenti EliminaSovrapposti(ListaAppuntamenti head)
    {
        if(head==NULL)
            return head;
    ListaAppuntamenti scorri_appuntamenti=head;
    ListaAppuntamenti scorri_appuntamenti_prec=NULL;
        while(scorri_appuntamenti!=NULL)
            {
                ListaAppuntamenti scorri_appuntamenti_succ=scorri_appuntamenti->prox;
                if(si_sovrappongono(scorri_appuntamenti, scorri_appuntamenti_succ))
                    {
                        if(scorri_appuntamenti_prec==NULL)
                            {
                                scorri_appuntamenti->prox=scorri_appuntamenti_succ->prox;
                                free(scorri_appuntamenti_succ);
                                scorri_appuntamenti_succ=scorri_appuntamenti->prox;
                            }
                        else
                            {
                                scorri_appuntamenti->prox=scorri_appuntamenti_succ->prox;
                                free(scorri_appuntamenti_succ);
                                scorri_appuntamenti_succ=scorri_appuntamenti->prox;
                            }
                    }
                else{
                        scorri_appuntamenti_prec=scorri_appuntamenti;
                        scorri_appuntamenti=scorri_appuntamenti_succ;
                    }
            }
        return head;
    }

int si_sovrappongono(ListaAppuntamenti prev, ListaAppuntamenti succ)
    {
        if(succ==NULL)
            return 0;
        if(prev->oraFine>succ->oraInizio)
            return 1;
        if(prev->oraFine==succ->oraInizio)
            {
                if(prev->minutoFine>succ->minutoInizio)
                    return 1;
                else
                    return 0;
            }
    return 0;
    }


