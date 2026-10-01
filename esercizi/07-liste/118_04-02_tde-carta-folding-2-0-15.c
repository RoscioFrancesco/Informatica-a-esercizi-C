//
//  main.c
//  tde carta folding 2.0 -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct EL {
    int dato;
    struct EL *next;
} nodo;

typedef nodo* lista;


lista folding(lista head); /* TODO */

/* =========================
   UTILITY (per test: cicli OK)
   ========================= */
static lista newNode(int x, lista next) {
    lista n = (lista)malloc(sizeof(nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = x;
    n->next = next;
    return n;
}

/* costruisce lista da array mantenendo l'ordine */
static lista fromArray(const int a[], int n) {
    lista l = NULL;
    for (int i = n - 1; i >= 0; --i)
        l = newNode(a[i], l);
    return l;
}

static void printLista(lista l) {
    while (l != NULL) {
        printf("%d -> ", l->dato);
        l = l->next;
    }
    printf("NULL\n");
}

static void freeLista(lista l) {
    while (l != NULL) {
        lista tmp = l->next;
        free(l);
        l = tmp;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
void merge(lista l1, lista l2);
void stampa(lista l1);
void trovacentro(lista head, lista *l1, lista *l2);
void f(lista head, lista *scorri, lista *new, int *count);
lista invertilista(lista head);
int main(void) {
    int a1[] = {1,2,3,4,5,6};
    lista l1 = fromArray(a1, 6);

    printf("IN : ");
    printLista(l1);
    
    lista prima=NULL;
    lista seconda=NULL;
    trovacentro(l1, &prima, &seconda);
    printLista(prima);
    seconda=invertilista(seconda);
    printLista(seconda);
    merge(prima, seconda);
    printLista(prima);

//    printf("\nIN : ");
//    printLista(l2);
//
//    l2 = folding(l2);
//
//    printf("OUT: ");
//    printLista(l2);
//
//    freeLista(l2);
//
//    return 0;
}
//In: 1  2  3  4  5  6  NULL
//    Out: 1  6  2  5  3  4  NULL


//La soluzione classica è:
//
//trova il centro (slow/fast)
//
//taglia la lista in due metà
//
//inverte la seconda metà
//
//intreccia (merge alternato) prima metà + seconda invertita

void trovacentro(lista head, lista *l1, lista *l2)
    {
    lista slow=head;
    lista fast=head;
    lista prev=NULL;
    *l1=head;
    while (fast!=NULL) {
        prev=slow;
        slow=slow->next;
        fast=fast->next->next;
        }
    *l2=slow;
    prev->next=NULL;
    }
void stampa(lista l1)
    {
    lista scorri=l1;
    while(scorri!=NULL)
        {
            printf("%d-->", scorri->dato);
            scorri=scorri->next;
        }
    }
lista invertilista(lista head)
    {
        if(head==NULL || head->next==NULL)
            {
                return head;
            }
        lista temp=invertilista(head->next);
        head->next->next=head;
        head->next=NULL;
        return temp;
    }

void merge(lista l1, lista l2)
    {
        if(l1==NULL || l2==NULL)
            return;
        lista l1_next=l1->next;
        lista l2_next=l2->next;
        l1->next=l2;
        l2->next=l1_next;
    merge(l1_next, l2_next);
    }
