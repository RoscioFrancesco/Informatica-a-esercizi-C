//  Created by Francesco Roscio Ricon on 07/03/26.
#include <stdio.h>
#include <stdlib.h>
typedef struct EL{
    int x;
    struct EL *next;
}Nodo;
typedef Nodo* Lista;
void eliminaBlocchiPari(Lista *L);
Lista inseriscincoda(Lista head, int x);
void eliminaBlocchiPari(Lista *L);
void stampa(Lista head);
int main() {
    Lista new=NULL;
    new=inseriscincoda(new, 2);
    new=inseriscincoda(new, 4);
    new=inseriscincoda(new, 6);
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 8);
    new=inseriscincoda(new, 10);
    new=inseriscincoda(new, 5);
    new=inseriscincoda(new, 12);
    eliminaBlocchiPari(&new);
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
        if(head==NULL)
            return 0;
        int len=0;
        while(head!=NULL)
            {
                if(head->x%2==1)
                    break;
                len++;
                head=head->next;
            }
        if(len>=2)
            return len;
    return 0;
    }

Lista eliminablocco(Lista head, int k)
    {
    if(head==NULL)
        return head;
    for(int i=0; i<k && head!=NULL; i++)
        {
            Lista temp=head->next;
            free(head);
            head=temp;
        }
    return head;
    }

void eliminaBlocchiPari(Lista *L)
    {
        if(*L==NULL)
            return;
        Lista *pp=L;
        while(*pp!=NULL)
            {
                int num=blocco(*pp);
                if(num>0)
                    {
                        *pp=eliminablocco(*pp, num);
                        
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
            return ;
        while(head!=NULL)
            {
                printf("%d-->", head->x);
                head=head->next;
            }
    }
