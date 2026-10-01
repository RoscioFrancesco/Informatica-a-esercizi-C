//
//  main.c
//  es 1 doppi punt -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//
#include <stdio.h>

void cambia(int **pp) {
    **pp=50;
}

int main() {
    int x = 10;
    int *p = &x;

    cambia(&p);

    printf("x = %d\n", x);   /* deve stampare 50 */
    return 0;
}
