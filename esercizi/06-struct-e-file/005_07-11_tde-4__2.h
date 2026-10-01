// Created by Francesco Roscio Ricon on 07/11/25.
#include <stdio.h>

#define N 10
typedef int VT[N];

typedef struct {
    int a;
    int b;
} struttura;

void ft(VT A, struttura *l, int len);

int main(void) {
    VT A;
    struttura l = {0, 0};
    int i, len = N;

    for (i = 0; i < len; i++) {
        printf("Inserire il valore %d: ", i + 1);
        if (scanf("%d", &A[i]) != 1)
            return 1;
    }
    ft(A, &l, len);
    printf("Somma indici pari: %d\nSomma indici dispari: %d\n", l.a, l.b);
    return 0;
}

void ft(VT A, struttura *l, int len) {
    int i;
    for (i = 0; i < len; i++) {
        if (i % 2 == 0)
            l->a += A[i];
        else
            l->b += A[i];
    }
}
