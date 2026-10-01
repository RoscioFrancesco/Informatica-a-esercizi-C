//
//  main.c
//  asterischi.2
//
//  Created by Francesco Roscio Ricon on 02/10/25.
//

#include <stdio.h>

int main() {
    int l, x, y;
    char scelta;
    printf("Inserisci il lato");
    scanf("%d", &l);
    printf("Vuoi solo i bordi?s/n");
    scanf(" %c", &scelta);
    x = 1;
    y = 0;

    
    if (scelta == 's')
        {  while (y <= l)
        {
            while (x <= l)
            {
                if ((y == 0) || (x == 1) || (y == l) || (x == l))
                {
                    printf(" * ");
                }
                 else
                 {
                     printf("   ");
                 }
                
                x = x + 1;
            }
            printf("\n");
            x = 1;
            y = y + 1;
                          }
    }
    else {    while (y < l) {
        while (x<= l)  {                          // con questo whiule faccio tutta una riga
            printf("*");
            x = x + 1;
        }
        printf("\n");
        x = 1;
        y = y + 1;
    }
    }
    return 0;
}
