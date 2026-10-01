//
//  main.c
//  es **
//
//  Created by Francesco Roscio Ricon on 02/03/26.
//

#include <stdio.h>
void scambiaSeMaggiore(int **a, int **b);
int main() {
    int *a;
    int *b;
    int c=17;
    int d=15;
    a=&c;
    b=&d;
    printf("a=%d\n", *a);
    printf("b=%d\n", *b);
    printf("\n");
    scambiaSeMaggiore(&a, &b);
    printf("a=%d\n", *a);
    printf("b=%d\n", *b);
}
void scambiaSeMaggiore(int **a, int **b)
    {
        if(**a>**b)
            {
                int *new;
                new=*a;
                *a=*b;
                *b=new;
            }
    }

