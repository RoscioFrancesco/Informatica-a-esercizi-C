//
//  main.c
//  tabella di pitagora 2
//
//  Created by Francesco Roscio Ricon on 28/09/25.
//
#include <stdio.h>
// lo scopo è stampare solo la diagonale
int main() {
    int x, y, prod;
    x=0;
    y=0;
    
    while (y <= 10)
        
    {
        while (x<= 10)
              {
                 prod = x * y;
                  if (x == y)
                        printf("%4d", prod);
                  else
                        printf("      ");
                               
                  x = x + 1;
              }
        printf("\n\n\n");
        x = 0;
        y = y + 1;
        
    }

    
}
