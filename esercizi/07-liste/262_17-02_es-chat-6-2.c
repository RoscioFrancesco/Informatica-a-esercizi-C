//
//  main.c
//  es chat 6 -2
//
//  Created by Francesco Roscio Ricon on 17/02/26.

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int v;
    struct nodo *next;
} nodo;

typedef nodo* Lista;


void inserisciInCoda(Lista *l, int x);

/* =========================
   FUNZIONI DI SUPPORTO
   ========================= */

void stampaLista(Lista l) {
    while (l != NULL) {
        printf("%d", l->v);
        if (l->next != NULL)
            printf(" -> ");
        l = l->next;
    }
    printf("\n");
}

void liberaLista(Lista l) {
    while (l != NULL) {
        Lista tmp = l;
        l = l->next;
        free(tmp);
    }
}

int main() {

    Lista L = NULL;

    printf("Lista iniziale:\n");
    stampaLista(L);

    printf("\nInserimento 1:\n");
    int f=3;
    inserisciInCoda(&L, f);
    stampaLista(L);

    printf("\nInserimento 2:\n");
    int x=5;
    inserisciInCoda(&L, x);
    stampaLista(L);

    printf("\nInserimento 3:\n");
    int j=7;
    inserisciInCoda(&L, j);
    stampaLista(L);

    liberaLista(L);

    return 0;
}
void inserisciInCoda(Lista *l, int x)
    {
        if(*l==NULL)
        {
            Lista new=(Lista)malloc(sizeof(*new));
            new->next=NULL;
            new->v=x;
            *l=new;
            return;
        }
    inserisciInCoda(&(*l)->next, x);
    }
