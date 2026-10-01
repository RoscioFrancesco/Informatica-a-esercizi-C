//  Created by Francesco Roscio Ricon on 26/10/25.

#include <stdio.h>
int Sommadivisori (int n);
int Sommadivisori(int n)
    {
    int i;
    int somma=0;
    for(i=2; i<=n/2; i++)
    {
        if(n % i == 0)
            somma = somma + i;
    }
    return somma;
    }

int main() {
    int num;
    int ris;
    printf("Inserire il numero");
    scanf("%d", &num);
    ris = Sommadivisori(num);
    printf("%d", ris);
}
