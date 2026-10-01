//
//  main.c
//  tabelle
//
//  Created by Francesco Roscio Ricon on 02/10/25.
//

#include <stdio.h>

int main() {
    int l, x, y, i; // i incrementa
    printf("Inserisci il lato della matrice");
    scanf("%d", &l);
    x=1;
    y=1;
    i=0;
    while (y <= l)
    {
            while (x <= l)
            {
                            if (x == i + 1 || y == i + 1 || x == l-i || y == l-i)
                                printf("%d  ", l-i);
                                x++;
                    
                }
        
        printf("\n");
        y++;
        x = 1;
        i++;
    }

}
