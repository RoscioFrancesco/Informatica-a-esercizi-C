//  Created by Francesco Roscio Ricon on 22/01/26.

#include <stdio.h>
#include <stdlib.h>

typedef struct EL {
    int dato;
    struct EL *next;
} nodo;

typedef nodo *lista;

/* ===== funzioni di supporto ===== */

lista inserisciInCoda(lista head, int val) {
    nodo *new = (nodo *)malloc(sizeof(nodo));
    if (!new) exit(1);

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

lista cancellaelementi(lista head);


int main(void) {
    lista l = NULL;

    /* Input: 1 -> 40 -> 15 -> 16 -> 3 -> 15 -> 5 -> 6 -> NULL */
    l = inserisciInCoda(l, 1);
    l = inserisciInCoda(l, 40);
    l = inserisciInCoda(l, 15);
    l = inserisciInCoda(l, 16);
    l = inserisciInCoda(l, 3);
    l = inserisciInCoda(l, 15);
    l = inserisciInCoda(l, 5);
    l = inserisciInCoda(l, 6);

    printf("Lista iniziale: ");
    stampaLista(l);

    l = cancellaelementi(l);

    printf("Lista dopo cancellaTriplette: ");
    stampaLista(l);

    /* Output atteso: 1 -> 40 -> 15 -> 16 -> 6 -> NULL */

    return 0;
}

lista cancellaelementi(lista head)
    {
        if(head==NULL)
            return head;
    lista scorrilista=head;
    lista prec=NULL;
    while(scorrilista!=NULL)
    {
        if(scorrilista->dato%2==1)
        {
            int contatore=0;
            lista puntatore=scorrilista;
            while(puntatore!=NULL && puntatore->dato%2==1)
            {
                contatore++;
                puntatore=puntatore->next;
            }
            if(contatore>=3){
                if(prec==NULL)
                {
                    lista temp=head;
                    head=puntatore;
                    while(temp!=head)
                        {
                            lista temp2=temp;
                            temp=temp->next;
                            free(temp2);
                        }
                    scorrilista=puntatore;
                }
                else
                {
                    lista temp=prec->next;
                    while(temp!=puntatore)
                        {
                            lista temp2=temp;
                            temp=temp->next;
                            free(temp2);
                        }
                    prec->next=puntatore;
                    scorrilista=puntatore;
                }
            }
            else {
                prec=scorrilista;
                scorrilista=scorrilista->next;
            }
        }
        else
        {
            prec=scorrilista;
            scorrilista=scorrilista->next;
        }
    }
    return head;
    }


