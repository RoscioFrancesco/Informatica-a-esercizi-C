//  Created by Francesco Roscio Ricon on 07/03/26.

#include <stdio.h>
#include <stdlib.h>
typedef struct nodo{
    int x;
    struct nodo *next;
}Nodo;
typedef Nodo* Lista;
void inserisciTesta(Lista *l, int valore);
void stampa(Lista head);
int main() {
    Lista l=NULL;
    inserisciTesta(&l, 8);
    inserisciTesta(&l, 5);
    inserisciTesta(&l, 3);
    stampa(l);
}
void inserisciTesta(Lista *l, int valore)
    {
        Lista new=(Lista)malloc(sizeof(Nodo));
        new->x=valore;
        new->next=*l;
        *l=new;
    }
void stampa(Lista head)
    {
    while (head!=NULL) {
        printf("%d-->", head->x);
        head=head->next;
    }
    }
