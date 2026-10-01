//
//  main.c
//  array a lunghezza variabile in memoria dinamica
//
//  Created by Francesco Roscio Ricon on 22/11/25.
//

#include <stdio.h>
#include <stdlib.h>
int * estendi(int *v, int numnew, int numold);
int main() {
    int num0;
    int len0=2;
    printf("quanti elementi vuoi inserire?");
    scanf("%d", &num0);
    int *v;
    int j=0;
    v= (int *)malloc(sizeof(int)*num0);
    int i=0;
    do {
        printf("Inserire il numero %d", i+1);
        scanf("%d", v+j);
        j++;
        i++;
        if(i==len0)
            {
                v = estendi(v, 2*len0, len0);
                len0=2*len0;
            }
    } while (*(v+j-1)>0);
    
}
int * estendi(int *v, int numnew, int numold)
    {
    int *temp;
    int *start;
    temp= (int *)malloc(sizeof(int)*numnew);
    start=temp;
    int i;
    for(i=0; i<numold;i++)
        {
            *temp=*(v+i);
            temp++;
        }
    free(v);
    return start; // sennò mi perdo la testa del mio vettore
    
    }
