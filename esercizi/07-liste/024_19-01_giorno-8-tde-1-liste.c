//  Created by Francesco Roscio Ricon on 19/01/26.

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


typedef struct Es {
    float dato;
    struct Es *next;
} nodo_mio;
typedef nodo_mio *lista_mia;

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
lista_mia inserisciincoda(float media, lista_mia head);
lista_mia crealista(listaDiListe head, int k);
float media_lista(lista singola_lista, int k);

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


    
    printf("Lista di liste:\n");
    stampaListaDiListe(ldl);


    lista_mia head=crealista(ldl, 3);
    
    printf("\nLista risultato con K=%d:\n", k);
    lista_mia scorri=head;
    while(scorri!=NULL)
        {
            printf("%f-->", scorri->dato);
            scorri=scorri->next;
        }
    
    return 0;
}

float media_lista(lista singola_lista, int k)
    {
    lista temp=singola_lista;
    int somma=0;
    int count=0;
    while(temp!=NULL)
        {
            if(temp->dato%k==0)
                {
                    somma=somma+temp->dato;
                    count++;
                }
            temp=temp->next;
        }
    return (somma+0.0)/count;
    }

lista_mia crealista(listaDiListe head, int k)
    {
        if(head==NULL)
            return NULL;
        lista_mia start=NULL;
        listaDiListe scorrilistadiliste=head;
        while(scorrilistadiliste!=NULL)
            {
                float media=media_lista(scorrilistadiliste->listaInterna, k);
                start=inserisciincoda(media, start);
                scorrilistadiliste=scorrilistadiliste->next;
            }
    return start;
    }

lista_mia inserisciincoda(float media, lista_mia head)
    {
    lista_mia nuovoNodo = (lista_mia)malloc(sizeof(nodo_mio));
    nuovoNodo->dato=media;
    nuovoNodo->next=NULL;
    lista_mia scorrilista=head;
    if(scorrilista==NULL)
        {
            return nuovoNodo;
        }
    while(scorrilista->next!=NULL)
        {
            scorrilista=scorrilista->next;
        }
    scorrilista->next=nuovoNodo;
    return head;
    }
