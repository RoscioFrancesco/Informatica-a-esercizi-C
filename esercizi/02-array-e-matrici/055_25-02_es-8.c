//
//  main.c
//  es 8
//
//  Created by Francesco Roscio Ricon on 25/02/26.
//
#include <stdio.h>
#define N 8


int main() {
        int M1[8][N] = {
        {1, 2, 3, 4, 5, 6, 7, 8},
        {8, 7, 6, 5, 1, 3, 2, 1},
        {2, 3, 4, 5, 6, 7, 8, 9},
        {9, 8, 7, 6, 5, 4, 3, 2},
        {1, 3, 5, 7, 9, 7, 5, 3},
        {3, 0, 4, 1, 5, 9, 2, 6},
        {6, 2, 9, 5, 1, 4, 9, 3},
        {3, 5, 7, 9, 7, 5, 3, 1}
    };


    int M2[4][N] = {
        {1, 2, 3, 4, 5, 6, 7, 8},
        {8, 7, 6, 5, 1, 3, 2, 1},
        {2, 3, 4, 5, 6, 7, 8, 9},
        {3, 5, 7, 9, 7, 5, 3, 1}
    };


    int M3[2][N] = {
        {1, 2, 3, 4, 5, 6, 7, 8},
        {3, 5, 7, 9, 7, 5, 3, 1}
    };
    
    int M4[4][N] = {
        {8, 7, 6, 5, 1, 3, 2, 1},
        {1, 3, 5, 7, 9, 7, 5, 3},
        {3, 0, 4, 1, 5, 9, 2, 6},
        {3, 5, 7, 9, 7, 5, 3, 1}
    };




    
    return 0;
}
// Riferimento: Informatica A (061202), TDE febbraio 2024, a.a. 2023/24: https://forms.office.com/e/9TP0e1k9Dp

int maxProdColonna(int mat[][N], int c)
    {
    int max=0;
    for(int r1=0; r1<N-1; r1++)
        {
            for(int r2=r1+1; r2<N; r2++)
                {
                    if(mat[r1][c]*mat[r2][c]>max)
                        {
                            max=mat[r1][c]*mat[r2][c];
                        }
                }
        }
    return max;
    }
