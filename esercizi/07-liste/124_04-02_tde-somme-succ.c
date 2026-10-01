//
//  main.c
//  tde somme succ
//
//  Created by Francesco Roscio Ricon on 04/02/26.
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
int ver(Lista head) // mi ridà 1 se devo eliminare, 0 altrimenti
    {
        if(head==NULL || head->next==NULL)
            return 0;
    Lista scorri=head->next;
    int somma=0;
    while(scorri!=NULL)
        {
            somma=somma+scorri->dato;
            scorri=scorri->next;
        }
        if(head->dato>somma)
            return 1;
    return 0;
    }
Lista f(Lista head)
    {
    Lista scorri=head;
    Lista prec=NULL;
    while(scorri!=NULL)
        {
            Lista succ=scorri->next;
            if(ver(scorri))
                {
                    if(prec==NULL)
                        {
                            free(head);
                            head=succ;
                            scorri=head;
                        }
                    else
                        {
                            prec->next=succ;
                            free(scorri);
                            scorri=succ;
                        }
                }
            else
                {
                    prec=scorri;
                    scorri=succ;
                }
        }
    return head;
    }
