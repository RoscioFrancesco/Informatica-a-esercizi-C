//  Created by Francesco Roscio Ricon on 07/03/26.
#include <stdio.h>
#include <stdlib.h>
typedef struct EL{
    int x;
    struct EL *next;
}Nodo;
typedef Nodo *Lista;

typedef struct ES{
    Lista head;
    struct ES *next;
}Vagone;
typedef Vagone* LdL;

Lista inserisciincoda(Lista head, int x);
LdL spezzaCrescenti(Lista L);
void stamaLDL(LdL head);
int main() {
    Lista new=NULL;
    new=inserisciincoda(new, 3);
    new=inserisciincoda(new, 7);
    new=inserisciincoda(new, 2);
    new=inserisciincoda(new, 9);
    new=inserisciincoda(new, 4);
    new=inserisciincoda(new, 1);
    new=inserisciincoda(new, 8);
    LdL L=NULL;
    L=spezzaCrescenti(new);
    stamaLDL(L);
}
int blocco(Lista head)
{
    if(head==NULL)
        return 0;
    int count=1;
    while(head!=NULL && head->next!=NULL)
    {
        if(head->x>head->next->x)
            break;
        count++;
        head=head->next;
    }
    return count;
}

Lista inserisciincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=NULL;
                new->x=x;
                return new;
            }
    head->next=inserisciincoda(head->next, x);
    return head;
    }
Lista copiaK(Lista head, int k)
{
    if(head==NULL || k==0)
        return NULL;
    Lista new=NULL;
    for(int i=0; i<k && head!=NULL; i++)
        {
            new=inserisciincoda(new, head->x);
            head=head->next;
        }
    return new;
    }
LdL inseriscincoda(LdL L, int k, Lista head)
    {
        if(L==NULL)
            {
                LdL new=(LdL)malloc(sizeof(*new));
                new->head=copiaK(head, k);
                new->next=NULL;
                return new;
            }
    L->next=inseriscincoda(L->next, k, head);
    return L;
    }
LdL spezzaCrescenti(Lista L)
    {
        if(L==NULL)
            return NULL;
        LdL new=NULL;
    Lista scorri=L;
        while(scorri!=NULL)
            {
                int num=blocco(scorri);
                if(num>0)
                    {
                        new=inseriscincoda(new, num, scorri);
                    }
                for(int i=0; i<num; i++)
                    {
                        scorri=scorri->next;
                    }
            }
    return new;
    }
void stampaLista(Lista head)
    {
        if(head==NULL)
            return;
        while(head!=NULL)
            {
                printf("%d-->", head->x);
                head=head->next;
            }
    }
void stamaLDL(LdL head)
    {
        if(head==NULL)
            return;
        while(head!=NULL)
            {
                printf("\n");
                stampaLista(head->head);
                head=head->next;
            }
    }
