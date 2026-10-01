//
//  main.c
//  fattoriale
//
//  Created by Francesco Roscio Ricon on 25/09/25.
//
#include <stdio.h>
int main() {
    int n, s, x;
    printf("Inserire il numero naturale di cui si vuole fare il fattoriale:");
    scanf("%d", &n);
    x = n - 1;
    s = n;
    while (x > 0) {
        s = s * x;
        x = x - 1;
    }
    printf("%d", s);
    return 0;
}
