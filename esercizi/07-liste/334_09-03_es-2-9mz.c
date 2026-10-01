//
//  main.c
//  es 2 9mz
//
//  Created by Francesco Roscio Ricon on 09/03/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct EL{
    char parola[100];
    struct EL *next;
}Nodo;
typedef Nodo *Lista;
void stampa(Lista head);
Lista inserisciinocda(Lista head, char parola[]);
void f(Lista *l);
int main() {
    Lista new=NULL;
    new=inserisciinocda(new, "mora");
    new=inserisciinocda(new, "ramo");
    new=inserisciinocda(new, "pentola");
    new=inserisciinocda(new, "lama");
    new=inserisciinocda(new, "cosa");
    new=inserisciinocda(new, "sesso");
    new=inserisciinocda(new, "aillo");

    f(&new);
    stampa(new);
}

Lista inserisciinocda(Lista head, char parola[])
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                strcpy(new->parola, parola);
                new->next=NULL;
                return new;
            }
        head->next=inserisciinocda(head->next, parola);
        return head;
    }
int ver(char parola1[], char parola2[])
    {
    int len1=strlen(parola1);
    int len2=strlen(parola2);
    if(parola1[len1-1]==parola2[1] && parola1[len1-2]==parola2[0])
        return 1;
    return 0;
    }
int blocco(Lista head)
    {
    int count=0;
    while(head!=NULL && head->next!=NULL)
        {
            if(ver(head->parola, head->next->parola)==0)
                break;
            head=head->next;
            count++;
            
        }
    if(count!=0)
        count++;
    return count;
    }
Lista eliminaK(Lista head, int k)
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
void f(Lista *l)
    {
        if(*l==NULL)
            return;
    Lista *pp=l;
    while (*pp!=NULL) {
        int num=blocco(*pp);
        if(num>0)
            {
                *pp=eliminaK(*pp, num);
                pp=l;
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
                printf("%s-->", head->parola);
                head=head->next;
            }
    }
