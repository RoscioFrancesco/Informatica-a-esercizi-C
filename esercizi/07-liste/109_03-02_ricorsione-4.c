//
//  main.c
//  ricorsione 4
//
//  Created by Francesco Roscio Ricon on 03/02/26.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct EL {
int dato;
struct EL * next;
} nodo;
typedef nodo * Lista;

Lista inserisciintesta(int x, Lista head)
    {
        Lista new=malloc(sizeof(nodo));
        new->dato=x;
        new->next=head;
        return new;
    }
void stampa(Lista temp)
    {
    if(temp==NULL)
        return;
    Lista head=temp;
    while(head!=NULL)
    {
        printf("%d-->", head->dato);
        head=head->next;
    }
    }
Lista f(Lista head);
Lista f2(Lista head, int *somma);
int main()
    {
    Lista l1=NULL;
    l1=inserisciintesta(6, l1);
    l1=inserisciintesta(5, l1);
    l1=inserisciintesta(15, l1);
    l1=inserisciintesta(3, l1);
    l1=inserisciintesta(50, l1);
    l1=inserisciintesta(1, l1);
    stampa(l1);
    l1=f(l1);
    printf("\n");
    stampa(l1);
    }
// rimuove da una lista tutti gli elementi maggiori della somma degli elementi seguenti
Lista f2(Lista head, int *somma)
    {
        if(head==NULL)
        {
            *somma=0;
            return head;
        }
        if (head->next == NULL) {
            *somma = head->dato;   // ← fondamentale
            return head;
        }
        head->next=f2(head->next, somma);
        if(head->dato>*somma)
            {
                Lista succ=head->next;
                printf("\nentrato%d\n\n", head->dato);
                free(head);
                return succ;
            }
        else
            {
                printf("\n%d", *somma);
                *somma=*somma+head->dato;
            }

                return head;
    }
Lista f(Lista head)
    {
    int somma=0;
    head=f2(head, &somma);
    return head;
    }
