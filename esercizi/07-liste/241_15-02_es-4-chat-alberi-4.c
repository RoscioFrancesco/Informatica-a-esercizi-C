//
//  main.c
//  es 4 chat alberi -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//
#include <stdio.h>
#include <stdlib.h>
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
typedef struct ES {
    int dato;
    int occ;
    struct ES *next;
} vagone_ris;
typedef vagone_ris * Ris;
lista creaNodo(int dato) {
    lista nuovoNodo = (lista)malloc(sizeof(nodo));
    nuovoNodo->dato = dato;
    nuovoNodo->next = NULL;
    return nuovoNodo;
}
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
void stampaLista(lista l) {
    while (l != NULL) {
        printf("%d -> ", l->dato);
        l = l->next;
    }
    printf("NULL\n");
}
void stampaListaDiListe(listaDiListe l) {
    while (l != NULL) {
        stampaLista(l->listaInterna);
        l = l->next;
    }
}

Ris inserimentoincoda(Ris head, int x, int occ);
lista funz(listaDiListe head, int K);

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
    risultato=funz(ldl, 6);
    printf("\nI %d valori in ordine di frequenza:\n", k);
    stampaLista(risultato);


    return 0;
}
int compareinlista(int x, lista head)
    {
        if(head==NULL)
            return 0;
    lista scorri=head;
    int count=0;
        while(scorri!=NULL)
            {
                if(scorri->dato==x)
                    count++;
                scorri=scorri->next;
            }
    return count;
    }
int containliste(listaDiListe head, int x)
    {
        if(head==NULL)
            return 0;
    listaDiListe scorri=head;
    int count=0;
    while(scorri!=NULL)
        {
            count=count+compareinlista(x, scorri->listaInterna);
            scorri=scorri->next;
        }
    return count;
    }
int trovato(Ris head, int x)
    {
            if(head==NULL)
                return 0;
    Ris scorri=head;
    while(scorri!=NULL)
        {
            if(scorri->dato==x)
                return 1;
            scorri=scorri->next;
        }
    return 0;
    }
Ris f(listaDiListe head)
    {
        if(head==NULL)
            return NULL;
    listaDiListe scorri=head;
    Ris new=NULL;
    while(scorri!=NULL)
        {
            lista punt=scorri->listaInterna;
            while(punt!=NULL)
                {
                    if(trovato(new, punt->dato)==0)
                        {
                            int occ=containliste(head, punt->dato);
                            int num=punt->dato;
                            new=inserimentoincoda(new, num, occ);
                        }
                    punt=punt->next;
                }
            scorri=scorri->next;
        }
    return new;
    }

Ris inserimentoincoda(Ris head, int x, int occ)
    {
        if(head==NULL || occ>head->occ || (occ==head->occ && x>head->dato))
            {
                Ris new=(Ris)malloc(sizeof(*new));
                new->dato=x;
                new->occ=occ;
                new->next=head;
                return new;
            }
    head->next=inserimentoincoda(head->next, x, occ);
    return head;
    }
lista funz(listaDiListe head, int K)
    {
        if(head==NULL)
            return NULL;
        Ris new=f(head);
    lista fin=NULL;
    for(int i=0; i<K && new!=NULL; i++)
        {
            fin=aggiungiInCoda(fin, new->dato);
            new=new->next;
        }
    return fin;
    }
