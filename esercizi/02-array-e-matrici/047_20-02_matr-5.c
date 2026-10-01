//
//  main.c
//  matr 5
//
//  Created by Francesco Roscio Ricon on 20/02/26.
//

#include <stdio.h>
#define N 6
void stampa(int mat[N][N]);
int trovamax(int mat[N][N], int r_part, int c_part);
int funz(int mat[N][N]);
int main(){
    int M[N][N]={1,12,0,7,8,8,
                 4,3,5,5,5,4,
                 3,8,5,5,5,4,
                 6,9,5,5,5,9,
                 0,1,2,3,4,4,
                 6,7,8,9,4,4};
    stampa(M);
    printf("\n%d", funz(M));
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
int ver(int mat[N][N], int r_part, int c_part, int val, int h)
    {
    for(int r=r_part; r<r_part+h; r++)
        {
            for(int c=c_part; c<c_part+h; c++)
                {
                    if(mat[r][c]!=val)
                        return 0;
                }
        }
        return 1;
    }
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int trovamax(int mat[N][N], int r_part, int c_part)
    {
    int val=mat[r_part][c_part];
    int h_max=0;
    for(int i=0; i<=N-max(r_part, c_part); i++)
        {
            if(ver(mat, r_part, c_part, val, i))
                {
                    h_max=i;
                }
        }
        return h_max;
    }
int funz(int mat[N][N])
    {
    int max=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    int ris=trovamax(mat, r, c);
                    if(ris>max)
                    {
                        max=ris;
                    }
                }
        }
    return max;
    }
