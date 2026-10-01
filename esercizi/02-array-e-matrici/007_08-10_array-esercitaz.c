//  Created by Francesco Roscio Ricon on 08/10/25.

#include <stdio.h>

int main()
{
#define maxarray 10
    char vet[maxarray]; // x  i manda a capo
    int i,l, x, flag;
    flag=0;
    do {
        printf("Inserisci numero di caratteri\n");
        scanf("%d", &l);
    } while(l > maxarray);
    for(i=0; i < l; i++)
    {
        printf("Inserisci il carattere %d\n", i+1);
        scanf(" %c", &vet[i]);
        
            if(vet[i] < 'a' || vet[i] > 'z')
            {
            printf("Il valore inserito non è accettato\n");
                i = i - 1;
            }
    
    }
    for(i=0; i < l-1; i++)
    {
        if(vet[i]<= vet[i+1])
            flag = 1;
        else
        {
            flag = 0;
            break;
        }
    }
    
    if(flag==1)
    {
        printf("Sono in ordine alfabetico");
    }
    if (flag == 0)
    {
        printf("Non sono in ordine alfabetico");
    }
}
