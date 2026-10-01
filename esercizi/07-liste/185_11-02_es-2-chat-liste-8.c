//
//  main.c
//  es 2 chat liste  -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int valore;
    struct nodo *next;
} Nodo;

typedef Nodo *Lista;


int listaIperCrescente(Lista l);
int correggiIperCrescente(Lista l);

/* ===== UTILITY PER TEST ===== */
static Nodo *nuovoNodo(int v) {
    Nodo *n = (Nodo*)malloc(sizeof(*n));
    if(!n){ perror("malloc"); exit(1); }
    n->valore = v;
    n->next = NULL;
    return n;
}

static void pushBack(Lista *l, int v) {
    Nodo *n = nuovoNodo(v);
    if(*l == NULL) { *l = n; return; }
    Nodo *c = *l;
    while(c->next) c = c->next;
    c->next = n;
}

static void stampaLista(const char *label, Lista l) {
    printf("%s: ", label);
    while(l) {
        printf("%d", l->valore);
        if(l->next) printf(" -> ");
        l = l->next;
    }
    printf(" -> NULL\n");
}

static void freeLista(Lista l) {
    while(l) {
        Nodo *nx = l->next;
        free(l);
        l = nx;
    }
}

/* ===== MAIN DI TEST ===== */
int main(void) {
    Lista l1 = NULL;
    
    pushBack(&l1, 3);
    pushBack(&l1, 3);
    pushBack(&l1, 4);
    pushBack(&l1, 4);
    pushBack(&l1, 6);

    stampaLista("Lista iniziale l1", l1);

    printf("listaIperCrescente(l1) = %d\n", listaIperCrescente(l1));

    /* corregge in-place e ritorna la somma degli incrementi */
    int sommaInc = correggiIperCrescente(l1);
    printf("correggiIperCrescente(l1) ha incrementato in totale di: %d\n", sommaInc);

    stampaLista("Lista corretta l1", l1);
    printf("listaIperCrescente(l1) = %d\n", listaIperCrescente(l1));

    printf("\n");

    /* Altro test: già (quasi) crescente, per vedere incrementi piccoli */
    Lista l2 = NULL;
    pushBack(&l2, 0);
    pushBack(&l2, 1);
    pushBack(&l2, 3);
    pushBack(&l2, 6);
    pushBack(&l2, 10);

    stampaLista("Lista iniziale l2", l2);
    printf("listaIperCrescente(l2) = %d\n", listaIperCrescente(l2));
    sommaInc = correggiIperCrescente(l2);
    printf("correggiIperCrescente(l2) ha incrementato in totale di: %d\n", sommaInc);
    stampaLista("Lista corretta l2", l2);
    printf("listaIperCrescente(l2) = %d\n", listaIperCrescente(l2));

    freeLista(l1);
    freeLista(l2);
    return 0;
}
//successivo ≥ (valore corrente + numero di nodi precedenti)
int listaIperCrescente(Lista l)
    {
    if(l==NULL || l->next==NULL)
        return 1;
    int count=1;
    Lista scorri=l;
    while (scorri->next!=NULL) {
        if(scorri->next->valore<(scorri->valore+count))
            return 0;
        count++;
        scorri=scorri->next;
    }
    return 1;
    }
int correggiIperCrescente(Lista l)
    {
    Lista scorri=l;
    int somma=0;
    int count=1;
    while (scorri->next!=NULL) {
        if(scorri->next->valore<(scorri->valore+count)){
            int temp=scorri->next->valore;
            scorri->next->valore=scorri->valore+count;
            somma=somma+scorri->valore+count-temp;
        }
        count++;
        scorri=scorri->next;
        }
        return somma;
    }
