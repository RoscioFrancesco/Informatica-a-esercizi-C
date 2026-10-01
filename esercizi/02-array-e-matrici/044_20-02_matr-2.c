//
//  main.c
//  matr 2
//
//  Created by Francesco Roscio Ricon on 20/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#define N 3
void riempimatrice(int mat[N][N]);
void stampa_mat(int mat[N][N]);
void f(int mat[N][N]);
void f(int mat[N][N]);
int main()
{
    int M[N][N];
    riempimatrice(M);
    stampa_mat(M);
    f(M);
    printf("\n");
    stampa_mat(M);

}
void riempimatrice(int mat[N][N])
    {
    mat[0][0]=1;
    mat[0][1]=2;
    mat[0][2]=3;
    mat[1][0]=4;
    mat[1][1]=5;
    mat[1][2]=6;
    mat[2][0]=7;
    mat[2][1]=8;
    mat[2][2]=9;
    }
void stampa_mat(int mat[N][N])
    {
    for(int r=0; r<N; r++)
        {
            printf("\n");
            for(int c=0; c<N; c++)
                {
                    printf("%d  ", mat[r][c]);
                }
        }
    }
void f(int mat[N][N])
    {
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(c>r)
                        {
                            mat[r][c]=mat[r][c]+mat[c][r];
                        }
                    if(c<r)
                        {
                            mat[r][c]=0;
                        }
                }
        }
    }
