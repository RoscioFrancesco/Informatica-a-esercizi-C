//
//  main.c
//  es 1 liste 3 -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int valore;
    struct nodo *next;
} Nodo;

typedef Nodo * Lista;

/* Lista di liste: ogni nodo punta a una sottolista */
typedef struct nodoLista {
    Lista sub;                 /* testa della sottolista */
    struct nodoLista *next;    /* prossimo blocco */
} NodoLista;

typedef NodoLista * ListaDiListe;


ListaDiListe partizionaCrescenti(Lista L);

/* =========================
   UTILITY PER TEST
   ========================= */
static Nodo *nuovoNodo(int v) {
    Nodo *n = (Nodo *)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->valore = v;
    n->next = NULL;
    return n;
}

static Lista pushBack(Lista head, int v) {
    Nodo *n = nuovoNodo(v);
    if (head == NULL) return n;
    Nodo *cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return head;
}

static void stampaLista(Lista l) {
    while (l != NULL) {
        printf("%d", l->valore);
        if (l->next != NULL) printf(" -> ");
        l = l->next;
    }
    printf("\n");
}

static void stampaListaDiListe(ListaDiListe ll) {
    int idx = 1;
    while (ll != NULL) {
        printf("Sottolista %d: [", idx);
        Nodo *cur = ll->sub;
        while (cur != NULL) {
            printf("%d", cur->valore);
            if (cur->next != NULL) printf(" -> ");
            cur = cur->next;
        }
        printf("]\n");
        ll = ll->next;
        idx++;
    }
}

static void freeLista(Lista l) {
    while (l != NULL) {
        Nodo *tmp = l;
        l = l->next;
        free(tmp);
    }
}

/* Libera anche tutte le sottoliste */
static void freeListaDiListe(ListaDiListe ll) {
    while (ll != NULL) {
        NodoLista *tmp = ll;
        ll = ll->next;
        freeLista(tmp->sub);
        free(tmp);
    }
}


/* =========================
   MAIN DI TEST
   ========================= */
Lista copialista(Lista head, int x);
Lista inseriscincoda2(Lista head, int x);
int main(void) {
    /* Costruisco input: 3 -> 5 -> 7 -> 2 -> 4 -> 1 -> 9 -> 10 -> 8 */
    int v[] = {3, 5, 7, 2, 4, 1, 9, 10, 8};
    int n = (int)(sizeof(v) / sizeof(v[0]));

    Lista L = NULL;
    for (int i = 0; i < n; i++) {
        L = pushBack(L, v[i]);
    }

    printf("Lista di input:\n");
    stampaLista(L);

    ListaDiListe out = partizionaCrescenti(L);

    printf("\nOutput (lista di liste):\n");
    if (out == NULL) {
        printf("(NULL)  <-- se qui è NULL, devi implementare partizionaCrescenti\n");
    } else {
        stampaListaDiListe(out);
    }

    /* Nota: la funzione NON deve modificare L */
    printf("\nLista di input DOPO la chiamata (deve essere identica):\n");
    stampaLista(L);

    /* Deallocazioni */
    freeLista(L);
    freeListaDiListe(out);

    return 0;
}

Lista copialista(Lista head, int x)
    {
        if(head==NULL)
            return NULL;
    Lista new=NULL;
    for(int i=0; i<x; i++)
        {
            new=inseriscincoda2(new, head->valore);
            head=head->next;
        }
    return new;
    }
void blocco(Lista start, int *count)
    {
        if(start==NULL || start->next==NULL)
            return;
    while (start!=NULL && start->next!=NULL && start->next->valore>start->valore) {
            (*count)++;
        start=start->next;
        }
    }
ListaDiListe inseriscincoda(ListaDiListe head, Lista sottolista, int x) // sottolista è l'inizio da dove copio
    {
        if(head==NULL)
            {
                ListaDiListe new=(ListaDiListe)malloc(sizeof(*new));
                new->next=NULL;
                new->sub=copialista(sottolista, x);
                return new;
            }
        head->next=inseriscincoda(head->next, sottolista, x);
        return head;
    }
ListaDiListe partizionaCrescenti(Lista head)
    {
    if(head==NULL)
        return NULL;
    Lista scorri=head;
    ListaDiListe new=NULL;
    while (scorri!=NULL) {
        int i=1;
        blocco(scorri, &i);
        new=inseriscincoda(new, scorri, i);
        for(int j=0; j<i; j++)
        {
            scorri=scorri->next;
        }
        }
    return new;
    }
Lista inseriscincoda2(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=NULL;
                new->valore=x;
                return new;
            }
    head->next=inseriscincoda2(head->next, x);
    return head;
    }
