//
//  main.c
//  es 1 7mz
//
//  Created by Francesco Roscio Ricon on 07/03/26.
//

#include <stdio.h>
#define N 5
void merge(int vett[], int start, int end, int mid);
void stampa(int vett[], int dim);
void mergeSort(int vett[], int start, int end);
int main() {
    int vett[N]={1,5,4,3,2};
    mergeSort(vett, 0, 4);
    stampa(vett, N);
}
void mergeSort(int vett[], int start, int end)
    {
        if(start<end)
            {
                int mid=(start+end)/2;
                mergeSort(vett, start, mid);
                mergeSort(vett, mid+1, end);
                merge(vett, start, end, mid);
            }
    }
void merge(int vett[], int start, int end, int mid)
    {
    int i=start, j=mid+1, k=start, copy[N];
    while(i<=mid && j<=end)
        {
            if(vett[i]>vett[j])
                {
                    copy[k]=vett[j];
                    j++;
                    k++;
                }
            else
                {
                    copy[k]=vett[i];
                    k++;
                    i++;
                }
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
            j++;
            k++;
        }
    for(int i=start; i<=end; i++)
        {
            vett[i]=copy[i];
        }
    }
void stampa(int vett[], int dim)
    {
    for(int i=0; i<dim; i++)
        {
            printf("%d,", vett[i]);
        }
    }
