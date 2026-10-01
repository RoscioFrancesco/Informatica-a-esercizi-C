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
        printf("Inserisci il voto numero in posizione %d\n", i+1);
        scanf("%d", &voto[i]);
        printf("Inserisci il peso numero in posizione %d\n", i+1);
        scanf("%d", &peso[i]);
    }
    for (i=0; i < numero; i++)
        {
            prod[i] =voto[i]*peso[i];
        }
    for (i=0; i < numero; i++)
        {
            sommapeso = sommapeso + peso[i];
        }
    for (i=0; i < numero; i++)
        {
            sommaprod = sommaprod + prod[i];
        }
    media = sommaprod / sommapeso;
    printf("La media è pari a %d\n", media);
    
}
