//
//  main.c
//  es 2 doppi punt -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//

#include <stdio.h>

void faiPuntare(int **pp, int *nuovo) {
    *pp=nuovo;
    
}

int main() {
    int a = 1, b = 2;
    int *p = &a;

    faiPuntare(&p, &b);

    printf("%d\n", *p);  /* deve stampare 2 */
    return 0;
}
