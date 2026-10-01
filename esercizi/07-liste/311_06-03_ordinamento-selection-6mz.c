//
//  main.c
//  ordinamento_selection 6mz
//
//  Created by Francesco Roscio Ricon on 06/03/26.
//

#include <stdio.h>

typedef struct EL{
    int x;
    struct EL *next;
}Nodo;
typedef Nodo *Lista;
void stampa(int vett[], int dim);
void selection_sort(int vett[], int dim);
void bubblesort(int vett[], int dim);
void mergeS(int vett[], int start, int end, int mid);
void mergeSort(int vett[], int start, int end);
int main() {
    int vett[5]={5,2,1,3,4};
    mergeSort(vett, 0, 4);
    stampa(vett, 5);
}
void selection_sort(int vett[], int dim)
    {
    for(int i=0; i<dim; i++)
        {
            for(int j=i+1; j<dim; j++)
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
void stampa(int vett[], int dim)
    {
    for(int i=0; i<dim; i++)
        {
            printf("%d,", vett[i]);
        }
    }
void bubblesort(int vett[], int dim)
    {
    int num=0;
    for(int i=0; i<dim-1; i++)
        {
            num=0;
            for(int j=0; j<dim-1; j++)
                {
                    if(vett[j]>vett[j+1])
                        {
                            int temp=vett[j];
                            vett[j]=vett[j+1];
                            vett[j+1]=temp;
                            num++;
                        }
                }
            if(num==0)
                break;
        }
    }
void mergeSort(int vett[], int start, int end)
    {
    if(start<end)
        {
            int mid=(start+end)/2;
            mergeSort(vett, start, mid);
            mergeSort(vett, mid+1, end);
            mergeS(vett, start, end, mid);
        }
    }
void mergeS(int vett[], int start, int end, int mid)
    {
    int i=start, j=mid+1, k=start, copy[5];
    while((i <= mid) && (j <= end)){
            if(vett[i] > vett[j]){
                copy[k] = vett[j];
                j++;
            }
            else{
                copy[k] = vett[i];
                i++;
            }
            k++;
        }
    while(j<=end)
        {
            copy[k]=vett[j];
            k++;
            j++;
        }
    while(i<=mid)
        {
            copy[k]=vett[i];
            i++;
            k++;
        }
    for(int i=start; i<=end; i++)
        {
            vett[i]=copy[i];
        }
    }
