//
//  main.c
//  es 1 prima
//
//  Created by Francesco Roscio Ricon on 19/02/26.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct nodo {
    int valore;
    struct nodo *next;
} nodo;

typedef nodo* lista;

/* =========================
   FUNZIONI DI SUPPORTO
   ========================= */

lista inserisciInCoda(lista L, int x) {
    if (L == NULL) {
        lista nuovo = (lista)malloc(sizeof(nodo));
        nuovo->valore = x;
        nuovo->next = NULL;
        return nuovo;
    }
    L->next = inserisciInCoda(L->next, x);
    return L;
}

void stampaLista(lista L) {
    while (L != NULL) {
        printf("%d", L->valore);
        if (L->next != NULL)
            printf(" -> ");
        L = L->next;
    }
    printf("\n");
}

void liberaLista(lista L) {
    while (L != NULL) {
        lista tmp = L;
        L = L->next;
        free(tmp);
    }
}



lista espandiNegativi(lista L);

lista pulisci(lista head);
lista f(lista head);
int main() {

    lista L = NULL;

    /* Test 1 */
    L = inserisciInCoda(L, -2);
    L = inserisciInCoda(L, 3);
    L = inserisciInCoda(L, 5);
    L = inserisciInCoda(L, -3);
    L = inserisciInCoda(L, 1);

    printf("Lista originale:\n");
    stampaLista(L);

    L = f(L);

    printf("Lista trasformata:\n");
    stampaLista(L);

    liberaLista(L);

    return 0;
}
lista inserisciincoda(lista head, int x)
    {
        if(head==NULL)
            {
                lista new=(lista)malloc(sizeof(nodo));
                new->valore=x;
                new->next=NULL;
                return new;
            }
    head->next=inserisciincoda(head->next, x);
    return head;
    }
lista creablocco(lista head, int num)
    {
        num=-num;
    for(int i=0; i<num; i++)
        {
            head=inserisciincoda(head, 1);
        }
    return head;
    }

lista f(lista head)
    {
        if(head==NULL)
            return head;
        lista scorri=head;
    lista prec=NULL;
    while (scorri!=NULL) {
        lista succ=scorri->next;
        if(scorri->valore<0)
            {
                lista blocco=NULL;
                blocco=creablocco(blocco, scorri->valore);
                stampaLista(blocco);
                if(prec==NULL)
                    {
                        lista scorri_blocco=blocco;
                        while(scorri_blocco!=NULL && scorri_blocco->next!=NULL)
                            {
                                scorri_blocco=scorri_blocco->next;
                            }
                        scorri_blocco->next=head;
                        head=blocco;
                        prec=scorri_blocco;
                        scorri=scorri->next;
                    }
                else
                    {
                        scorri->next=blocco;
                        lista scorri_blocco=blocco;
                        while(scorri_blocco!=NULL && scorri_blocco->next!=NULL)
                            {
                                scorri_blocco=scorri_blocco->next;
                            }
                        scorri_blocco->next=succ;
                        prec=scorri;
                        scorri=scorri->next;
                    }
            }
        else
            {
                prec=scorri;
                scorri=succ;
            }
        }
    head=pulisci(head);
    return head;
    }
lista pulisci(lista head)
    {
        if(head==NULL)
            return head;
        if(head->valore<0)
            {
                lista temp=head->next;
                free(head);
                head=temp;
                return pulisci(head);
            }
    head->next=pulisci(head->next);
    return head;
    }
