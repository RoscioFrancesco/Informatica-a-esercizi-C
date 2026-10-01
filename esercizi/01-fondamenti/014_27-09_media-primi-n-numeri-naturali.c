//
//  main.c
//  media primi n numeri naturali
//
//  Created by Francesco Roscio Ricon on 27/09/25.
//
#include <stdio.h>

int main() {
  
        int n, s, ris, contatore;
        float media;
        char scelta;
    do {
        printf("Inserisci un numero N appartenente ai numeri natuali, il programma calcolarà la media dei primi N numeri partendo da 1\n");
        scanf("%d", &n);
        s = 1;
        ris = 0;
        contatore = 0;
        media = 0;

                       do {
                           ris = ris + s;
                           s = s + 1;
                           contatore = contatore + 1;
                        } while (n >= s);
        media = (ris * 1.0) / contatore;
        printf("La media dei primi n numeri naturali è pari a %f", media);
        printf ("Vuoi continuare? s/n\n");
        scanf (" %c", &scelta);
    } while(scelta == 's');
    
}
