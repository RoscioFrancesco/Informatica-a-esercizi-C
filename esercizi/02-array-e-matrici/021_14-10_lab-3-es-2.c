//  Created by Francesco Roscio Ricon on 14/10/25.


#include <stdio.h>
#define N 5
int main() {
    int vet[N], i, X, somma=0, prodotto =1;
        printf("Inserisci %d numeri", N);
    for(i=0; i<N; i++)
    {
        scanf("%d", &vet[i]);
    }
    do{
        printf("Inserisci un indice X tra 0 ed N-1");
        scanf("%d", &X);
    }while(X<0 || X>N-1);
    for(i=0; i<X; i++)
    {
        somma= somma + vet[i];
    }
    for(i=X; i<N; i++)
    {
        prodotto= prodotto * vet[i];
    }
    printf("%d", somma);
    printf("\n");
    printf("%d", prodotto);
    return 0;
}
