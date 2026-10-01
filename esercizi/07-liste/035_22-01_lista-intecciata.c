//  Created by Francesco Roscio Ricon on 22/01/26.
#include <stdio.h>
#include <stdlib.h>

typedef struct EL {
    int dato;
    struct EL *next;
} nodo;

typedef nodo * lista;

lista inerisciincoda(lista head, int val);

lista inserisciInCoda(lista head, int valore) {
    nodo *new = (nodo *)malloc(sizeof(nodo));
    new->dato = valore;
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

/* ===== prototipo funzione dell'esercizio ===== */

lista intreccia(lista lista1, lista lista2);
lista insericiinmezzo(lista prec, lista succ, int val, lista head);

int main() {
    lista lis1 = NULL;
    lista lis2 = NULL;

    /* lis1: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> NULL */
    lis1 = inserisciInCoda(lis1, 1);
    lis1 = inserisciInCoda(lis1, 2);
    lis1 = inserisciInCoda(lis1, 3);
    lis1 = inserisciInCoda(lis1, 4);
    lis1 = inserisciInCoda(lis1, 5);
    lis1 = inserisciInCoda(lis1, 6);

    /* lis2: 7 -> 8 -> 9 -> 10 -> NULL */
    lis2 = inserisciInCoda(lis2, 7);
    lis2 = inserisciInCoda(lis2, 8);
    lis2 = inserisciInCoda(lis2, 9);
    lis2 = inserisciInCoda(lis2, 10);

    printf("Lista 1: ");
    stampaLista(lis1);

    printf("Lista 2: ");
    stampaLista(lis2);

    lista res = intreccia(lis1, lis2);

    printf("\nLista intrecciata: ");
    stampaLista(res);

    return 0;
}

lista intreccia(lista lista1, lista lista2)
    {
    lista scorrilista1=lista1;
    lista scorrilista2=lista2;
    lista new=NULL;
    int flag=0;
        while(scorrilista2!=NULL && scorrilista1!=NULL)
            {

                if(flag%2==0)
                {
                    new=inerisciincoda(new, scorrilista1->dato);
                    scorrilista1=scorrilista1->next;
                }
                else
                {
                    new=inerisciincoda(new, scorrilista2->dato);
                    scorrilista2=scorrilista2->next;
                }
                flag=flag+1;
                
            }
    if(scorrilista2==NULL)
        {
            lista scorrinew=new;
            while (scorrinew->next!=NULL) {
                scorrinew=scorrinew->next;
            }
            scorrinew->next=scorrilista1;
            return new;
        }
    if(scorrilista1==NULL)
        {
            lista scorrinew=new;
            while (scorrinew->next!=NULL) {
                scorrinew=scorrinew->next;
            }
            scorrinew->next=scorrilista2;
            return new;
        }
    return new;
    }
lista inerisciincoda(lista head, int val)
    {
    lista new=(lista)malloc(sizeof(nodo));
    new->dato=val;
    new->next=NULL;
    if(head==NULL)
        {
            return new;
        }
    lista scorrilista=head;
    while (scorrilista->next!=NULL){
        scorrilista=scorrilista->next;
    }
    scorrilista->next=new;
    return head;
    }
