//
//  main.c
//  es 6 chat int -5
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


/* =====================================================
   MAIN DI TEST
   ===================================================== */
lista eliminaBlocchiPari(lista L);
int main() {

    lista L = NULL;

    /* ESEMPIO DEL TESTO */
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
int blocco(lista head)
    {
        if(head==NULL)
            return 0;
        int count=1;
        head=head->next;
        while(head!=NULL)
            {
                if(head->dato%2==1)
                    break;
                count++;
                head=head->next;
            }
        if(head==NULL)
            return 0;
        return count+1;
    }
lista eliminaK(lista head, int K)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<K; i++)
        {
            lista temp=head->next;
            free(head);
            head=temp;
        }
    return head;
    }

void f(lista *l)
    {
        if(*l==NULL)
            return;
        lista *pp=l;
    while (*pp!=NULL) {
        if((*pp)->dato%2==1)
            {
                int val=blocco(*pp);
                if(val>0)
                    {
                        *pp=eliminaK(*pp, val);
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
