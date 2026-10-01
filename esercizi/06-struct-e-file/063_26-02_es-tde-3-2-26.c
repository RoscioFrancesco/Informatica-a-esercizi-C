//
//  main.c
//  es tde 3.2 26
//
//  Created by Francesco Roscio Ricon on 26/02/26.
//
#include <stdio.h>
#define N 5
#include <stdlib.h>
/* coordinata di un elemento "speciale" */
typedef struct {
    int r;
    int c;
    int val;
} Pos;


int trovaMassimiIncrociati(int A[N][N], Pos out[], int maxOut);

static void stampaMatrice(int A[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%4d", A[i][j]);
        printf("\n");
    }
}
void f(int mat[N][N], int *len, int vett[]);
int main(void) {

    /* ESEMPIO 1: matrice di test (modifica liberamente i valori) */
    int A[N][N] = {
        { 5,  1,  2,  3,  4},
        { 0,  9,  1,  2,  3},
        { 1,  2, 10,  2,  1},
        { 3,  2,  1,  8,  0},
        { 4,  3,  2,  1,  7}
    };
    printf("Matrice A (%dx%d):\n", N, N);
    stampaMatrice(A);

    int *vett=malloc(sizeof(int)*N*N);
    int len=0;
    f(A, &len, vett);
    for(int i=0; i<len; i++)
        {
            printf("%d ", vett[i]);
        }
}
int ver(int r, int c, int mat[N][N])
    {
    int num=mat[r][c];
    for(int scorri_r=0;scorri_r<N; scorri_r++)
        {
            for(int scorri_c=0; scorri_c<N; scorri_c++)
                {
                    if(scorri_c==c && mat[scorri_r][scorri_c]>num)
                        return 0;
                    if(scorri_r==r && mat[scorri_r][scorri_c]>num)
                        return 0;
                    if(scorri_r-scorri_c==r-c && mat[scorri_r][scorri_c]>num)
                        return 0;
                    if(scorri_r+scorri_c==r+c && mat[scorri_r][scorri_c]>num)
                        return 0;
                }
        }
    return 1;
    }
void f(int mat[N][N], int *len, int vett[])
    {
    int segna=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(ver(r, c, mat))
                        {
                            vett[segna]=mat[r][c];
                            segna++;
                        }
                }
        }
    *len=segna;
    }
