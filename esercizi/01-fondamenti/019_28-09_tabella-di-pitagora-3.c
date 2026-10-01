//
//  main.c
//  tabella di pitagora 3
//
//  Created by Francesco Roscio Ricon on 28/09/25.
//

#include <stdio.h>

int main() {
    int x, y, prod;
    char porzione, continuare;
    x=0;
    y=0;
    do {
        x=0;
        y=0;
        printf("Vuoi la parte sopra (u), sotto (d) o la diagonale (k) della tabella?\n");
        scanf(" %c", &porzione);
        
        if (porzione == 't') {
            
            while (y <= 10)
                
            {
                while (x<= 10)
                {
                    prod = x * y;
                    printf("%4d", prod);
                    x = x + 1;
                }
                printf("\n\n\n");
                x = 0;
                y = y + 1;
                
                 }
                            }
        
        
        if (porzione == 'u') {
        
            while (y <= 10) {
                                       while (x<= 10)  {                          // con questo whiule faccio tutta una riga
                                                         prod = x * y;
                                                               if (x >= y)
                                                                       printf("%4d", prod);
                                                               else
                                                                         printf("    ");
                    
                                                         x = x + 1;
                                                        }
                             printf("\n\n\n");
                             x = 0; // resetto la variabile x, incremento la y e vado a capo, in qs modo faccio la seconda riga
                             y = y + 1;
                 
                            }
                               } // divio i 3 casi, se scegli la porzione sopra sotto o la diagonale
        if (porzione == 'd') {
            while (y <= 10)
            {
                while (x<= 10)
                {
                    prod = x * y;
                    if (x <= y)
                        printf("%4d", prod);
                    else
                        printf("    ");
                    
                    x = x + 1;
                }
                printf("\n\n\n");
                x = 0;
                y = y + 1;
                
            }
        }
        
            if (porzione == 'k') {
                while (y <= 10)
                {
                    while (x<= 10)
                    {
                        prod = x * y;
                        if (x == y)
                            printf("%4d", prod);
                        else
                            printf("    ");
                        
                        x = x + 1;
                    }
                    printf("\n\n\n");
                    x = 0;
                    y = y + 1;
                    
                }
            }
            printf("Vuoi ripetere il porcesso? s/n\n");
            scanf(" %c", &continuare);
        } while(continuare == 's');
    
}
