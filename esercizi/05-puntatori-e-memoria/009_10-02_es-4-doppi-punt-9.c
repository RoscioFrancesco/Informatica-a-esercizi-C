//
//  main.c
//  es 4 doppi punt -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//

#include <stdio.h>
#include <stdlib.h>

void f(int **pp) {
    printf("\n--- dentro f ---\n");

    printf("&pp  = %p\n", (void*)&pp);
    printf("pp   = %p\n", (void*)pp);
    printf("*pp  = %p\n", (void*)*pp);

    printf("scrivo **pp = 7\n");
    **pp = 7;

    printf("**pp = %d\n", **pp);
    printf("--- fine f ---\n");
}

int main() {
    int *p = malloc(sizeof(int));

    printf("--- in main (prima) ---\n");
    printf("&p = %p\n", (void*)&p);
    printf("p  = %p\n", (void*)p);

    f(&p);

    printf("\n--- in main (dopo) ---\n");
    printf("p  = %p\n", (void*)p);
    printf("*p = %d\n", *p);

    free(p);
    return 0;
}
