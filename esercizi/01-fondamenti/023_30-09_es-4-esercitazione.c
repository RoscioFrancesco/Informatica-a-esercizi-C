//
//  main.c
//  es 4 esercitazione
//
//  Created by Francesco Roscio Ricon on 30/09/25.
//

#include <stdio.h>

int main() {
    float prezzo, sconto, ris;
    printf("Inserisci il prezzo\n");
    scanf("%f", &prezzo);
    printf("Inserisci lo sconto\n");
    scanf("%f", &sconto);
    ris = prezzo * 1.0 * (1-(sconto / 100.0));
    printf("Il prezzo scontato è %.2f", ris);
}
