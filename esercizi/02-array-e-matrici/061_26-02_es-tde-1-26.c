//
//  main.c
//  es tde 1 26
//
//  Created by Francesco Roscio Ricon on 26/02/26.
//
#include <stdio.h>

#define N 3
#define M 2


void incastro(int mat1[][N], int mat2[][M], int *riga, int *col);

int verifica(int mat1[N][N], int mat2[M][M], int r, int c);
int main(void) {
    /* === DICHIARAZIONE E INIZIALIZZAZIONE VARIABILI === */
    int mat1[N][N] = {
        {  1, -1,  1 },
        { -1,  1, -1 },
        {  1,  1,  1 }
    };

    int mat2[M][M] = {
        {  1, -1 },
        { -1,  1 }
    };

    int riga = -1;
    int col  = -1;

    /* === STAMPA INPUT (solo per test) === */
    printf("mat1 (%dx%d):\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d", mat1[i][j]);
        }
        printf("\n");
    }

    printf("\nmat2 (%dx%d):\n", M, M);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            printf("%4d", mat2[i][j]);
        }
        printf("\n");
    }

    
    incastro(mat1, mat2, &riga, &col);

    /* === OUTPUT ATTESO (per l'esempio del testo) === */
    printf("\nCoordinate trovate: riga = %d, col = %d\n", riga, col);

    return 0;
}

int èpositivo(int x)
    {
        if(x>0)
            return 1;
    return 0;
    }
int verifica(int mat1[N][N], int mat2[M][M], int r, int c)
    {
    for(int scorri_r=0; scorri_r+r<N && scorri_r<M; scorri_r++)
        {
            for(int scorri_c=0; scorri_c+c<N && scorri_c<M; scorri_c++)
                {
                    if(èpositivo(mat1[scorri_r+r][scorri_c+c])==èpositivo(mat2[scorri_r][scorri_c]))
                        return 0;
                }
        }
    return 1;
    }

void incastro(int mat1[][N], int mat2[][M], int *riga, int *col)
    {
    for(int r=0; r<N && r<=N-M; r++)
        {
            for(int c=0; c<N && c<=N-M; c++)
                {
                    if(verifica(mat1, mat2, r, c))
                        {
                            *riga=r;
                            *col=c;
                        }
                }
        }
    }
