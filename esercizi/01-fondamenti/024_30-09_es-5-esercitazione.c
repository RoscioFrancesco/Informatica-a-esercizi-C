//  Created by Francesco Roscio Ricon on 30/09/25.


//Se l'utente sceglie 0, il programma stampa un messaggio di saluto, ad esempio "Grazie ed arrivederci".

//Se l'utente sceglie un qualsiasi altro numero, il programma stampa a schermo un messaggio d'errore e si ferma.

#include <stdio.h>

int main() {
    int scelta;
    float a, b, prod, somma;
    do {
        printf("Vuoi fare la somma(1), il prodotto(2) o fermare il programma(0)?\n");
        scanf("%d", &scelta);
        if (!(scelta == 0 || scelta == 2 || scelta == 1))
            printf("\nErrore,riprovare a inserire un altro valore\n");
    } while (!(scelta == 0 || scelta == 2 || scelta == 1));
    if (scelta == 1)
    {
        printf("\nInserisci il primo addendo \n");
        scanf("%f", &a);
        printf("\nInserisci il secondo addendo \n");
        scanf("%f", &b);
        somma = a + b + 0.0;
        printf("%.2f + %.2f = %.2f", a, b, somma);
        
    }
    if (scelta == 2)
    {
        printf("\nInserisci il primo numero \n");
        scanf("%f", &a);
        printf("\n Inserisci il secondo numero \n");
        scanf("%f", &b);
        prod = a * b * 1.0;
        printf("%.2f + %.2f = %.2f\n", a, b, prod);
        
    }
    
    return 0;
    
}
