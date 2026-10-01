//
//  main.c
//  es tde 13 27
//
//  Created by Francesco Roscio Ricon on 27/02/26.
//
#include <stdio.h>
#define N 4

int dividi_riga(int x, int mat[N][N], int R);
int verifificamatrice(int mat[N][N], int x);
int f(int mat[N][N], int array[N]);

int main() {

    int M[N][N] = {
        {  6, 12, 18, 24 },   // <- tutti multipli di 6 e di 3
        {  5, 10, 15, 20 },   // <- tutti multipli di 5
        {  7, 14, 21, 28 },   // <- tutti multipli di 7
        {  9, 11, 13, 17 }    // <- nessun divisore comune > 1
    };

    int A[N] = { 41, 61, 51, 18 };

    // chiamerai: f(M, A);

    printf("Matrice M:\n");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%4d", M[i][j]);
        }
        printf("\n");
    }

    printf("\nArray A:\n");
    for(int i=0;i<N;i++){
        printf("%4d", A[i]);
    }
    printf("\n%d", f(M, A));
}
int dividi_riga(int x, int mat[N][N], int R)
    {
    for(int c=0; c<N; c++)
        {
            if(mat[R][c]%x!=0)
                return 0;
        }
    return 1;
    }
int verifificamatrice(int mat[N][N], int x)
    {
    for(int R=0; R<N; R++)
        {
            if(dividi_riga(x, mat, R))
                return 1;
        }
    return 0;
    }
int f(int mat[N][N], int array[N])
    {
    for(int i=0; i<N; i++)
        {
            if(verifificamatrice(mat, array[i]))
                return 1;
        }
    return 0;
    }
