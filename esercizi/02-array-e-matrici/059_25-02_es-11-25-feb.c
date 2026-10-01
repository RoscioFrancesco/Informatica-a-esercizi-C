//
//  main.c
//  es 11 25 feb
//
//  Created by Francesco Roscio Ricon on 25/02/26.
//

#include<stdio.h>
#include <math.h>
#define N 4
int trovavicino(int mat[N][N], int x);
void f(int mat[N][N], int x);
void stampa(int mat[N][N]);
int main()
{
    int M[N][N] = {1, 3, 5, 3, 5, 6, 7, 5, 5, 6, 2, 1, 3, 6, 9, 4};
    int x = 7;
    stampa(M);
    printf("\n");
    f(M, x);
    stampa(M);


    return 0;
}

void distruggi(int mat[N][N], int r, int c)
    {
    int num=c-r;
    for(int scorri_r=0; scorri_r<N; scorri_r++)
        {
            for(int scorri_c=0; scorri_c<N; scorri_c++)
                {
                    if(scorri_c-scorri_r==num)
                        {
                            mat[scorri_r][scorri_c]=0;
                        }
                }
        }
    }
int abs(int x)
    {
    if(x>=0)
        return x;
    return -x;
}
int trovavicino(int mat[N][N], int x)
    {
    int diff=x;
    int vicino=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(x==mat[r][c])
                        return x;
                    int l=mat[r][c]-x;
                    if(abs(l)<diff)
                        {
                            vicino=mat[r][c];
                            diff=(l);
                        }
                }
        }
        return vicino;
    }
void f(int mat[N][N], int x)
    {
    int num=trovavicino(mat, x);
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(mat[r][c]==x)
                        {
                            distruggi(mat, r, c);
                        }
                }
        }
    }
void stampa(int mat[N][N])
    {
    for(int r=0; r<N; r++)
        {
            printf("\n");
            for(int c=0; c<N; c++)
                {
                    printf("%d ", mat[r][c]);
                }
        }
    }
