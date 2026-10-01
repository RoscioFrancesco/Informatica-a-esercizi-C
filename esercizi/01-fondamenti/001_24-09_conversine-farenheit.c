//
//  main.c
//  conversine.farenheit
//
//  Created by Francesco Roscio Ricon on 24/09/25.
//

#include <stdio.h>

int main() {
    int F;
    float C;
  
    printf("Inserire temperatura in gradi Farenheit:");
    scanf("%d", &F);
    C= (5.0/9)*(F-32) ;
    printf("La temperatura equivalente in Celsius è: %f" , C);
// è importante essere coerenti quando si imposta le variabili in float o in int. alla fine bisogna essere coerenti
    return 0;
}
