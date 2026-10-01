//
//  main.c
//  tde 3 es 1 -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE DATE
   ========================= */

typedef struct nodo {
    int numero;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

typedef struct nodoCompresso {
    int numero;
    int quanti;
    struct nodoCompresso *next;
} NodoCompresso;

typedef NodoCompresso* ListaCompressa;

/* =========================
   PROTOTIPI RICHIESTI
   ========================= */

ListaCompressa comprimi(Lista A);
ListaCompressa comprimiTantissimo(Lista A);

/* =========================
   FUNZIONI DI SUPPORTO
   ========================= */

Nodo* newNodo(int x) {
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    n->numero = x;
    n->next = NULL;
    return n;
}

Lista inserisciCoda(Lista L, int x) {
    Nodo* nn = newNodo(x);
    if(L == NULL)
        return nn;

    Nodo* tmp = L;
    while(tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = nn;
    return L;
}

void stampaLista(Lista L) {
    printf("(");
    while(L) {
        printf("%d", L->numero);
        if(L->next) printf(", ");
        L = L->next;
    }
    printf(")\n");
}

void stampaListaCompressa(ListaCompressa L) {
    printf("(");
    while(L) {
        printf("(%d, %d)", L->numero, L->quanti);
        if(L->next) printf(", ");
        L = L->next;
    }
    printf(")\n");
}

void freeLista(Lista L) {
    while(L) {
        Nodo* tmp = L;
        L = L->next;
        free(tmp);
    }
}

void freeListaCompressa(ListaCompressa L) {
    while(L) {
        NodoCompresso* tmp = L;
        L = L->next;
        free(tmp);
    }
}

/* =========================
   MAIN
   ========================= */
ListaCompressa comprimi(Lista A);
int contaocc(Lista head, int x);
int main() {

    Lista A = NULL;

    int dati[] = {3,3,3,3,2,2,3,5,5,5};
    int n = sizeof(dati)/sizeof(dati[0]);

    for(int i = 0; i < n; i++)
        A = inserisciCoda(A, dati[i]);

    printf("Lista A: ");
    stampaLista(A);

    ListaCompressa B1 = comprimi(A);
    printf("\nComprimi (consecutiva): ");
    stampaListaCompressa(B1);

    ListaCompressa B2 = comprimiTantissimo(A);
    printf("\nComprimiTantissimo (totali ordinati): ");
    stampaListaCompressa(B2);

    freeLista(A);
    freeListaCompressa(B1);
    freeListaCompressa(B2);

    return 0;
}
int contaconsecutive(Lista head, int x)
    {
    int count=0;
        while(head!=NULL && head->numero==x)
            {
                count++;
                head=head->next;
            }
    return count;
    }
ListaCompressa inserisciincoda(ListaCompressa head, int val, int rip)
    {
        if(head==NULL)
            {
                ListaCompressa new=(ListaCompressa)malloc(sizeof(*new));
                new->numero=val;
                new->quanti=rip;
                new->next=NULL;
                return new;
            }
    head->next=inserisciincoda(head->next, val, rip);
    return head;
    }
ListaCompressa comprimi(Lista A) {
    if(A==NULL)
        return NULL;
    ListaCompressa new=NULL;
    while(A!=NULL)
        {
            int num=A->numero;
            int ric=contaconsecutive(A, num);
            new=inserisciincoda(new, num, ric);
            for(int i=0; i<ric; i++)
                {
                    A=A->next;
                }
        }
    return new;
}

ListaCompressa inserisciordinato(ListaCompressa head, int val, int rip)
    {
        if(head==NULL || val<head->numero)
            {
                ListaCompressa new=(ListaCompressa)malloc(sizeof(*new));
                new->numero=val;
                new->quanti=rip;
                new->next=head;
                return new;
            }
    head->next=inserisciincoda(head->next, val, rip);
    return head;
    }
int trova(ListaCompressa head, int x)
    {
        if(head==NULL)
            return 0;
    while (head!=NULL) {
        if(head->numero==x)
            return 1;
        head=head->next;
        }
    return 0;
    }
ListaCompressa comprimiTantissimo(Lista A) {
    if(A==NULL)
        return NULL;
    Lista scorriA=A;
    ListaCompressa new=NULL;
    while(scorriA!=NULL)
        {
            if(trova(new, scorriA->numero)==0)
                {
                    int occ=contaocc(A, scorriA->numero);
                    new=inserisciordinato(new, scorriA->numero, occ);
                }
            scorriA=scorriA->next;
        }
    return new;
}
int contaocc(Lista head, int x)
    {
        if(head==NULL)
            return 0;
        int count=0;
        while(head!=NULL)
            {
                if(head->numero==x)
                    count++;
                head=head->next;
            }
    return count;
    }
