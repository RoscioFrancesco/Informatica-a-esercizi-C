//
//  main.c
//  elimina i duplicati in una lista
//
//  Created by Francesco Roscio Ricon on 24/01/26.
//

#include <stdio.h>
#include <stdlib.h>

// ====== STRUTTURA NODO ======
typedef struct nodo {
    int val;
    struct nodo* next;
} Nodo;

typedef Nodo* Lista;
// ====== PROTOTIPI FUNZIONI ======
Nodo* inserisciCoda(Nodo* head, int val);
void liberaLista(Nodo* head);

Lista eliminaduplicati(Lista head);
void stampalista(Lista head);


// ====== MAIN ======
int main() {

    // ---------- TEST ITERATIVO ----------
   Lista lista1 = NULL;

    // lista con duplicati: 3 -> 5 -> 3 -> 7 -> 5 -> 5 -> 9 -> 3
    lista1 = inserisciCoda(lista1, 3);
    lista1 = inserisciCoda(lista1, 5);
    lista1 = inserisciCoda(lista1, 3);
    lista1 = inserisciCoda(lista1, 7);
    lista1 = inserisciCoda(lista1, 5);
    lista1 = inserisciCoda(lista1, 5);
    lista1 = inserisciCoda(lista1, 9);
    lista1 = inserisciCoda(lista1, 3);

    printf("Lista iniziale (ITERATIVO):\n");
    stampalista(lista1);

    lista1 = eliminaduplicati(lista1);

    printf("\nLista senza duplicati (ITERATIVO):\n");
    stampalista(lista1);

    liberaLista(lista1);


}


// ====== FUNZIONI DI SUPPORTO ======
Nodo* inserisciCoda(Nodo* head, int val) {
    Nodo* nuovo = (Nodo*)malloc(sizeof(Nodo));
    nuovo->val = val;
    nuovo->next = NULL;

    if (head == NULL) return nuovo;

    Nodo* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = nuovo;
    return head;
}


void liberaLista(Nodo* head) {
    Nodo* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int trovato(Lista head, int val)
    {
    Lista scorrilista=head;
    while (scorrilista!=NULL) {
        if(scorrilista->val==val)
            return 1;
        scorrilista=scorrilista->next;
    }
    return 0;
}

Lista eliminaduplicati(Lista head)
    {
    Lista scorrilista=head;
    Lista prec=NULL;
    while (scorrilista != NULL && scorrilista->next != NULL) {
        Lista succ=scorrilista->next;
        if(trovato(succ, scorrilista->val))
            {
               if(scorrilista==head)
                    {
                        head=succ;
                        free(scorrilista);
                        scorrilista=head;
                    }
                else
                    {
                        prec->next=succ;
                        free(scorrilista);
                        scorrilista=succ;
                    }
            }
        else
        {
            prec=scorrilista;
            scorrilista=succ;
        }
    }
    return head;
    }
void stampalista(Lista head)
    {
    while(head!=NULL)
        {
            printf("%d--> ", head->val);
            head=head->next;
        }
}
