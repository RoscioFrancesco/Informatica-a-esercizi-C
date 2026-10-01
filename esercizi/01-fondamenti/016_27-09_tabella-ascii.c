//
//  main.c
//  tabella ascii
//
//  Created by Francesco Roscio Ricon on 27/09/25.
//
#include <stdio.h>

int main() {
    int numero;
    char carattere;

    printf("Inserisci un numero intero (0-127): ");
    scanf("%d", &numero);

    carattere = (char) numero;   // converto il numero in char

    printf("Il numero %d corrisponde al carattere ASCII: %c\n", numero, carattere);

    return 0;
}
