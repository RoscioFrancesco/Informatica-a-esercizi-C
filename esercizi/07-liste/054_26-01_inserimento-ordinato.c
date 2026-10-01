//
//  main.c
//  inserimento ordinato
//
//  Created by Francesco Roscio Ricon on 26/01/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

/*** PROTOTIPI ***/
Lista inserimentoOrdinatoRic(Lista l, int x);
void stampaLista(Lista l);
void freeLista(Lista l);

/*** INSERIMENTO ORDINATO RICORSIVO (crescente) ***/
Lista inserimentoOrdinatoRic(Lista l, int x) {
    if(l==NULL || x>l->val)
        {
            Lista new=(Lista)malloc(sizeof(Nodo));
            if(new==NULL)
                return l;
            new->val=x;
            new->next=l;
            return new;
        }
    l->next=inserimentoOrdinatoRic(l->next, x);
    return l;
    }

void stampaLista(Lista l) {
    while (l != NULL) {
        printf("%d -> ", l->val);
        l = l->next;
    }
    printf("NULL\n");
}

void freeLista(Lista l) {
    while (l != NULL) {
        Nodo *tmp = l;
        l = l->next;
        free(tmp);
    }
}

/*** MAIN ***/
int main() {
    Lista l = NULL;

    int valori[] = {5, 2, 9, 1, 5, 7, 3};
    int n = sizeof(valori) / sizeof(valori[0]);

    printf("Inserimenti (ordinati) in lista:\n");

    for (int i = 0; i < n; i++) {
        printf("\nInserisco %d\n", valori[i]);
        l = inserimentoOrdinatoRic(l, valori[i]);
        stampaLista(l);
    }

    freeLista(l);
    return 0;
}
