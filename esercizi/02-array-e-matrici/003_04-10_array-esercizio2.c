//  Created by Francesco Roscio Ricon on 04/10/25.

#include <stdio.h>

int main() {
    int i, quant, max;
    #define nmax 100
    int vet [nmax];
    max = 0;
    do {
        printf("Inserisci il numero di numeri che vuoi inserire");
        scanf("%d", &quant);
    } while(quant < 0 || quant > nmax);
    for(i=0; i<quant; i++)
    {
        printf("Inserisci il numero");
        scanf("%d", &vet[i]);
        if (vet[i] > max)
            max = vet[i];
    }
    printf("questo è l'array:");
    for(i = quant-1; i >= 0; i = i - 1)
        printf("\n%d\n", vet[i]);
    printf("Questo è il massimo %d\n", max);
        }

