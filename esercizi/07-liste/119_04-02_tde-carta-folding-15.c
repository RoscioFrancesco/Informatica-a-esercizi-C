//
//  main.c
//  tde carta folding -15
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
void f(lista head, lista *scorri, lista *new, int *count);
int main(void) {
    int a1[] = {1,2,3,4,5,6};
    lista l1 = fromArray(a1, 6);

    printf("IN : ");
    printLista(l1);

    l1 = folding(l1);   

    printf("OUT: ");
    printLista(l1);

    freeLista(l1);

    /* altro test: lista dispari */
    int a2[] = {1,2,3,4,5, 6};
    lista l2 = fromArray(a2, 6);

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
lista inseriscincoda(lista head, int x)
    {
        if(head==NULL)
            {
                lista new=(lista)malloc(sizeof(*new));
                new->next=NULL;
                new->dato=x;
                return new;
            }
        head->next=inseriscincoda(head->next, x);
        return head;
    }
void f(lista head, lista *scorri, lista *new, int *count)
    {
        if(head==NULL)
            return;
        if(*scorri==NULL)
            return;
        f(head->next, scorri, new, count);
        if(*count%2==1)
            {
                printf("\n dato: %d", (*scorri)->dato);
                *new=inseriscincoda(*new, (*scorri)->dato);
                (*scorri)=(*scorri)->next;
                (*count)++;
            }
        else
            {
                printf("\n\nhead prima : %d", (head)->dato);
                for(int i=0; i<*count/2; i++)
                    head=head->next;
                printf("\ncount=%d", *count);
                printf("\nhead dopo: %d", (head)->dato);
                *new=inseriscincoda(*new, head->dato);
                (*count)++;
            }
    }
lista folding(lista head)
    {
    lista new=NULL;
    lista scorri=head;
    int count=1;
    f(head,&scorri , &new, &count);
    return new;
    }
