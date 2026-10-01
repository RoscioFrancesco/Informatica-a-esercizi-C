//
//  main.c
//  liste 2 pag 73 -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct Node {
    int numero;
    struct Node *next;
} Nodo;

typedef Nodo *Lista;

typedef struct NodeList {
    Lista lis;               /* una lista (prefisso) */
    struct NodeList *next;   /* prossimo prefisso */
} NodoLista;

typedef NodoLista *ListaDiListe;
Lista inserisciintesta(Lista head, int x);
/* =========================
   PROTOTIPO FUNZIONE (ESERCIZIO)
   ========================= */
ListaDiListe generaListaPrefissi(Lista lis, int k); 

/* =========================
   UTILITY PER LISTE DI INT
   ========================= */
static Lista nuovoNodo(int x) {
    Lista n = (Lista)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->numero = x;
    n->next = NULL;
    return n;
}

static Lista inserisciInCoda(Lista head, int x) {
    Lista n = nuovoNodo(x);
    if (head == NULL) return n;
    Lista cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return head;
}

static void stampaLista(Lista l) {
    while (l != NULL) {
        printf("%d -> ", l->numero);
        l = l->next;
    }
    printf("NULL");
}

static void freeLista(Lista l) {
    while (l != NULL) {
        Lista tmp = l->next;
        free(l);
        l = tmp;
    }
}

/* =========================
   STAMPA LISTA DI LISTE (prefissi)
   ========================= */
static void stampaListaDiListe(ListaDiListe LL) {
    int i = 1;
    while (LL != NULL) {
        printf("Prefisso %d: ", i);
        stampaLista(LL->lis);
        printf("\n");
        LL = LL->next;
        i++;
    }
}

static void freeListaDiListe(ListaDiListe LL) {
    while (LL != NULL) {
        ListaDiListe tmp = LL->next;
        /* ogni nodo contiene una lista allocata a parte (prefisso) */
        freeLista(LL->lis);
        free(LL);
        LL = tmp;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
Lista copiafinoak(Lista head, int k);
ListaDiListe generaListaPrefissi(Lista lis, int k);

int main(void) {
    Lista lis = NULL;

    /* Esempio: 5 -> 6 -> 9 -> 2 -> 4 -> 1 */
    lis = inserisciInCoda(lis, 5);
    lis = inserisciInCoda(lis, 6);
    lis = inserisciInCoda(lis, 9);
    lis = inserisciInCoda(lis, 2);
    lis = inserisciInCoda(lis, 4);
    lis = inserisciInCoda(lis, 1);

    int k = 3;

    printf("Lista di input: ");
    stampaLista(lis);
    printf("\n");
    printf("k = %d\n\n", k);
    
    ListaDiListe prefissi = generaListaPrefissi(lis, k);
    printf("Lista dei prefissi (1..k):\n");
    stampaListaDiListe(prefissi);

    freeListaDiListe(prefissi);


    freeLista(lis);
    return 0;
}


Lista copiafinoak(Lista head, int k)
    {
    Lista new=NULL;
    if(head==NULL)
        return NULL;
    for(int i=0; i<=k; i++)
        {
            new=inserisciInCoda(new, head->numero);
            head=head->next;
        }
    return new;
    }
Lista inserisciintesta(Lista head, int x)
    {
    Lista new=(Lista)malloc(sizeof(*new));
    new->numero=x;
    new->next=head;
    return new;
    }
ListaDiListe generaListaPrefissi(Lista lis, int k);

Lista copialista(Lista head)
    {
    if(head==NULL)
        return NULL;
    Lista new=(Lista)malloc(sizeof(*new));
    new->numero=head->numero;
    new->next=copialista(head->next);
    return new;
    }
ListaDiListe inserisciincoda(ListaDiListe head, Lista lis)
    {
        if(head==NULL)
            {
                ListaDiListe new=(ListaDiListe)malloc(sizeof(*new));
                new->next=head;
                new->lis=NULL;
                new->lis=copialista(lis);
                return new;
            }
        head->next=inserisciincoda(head->next, lis);
        return head;
    }
ListaDiListe generaListaPrefissi(Lista lis, int k)
{
    if(k==0 || lis==NULL)
        return NULL;
    ListaDiListe new=NULL;
    for(int i=0; i<k; i++)
        {
            Lista temp=NULL;
            temp=copiafinoak(lis, i);
            new=inserisciincoda(new, temp);
        }
    return new;
    }

