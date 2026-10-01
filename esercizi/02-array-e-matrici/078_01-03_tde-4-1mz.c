//
//  main.c
//  tde 4 1mz
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//


#include <stdlib.h>
#include <stdio.h>
#define N 5
int cresce_riga(int mat[N][N], int r, int c, int diff, int len, int count);
int f(int mat[N][N], int len);
int main()
{
    int M[N][N]={
        {3    ,6    ,7    ,5    ,3},
        {5    ,6    ,2    ,9    ,1},
        {2    ,7    ,0    ,9    ,3},
        {6    ,0    ,6    ,2    ,6},
        {1    ,8    ,7    ,9    ,2}
    };
    printf("%d", f(M, 3));
    
}
int cresce_riga(int mat[N][N], int r, int c, int diff, int len, int count)
    {
        if (len <= 1) return 1;
        if(r==N-1 || c==N-1)
            return 0;
        if(!(mat[r][c+1]-mat[r][c]==diff))
            return 0;
        count++;
        if(count==len)
            return 1;
    return cresce_riga(mat, r, c+1, diff, len, count);
    }
int cresce_colonna(int mat[N][N], int r, int c, int diff, int len, int count)
    {
        if (len <= 1) return 1;
        if(r==N-1 || c==N-1)
            return 0;
        if(!(mat[r+1][c]-mat[r][c]==diff))
            return 0;
        count++;
        if(count==len)
            return 1;
    return cresce_colonna(mat, r+1, c, diff, len, count);
    }
int cresce_diag(int mat[N][N], int r, int c, int diff, int len, int count)
    {
    if (len <= 1) return 1;
    if(r==N-1 || c==N-1)
        return 0;
    if(!(mat[r+1][c+1]-mat[r][c]==diff))
        return 0;
        count++;
        if(count==len)
            return 1;
    return cresce_diag(mat, r+1, c+1, diff, len, count);
    }

int f(int mat[N][N], int len)
    {
        for(int r=0; r<N-1; r++)
        {
            for(int c=0; c<N-1; c++)
                {
                    int diff_r = mat[r][c+1] - mat[r][c];
                    int diff_c = mat[r+1][c] - mat[r][c];
                    int diff_d = mat[r+1][c+1] - mat[r][c];
                    if(cresce_riga(mat, r, c, diff_r, len, 1))
                        return 1;
                    if(cresce_colonna(mat, r, c, diff_c, len, 1))
                        return 1;
                    if(cresce_diag(mat, r, c, diff_d, len, 1))
                        return 1;
                }
        }
        return 0;
    }
