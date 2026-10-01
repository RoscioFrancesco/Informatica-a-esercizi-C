//
//  main.c
//  media mobile -12
//
//  Created by Francesco Roscio Ricon on 07/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA LISTA
   ========================= */
typedef struct nodo {
    float valore;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;


Lista mediaMobile(Lista L, int N);

/* =========================
   FUNZIONI DI SUPPORTO
   (solo per costruire e stampare)
   ========================= */
Lista inserisciInCoda(Lista head, float val) {
    if (head == NULL) {
        Lista nuovo = malloc(sizeof(Nodo));
        nuovo->valore = val;
        nuovo->next = NULL;
        return nuovo;
    }
    head->next = inserisciInCoda(head->next, val);
    return head;
}

void stampaLista(Lista L) {
    while (L != NULL) {
        printf("%.2f ", L->valore);
        L = L->next;
    }
    printf("\n");
}

/* =========================
   MAIN DI TEST
   ========================= */
Lista mediaMobile_2(Lista l, int finestra, float tot, int quanti, Lista last);
int main() {
    Lista L = NULL;
    Lista risultato;
    int N = 3;

    /* lista di esempio: 10 2 3 13 101 */
    L = inserisciInCoda(L, 10);
    L = inserisciInCoda(L, 2);
    L = inserisciInCoda(L, 3);
    L = inserisciInCoda(L, 13);
    L = inserisciInCoda(L, 101);

    printf("Lista originale:\n");
    stampaLista(L);

    risultato = mediaMobile(L, N);

    printf("Lista media mobile (N = %d):\n", N);
    stampaLista(risultato);

    return 0;
}

Lista mediaMobile(Lista l, int finestra)
    {
    return mediaMobile_2(l, finestra, 0, 0, l);
    }


Lista mediaMobile_2(Lista l, int finestra, float tot, int quanti, Lista last)
{
    if(l==NULL)
        return NULL;
    Lista nuovo=(Lista)malloc(sizeof(*nuovo));
    if(quanti==finestra)
    {
        tot=tot-last->valore;
        last=last->next;
    }
    else
    {
        quanti++;
    }
        tot=tot+l->valore;
        printf("tot:%f\n",tot);
        nuovo->valore=tot/quanti;
        nuovo->next=mediaMobile_2(l->next, finestra, tot, quanti, last);
        return nuovo;
}
