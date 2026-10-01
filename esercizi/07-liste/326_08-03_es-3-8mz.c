//  Created by Francesco Roscio Ricon on 08/03/26.

#include <stdio.h>
#include <stdlib.h>
typedef struct EL{
    int x;
    struct EL *next;
}Nodo;
typedef Nodo * Lista;
void f(Lista *head);
Lista inseriscincoda(Lista head, int x);
void stampa(Lista head);
int main() {
    Lista new=NULL;
    new=inseriscincoda(new, 1);
    new=inseriscincoda(new, 40);
    new=inseriscincoda(new, 15);
    new=inseriscincoda(new, 16);
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 15);
    new=inseriscincoda(new, 5);
    new=inseriscincoda(new, 6);
    f(&new);
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
int blocco(Lista head)
    {
    int count=0;
    while(head!=NULL)
        {
            if(head->x%2==0)
                break;
            count++;
            head=head->next;
        }
    if(count>=3)
        return count;
    return 0;
    }
Lista eliminaK(Lista head, int k)
    {
    for(int i=0; i<k; i++)
        {
            Lista temp=head->next;
            free(head);
            head=temp;
        }
    return head;
    }
void f(Lista *head)
    {
        if(*head==NULL)
            return;
        Lista *pp=head;
        while(*pp!=NULL)
            {
                int num=blocco(*pp);
                if(num>0)
                    {
                        *pp=eliminaK(*pp, num);
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
void stampa(Lista head)
{
    if(head==NULL)
        return;
    while(head!=NULL)
        {
            printf("%d-->", head->x);
            head=head->next;
        }
    }
