//  Created by Francesco Roscio Ricon on 14/10/25.

#include <stdio.h>
#define N 100
int main() {
    int vet[N], i, n, max, min, posiz_max=0, posiz_min=0;
    do{
        printf("Quanti elementi vuoi inserire?");
        scanf("%d", &n);
    }while(n<0 || n>N);
    for(i=0; i<n; i++)
    {
        scanf("%d", &vet[i]);
    }
    max=vet[0];
    min=vet[0];
    for(i=0; i<n-1; i++)
    {
        if(vet[i+1]>max)
        {
            max = vet[i+1];
            posiz_max= i+1;
            
        }
        if(vet[i+1]<min)
        {
            min = vet[i+1];
            posiz_min=i+1;
        }
    }
    printf("Il massimo è %d, ed è in posizione %d\n", max, posiz_max);
    printf("Il minimo è %d, ed è in posizione %d\n", min, posiz_min);
    
}
