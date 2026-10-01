//
//  main.c
//  es tde 4 27
//
//  Created by Francesco Roscio Ricon on 27/02/26.
//
#include <stdio.h>
#define N 4
int scorrimat(int x, int m1[N][N]);
int trova(int x, int r, int c, int mat[N][N]);
int finale(int m1[N][N], int m2[N][N]);
int main(){
    int m1[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    
    int m2[N][N] = {
        {3, 7, 20, 30},   // 3=1+2, 7=3+4, 20=9+11, 30=14+16
        {17, 100, 5, 19}, // 17=1+16, 5=2+3, 19=8+11
        {40, 8, 50, 9},   // 8=1+7, 9=4+5
        {200, 6, 21, 18}  // 6=1+5, 21=10+11, 18=7+11
    };
    printf("%d", finale(m1, m2));
}

int trova(int x, int r, int c, int mat[N][N])
    {
    for(int scorri_r=0; scorri_r<N; scorri_r++)
        {
            for(int scorri_c=0; scorri_c<N; scorri_c++)
                {
                    if(!(scorri_c==c && scorri_r==r))
                        {
                            if(mat[r][c]+mat[scorri_r][scorri_c]==x)
                                return 1;
                        }
                }
        }
    return 0;
    }
int scorrimat(int x, int m1[N][N])
    {
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(trova(x, r, c, m1))
                        return 1;
                }
        }
    return 0;
    }
int finale(int m1[N][N], int m2[N][N])
    {
    int count=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(scorrimat(m2[r][c],m1))
                        count++;
                }
        }
    return count;
    }
