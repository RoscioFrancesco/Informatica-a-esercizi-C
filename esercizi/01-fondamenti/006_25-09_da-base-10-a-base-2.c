//
//  main.c
//  da base 10 a base 2
//
//  Created by Francesco Roscio Ricon on 25/09/25.
//

#include <stdio.h>

int main() {
    int n10, resto1, resto2, resto3, resto4, resto5, ris1, ris2, ris3, ris4, ris5;
    printf("Inserire un numero intero positivo minore o uguale a 31:"); // il massimo numero che può rappresentare è in 4 bit
    scanf("%d", &n10);
    if (n10==0)
        printf("Il numero in base 2 è pari a 0000");
        else
            if (n10==1)
                printf("Il numero in base 1 è pari a 0001");
            else
    ris1 = n10 / 2;
    resto1 = n10 % 2;
    ris2 = ris1 / 2;
    resto2 = ris1 % 2;
    ris3 = ris2 / 2;
    resto3 = ris2 % 2;
    ris4 = ris3 / 2;
    resto4 = ris3 % 2;
    ris5 = ris4 / 2;
    resto5 = ris4 % 2;  // volendo si può scalare il programma fino ad n bit (non è per niente efficiente come metodo)
    
    
    printf("\nIl numero in codice binario è pari a %d%d%d%d%d\n", resto5, resto4, resto3, resto2, resto1);
}
