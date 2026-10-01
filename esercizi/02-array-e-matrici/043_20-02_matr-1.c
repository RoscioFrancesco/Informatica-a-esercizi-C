//
//  main.c
//  matr 1
//
//  Created by Francesco Roscio Ricon on 20/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#define N 3
void riempimatrice(int mat[N][N]);
void stampa_mat(int mat[N][N]);
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
    int r=0;
    int c=0;
    for(int r=0; r<N; r++)
    {
        for(c=0; c<N; c++)
            {
                int num=0;
                printf("Inserire il valore della riga %d e della colonna %d", r, c);
                scanf("%d", &num);
                mat[r][c]=num;
            }
        }
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
                    if(mat[r][c]%2==0)
                        {
                            mat[r][c]=mat[r][c]/2;
                        }
                }
        }
    }
