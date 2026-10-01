//  Created by Francesco Roscio Ricon on 04/10/25.

#include <stdio.h>

int main() {
    int i, quant, max,q;
    #define nmax 100
    int vet [nmax];
    int vetcontrario [nmax];
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
    q = 1;
    i= i - 1;
    for(i=quant-1; i >= 0; i = i - 1)
    {
        vetcontrario[q] = vet[i];
        q++;
    }
    
    printf("questo è l'array al contrario:");
    for(i = quant-1; i >= 0; i = i - 1)
        printf("\n%d\n", vet[i]);
  //                                          printf("Questo è il massimo %d\n", max);
    printf("questo è l'array al contrario al contrario:");
    for(i = quant; q >= 0; q = q - 1)
        printf("\n%d\n", vetcontrario[q]);
        }


