//
//  main.c
//  es 5 doppi punt -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//
#include <stdio.h>

void swap(int **p1, int **p2) {
    printf("\n--- DENTRO swap() ---\n");

    printf("&p1 = %p\n", (void*)&p1);
    printf("&p2 = %p\n", (void*)&p2);

    printf("p1  = %p\n", (void*)p1);
    printf("p2  = %p\n", (void*)p2);

    printf("*p1 = %p\n", (void*)*p1);
    printf("*p2 = %p\n", (void*)*p2);

    printf("**p1 = %d\n", **p1);
    printf("**p2 = %d\n", **p2);

    int *tmp = *p1;
    printf("\nDopo tmp = *p1\n");
    printf("tmp = %p\n", (void*)tmp);

    *p1 = *p2;
    printf("\nDopo *p1 = *p2\n");
    printf("*p1 = %p\n", (void*)*p1);
    printf("*p2 = %p\n", (void*)*p2);

    *p2 = tmp;
    printf("\nDopo *p2 = tmp\n");
    printf("*p1 = %p\n", (void*)*p1);
    printf("*p2 = %p\n", (void*)*p2);

    printf("**p1 = %d\n", **p1);
    printf("**p2 = %d\n", **p2);

    printf("--- FINE swap() ---\n");
}

int main() {
    int a = 3, b = 4;
    int *p = &a;
    int *q = &b;

    printf("--- INIZIO main ---\n");

    printf("&p = %p\n", (void*)&p);
    printf("p  = %p\n", (void*)p);
    printf("*p = %d\n", *p);

    printf("\n&q = %p\n", (void*)&q);
    printf("q  = %p\n", (void*)q);
    printf("*q = %d\n", *q);

    swap(&p, &q);

    printf("\n--- DOPO swap() ---\n");

    printf("&p = %p\n", (void*)&p);
    printf("p  = %p\n", (void*)p);
    printf("*p = %d\n", *p);

    printf("\n&q = %p\n", (void*)&q);
    printf("q  = %p\n", (void*)q);
    printf("*q = %d\n", *q);

    return 0;
}
