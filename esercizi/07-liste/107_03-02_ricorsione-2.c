//
//  main.c
//  ricorsione 2
//
//  Created by Francesco Roscio Ricon on 03/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA LISTA
   ========================= */

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef Node* Lista;

/* =========================
   PROTOTIPO (DA SVOLGERE)
   ========================= */

/*
   Elimina ricorsivamente tutti i nodi
   il cui valore è maggiore del valore
   del nodo successivo.
   Vietati cicli.
*/
Lista eliminaMaggioriDelSuccessivo(Lista head);

/* =========================
   UTILITY (QUI I CICLI SONO OK)
   ========================= */

static Lista push_back(Lista l, int x) {
    if (l == NULL) {
        Lista n = malloc(sizeof(Node));
        if (!n) { perror("malloc"); exit(1); }
        n->val = x;
        n->next = NULL;
        return n;
    }
    l->next = push_back(l->next, x);
    return l;
}

static void printLista(Lista l) {
    printf("[ ");
    while (l != NULL) {
        printf("%d ", l->val);
        l = l->next;
    }
    printf("]\n");
}

static void freeLista(Lista l) {
    if (l == NULL) return;
    freeLista(l->next);
    free(l);
}

/* =========================
   MAIN DI TEST
   ========================= */

int main(void) {

    Lista l = NULL;

    /* Lista di esempio:
       5 -> 3 -> 7 -> 2 -> 9
    */
    l = push_back(l, 5);
    l = push_back(l, 3);
    l = push_back(l, 7);
    l = push_back(l, 2);
    l = push_back(l, 9);

    printf("Lista iniziale: ");
    printLista(l);

    l = eliminaMaggioriDelSuccessivo(l);

    printf("Lista dopo eliminazione: ");
    printLista(l);

    freeLista(l);
    return 0;
}
Lista eliminaMaggioriDelSuccessivo(Lista head)
    {
        if(head==NULL || head->next==NULL)
            return head;
    head->next=eliminaMaggioriDelSuccessivo(head->next);
        if(head->val>head->next->val)
            {
                Lista temp=head->next;
                free(head);
                return eliminaMaggioriDelSuccessivo(temp);
            }
        return head;
    }
