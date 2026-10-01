//
//  main.c
//  es 2 lab
//
//  Created by Francesco Roscio Ricon on 30/09/25.
//

#include <stdio.h>

int main() {
    int a;
    printf("Inserisci il numero di cui vuoi il valore assoluto\n");
    scanf("%d", &a);
    if (a < 0)
    {
        a = -a;
    }
    printf("Il valore assoluto è %d\n", a);
}
