//
//  main.c
//  matr 6
//
//  Created by Francesco Roscio Ricon on 20/02/26.
//

#define N 5
#include <stdio.h>
int scorri(int mat[N][N]);
int M[N][N] = {
    {1, 2, 3, 1, 4},
    {5, 1, 6, 1, 7},
    {8, 1, 9, 2, 1},
    {3, 4, 1, 5, 6},
    {1, 7, 8, 9, 0}
};
int main()
    {
    printf("\n%d", scorri(M));
    }
int contaval(int x, int mat[N][N])
    {
    int count=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(mat[r][c]==x)
                        count++;
                }
        }
    return count;
    }
int scorri(int mat[N][N])
    {
    int occ_max=0;
    int val_max=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    int occ=contaval(mat[r][c], mat);
                    if(occ>occ_max)
                        {
                            occ_max=occ;
                            val_max=mat[r][c];
                        }
                }
        }
    return val_max;
    }
