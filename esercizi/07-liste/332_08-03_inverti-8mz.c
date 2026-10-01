//
//  main.c
//  inverti 8mz
//
//  Created by Francesco Roscio Ricon on 08/03/26.
//

#include <stdio.h>
#include <stdlib.h>
typedef struct EL{
    int x;
    struct EL *next;
}Nodo;
typedef Nodo* Lista;
Lista inverti(Lista head);
Lista inseriscincoda(Lista head, int x);
void stampa(Lista head);

int main() {
    Lista new=NULL;
    new=inseriscincoda(new, 1);
    new=inseriscincoda(new, 2);
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 4);
    new=inseriscincoda(new, 5);
    new=inverti(new);
    printf("\n finale:");
    stampa(new);
}
Lista inseriscincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->x=x;
                new->next=NULL;
                return new;
            }
    head->next=inseriscincoda(head->next, x);
    return head;
    }
Lista inverti(Lista head)
    {
        if(head==NULL || head->next==NULL)
            return head;
        Lista temp=inverti(head->next);
    printf("\n");
        stampa(temp);
        head->next->next=head;
        head->next=NULL;
        return temp;
    }
void stampa(Lista head)
    {
        while(head!=NULL)
            {
                printf("%d-->",head->x);
                head=head->next;
            }
    }
