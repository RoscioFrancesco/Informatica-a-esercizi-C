//
//  main.c
//  merge_sort 2mz
//
//  Created by Francesco Roscio Ricon on 02/03/26.
//
#define N 5
#include <stdio.h>
void merge(int vett[], int start, int end, int mid);
void mergeSort(int vett[], int start, int end);
void stampa(int vett[], int len);
int main() {
    int vett[5]={1,5,4,2,3};
    mergeSort(vett, 0, 4);
    stampa(vett, 5);
}
void mergeSort(int vett[], int start, int end)
    {
    int mid;
    if(start<end)
        {
            mid=(start+end)/2;
            mergeSort(vett, start, mid);
            mergeSort(vett, mid+1, end);
            merge(vett, start, end, mid);
        }
    }
void merge(int vett[], int start, int end, int mid)
    {
        int i=start,j=mid+1, k=start, copy[N]; // con k scorro copy, con i e j scorro vett
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
                k++;
                i++;
            }
        while(j<=end)
            {
                copy[k]=vett[j];
                k++;
                j++;
            }
    for(int i=0; i<=end; i++)
        {
            vett[i]=copy[i];
        }
    }

void stampa(int vett[], int len)
    {
    for(int i=0; i<len; i++)
        {
            printf("%d,", vett[i]);
        }
    }
