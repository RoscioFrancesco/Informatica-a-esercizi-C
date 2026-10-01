//
//  main.c
//  matr 3
//
//  Created by Francesco Roscio Ricon on 20/02/26.
//

#include <stdio.h>
#define N 4
int scorri(int mat[N][N], int h, int k);
void stampa(int mat[N][N]);
int main(){
int M[N][N]={1,2,0,1,0,3,0,2,0,3,1,2,1,1,2,4};
    stampa(M);
    int h=2;
    int k=2;
    int ris=scorri(M, h, k);
    printf("\n%d", ris);


return 0;
}
int f(int mat[N][N], int r_part, int c_part, int k, int h)
    {
    int count=0;
    for(int r=r_part; r<r_part+h; r++)
        {
            for(int c=c_part; c<c_part+h; c++)
                {
                    if(mat[r][c]==1)
                        count++;
                }
        }
    if(count==k)
        return 1;
    return 0;
    }
int scorri(int mat[N][N], int h, int k)
    {
    int count=0;
    for(int r=0; r<=N-h; r++)
        {
            for(int c=0; c<=N-h; c++)
                {
                    count=count+f(mat, r, c, k, h);
                }
        }
    return count;
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
