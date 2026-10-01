//
//  main.c
//  lista di liste
//
//  Created by Francesco Roscio Ricon on 25/01/26.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct EL {
    int dato;
    struct EL *next;
} nodo;
typedef nodo *lista;
typedef struct ES {
    int dato;
    int occorrenze;
    struct ES *next;
} nodo_mio;
typedef nodo_mio *lista_mia;
typedef struct ELL {
    lista listaInterna;
    struct ELL *next;
} nodoLista;
typedef nodoLista *listaDiListe;
lista creaNodo(int dato) {
    lista n = (lista)malloc(sizeof(nodo));
    n->dato = dato;
    n->next = NULL;
    return n;
}
lista aC(lista l, int dato) {
    if (l == NULL) {
        return creaNodo(dato);}
    lista temp = l;
    while (temp->next != NULL) {
        temp = temp->next;}
    temp->next = creaNodo(dato);
    return l;
}
listaDiListe aLC(listaDiListe l, lista nL) {
    nodoLista *nN = (nodoLista *)malloc(sizeof(nodoLista));
    nN->listaInterna = nL;
    nN->next = NULL;
    if (l == NULL) {
        return nN;
    }
    listaDiListe temp = l;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = nN;
    return l;
}
void sL(lista l) {
    while (l != NULL) {
        printf("%d -> ", l->dato);
        l = l->next;
    }
    printf("NULL\n");
}
void sLDl(listaDiListe l) {
    while (l != NULL) {
        sL(l->listaInterna);
        l = l->next;
    }
}
int trovato(lista_mia head, int val);
lista_mia inserimento(lista_mia head, int val, int occ);
lista_mia funzione(listaDiListe head);
lista_mia inserimento(lista_mia head, int val, int occ);
int num_occlistadiliste(int val, listaDiListe head);
int trovaval(int k, lista head);
lista f(listaDiListe lDl, int k);
int main() {
    int i,k=3;
    listaDiListe ldl = NULL;
    lista r=NULL;lista l1 = NULL;
    for (i = 1; i <= 7; i++) l1 = aC(l1, i);lista l2 = NULL;
    for (i = 4; i <= 11; i++) l2 = aC(l2, i);lista l3 = NULL;
    for (i = 7; i <= 14; i++) l3 = aC(l3, i);lista l4 = NULL;
    for (i = 1; i <= 8; i++) l4 = aC(l4, i);lista l5 = NULL;for (i = 2; i <= 9; i++) l5 = aC(l5, i);lista l6 = NULL;for (i = 7; i <= 13; i++) l6 = aC(l6, i);lista l7 = NULL;for (i=3;i<=10;i++) l7 = aC(l7, i);ldl = aLC(ldl, l1);ldl = aLC(ldl, l2);ldl = aLC(ldl, l3);ldl = aLC(ldl, l4);ldl=aLC(ldl,l5);ldl=aLC(ldl,l6);ldl=aLC(ldl,l7);
    sLDl(ldl);
    r=f(ldl, k);
    printf("\n");
    sL(r);
}
int trovaval(int k, lista head)
    {while(head!=NULL)
    {
    if(k==head->dato)
        return 1;
    head=head->next;
    }return 0;}
int num_occlistadiliste(int val, listaDiListe head)
    {
    listaDiListe sl=head;
    int somma=0;
    while(sl!=NULL)
        {
            somma=somma+trovaval(val, sl->listaInterna);
            sl=sl->next;
        }
    return somma;}
lista_mia funzione(listaDiListe head)
    {
    lista_mia head_mia=NULL;
    listaDiListe se=head;
    while (se!=NULL) {
        lista scorrilista=se->listaInterna;
        while (scorrilista!=NULL) {
            int o=num_occlistadiliste(scorrilista->dato, head);
            if(!trovato(head_mia, scorrilista->dato))
                {
                    int val=scorrilista->dato;
                    head_mia=inserimento(head_mia, val, o);
                }
            scorrilista=scorrilista->next;
        }
        se=se->next;}return head_mia;
    }
int trovato(lista_mia head, int val)
{
    if(head==NULL)
    return 0;
    while(head!=NULL)
        {
        if(head->dato==val)
                return 1;
            head=head->next;
    }
return 0;
}
lista_mia inserimento(lista_mia head, int val, int occ) // inserimento ordinato ricorsivo importante
    {
    if(head==NULL || head->occorrenze<occ)
    {
        lista_mia new=(lista_mia)malloc(sizeof(nodo_mio));
        new->occorrenze=occ;
        new->dato=val;
        new->next=head;
        return new;
    }
    head->next=inserimento(head->next, val, occ);
    return head;
    }
lista f(listaDiListe lDl, int k)
{
    lista_mia head=funzione(lDl);
    lista_mia s=head;
    lista new_head=NULL;
    int i=0;
    for(i=0; i<k; i++)
    {
        new_head=aC(new_head, s->dato);
        s=s->next;
    }
    return new_head;
}
