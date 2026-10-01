//
//  main.c
//  stampa tabella ascii
//
//  Created by Francesco Roscio Ricon on 01/10/25.
//
#include <stdio.h>
#include <math.h>

int main() {
    char x;
    int i; // x è il numero di colonne, y è il numero di righe, il sofware funziona in modo tale da fare un cilo di while con la x(fare tutta una riga), andare a capo ed incrementre la y, facendo un altro ciclo con la x
    i=0;
                do
                   {
                    printf(" %c ", i);
                    i = i + 1;
                    if (i % 10 == 0)
                        printf("\n\n\n");
                   } while(i <  256);
        
    
}
