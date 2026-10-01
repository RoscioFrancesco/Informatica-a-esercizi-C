//
//  main.c
//  tde 10 28
//
//  Created by Francesco Roscio Ricon on 28/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#define N 5
int trova(int x, int mat[N][N]);
int * f(int mat[N][N], int *len);
int main(){
    int M[N][N] = {
        {16, 0,  3, 0, 0},
        { 3, 1,  1, 2, 1},
        { 0, 0, 13, 0, 0},
        { 0, 7,  2, 3, 2},
        { 0, 5,  1, 6, 4}
    };
    int *punt=NULL;
    int len=0;
    punt=f(M, &len);
    for(int i=0; i<N; i++)
        {
            printf("%d  ", punt[i]);
        }
    printf("\n%d", len);
    free(punt);
}
int trova(int x, int mat[N][N])
    {
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(c<r && mat[r][c]==x)
                        {
                            return 1;
                        }
                }
        }
        return 0;
    }
int * f(int mat[N][N], int *j)
    {
    int len=0;
    int *array=malloc(sizeof(int)*N);
    for(int r=0; r<N; r++)
        {
            if(trova(mat[r][r], mat))
                {
                    array[len]=mat[r][r];
                    len++;
                }
        }
    *j=len;
    for(int i=len; i<N; i++)
        {
            array[i]=-1;
        }
    return array;
    }
