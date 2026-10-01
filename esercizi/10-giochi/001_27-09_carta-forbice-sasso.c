//
//  main.c
//  carta forbice sasso
//
//  Created by Francesco Roscio Ricon on 27/09/25.
//

#include <stdio.h>

int main() {
    char p1, p2, vincitore, continuare;
    do {
        do {
            printf("Ciao giocatore 1, inserisci la tua mossa tra carta forbice sasso.\n");
            printf("Inserire uno dei valori c (carta), f (forbice), s (sasso): ");
            scanf(" %c", &p1);  // spazio prima di %c
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("Ciao giocatore 2, inserisci la tua mossa tra carta forbice sasso.\n");
            printf("Inserire uno dei valori c (carta), f (forbice), s (sasso): ");
            scanf(" %c", &p2);  // anche qui lo spazio
        } while (!(p1 == 'c'|| p1 == 'f' || p1 == 's') || !(p2 == 'c'|| p2 == 'f' || p2 == 's'));
        
        printf("\nGiocatore 1 ha scelto: %c\n", p1);
        printf("Giocatore 2 ha scelto: %c\n", p2);
        // provo a fare con tanti if
        if (p1 == p2) {
            printf("Pareggio");
        }
        
        if ((p1 == 'c' && p2 == 's') || (p1 == 'f' && p2 == 'c') || (p1 == 's' && p2 == 'f'))
        {
            printf("Vince il giocatore uno");
        }
        else
        {
            printf("\nVince il giocatore due");
        }
        printf("\n");
        
        do {
            printf("Vuoi continuare a giocare? rispondi s o n: ");
            scanf(" %c", &continuare);
        } while(!(continuare == 's' || continuare == 'n'));
    } while(continuare == 's');
}
        

  
