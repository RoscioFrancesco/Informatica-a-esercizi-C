//  Created by Francesco Roscio Ricon on 09/02/26.

#include <stdio.h>
#include <stdlib.h>

/* =====================
   STRUTTURE DATI
   ===================== */
typedef struct EL {
    int dato;
    struct EL *next;
} nodo;

typedef nodo * lista;


lista cancellaElementiGrandi(lista l);

/* =====================
   FUNZIONI DI SUPPORTO
   ===================== */
lista inserisciInCoda(lista l, int x) {
    if (l == NULL) {
        lista new = (lista)malloc(sizeof(*new));
        new->dato = x;
        new->next = NULL;
        return new;
    }
    l->next = inserisciInCoda(l->next, x);
    return l;
}

void stampaLista(lista l) {
    while (l != NULL) {
        printf("%d -> ", l->dato);
        l = l->next;
    }
    printf("NULL\n");
}

void liberaLista(lista l) {
    while (l != NULL) {
        lista tmp = l;
        l = l->next;
        free(tmp);
    }
}

/* =====================
   MAIN DI TEST
   ===================== */
int sommaseguenti(lista head);
int main() {
    lista l = NULL;

    /* Input: 1 -> 40 -> 3 -> 15 -> 5 -> 6 */
    l = inserisciInCoda(l, 1);
    l = inserisciInCoda(l, 40);
    l = inserisciInCoda(l, 3);
    l = inserisciInCoda(l, 15);
    l = inserisciInCoda(l, 5);
    l = inserisciInCoda(l, 6);

    printf("Lista iniziale:\n");
    stampaLista(l);

    /* chiamata alla funzione da svolgere */
    l = cancellaElementiGrandi(l);

    printf("Lista dopo la cancellazione:\n");
    stampaLista(l);

    liberaLista(l);
    return 0;
}

/* =====================
   STUB DELLA FUNZIONE
   ===================== */
lista cancellaElementiGrandi(lista l) {
    if(l==NULL || l->next==NULL)
        return l;
    if(l->dato>sommaseguenti(l->next))
        {
            lista temp=l->next;
            l->next=NULL;
            free(l);
            return cancellaElementiGrandi(temp);
        }
    l->next=cancellaElementiGrandi(l->next);
    return l;
}
int sommaseguenti(lista head)
    {
        if(head==NULL)
            return 0;
    lista scorri=head;
    int somma=0;
    while (scorri!=NULL) {
        somma=somma+scorri->dato;
        scorri=scorri->next;
        }
    return somma;
    }
