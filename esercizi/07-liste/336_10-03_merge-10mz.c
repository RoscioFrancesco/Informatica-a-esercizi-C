//
//  main.c
//  merge 10mz
//
//  Created by Francesco Roscio Ricon on 10/03/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct EL{
    int x;
    struct EL *next;
}Nodo;
typedef Nodo *Lista;
#define N 5
void selection(int vett[], int len);
void bubblesort(int vett[], int len);
void Mergesort(int vett[], int start, int end, int mid);
void merge(int vett[], int start, int end);
int main() {
    int vett[5]={1,5,3,4,2};
    bubblesort(vett, 5);
    for(int i=0; i<5; i++)
        {
            printf("%d", vett[i]);
        }
}
Lista inserisciincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->x=x;
                new->next=NULL;
                return new;
            }
    head->next=inserisciincoda(head->next, x);
    return head;
    }
void selection(int vett[], int len)
    {
    for(int i=0; i<len; i++)
        {
            for(int j=i+1; j<len; j++)
                {
                    if(vett[i]>vett[j])
                        {
                            int temp=vett[i];
                            vett[i]=vett[j];
                            vett[j]=temp;
                        }
                }
        }
    }
void bubblesort(int vett[], int len)
    {
    int scambi=0;
    for(int i=0; i<len-1; i++)
        {
            for(int j=0; j<len-1-i; j++)
                {
                    if(vett[j]>vett[j+1])
                        {
                            int temp=vett[j];
                            vett[j]=vett[j+1];
                            vett[j+1]=temp;
                            scambi++;
                        }
                }
            if(scambi==0)
                break;
        }
    }
void merge(int vett[], int start, int end)
    {
    int mid;
    if(start<end)
        {
            mid=(start+end)/2;
            merge(vett, start, mid);
            merge(vett, mid+1, end);
            Mergesort(vett, start, end, mid);
        }
    }
void Mergesort(int vett[], int start, int end, int mid)
    {
    int i=start, k=start, j=mid+1, copy[N];
    while(i<=mid && j<=end)
        {
            if(vett[i]<vett[j])
                {
                    copy[k]=vett[i];
                    i++;
                }
            else
                {
                    copy[k]=vett[j];
                    j++;
                }
            k++;
        }
    while(i<=mid)
        {
            copy[k]=vett[i];
            i++;
            k++;
        }
    while(j<=end)
        {
            copy[k]=vett[j];
            j++;
            k++;
        }
    for(int i=start; i<=end; i++)
        {
            vett[i]=copy[i];
        }
    }
