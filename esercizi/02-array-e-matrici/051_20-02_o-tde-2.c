//  Created by Francesco Roscio Ricon on 20/02/26.
#include <stdio.h>
#define N 5
int scorri(int mat[N][N], int k);
int main()
    {
    int mat[N][N]={
        {1,2,3,4,5},
        {12,14,23,67,89},
        {1,1,2,2,2},
        {7,1,2,2,2},
        {3,1,2,2,2}
    };
    printf("%d",scorri(mat, 3));
    }
int verifica(int mat[N][N], int r_star, int c_start, int k, int val)
    {
    for(int r=r_star; r<r_star+k; r++)
        {
            for(int c=c_start; c<c_start+k; c++)
                {
                    if(mat[r][c]!=val)
                        return 0;
                }
        }
    return 1;
    }
int scorri(int mat[N][N], int k)
    {
    for(int r=0; r<=N-k; r++)
        {
            for(int c=0; c<=N-k; c++)
                {
                    if(verifica(mat, r, c, k, mat[r][c]))
                        return 1;
                }
        }
    return 0;
    }
