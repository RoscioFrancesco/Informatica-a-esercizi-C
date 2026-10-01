//  Created by Francesco Roscio Ricon on 07/03/26.
#include <stdio.h>
#include <stdlib.h>
typedef struct EL{
    int x;
    struct EL *next;
}Nodo;
typedef Nodo *Lista;
Lista inseriscincoda(Lista head, int x);
Lista f(Lista head, int k);
void stampa(Lista head);
int main() {
    Lista new=NULL;
    new=inseriscincoda(new, 1);
    new=inseriscincoda(new, 2);
    new=inseriscincoda(new, 3);
    new=inseriscincoda(new, 4);
    new=inseriscincoda(new, 5);
    new=inseriscincoda(new, 6);
    new=inseriscincoda(new, 7);
    new=inseriscincoda(new, 8);
    stampa(new);
    printf("\n");
    new=f(new, 3);
    stampa(new);
}
int *help(Lista head, int *len)
    {
    Lista scorri=head;
    int count=0;
    while(scorri!=NULL)
        {
            count++;
            scorri=scorri->next;
        }
    int *vett=malloc(sizeof(int)*count);
    for(int i=0; i<count && head!=NULL; i++)
        {
            vett[i]=head->x;
            head=head->next;
        }
    *len=count;
    return vett;
}
void gira(int vett[], int len ,int start, int end)
    {
    int i=start;
    int j=end;
    while(i<j)
        {
            int temp=vett[i];
            vett[i]=vett[j];
            vett[j]=temp;
            i++;
            j--;
        }
    
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
Lista f(Lista head, int k)
    {
        int len=0;
        int *punt=help(head, &len);
        for(int i=0; i<len-k; i++)
            {
                gira(punt, len, i, i+k-1);
                i=i+k-1;
            }
    Lista n=head;
    for(int i=0; i<len; i++)
        {
            head->x=punt[i];
            head=head->next;
        }
    return n;
    }
void stampa(Lista head)
    {
        if(head==NULL)
            return;
        while(head!=NULL)
            {
                printf("%d", head->x);
                head=head->next;
            }
    }
