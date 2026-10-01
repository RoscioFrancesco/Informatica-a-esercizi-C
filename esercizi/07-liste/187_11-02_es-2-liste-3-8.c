//
//  main.c
//  es 2 liste 3 -8
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

typedef struct nodoLista {
    int numDivisori;
    Lista sub;
    struct nodoLista *next;
} NodoLista;

typedef NodoLista * ListaDiListe;



ListaDiListe raggruppaPerDivisori(Lista L);


/* =========================
   FUNZIONI DI SUPPORTO
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
    while (cur->next != NULL)
        cur = cur->next;

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
    while (ll != NULL) {
        printf("[");
        Nodo *cur = ll->sub;
        while (cur != NULL) {
            printf("%d", cur->valore);
            if (cur->next != NULL) printf(" -> ");
            cur = cur->next;
        }
        printf("]   // %d divisori\n", ll->numDivisori);
        ll = ll->next;
    }
}

static void freeLista(Lista l) {
    while (l != NULL) {
        Nodo *tmp = l;
        l = l->next;
        free(tmp);
    }
}

static void freeListaDiListe(ListaDiListe ll) {
    while (ll != NULL) {
        NodoLista *tmp = ll;
        ll = ll->next;
        freeLista(tmp->sub);
        free(tmp);
    }
}
ListaDiListe crealdlincoda(ListaDiListe head, int num_div, int num);
int main(void) {

    /* Costruisco lista di input:
       4 -> 7 -> 6 -> 9 -> 5 -> 8
    */
    int valori[] = {4, 7, 6, 9, 5, 8};
    int n = sizeof(valori) / sizeof(valori[0]);

    Lista L = NULL;

    for (int i = 0; i < n; i++)
        L = pushBack(L, valori[i]);

    printf("Lista di input:\n");
    stampaLista(L);

    ListaDiListe risultato = raggruppaPerDivisori(L);

    if (risultato == NULL) {
        printf("(NULL) <-- devi implementare raggruppaPerDivisori\n");
    } else {
        stampaListaDiListe(risultato);
    }

    printf("\nLista originale dopo la chiamata (NON deve cambiare):\n");
    stampaLista(L);

    /* Deallocazioni */
    freeLista(L);
    freeListaDiListe(risultato);

    return 0;
}

int numerodivisori(int x)
    {
    int divisori=0;
    for(int i=1; i<=x; i++)
        {
            if(x%i==0)
                divisori++;
        }
    return divisori;
    }
ListaDiListe trova(ListaDiListe head, int div)
    {
    while (head!=NULL) {
        if(div==head->numDivisori)
            return head;
        head=head->next;
        }
    return NULL;
    }
Lista inseriscincoda(Lista head, int x)
    {
    if(head==NULL || x<head->valore)
        {
            Lista new=(Lista)malloc(sizeof(*new));
            new->next=head;
            new->valore=x;
            return new;
        }
    head->next=inseriscincoda(head->next, x);
    return head;
    }

ListaDiListe raggruppaPerDivisori(Lista head)
    {
        if(head==NULL)
            return NULL;
    Lista scorri=head;
    ListaDiListe new=NULL;
    while (scorri!=NULL) {
        int num_div=0;
        int num=scorri->valore;
        num_div=numerodivisori(num);
        ListaDiListe punt=trova(new, num_div);
        if(punt==NULL)
            {
                new=crealdlincoda(new, num_div, num);
            }
        else
            {
                punt->sub=inseriscincoda(punt->sub, num);
            }
        scorri=scorri->next;
    }
    return new;
    }
ListaDiListe crealdlincoda(ListaDiListe head, int num_div, int num)
    {
        if(head==NULL || num_div<head->numDivisori)
            {
                ListaDiListe new=(ListaDiListe)malloc(sizeof(*new));
                new->next=head;
                new->numDivisori=num_div;
                new->sub=NULL;
                new->sub=inseriscincoda(new->sub, num);
                return new;
            }
    head->next=crealdlincoda(head->next, num_div, num);
    return head;
    }
