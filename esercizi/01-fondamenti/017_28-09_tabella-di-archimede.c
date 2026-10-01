//
//  main.c
//  tabella di archimede
//
//  Created by Francesco Roscio Ricon on 28/09/25.
//

#include <stdio.h>

int main() {
    int x, y, prod;
    x=0;
    y=0;
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
        y++;
        
    }

    
}
