//
//  main.c
//  tde 7 28
//
//  Created by Francesco Roscio Ricon on 28/02/26.
//

#include <stdio.h>
#define N 7

int M[N][N] = {
    { 1, 0, 2, 1, 0, 1, 0 },
    { 2, 1, 0, 2, 1, 0, 1 },
    { 3, 1, 2, 1, 2, 1, 0 },
    { 6, 4, 5, 6, 4, 5, 6 },
    { 3, 1, 2, 1, 2, 1, 0 },
    { 2, 1, 0, 2, 1, 0, 1 },
    { 1, 0, 2, 1, 0, 1, 0 }
};

/* (facoltativo) stampa per controllare */
void stampaMatrice(int A[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d", A[i][j]);
        printf("\n");
    }
}

int f(int M[][N]);  // la tua funzione

int main() {
    stampaMatrice(M);
     printf("\n%d\n", f(M));  // quando la implementi
    return 0;
}
int sommariga(int R, int M[N][N])
    {
    int somma=0;
    for(int c=0; c<N; c++)
        {
            somma=somma+M[R][c];
        }
    return somma;
    }
int f(int M[N][N])
    {
    int vett[N];
    for(int i=0; i<N; i++)
        {
            vett[i]=sommariga(i, M);
        }
    int max=0;
    int p=0;
    for(int i=0; i<N; i++)
        {
            if(vett[i]>max)
                {
                    max=vett[i];
                    p=i;
                }
        }
    for(int i=0; i<N; i++)
        {
            if(i<p && vett[i]>vett[i+1])
            {return 0;}
            if(i>p && vett[i+1]>vett[i])
                return 0;
        }
    return 1;
    }
