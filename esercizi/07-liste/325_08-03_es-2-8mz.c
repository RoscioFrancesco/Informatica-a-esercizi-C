//  Created by Francesco Roscio Ricon on 08/03/26.

#include <stdio.h>
#include <stdlib.h>
typedef struct EL {
int dato;
struct EL * next;
} nodo;
typedef nodo * lista;
lista inseriscincoda(lista head, int x);
int len(lista head);
void stampa(lista head);
lista f(lista head);
int main() {
    lista new=NULL;
    new=inseriscincoda(new, 1);
    new=inseriscincoda(new, 2);
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 4);
    new=inseriscincoda(new, 5);
    new=inseriscincoda(new, 6);

    new=f(new);
    printf("\n");
    stampa(new);
}
lista inseriscincoda(lista head, int x)
    {
        if(head==NULL)
            {
                lista new=(lista)malloc(sizeof(*new));
                new->dato=x;
                new->next=NULL;
                return new;
            }
    head->next=inseriscincoda(head->next, x);
    return head;
    }
lista copiak(lista head, int k)
    {
    lista new=NULL;
    for(int i=0; i<k && head!=NULL; i++)
        {
            new=inseriscincoda(new, head->dato);
            head=head->next;
        }
    return new;
    }
lista inverti(lista head)
    {
        if(head==NULL || head->next==NULL)
            {
                return head;
            }
    lista temp=inverti(head->next);
    head->next->next=head;
    head->next=NULL;
    return temp;
    }
int len(lista head)
    {
    int p=0;
        while(head!=NULL)
            {
                p++;
                head=head->next;
            }
    return p;
    }
lista f(lista head)
    {
    lista app=NULL;
    int l=len(head);
    app=copiak(head, l);
    app=inverti(app);
    lista new=NULL;
    lista p=head;
    lista y=app;
    for(int i=0; i<l/2; i++)
        {
            new=inseriscincoda(new, head->dato);
            new=inseriscincoda(new, app->dato);
            head=head->next;
            app=app->next;
        }
    stampa(new);
    app=y;
    head=p;
    for(int i=0; i<l && new!=NULL; i++)
        {
            head->dato=new->dato;
            head=head->next;
            new=new->next;
        }
    free(app);
    return p;
    }
void stampa(lista head)
    {
    if(head==NULL)
        return;
    while(head!=NULL)
        {
            printf("%d", head->dato);
            head=head->next;
        }
}
