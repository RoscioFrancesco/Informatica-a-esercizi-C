//
//  main.c
//  tde 12 28
//
//  Created by Francesco Roscio Ricon on 28/02/26.
//

#include <stdio.h>

#define N 5
int verifica(int mat[N][N], int riga, int x);
int f(int mat[N][N], int R);
int main() {
    int M[N][N] = {
        /* riga 0 */ { 3,  2,  4,  1,  5 },   // somma = 15
        /* riga 1 */ { 6,  1,  2,  3,  4 },   // somma = 16
        /* riga 2 */ { 2,  7,  1,  4,  3 },   // somma = 17
        /* riga 3 */ { 1,  2,  1,  3,  2 },   // somma = 9   <-- riga "piccola"
        /* riga 4 */ { 4,  0,  6,  1,  2 }    // somma = 13
    };

    int R = 3;  // prova a cambiare R

    /* stampa matrice per controllare */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%3d", M[i][j]);
        printf("\n");
    }
    
    printf("\nR = %d\n", R);

    printf("%d", f(M, R));
    return 0;
}

int somma_riga(int R, int mat[N][N])
    {
    int somma=0;
    for(int c=0; c<N; c++)
        {
            somma=somma+mat[R][c];
        }
    return somma;
    }

int verifica(int mat[N][N], int riga, int x)
    {
    for(int c=0; c<N; c++)
        {
            if(mat[riga][c]>=x)
                return 0;
        }
    return 1;
    }
int f(int mat[N][N], int R)
    {
    int vett[N];
    for(int i=0; i<N; i++)
        {
            vett[i]=somma_riga(i, mat);
        }
    for(int i=0; i<N; i++)
        {
            if(verifica(mat, R, vett[i])==0)
                return 0;
        }
    return 1;
    }
