//
//  main.c
//  matr 8
//
//  Created by Francesco Roscio Ricon on 20/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#define N 5
void inizializza(int mat[N][N]);
void funz(int mat[N][N]);
void stampa(int mat[N][N]);
int main()
    {
    int Mat[N][N];
    inizializza(Mat);
    stampa(Mat);
    funz(Mat);
    printf("\n");
    stampa(Mat);
    }
void inizializza(int mat[N][N]) {
    int tmp[N][N] = {
        {1, 3, 46, 7, 34},
        {42, 4, 42, 34, 41},
        {24, 34, 47, 64, 4},
        {49, 47, 44, 24, 14},
        {54, 84, 47, 46, 45}
    };
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            mat[r][c] = tmp[r][c];
}

int somma(int mat[N][N], int riga)
    {
    int sum=0;
    for(int i=0; i<N; i++)
        {
            sum=sum+mat[riga][i];
        }
    return sum;
    }
void swap(int mat[N][N], int riga_part, int riga_arr, int len)
    {
    int *riga_p=malloc(sizeof(int)*len);
    int *riga_b=malloc(sizeof(int)*len);
    for(int i=0; i<len; i++)
        {
            riga_p[i]=mat[riga_part][i];
        }
    for(int i=0; i<len; i++)
        {
            riga_b[i]=mat[riga_arr][i];
        }
    for(int i=0; i<len; i++)
        {
            mat[riga_arr][i]=riga_p[i];
        }
    for(int i=0; i<len; i++)
        {
            mat[riga_part][i]=riga_b[i];
        }
    free(riga_p);
    free(riga_b);
    }
void funz(int mat[N][N])
    {
    for(int i=0; i<N; i++)
        {
            for(int j=i+1; j<N; j++)
                {
                    if(somma(mat, i)<somma(mat, j))
                        {
                            swap(mat, i, j, N);
                        }
                }
        }
    }


void stampa(int mat[N][N]) {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++)
            printf("%3d ", mat[r][c]);
        printf(" | somma=%d\n", somma(mat, r));
    }
}
