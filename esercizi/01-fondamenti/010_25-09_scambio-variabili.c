//
//  main.c
//  scambio,variabili
//
//  Created by Francesco Roscio Ricon on 25/09/25.
//

#include <stdio.h>

int main()
{ int a, b, c;
    printf("\nInserisci il valore di A:");
    scanf("%d" , &a);fflush(stdin);
    printf("\nInserisci il valore di B:");
    scanf("%d" , &b);
    
    c = a; // sto salvando i valore di a in c
    a = b; // sto assegnando alla cella a il valore di b (?)
    b = c; // 
    printf("\nA è %d", a);
    printf("\nB è %d", b);
}
