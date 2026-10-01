//
//  main.c
//  tde 4 es liste -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int valore;
    struct Node *next;
} Nodo;

typedef Nodo* Lista;
Lista inseriscincoda(Lista head, int x);
/* =========================
   LISTA DI LISTE
   ========================= */

typedef struct NodeList {
    Lista lis;
    struct NodeList *next;
} NodoLista;

typedef NodoLista* ListaDiListe;

/* =========================
   PROTOTIPO RICHIESTO
   ========================= */

ListaDiListe generaListaPrefissi(Lista lis, int k);  // TODO

/* =========================
   FUNZIONI DI SUPPORTO
   ========================= */

Nodo* newNodo(int x) {
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    n->valore = x;
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

Lista buildFromArray(int a[], int n) {
    Lista L = NULL;
    for(int i = 0; i < n; i++)
        L = inserisciCoda(L, a[i]);
    return L;
}

void stampaLista(Lista L) {
    while(L != NULL) {
        printf("%d", L->valore);
        if(L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL");
}

void stampaListaDiListe(ListaDiListe LL) {
    int i = 1;
    while(LL != NULL) {
        printf("Prefisso %d: ", i);
        stampaLista(LL->lis);
        printf("\n");
        LL = LL->next;
        i++;
    }
}

void freeLista(Lista L) {
    while(L) {
        Nodo* tmp = L;
        L = L->next;
        free(tmp);
    }
}

void freeListaDiListe(ListaDiListe LL) {
    while(LL) {
        NodoLista* tmp = LL;
        LL = LL->next;
        freeLista(tmp->lis);
        free(tmp);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
ListaDiListe inserisciincoda(ListaDiListe head, Lista l, int k);
int main() {

    int a[] = {5, 6, 9, 2, 4, 1};
    Lista L = buildFromArray(a, 6);

    printf("Lista originale:\n");
    stampaLista(L);
    printf("\n\n");

    int k = 3;
    printf("Genero prefissi fino a lunghezza %d\n\n", k);

    ListaDiListe risultato = generaListaPrefissi(L, k);

    stampaListaDiListe(risultato);

    freeLista(L);
    freeListaDiListe(risultato);

    return 0;
}



ListaDiListe generaListaPrefissi(Lista lis, int k) {
    ListaDiListe new=NULL;
    for(int i=1; i<=k; i++)
        {
            new=inserisciincoda(new, lis, i);
        }
    return new;
}

Lista copiaKvalori(Lista head, int k)
    {
    Lista scorri=head;
    Lista new=NULL;
    for(int i=0; i<k; i++)
        {
            new=inseriscincoda(new, head->valore);
            head=head->next;
        }
    return new;
    }
Lista inseriscincoda(Lista head, int x)
    {
            if(head==NULL)
                {
                    Lista new=(Lista)malloc(sizeof(*new));
                    new->next=NULL;
                    new->valore=x;
                    return new;
                }
        head->next=inseriscincoda(head->next, x);
        return head;
    }
ListaDiListe inserisciincoda(ListaDiListe head, Lista l, int k)
{
    if(head==NULL)
        {
            ListaDiListe new=(ListaDiListe)malloc(sizeof(*new));
            new->next=NULL;
            new->lis=copiaKvalori(l, k);
            return new;
        }
    head->next=inserisciincoda(head->next, l, k);
    return head;
}
