//  Created by Francesco Roscio Ricon on 17/01/26.

#include <stdio.h>
#include <stdlib.h>


// Definizione delle strutture
typedef struct EL {
    int dato;
    struct EL *next;
} nodo;
typedef nodo *lista;

typedef struct ES {
    int dato;
    int occorenza;
    struct ES *next;
} nodo_mio;
typedef nodo_mio *lista_mia;


typedef struct ELL {
    lista listaInterna;
    struct ELL *next;
} nodoLista;
typedef nodoLista *listaDiListe;


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

lista_mia creaNodo_mia(int dato, int occorenza);
lista_mia aggiungiInCoda_mia(lista_mia l, int dato, int occorenza);
lista_mia popolalista(lista head);
lista funzione(listaDiListe listadiliste, int k);

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


    risultato=funzione(ldl, k);
    printf("\nI %d valori in ordine di frequenza:\n", k);
    stampaLista(risultato);


    return 0;
}
lista funzione(listaDiListe listadiliste, int k)
    {
    listaDiListe scorrilistediliste=listadiliste;
    lista head=NULL;
    lista_mia lista_con_occorenze=NULL;
    while(scorrilistediliste!=NULL)
        {
            lista_con_occorenze=popolalista(scorrilistediliste->listaInterna);
            scorrilistediliste=scorrilistediliste->next;
        }
    int i;
    int max=0;
    for(i=0; i<k; i++)
        {
            head=aggiungiInCoda(head, lista_con_occorenze->dato);
            lista_con_occorenze=lista_con_occorenze->next;
        }
    return head;
    }
lista_mia popolalista(lista head)
    {
    lista_mia head_mia=NULL;
    lista scorrilista=head;
    lista scorrilista2=head->next;
    while(scorrilista!=NULL)
        {
            int occorrenza=0;
            while (scorrilista2!=NULL)
            {
                if(scorrilista->dato==scorrilista2->dato)
                    {
                        occorrenza++;
                    }
                scorrilista2=scorrilista2->next;
            }
            head_mia=aggiungiInCoda_mia(head_mia, scorrilista->dato, occorrenza);
            scorrilista=scorrilista->next;
        }
    return head_mia;
    }

lista_mia aggiungiInCoda_mia(lista_mia l, int dato, int occorenza) {
    if (l == NULL) {
        return creaNodo_mia(dato, occorenza);
    }
    lista_mia temp = l;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = creaNodo_mia(dato, occorenza);
    return l;
}
lista_mia creaNodo_mia(int dato, int occorenza) {
    lista_mia nuovoNodo = (lista_mia)malloc(sizeof(nodo_mio));
    nuovoNodo->dato = dato;
    nuovoNodo->next = NULL;
    nuovoNodo->occorenza=occorenza;
    return nuovoNodo;
}
