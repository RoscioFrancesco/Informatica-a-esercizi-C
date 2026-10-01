//
//  main.c
//  mcd tra 2 numeri metodo gambero
//
//  Created by Francesco Roscio Ricon on 27/09/25.
// faccio l'mcd di due numeri partendo dal minimo e tornando indietro di uno, provando i vari valori in modo decrescente. il primo divisore comune che trovo è mcd dei due numeri
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
        if (a == b)
            mcd = a;
        if (a > b)
            min = b;
        else min = a;
        candidato = min;// è importante trovare il min perchè sarà il punto di partenza per la "discesa" del mio candidato
        while (mcd != candidato) { // il ciclo continua fino a quando mcd non è uguale al candidato
                    
                     candidato = candidato -1;
                    if (a % candidato == 0 && b % candidato == 0) //andando in ordine decrescente il primo candidato trovato che verifica le condizioni è anche l'mcd.  assegno il valore di candidato ad mcd ed interrompo il ciclo.
                        mcd = candidato;
                     }
        printf("Il risulatato è pari a %d\n", mcd);
        printf("Vuoi continuare? s/n?");
        scanf(" %c", &continuare);
    } while (continuare == 's');
    
    
   
}
