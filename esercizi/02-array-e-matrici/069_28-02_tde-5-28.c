//
//  main.c
//  tde 5 28
//
//  Created by Francesco Roscio Ricon on 28/02/26.
//

#include <stdio.h>
#define N 8

int M[N][N] = {
    { 5, 1, 2, 7, 7, 7, 3, 9 },
    { 4, 5, 1, 2, 8, 6, 7, 3 },
    { 9, 4, 5, 1, 2, 8, 6, 7 },
    { 6, 9, 4, 5, 1, 2, 8, 6 },
    { 6, 6, 9, 4, 5, 1, 2, 8 },
    { 3, 6, 6, 9, 4, 5, 1, 2 },
    { 2, 3, 6, 6, 9, 4, 5, 1 },
    { 1, 2, 3, 6, 6, 9, 4, 5 }
};

void stampaMatrice(int A[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%3d", A[i][j]);
        printf("\n");
    }
}
int f(int mat[N][N]);
int main() {
    stampaMatrice(M);
    printf("\n%d", f(M));
    return 0;
}
int cerca_orizz(int r, int c, int mat[N][N], int x)
    {
        if(r==N || c==N)
            return 0;
        if(mat[r][c]!=x)
            return 0;
    return 1+cerca_orizz(r, c+1, mat, x);
    }

int cerca_vert(int r, int c, int mat[N][N], int x)
    {
        if(r==N || c==N)
            return 0;
        if(mat[r][c]!=x)
            return 0;
    return 1+cerca_vert(r+1, c, mat, x);
    }

int cerca_d(int r, int c, int mat[N][N], int x)
    {
        if(r==N || c==N)
            return 0;
        if(mat[r][c]!=x)
            return 0;
    return 1+cerca_d(r+1, c+1, mat, x);
    }
int max(int r, int c, int mat[N][N])
    {
    int len_r=1;
    int len_c=1;
    int len_d=1;
    len_c=cerca_vert(r+1, c, mat, mat[r][c]);
    len_r=cerca_orizz(r, c+1, mat, mat[r][c]);
    len_d=cerca_d(r+1, c+1, mat, mat[r][c]);
    if(len_c>len_r && len_c>len_d)
        return len_c;
    if(len_r>len_c && len_r>len_d)
        return len_r;
    return len_d;
    }
int f(int mat[N][N])
    {
    int massimo=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    int num=max(r, c, mat);
                    if(num>massimo)
                        {
                            massimo=num;
                        }
                }
        }
    return massimo;
    }
