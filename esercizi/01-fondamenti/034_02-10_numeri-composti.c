//
//  main.c
//  numeri.composti
//
//  Created by Francesco Roscio Ricon on 02/10/25.
//

#include <stdio.h>

int main() {
    int n, i, numero_divisoriA, numero_divisoriB, max;
    n = 2; // numero da dividere
    i = 1; // divisore
    numero_divisoriA = 1; //patatine
    numero_divisoriB = 1; // carrello
    printf("Inserire il numero max");
    scanf("%d", &max);
    do {
        do {
                if (n % i == 0)
                {
                numero_divisoriA++;
                }
            
            i++;
            } while (i<=n);
        
        if (numero_divisoriA > numero_divisoriB)
        {
            numero_divisoriB = numero_divisoriA;
            printf("%d\n", n);
        }
        n++;
        i = 1;
        numero_divisoriA = 1;
    
    } while(n<max);
    
    return 0;
}
