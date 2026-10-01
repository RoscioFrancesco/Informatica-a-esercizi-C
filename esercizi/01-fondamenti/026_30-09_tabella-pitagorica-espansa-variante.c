//
//  main.c
//  tabella pitagorica espansa variante
//
//  Created by Francesco Roscio Ricon on 30/09/25.
//
#include <stdio.h>
#include <math.h>

int main() {
    int x, y, prod; // x è il numero di colonne, y è il numero di righe, il sofware funziona in modo tale da fare un cilo di while con la x(fare tutta una riga), andare a capo ed incrementre la y, facendo un altro ciclo con la x
    char porzione, continuare;
    int nrs, ncs, nrf, ncf;
    int i;
    x=0;
    y=0;
    i=0;

    do {
        x=0;
        y=0;
        do {
            printf("Vuoi tutta la tabella (t), la parte sopra (u), sotto (d), la diagonale (k) della tabella o un'altra parte di tabella(a)?\n");
            scanf(" %c", &porzione);
            if (porzione == 'k')
                {
              i= i + 1;
                  }
        } while (porzione != 'u' && porzione != 'd' && porzione != 'k' && porzione != 'a' && porzione != 't' && porzione != '-');
        
        
        
        if (i >= 3 && porzione == '-')
            {
            printf ("Easter egg\n");
            
            while (y <= 10)
            {
                while (x<= 10)
                {
                    prod = x * y;
                    if ((y <= 7 && y >= 0 && x <= 6 && x >= 4) || (y <= 10  && y >= 8 && x <= 3 && x >= 1) || (y <= 10 && y >= 8 && x <= 9 && x >= 7))
                    {
                        printf("%4d", prod);
                    }
                    else {
                        printf("    ");
                    }
                    
                    x = x + 1;
                }
                printf("\n\n");
                x = 0;
                y = y + 1;
                
            }
            
            
            
            
            
        }
        
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
        
        
        if (porzione == 'd' && i != 3) {
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
        
        if (porzione == 'a') {
            printf("Scegli una porzione\n");
            printf("Inserisci il numero di riga in cui le righe devono partire\n");
            scanf("%d", &nrs);
            printf("Inserisci il numero di colonna in cui le colonne devono partire\n");
            scanf("%d", &ncs);
            printf("Inserisci il numero di riga in cui le righe devono finire\n");
            scanf("%d", &nrf);
            printf("Inserisci il numero di colonna in cui le colonne devono finire\n");
            scanf("%d", &ncf);
            
            while (y <= 10)
            {
                while (x <= 10)
                {
                    prod = x * y;
                    if (y <= ncf && y >= ncs && x <= nrf && x >= nrs)
                    {
                        printf("%4d", prod);
                    }
                    else {
                        printf("    ");
                    }
                    
                    x = x + 1;
                    
                }
                printf("\n\n\n");
                x = 0;
                y = y + 1;
                
            }
            
        }
        
        do {
            printf("Vuoi ripetere il porcesso? s/n\n");
            scanf(" %c", &continuare);
        } while (continuare != 's' && continuare != 'n');
        
    } while(continuare == 's');
    
}
