//
//  main.c
//  numeri casuali
//
//  Created by Francesco Roscio Ricon on 01/10/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int nsegreto;
    char continuare;
    srand(time(NULL));
    do {
        nsegreto = rand() % 100 + 1;
        printf("%d\n", nsegreto);
        printf("Vuoi continuare?s/n\n");
        scanf(" %c", &continuare);
    } while (continuare == 's');
}
