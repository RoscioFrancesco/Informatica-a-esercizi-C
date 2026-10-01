//
//  main.c
//  tde 6 28
//
//  Created by Francesco Roscio Ricon on 28/02/26.
//

#include <stdio.h>

#define N 10

void f(int a[], int b[]);   // NON implementare qui

void stampaVettore(int v[], const char *nome) {
    printf("%s: ", nome);
    for(int i = 0; i < N; i++)
        printf("%d ", v[i]);
    printf("\n");
}

int pari_gradni_prima(int vett[], int x);
void funz(int a[], int b[], int len_a, int *len_b);
int main() {

    int a[N] = {8, 3, 6, 5, 4, 7, 2, 9, 10, 1};
    int b[N] = {0};   // inizializzato tutto a 0

    printf("Vettore iniziale:\n");
    stampaVettore(a, "a");

    int lenb=0;
    funz(a, b, 10, &lenb);

    printf("\nVettore risultato:\n");
    stampaVettore(b, "b");

    return 0;
}
int pari_gradni_prima(int vett[], int x)
    {
    int count=0;
    for(int i=0; i<x; i++)
        {
            if(vett[i]%2==0 && vett[i]>vett[x])
                count++;
        }
    return count;
    }

int dispari_piccoli_dopo(int vett[], int x, int len)
    {
    int count=0;
    for(int i=x; i<len; i++)
        {
            if(vett[i]%2==1 && vett[i]<vett[x])
                count++;
        }
    return count;
    }
void funz(int a[], int b[], int len_a, int *len_b)
    {
    for(int i=0; i<len_a; i++)
        {
            if(pari_gradni_prima(a, i)==dispari_piccoli_dopo(a, i, len_a))
                {
                    b[*len_b]=a[i];
                    (*len_b)++;
                }
        }
    for(int i=(*len_b)+1; i<N; i++)
        {
            b[i]=0;
        }
    }
