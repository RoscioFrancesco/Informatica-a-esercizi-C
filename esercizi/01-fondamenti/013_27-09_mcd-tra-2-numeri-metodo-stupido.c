//
//  main.c
//  mcd tra 2 numeri metodo stupido
//
//  Created by Francesco Roscio Ricon on 27/09/25.
//

#include <stdio.h>

int main() {
    
    int a, b, mcd, min, candidato;
    char continuare;
    do {
        printf ("Inserie il primo numero:\n");
        scanf("%d", &a);
        printf("Inserire il secondo numero:\n");
        scanf("%d", &b);
        mcd = 1;
        candidato = 1;
        if (a == b)
            mcd = a;
        if (a > b)
            min = b;
        else min = a;
                while (candidato <= min) // seleziono il numero minore con min, provo tutti i valori da 1 al min e vedo se è sottomultiplo di entrambi, questo primo candidato lo assegno alla variabile mcd, alla fine prendo l'ultimo candidato assegnato alla variabile mcd, che è il più grande di tutti.
                    {
                     candidato = candidato + 1;
                    if (a % candidato == 0 && b % candidato == 0)
                        mcd = candidato;
                     }
        printf("Il risulatato è pari a %d\n", mcd);
        printf("Vuoi continuare? s/n?");
        scanf(" %c", &continuare);
    } while (continuare == 's');
    
    
   
}
