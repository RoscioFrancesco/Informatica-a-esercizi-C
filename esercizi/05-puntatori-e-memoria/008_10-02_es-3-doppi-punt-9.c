//
//  main.c
//  es 3 doppi punt -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//
#include <stdio.h>
#include <stdlib.h>

void a(int **pp) {
    int *b = malloc(sizeof *b);
    if (!b) { perror("malloc"); exit(1); }

    *b = 0;

    printf("\n\n--- INIZIO a() ---\n");
    printf("&pp   = %p\n", (void*)&pp);
    printf("pp    = %p\n", (void*)pp);
    printf("*pp   = %p\n", (void*)*pp);

    printf("\n&b    = %p\n", (void*)&b);
    printf("b     = %p\n", (void*)b);
    printf("*b    = %d\n", *b);

    *b = 99;
    printf("\nDopo *b=99:\n");
    printf("b     = %p\n", (void*)b);
    printf("*b    = %d\n", *b);

    *pp = b;
    printf("\nDopo *pp=b:\n");
    printf("pp    = %p\n", (void*)pp);
    printf("*pp   = %p\n", (void*)*pp);
    printf("**pp  = %d\n", **pp);
    printf("--- FINE a() ---\n");
}

int main() {
    int *p = NULL;

    printf("In main:\n");
    printf("&p = %p\n", (void*)&p);
    printf("p  = %p\n", (void*)p);

    a(&p);

    printf("\nDopo a(&p):\n");
    printf("&p = %p\n", (void*)&p);
    printf("p  = %p\n", (void*)p);
    printf("*p = %d\n", *p);

    free(p);
    return 0;
}
