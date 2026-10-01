//
//  main.c
//  es 5 chat int -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo* next;
} Nodo;

typedef Nodo* lista;

lista eliminaBlocchiPari(lista L);
lista inserisciInCoda(lista L, int x) {
    if (L == NULL) {
        lista nuovo = (lista)malloc(sizeof(Nodo));
        nuovo->dato = x;
        nuovo->next = NULL;
        return nuovo;
    }
    L->next = inserisciInCoda(L->next, x);
    return L;
}

void stampaLista(lista L) {
    while (L != NULL) {
        printf("%d", L->dato);
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


int main() {

    lista L = NULL;

    /* TEST PRINCIPALE */
    L = inserisciInCoda(L, 3);
    L = inserisciInCoda(L, 4);
    L = inserisciInCoda(L, 6);
    L = inserisciInCoda(L, 8);
    L = inserisciInCoda(L, 5);
    L = inserisciInCoda(L, 2);
    L = inserisciInCoda(L, 10);
    L = inserisciInCoda(L, 7);

    printf("Lista iniziale:\n");
    stampaLista(L);

    L = eliminaBlocchiPari(L);

    printf("Lista dopo eliminazione:\n");
    stampaLista(L);

    liberaLista(L);

    return 0;
}
// qua non devo eliminare gli estremi dispari
int contablocchi(lista head)
    {
        if(head==NULL)
            return 0;
        head=head->next;
        int count=0;
        while(head!=NULL)
            {
                if(head->dato%2==1)
                    break;
                count ++;
                head=head->next;
            }
        return count;
    }
lista eliminak(lista head, int k)
    {
        if(head==NULL)
            return head;
        head=head->next;
        for(int i=0; i<k; i++)
            {
                lista succ=head->next;
                free(head);
                head=succ;
            }
        return head;
    }
void f(lista *l)
    {
        if(*l==NULL)
            return;
    lista *pp=l;
        while(*pp!=NULL)
            {
                if((*pp)->dato%2==1)
                    {
                        int val=contablocchi(*pp);
                        if(val>0)
                            {
                                (*pp)->next=eliminak((*pp), val);
                                pp=&(*pp)->next;
                            }
                        else
                            {
                                pp=&(*pp)->next;
                            }
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
lista eliminaBlocchiPari(lista L) {
    f(&L);
    return L;
}
