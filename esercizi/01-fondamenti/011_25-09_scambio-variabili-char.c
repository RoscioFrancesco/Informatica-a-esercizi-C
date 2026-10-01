//
//  main.c
//  scambio variabili char
//
//  Created by Francesco Roscio Ricon on 25/09/25.
//

#include <stdio.h>
int main()
{
    char a, b, c;
    printf("\nInseire il carattere A:");
    scanf(" %c" , &a);
    printf("\nInserire il carattere B:");
    scanf(" %c" , &b);
    
    c = a;
    a = b;
    b = c;
    printf("\nA= %c",a);
    printf("\nB= %c",b);
    
}
