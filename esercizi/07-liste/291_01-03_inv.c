//
//  main.c
//  inv
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct EL{
    int x;
    struct EL *next;
}Elem;
typedef Elem *Lista;
Lista inseriscincoda(Lista head, int x);
Lista inverti(Lista head);
void stampa(Lista head);

int main() {
    Lista new=NULL;
    new=inseriscincoda(new, 1);
    new=inseriscincoda(new, 2);
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 4);
    new=inseriscincoda(new, 5);
    new=inverti(new);
    stampa(new);
    
}
Lista inseriscincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=malloc(sizeof(*new));
                new->next=NULL;
                new->x=x;
                return new;
            }
    head->next=inseriscincoda(head->next,x);
    return head;
    }
Lista inverti(Lista head)
    {
        if(head==NULL || head->next==NULL)
            return head;
    Lista temp=inverti(head->next);
    head->next->next=head;
    head->next=NULL;
    return temp;
    }
void stampa(Lista head)
    {
        while(head!=NULL)
            {
                printf("%d", head->x);
                head=head->next;
            }
    
    }
