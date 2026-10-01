//  Created by Francesco Roscio Ricon on 04/10/25.

#include <stdio.h> // in questa prima versione acquisisce l'array e lo printa

int main() {
    int i, quant;
    #define nmax 100
    int vet [nmax];
    do {
        printf("Inserisci il numero di numeri che vuoi inserire");
        scanf("%d", &quant);
    } while(quant < 0 || quant > nmax);
    for(i=0; i<quant; i++)
    {
        printf("Inserisci il numero");
        scanf("%d", &vet[i]);
    }
    printf("questo è l'array:");
    for(i=0; i<quant; i++)
        printf("\n%d\n", vet[i]);
        }
