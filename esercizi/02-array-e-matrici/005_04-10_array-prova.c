//
//  main.c
//  array.prova
//
//  Created by Francesco Roscio Ricon on 04/10/25.
//

#include <stdio.h>

int main() {
    int i;
    #define valorenumerico 300
    int vet[valorenumerico];
    for(i=0; i < valorenumerico; i++)
        vet[i] = i+1;
    printf("l'array è:\n");
    for(i=0; i < valorenumerico; i++)
        if (i % 2 == 0)
            printf("%d\n", vet[i]); // in questo caso vedo i numeri dispari, in quanto i è l'indirizzo, non il valore dentro l'array e l'indirizzo parte da 0 in posizione 0 c'è l'uno, nella prima c'è il due, nella seconda c'è il tre
        if (i % 2 == 1) // con questa scrittura mi stampa i pari.
        printf("%d\n", vet[i]);
    return 0;
}
