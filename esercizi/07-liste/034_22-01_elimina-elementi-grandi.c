//  Created by Francesco Roscio Ricon on 22/01/26.

#include <stdio.h>
#include <stdlib.h>

typedef struct EL {
    int dato;
    struct EL *next;
} nodo;

typedef nodo *lista;

int verifcacondizione(lista punto);

lista inserisciInCoda(lista head, int val) {
    nodo *new = (nodo *)malloc(sizeof(nodo));
    new->dato = val;
    new->next = NULL;

    if (head == NULL) return new;

    nodo *p = head;
    while (p->next != NULL)
        p = p->next;

    p->next = new;
    return head;
}

void stampaLista(lista l) {
    while (l != NULL) {
        printf("%d -> ", l->dato);
        l = l->next;
    }
    printf("NULL\n");
}

/* ===== Prototipo funzione dell'esercizio ===== */
lista cancellaElementiGrandi(lista l);

int main() {
    lista l = NULL;

    /* Lista di input: 1 -> 40 -> 3 -> 15 -> 5 -> 6 -> NULL */
    l = inserisciInCoda(l, 1);
    l = inserisciInCoda(l, 40);
    l = inserisciInCoda(l, 3);
    l = inserisciInCoda(l, 15);
    l = inserisciInCoda(l, 5);
    l = inserisciInCoda(l, 6);

    printf("Lista iniziale: ");
    stampaLista(l);

    l = cancellaElementiGrandi(l);

    printf("Lista dopo cancellaElementiGrandiiandi: ");
    stampaLista(l);

    /* Output atteso: 1 -> 3 -> 5 -> 6 -> NULL */

    return 0;
}


int verifcacondizione(lista punto)
    {
    if(punto==NULL)
        return 0;
    if(punto->next==0)
        return 0;
    int valore=punto->dato;
    punto=punto->next;
    int somma=0;
    while(punto!=NULL)
        {
            somma=somma+punto->dato;
            punto=punto->next;
        }
    if(valore>somma)
        return 1;
    return 0;
    }

lista cancellaElementiGrandi(lista head)
    {
    lista scorrilista=head;
    lista prec=NULL;
    while (scorrilista!=NULL) {
        lista scorrilistasucc=scorrilista->next;
        if(verifcacondizione(scorrilista))
            {
                if(prec==NULL)
                    {
                        head=scorrilistasucc;
                        free(scorrilista);
                        scorrilista=head;
                    }
                else
                    {
                        prec->next=scorrilistasucc;
                        free(scorrilista);
                        scorrilista=scorrilistasucc;
                    }
            }
        else
        {
            prec=scorrilista;
            scorrilista=scorrilistasucc;
        }
    }
    return head;
    }
