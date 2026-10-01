//
//  main.c
//  media con array
//
//  Created by Francesco Roscio Ricon on 08/10/25.
//

#include <stdio.h>

int main() {
    #define maxarray 100
    int peso[maxarray], i, numero;
    int voto[maxarray], sommaprod, prod[maxarray], sommapeso, media;
    do{
        printf("quanti voti vuoi inserire?");
        scanf("%d", &numero);
    }while(numero > maxarray);
    sommapeso = 0;
    sommaprod = 0;
    for (i=0; i < numero; i++)
    {
        printf("Inserisci il voto numero %d\n", i+1);
        scanf("%d", &voto[i]);
        printf("Inserisci il peso numero %d\n", i+1);
        scanf("%d", &peso[i]);
    }
    for (i=0; i < numero; i++)
        {
            prod[i] =voto[i]*peso[i];

            sommapeso = sommapeso + peso[i];

            sommaprod = sommaprod + prod[i];
        }
    media = sommaprod / sommapeso;
    printf("i voti con il rispettivo peso sono:");
    for(i=0; i < numero; i++)
        {
            printf("\n %d con peso %d\n", voto[i], peso[i]);
        }
    printf("La media è pari a %d\n", media);
    
}
