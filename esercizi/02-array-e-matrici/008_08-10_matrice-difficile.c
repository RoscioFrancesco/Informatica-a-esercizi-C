//
//  main.c
//  matrice difficile
//
//  Created by Francesco Roscio Ricon on 08/10/25.
//

#include <stdio.h>

int main()
{
    #define maxarray 10
    int vet[maxarray]; // x  i manda a capo
    int i,l, x;
    do {
        printf("Inserisci numero di righe\n");
        scanf("%d", &l);
    } while(l > maxarray);
    for(i=0; i <= l; i++)
        {
        vet[i]=l;
        }
    
    for(x=0; x <= l; x++)
    {
            for(i=0; i <= l; i++)
            {
                printf("%d ", vet[i]);
            }
        printf("\n");
    }

    
}
