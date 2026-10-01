//
//  main.c
//  esercizi stringhe
//
//  Created by Francesco Roscio Ricon on 09/10/25.
//

#include <stdio.h>

    
int main()
{
#define nmax 100 // nmax è la dimensione reale dell'array
    int vet[nmax], i, n, max, vet2[nmax], vetf[nmax], contatore, q, l; // contatore conta le occorrenze del massimo, vetf registra le posizioni del massimo
    do{
        printf("Quanti elementi vuoi inserire?");
        scanf("%d", &n);
        if(n<0 || n>nmax)
            printf("Valore non accettato");
    }while(n<0 || n>nmax);
    for(i=0; i<n; i++)
    {
        printf("Inserisci un numero");
        scanf("%d", &vet[i]);
        printf("\n");
    }
    max=vet[0];
    contatore=0;
    q=0;
    for(i=0; i<n; i++) // con questo ciclo for individuo il massimo
    {
        if(vet[i] >= max)
        {
            max = vet[i];
        }
    }
    for(i=0; i<n; i++)
    {
        if(vet[i] == max)
        {
            contatore++;
            vetf[q]=i+1;
            q++;
        }
    }
    l=q;
    printf("Il massimo è %d\n", max);
    // ora voglio che stampi in ordine contrario
    for(i=0; i<n; i++)
    {
        vet2[n-1-i]=vet[i];
    }
    printf("L'array stampato al contrario è:\n");
    for(i=0; i<n; i++)
    {
        printf("%d\n", vet2[i]);
    }
    printf("I massimi sono in posizione\n");
    for(q=0; q<l; q++)
    {
        printf("%d\n", vetf[q]);
    }
    printf("Il massimo compare %d volte.\n", contatore);
    printf("L'array stampato dall'ultimo massimo escluso è:");
    for(i=q; i<n; i++)
    {
        printf("%d\n", vet[i]);
    }
}
