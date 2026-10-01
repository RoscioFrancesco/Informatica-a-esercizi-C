//
//  main.c
//  es 3 lab
//
//  Created by Francesco Roscio Ricon on 30/09/25.
//

#include <stdio.h>

int main() {
    char c1, c2, c3, x;
    printf("Inserisci il primo carattere");
    scanf(" %c", &c1);
    printf("Inserisci il secondo carattere");
    scanf(" %c", &c2);
    printf("Inserisci il terzo carattere");
    scanf(" %c", &c3);
    x = 'a';
    do {
        if (c1 == x)
            printf("%c\n", c1);
        if (c2 == x)
            printf("%c\n", c2);
        if (c3 == x)
            printf("%c\n", c3);
        x = x + 1;
    } while (x < 'z');
    
}
