//
//  main.c
//  liste 2 pag 49 -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//

//La funzione … ds( … ) calcola la differenza simmetrica degli
//elementi di due liste ordinate in senso crescente e prive di
//duplicati, restituendola come una nuova lista (allocata allo
//scopo), anch'essa ordinata. La differenza simmetrica è
//costituita dagli elementi che appartengono a una delle due
//liste ma non all'altra lista (contiene cioè tutti gli elementi che
//non sono in comune alle due liste).

#include <stdio.h>
#include <stdlib.h>

typedef struct N {
    int valore;
    struct N *next;
} Nodo;

typedef Nodo * Lista;


Lista ds(Lista l1, Lista l2);

Lista inserisciInCoda(Lista head, int v) {
    if (head == NULL) {
        Lista nuovo = (Lista)malloc(sizeof(Nodo));
        nuovo->valore = v;
        nuovo->next = NULL;
        return nuovo;
    }
    head->next = inserisciInCoda(head->next, v);
    return head;
}

void stampaLista(Lista l) {
    while (l != NULL) {
        printf("%d -> ", l->valore);
        l = l->next;
    }
    printf("NULL\n");
}

void liberaLista(Lista l) {
    while (l != NULL) {
        Lista tmp = l;
        l = l->next;
        free(tmp);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int trova(Lista head, int x);
Lista inserimentoordinato(Lista head, int x);

int main() {
    Lista L1 = NULL;
    Lista L2 = NULL;
    Lista risultato = NULL;

    /* Lista 1: 1 3 5 7 */
    L1 = inserisciInCoda(L1, 1);
    L1 = inserisciInCoda(L1, 3);
    L1 = inserisciInCoda(L1, 5);
    L1 = inserisciInCoda(L1, 7);

    /* Lista 2: 3 4 7 9 */
    L2 = inserisciInCoda(L2, 3);
    L2 = inserisciInCoda(L2, 4);
    L2 = inserisciInCoda(L2, 7);
    L2 = inserisciInCoda(L2, 9);

    printf("Lista 1: ");
    stampaLista(L1);

    printf("Lista 2: ");
    stampaLista(L2);

    /* Chiamata alla funzione richiesta */
    risultato = ds(L1, L2);

    printf("Differenza simmetrica: ");
    stampaLista(risultato);

    liberaLista(L1);
    liberaLista(L2);
    liberaLista(risultato);

    return 0;
}
Lista inserimentoordinato(Lista head, int x)
    {
        if(head==NULL || x<head->valore)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=head;
                new->valore=x;
                return new;
            }
        head->next=inserimentoordinato(head->next, x);
        return head;
    }
int trova(Lista head, int x)
    {
        if(head==NULL)
            return 0;
    while (head!=NULL)
        {
            if(head->valore==x)
                return 1;
            head=head->next;
        }
    return 0;
    }
Lista ds(Lista l1, Lista l2)
    {
    Lista new=NULL;
    Lista scorril1=l1;
        while(scorril1!=NULL)
            {
                if(trova(l2, scorril1->valore)==0)
                    {
                        new=inserimentoordinato(new, scorril1->valore);
                    }
                scorril1=scorril1->next;
            }
    Lista scorril2=l2;
        while(scorril2!=NULL)
            {
                if(trova(l1, scorril2->valore)==0)
                    {
                        new=inserimentoordinato(new, scorril2->valore);
                    }
                scorril2=scorril2->next;
            }
        return new;
    }
