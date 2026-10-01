//
//  main.c
//  es tde 4 26
//
//  Created by Francesco Roscio Ricon on 26/02/26.
//
#include <stdio.h>
#define N 4

typedef struct P {
    int i, j;
} Punto;


float f(int M[][N], Punto P[]);

static void stampaMatrice(int M[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%3d", M[i][j]);
        printf("\n");
    }
}

static void stampaPunti(Punto P[]) {
    for (int k = 0; k < N*N; k++) {
        printf("P[%2d] = (%2d,%2d)\n", k, P[k].i, P[k].j);
    }
}

int main(void) {

    /* Matrice di test (positivi e zeri) */
    int M[N][N] = {
        {1, 0, 3, 4},
        {0, 5, 6, 0},
        {7, 8, 0, 9},
        {1, 2, 3, 4}
    };

    Punto P[N*N];   /* deve contenere N*N elementi */

    printf("Matrice M (%dx%d):\n", N, N);
    stampaMatrice(M);

    
    float ret = f(M, P);

    printf("\nValore di ritorno f: %.2f\n", ret);
    printf("\nVettore P (N*N = %d elementi):\n", N*N);
    stampaPunti(P);

    return 0;
}

float f(int M[][N], Punto P[])
    {
    int segna=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(M[r][c]==0)
                        {
                            P[segna].i=r;
                            P[segna].j=c;
                        }
                    else
                        {
                            P[segna].i=-1;
                            P[segna].j=-1;
                        }
                    segna++;
                }
        }
    return 0;
    }
