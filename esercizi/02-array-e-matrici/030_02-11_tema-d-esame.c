//  Created by Francesco Roscio Ricon on 02/11/25.

#define L 100
int leggiInt();
int leggiIntN();
int leggiArrayInt(int vet[]);
#include <stdio.h>
int main()
{
    int contaOccorrenze(), contatore;
    contatore= contaOccorrenze();
    printf("%d", contatore);
    
}

int leggiInt()
{
    int n;
    scanf("%d", &n);
    return n;
}
int leggiIntN()
{
    int N;
    int num;
    printf("Inserisci il numero N massimo");
    scanf("%d", &N);
    do
    {
        printf("Inserisci numero");
        num = leggiInt();
    }while(!((num<N)&& num>0));
    
        return num;
}
int leggiArrayInt(int vet[])
    {
    int i;
    int lunghezza;
    do{
        printf("Quanti numeri vuoi inserire?");
        scanf("%d", &lunghezza);
    }while(lunghezza>L);
    for(i=0; i<lunghezza; i++)
        {
            printf("Inserisci numero %d\n", i+1);
            vet[i]= leggiInt();
        }
    return lunghezza;
}
int contaOccorrenze()
    {
        int occorrenze=0, Nsearch;
        printf("Di quale numero vuoi contare le occorrenze?");
        scanf("%d",&Nsearch);
        int array[L], len, i;
        len = leggiArrayInt(array);
        for(i=0; i<len; i++)
        {
            if(Nsearch==array[i])
                occorrenze++;
        }
    return occorrenze;
        
    }

