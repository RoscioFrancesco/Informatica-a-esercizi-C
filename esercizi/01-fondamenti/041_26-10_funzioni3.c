//  Created by Francesco Roscio Ricon on 26/10/25.

//  Indirizzo della variabile puntata dal puntatore
//  Indirizzo della variabile a cui punta il puntatore
//  Valore della variabile
//  Valore della variabile a cui punta il puntatore

#include <stdio.h>

int main() {
    int a, *pa;
    pa = &a;
    printf("Inserire il valore di a: ");
    scanf("%d", pa);
    printf("Il valore della variabile a è: %d", *pa);
    printf("Il valoe del puntatore è: %p\n", pa);
    printf("L'indirizzo della variabile puntata è: %p", &a);
    *pa = 2*(*pa);
    printf("Il valore della variabile dopo il raddoppio è: %d", *pa);
    printf("Il valore del puntatore dopo il raddoppio è: %p\n", pa);
    printf("L'indirizzo della variabile puntata dopo il raddoppio è: %p", &a);
    
    
}
