//
//  main.c
//  array.es4
//
//  Created by Francesco Roscio Ricon on 04/10/25.

#include <stdio.h>

int main() {
    int i, quant, max, posizmax;
    #define nmax 100
    int vet [nmax];
    max = 0;
    do {
        printf("Inserisci il numero di numeri che vuoi inserire");
        scanf("%d", &quant);
    } while(quant < 0 || quant > nmax);
    for(i=0; i<quant; i++)
    {
        printf("Inserisci il numero in posizione: %d\n", i+1);
        scanf("%d", &vet[i]);
        if (vet[i] > max)
        {
            max = vet[i];
            posizmax = i+1;
        }
    }
            printf("questo è l'array stampato al contrario:");
                for(i = quant-1; i >= 0; i = i - 1) // qua ho inserito quant-1 perche il conteggio parte da zero, quindi l'm-esimo termine è nella caella n-1
                printf("\n%d\n", vet[i]);
    
    
    printf("questo è l'array stampato giusto");
    for(i = 0; i < quant; i++)
    {
        printf("\n%d\n", vet[i]);
    }
    printf("Questo è il massimo %d\n", max);
    printf("L'indirizzo del massimo è %d\n", &vet[posizmax]);
        }


