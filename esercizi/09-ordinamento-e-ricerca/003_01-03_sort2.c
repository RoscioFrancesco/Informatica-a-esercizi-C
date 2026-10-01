//
//  main.c
//  sort2
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//
// Librerie
#include <stdio.h>

#define N 10

void mergeSort(int v[], int start, int end);
void merge(int v[], int start, int end, int mid);
void stampaArray(int v[], int dim);


int main() {
    int vett[N]={2,4,1,6,5,9,5,10,4,2};
    mergeSort(vett, 0, N-1);
    stampaArray(vett, N);
}

void mergeSort(int v[], int start, int end){
    int mid;
    if(start < end){
        mid = (start + end)/2;
        mergeSort(v, start, mid);
        mergeSort(v, mid + 1, end);
        merge(v, start, end, mid);
    }
}

void merge(int v[], int start, int end, int mid){
    int i=start, j=mid+1, k=start, copy[N];
    // faccio il merge fino alla fine di una delle due porzioni
    while((i <= mid) && (j <= end)){
        if(v[i] > v[j]){
            copy[k] = v[j];
            j++;
        }
        else{
            copy[k] = v[i];
            i++;
        }
        k++;
    }
    // finisco la copia della prima porzione (se necessario)
    while(i <= mid){
        copy[k] = v[i];
        k++;
        i++;
    }
    // OPPURE finisco la copia della seconda porzione (se necessario)
    while(j <= end){
        copy[k] = v[j];
        k++;
        j++;
    }
    // copio "copy" nell'array di partenza, ma solo nella porzione interessata
    for(i=start; i <= end; i++){
        v[i] = copy[i];
    }
}

void stampaArray(int v[], int dim){
    printf("[");
    for(int i = 0; i<dim; i++) printf("%d,", v[i]);
    printf("]\n");
}

void copiaArray(int src[], int dest[], int dim){
    for(int i = 0; i < dim; i++){
        dest[i] = src[i];
    }
}
