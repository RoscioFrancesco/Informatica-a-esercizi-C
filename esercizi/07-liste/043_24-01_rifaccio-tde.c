//  Created by Francesco Roscio Ricon on 24/01/26.

#include <stdio.h>
#include <stdlib.h>


// Definizione delle strutture
typedef struct EL {
    int dato;
    struct EL *next;
} nodo;
typedef nodo *lista;


typedef struct ELL {
    lista listaInterna;
    struct ELL *next;
} nodoLista;
typedef nodoLista *listaDiListe;

typedef struct ES{
    float media;
    struct ES *next;
}Nodo_medie;
typedef Nodo_medie *Lista_media;

// Funzione per creare un nuovo nodo di una lista
lista creaNodo(int dato) {
    lista nuovoNodo = (lista)malloc(sizeof(nodo));
    nuovoNodo->dato = dato;
    nuovoNodo->next = NULL;
    return nuovoNodo;
}


// Funzione per aggiungere un elemento alla fine di una lista
lista aggiungiInCoda(lista l, int dato) {
    if (l == NULL) {
        return creaNodo(dato);
    }
    lista temp = l;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = creaNodo(dato);
    return l;
}


// Funzione per aggiungere una lista a una lista di liste
listaDiListe aggiungiListaInCoda(listaDiListe l, lista nuovaLista) {
    nodoLista *nuovoNodo = (nodoLista *)malloc(sizeof(nodoLista));
    nuovoNodo->listaInterna = nuovaLista;
    nuovoNodo->next = NULL;


    if (l == NULL) {
        return nuovoNodo;
    }
    listaDiListe temp = l;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = nuovoNodo;
    return l;
}




// Funzione per stampare una lista
void stampaLista(lista l) {
    while (l != NULL) {
        printf("%d -> ", l->dato);
        l = l->next;
    }
    printf("NULL\n");
}


// Funzione per stampare una lista di liste
void stampaListaDiListe(listaDiListe l) {
    while (l != NULL) {
        stampaLista(l->listaInterna);
        l = l->next;
    }
}
float calcolamedia(listaDiListe punt);
Lista_media scorrilistadiliste(listaDiListe head);
void stampa(Lista_media head);

int main() {
    // Crea un caso di test con almeno 7 liste di almeno 8 elementi ciascuna
    int i,k=3;
    listaDiListe ldl = NULL;
    lista risultato=NULL;


    lista l1 = NULL;
    for (i = 1; i <= 7; i++) l1 = aggiungiInCoda(l1, i);


    lista l2 = NULL;
    for (i = 4; i <= 11; i++) l2 = aggiungiInCoda(l2, i);


    lista l3 = NULL;
    for (i = 7; i <= 14; i++) l3 = aggiungiInCoda(l3, i);


    lista l4 = NULL;
    for (i = 1; i <= 8; i++) l4 = aggiungiInCoda(l4, i);


    lista l5 = NULL;
    for (i = 2; i <= 9; i++) l5 = aggiungiInCoda(l5, i);


    lista l6 = NULL;
    for (i = 7; i <= 13; i++) l6 = aggiungiInCoda(l6, i);


    lista l7 = NULL;
    for (i = 3; i <= 10; i++) l7 = aggiungiInCoda(l7, i);


    ldl = aggiungiListaInCoda(ldl, l1);
    ldl = aggiungiListaInCoda(ldl, l2);
    ldl = aggiungiListaInCoda(ldl, l3);
    ldl = aggiungiListaInCoda(ldl, l4);
    ldl = aggiungiListaInCoda(ldl, l5);
    ldl = aggiungiListaInCoda(ldl, l6);
    ldl = aggiungiListaInCoda(ldl, l7);


    // Stampa la lista di liste
    printf("Lista di liste:\n");
    stampaListaDiListe(ldl);

    Lista_media head=NULL;
    head=scorrilistadiliste(ldl);
    
    // Stampa i risultati
    printf("\nLista risultato con K=%d:\n", k);
    stampa(head);
    
    return 0;
}

Lista_media inserisci_in_coda_media(Lista_media head, float val)
    {
    Lista_media new=(Lista_media)malloc(sizeof(Nodo_medie));
    new->media=val;
    new->next=NULL;
    Lista_media scorrilista=head;
    if(head==NULL)
        {
            return  new;
        }
    while (scorrilista->next!=NULL) {
        scorrilista=scorrilista->next;
    }
    scorrilista->next=new;
    return head;
}

Lista_media scorrilistadiliste(listaDiListe head)
    {
        if(head==NULL)
            return NULL;
    listaDiListe scorriliste=head;
    Lista_media head_medie=NULL;
        while(scorriliste!=NULL)
            {
                float media=calcolamedia(scorriliste);
                head_medie=inserisci_in_coda_media(head_medie, media);
                scorriliste=scorriliste->next;
            }
    return head_medie;
    }

float calcolamedia(listaDiListe punt)
    {
    lista scorrivalori=punt->listaInterna;
    float somma=0;
    int contatore=0;
    while(scorrivalori!=NULL)
        {
            somma=somma+scorrivalori->dato;
            contatore++;
            scorrivalori=scorrivalori->next;
        }
    return (somma+0.0)/contatore;
    }
void stampa(Lista_media head)
    {
    while (head!=NULL) {
        printf("%.2f\n", head->media);
        head=head->next;
    }
}
