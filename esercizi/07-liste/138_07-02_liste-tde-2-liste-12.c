//
//  main.c
//  liste tde 2 liste -12
//
//  Created by Francesco Roscio Ricon on 07/02/26.
//



#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE DATI INPUT
   ========================= */
typedef struct nodo {
    int valore;
    struct nodo* next;
} nodo;

typedef nodo* lista;

/* =========================
   STRUTTURE DATI OUTPUT
   ========================= */
typedef struct n {
    int valore;
    int quanteVolte;
    struct n* next;
} nodoRisultato;

typedef nodoRisultato* listaRisultato;

/* =========================
   PROTOTIPO FUNZIONE
   (DA SVOLGERE)
   ========================= */
listaRisultato costruisciListaRisultato(lista L);   /* TODO */

/* =========================
   FUNZIONI DI SUPPORTO
   (per test nel main)
   ========================= */
lista inserisciInCoda(lista head, int val)
{
    lista nuovo = malloc(sizeof(nodo));
    nuovo->valore = val;
    nuovo->next = NULL;

    if(head == NULL)
        return nuovo;

    lista temp = head;
    while(temp->next != NULL)
        temp = temp->next;

    temp->next = nuovo;
    return head;
}

void stampaLista(lista L)
{
    while(L != NULL)
    {
        printf("%d ", L->valore);
        L = L->next;
    }
    printf("\n");
}

void stampaListaRisultato(listaRisultato L)
{
    while(L != NULL)
    {
        printf("(%d, %d) ", L->valore, L->quanteVolte);
        L = L->next;
    }
    printf("\n");
}

/* =========================
   MAIN DI TEST
   ========================= */
int trovato(listaRisultato head, int x);
listaRisultato inserisciincoda(listaRisultato head, int val, int occ);

int main()
{
    lista L = NULL;
    listaRisultato R = NULL;

    /* Lista di input: 3 5 3 2 5 5 3 */
    L = inserisciInCoda(L, 3);
    L = inserisciInCoda(L, 5);
    L = inserisciInCoda(L, 3);
    L = inserisciInCoda(L, 2);
    L = inserisciInCoda(L, 5);
    L = inserisciInCoda(L, 5);
    L = inserisciInCoda(L, 3);

    printf("Lista input: ");
    stampaLista(L);

    R = costruisciListaRisultato(L);

    printf("Lista risultato (valore, quanteVolte): ");
    stampaListaRisultato(R);

    return 0;
}


//contenente per ogni valore distinto contenuto nella lista in input un nodo che contiene il valore e il numero di volte che si presenta nella lista di input
listaRisultato inserisciincoda(listaRisultato head, int val, int occ)
    {
        if(head==NULL)
            {
                listaRisultato new=(listaRisultato)malloc(sizeof(*new));
                new->quanteVolte=occ;
                new->valore=val;
                new->next=NULL;
                return new;
            }
        head->next=inserisciincoda(head->next, val, occ);
        return head;
    }
int trovato(listaRisultato head, int x)
    {
        if(head==NULL)
            return 0;
    listaRisultato scorri=head;
    while (scorri!=NULL) {
        if(scorri->valore==x)
            return 1;
        scorri=scorri->next;
        }
    return 0;
    }
void contaoccorenze(lista start, int x, int *count)
    {
        if(start==NULL)
            return;
        lista scorri=start;
        while(scorri!=NULL)
            {
                if(scorri->valore==x)
                    (*count)++;
                scorri=scorri->next;
            }
    }
listaRisultato costruisciListaRisultato(lista head)
    {
    listaRisultato new=NULL;
    if(head==NULL)
        return new;
    lista scorri=head;
    while(scorri!=NULL)
        {
            if(trovato(new, scorri->valore)==0)
                {
                    int occ=0;
                    contaoccorenze(scorri, scorri->valore, &occ);
                    new=inserisciincoda(new, scorri->valore, occ);
                }
            scorri=scorri->next;
        }
    return new;
    }
