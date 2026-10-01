//
//  main.c
//  lista new
//
//  Created by Francesco Roscio Ricon on 25/01/26.
//
#include <stdio.h>
#include <stdlib.h>

/*** STRUTTURE ***/
typedef struct nd1 {
    int valore;
    struct nd1* next;
} Nodo;

typedef Nodo* Lista;

typedef struct nd2 {
    int valore;
    int quanteVolte;
    struct nd2* next;
} NodoRisultato;

typedef NodoRisultato* ListaRisultato;


/*** PROTOTIPI ***/
Lista inserisciInCoda(Lista l, int x);
void stampaLista(Lista l);

void stampaListaRisultato(ListaRisultato lr);

ListaRisultato conteggiLista(Lista l);


/*** FUNZIONI DI SUPPORTO ***/
Lista inserisciInCoda(Lista l, int x) {
    Nodo* nuovo = (Nodo*)malloc(sizeof(Nodo));
    nuovo->valore = x;
    nuovo->next = NULL;

    if (l == NULL) return nuovo;

    Nodo* temp = l;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = nuovo;
    return l;
}

void stampaLista(Lista l) {
    printf("Lista input: ");
    while (l != NULL) {
        printf("%d -> ", l->valore);
        l = l->next;
    }
    printf("NULL\n");
}

void stampaListaRisultato(ListaRisultato lr) {
    printf("Lista risultato (valore, quanteVolte):\n");
    while (lr != NULL) {
        printf("(%d, %d) -> ", lr->valore, lr->quanteVolte);
        lr = lr->next;
    }
    printf("NULL\n");
}
ListaRisultato inseriscitesta(ListaRisultato head, int val);
ListaRisultato trovavalore(ListaRisultato head, int valore);
/*** MAIN ***/
int main() {
    Lista l = NULL;

    // esempio di input con duplicati
    int valori[] = {5, 2, 5, 7, 2, 2, 9, 7, 5};
    int n = sizeof(valori) / sizeof(valori[0]);

    // costruzione lista
    for (int i = 0; i < n; i++) {
        l = inserisciInCoda(l, valori[i]);
    }

    // stampa lista input
    stampaLista(l);

    ListaRisultato lr = conteggiLista(l);

    // stampa lista risultato
    stampaListaRisultato(lr);

    return 0;
}

ListaRisultato conteggiLista(Lista l)
    {
        if(l==NULL)
            return NULL;
    Lista scorrilista=l;
    ListaRisultato head=NULL;
    while (scorrilista!=NULL)
                    {
                        if(trovavalore(head, scorrilista->valore)!=NULL)
                            {
                                ListaRisultato punt=trovavalore(head, scorrilista->valore);
                                (punt->quanteVolte)++;
                            }
                        else
                            {
                                head=inseriscitesta(head, scorrilista->valore);
                            }
                        scorrilista=scorrilista->next;
                    }
    return head;
    }
ListaRisultato inseriscitesta(ListaRisultato head, int val)
    {
    ListaRisultato new=(ListaRisultato)malloc(sizeof(NodoRisultato));
    new->next=head;
    new->valore=val;
    new->quanteVolte=1;
    return new;
    }
ListaRisultato trovavalore(ListaRisultato head, int valore)
    {
    ListaRisultato scorri=head;
    if(head==NULL)
        return NULL;
    while (scorri!=NULL) {
        if(scorri->valore==valore)
            return scorri;
        scorri=scorri->next;
    }
    return NULL;
    }
