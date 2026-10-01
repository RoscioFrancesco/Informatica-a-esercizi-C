//
//  main.c
//  tde 1 lista 2 -3
//
//  Created by Francesco Roscio Ricon on 16/02/26.
//
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

typedef struct MIA{
    float dato;
    struct MIA *next;
}Vagone;
typedef Vagone *Lista_medie;

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
void calcolamedia(lista head, float *sum, int *count, int k);
float media(lista head, int k);
void stampa(Lista_medie head);
Lista_medie f(listaDiListe head, int k);
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


    Lista_medie new=f(ldl, k);
    stampa(new);
    
    // Stampa i risultati
    printf("\nLista risultato con K=%d:\n", k);
    
    return 0;
}

void calcolamedia(lista head, float *sum, int *count, int k)
    {
        if(head==NULL)
            return;
    lista scorri=head;
    while (scorri!=NULL) {
        if(scorri->dato%k==0)
        {
            *sum=(*sum)+scorri->dato;
            (*count)++;
        }
        scorri=scorri->next;
        }
    }
float media(lista head, int k)
    {
    float somma=0;
    int count=0;
    calcolamedia(head, &somma, &count, k);
    if(count!=0)
    {
        return somma/count;
    }
    return 0;
    }
Lista_medie inserisci_in_coda(Lista_medie head, float x)
    {
        if(head==NULL)
            {
                Lista_medie new=(Lista_medie)malloc(sizeof(Vagone));
                new->dato=x;
                new->next=NULL;
                return new;
            }
    head->next=inserisci_in_coda(head->next, x);
    return head;
    }
Lista_medie f(listaDiListe head, int k)
    {
        if(head==NULL)
            return NULL;
    Lista_medie new=NULL;
    listaDiListe scorri=head;
        while(scorri!=NULL)
            {
                float m=media(scorri->listaInterna, k);
                new=inserisci_in_coda(new, m);
                scorri=scorri->next;
            }
    return new;
    }
void stampa(Lista_medie head)
    {
        if(head==NULL)
            return;
    Lista_medie scorri=head;
    while (scorri!=NULL) {
        printf("%f -->", scorri->dato);
        scorri=scorri->next;
    }
    }

