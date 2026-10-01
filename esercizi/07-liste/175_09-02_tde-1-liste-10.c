//
//  main.c
//  tde 1 liste -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//


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


lista intreccia(lista lis1, lista lis2);

/* =====================
   FUNZIONI DI SUPPORTO
   ===================== */
lista inserisciInCoda(lista l, int val) {
    if (l == NULL) {
        lista nuovo = (lista)malloc(sizeof(nodo));
        nuovo->dato = val;
        nuovo->next = NULL;
        return nuovo;
    }
    l->next = inserisciInCoda(l->next, val);
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
lista inserisciincoda(lista head, int x);
int len(lista head);

int main() {
    lista lis1 = NULL;
    lista lis2 = NULL;
    lista risultato;

    /* lis1: 1 -> 2 -> 3 -> 4 -> 5 -> 6 */
    lis1 = inserisciInCoda(lis1, 1);
    lis1 = inserisciInCoda(lis1, 2);
    lis1 = inserisciInCoda(lis1, 3);
    lis1 = inserisciInCoda(lis1, 4);
    lis1 = inserisciInCoda(lis1, 5);
    lis1 = inserisciInCoda(lis1, 6);

    /* lis2: 7 -> 8 -> 9 -> 10 */
    lis2 = inserisciInCoda(lis2, 7);
    lis2 = inserisciInCoda(lis2, 8);
    lis2 = inserisciInCoda(lis2, 9);
    lis2 = inserisciInCoda(lis2, 10);

    printf("Lista 1: ");
    stampaLista(lis1);

    printf("Lista 2: ");
    stampaLista(lis2);

    /* chiamata alla funzione da svolgere */
    risultato = intreccia(lis1, lis2);

    printf("Lista intrecciata: ");
    stampaLista(risultato);

    liberaLista(risultato);

    return 0;
}

/* =====================
   STUB DELLA FUNZIONE
   ===================== */
lista intreccia(lista lis1, lista lis2) {
    int lungh1=len(lis1);
    int lungh2=len(lis2);
    lista new=NULL;
    int i=0;
    for(i=0; i<lungh1 && i<lungh2; i++)
        {
            new=inserisciincoda(new, lis1->dato);
            new=inserisciincoda(new, lis2->dato);
            lis1=lis1->next;
            lis2=lis2->next;
        }
    if(i==lungh1)
    {
        for(; i<lungh2; i++)
        {
            new=inserisciincoda(new, lis2->dato);
            lis2=lis2->next;
        }
    }
    else
        {
            for(; i<lungh1; i++)
                {
                    new=inserisciincoda(new, lis1->dato);
                    lis1=lis1->next;
                }
        }
    return new;
}
lista inserisciincoda(lista head, int x)
    {
        if(head==NULL)
            {
                lista new=(lista)malloc(sizeof(*new));
                new->next=NULL;
                new->dato=x;
                return new;
            }
        head->next=inserisciincoda(head->next, x);
        return head;
    }
int len(lista head)
    {int i=0;
    while (head!=NULL) {
        head=head->next;
        i++;
    }
    return i;
    }
