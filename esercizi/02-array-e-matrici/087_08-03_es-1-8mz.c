//  Created by Francesco Roscio Ricon on 08/03/26.

#include <stdio.h>
#define N 3
#define M 5
int f(int mat[N][M], int h, int k);
int main() {
    int mat1[N][M]={
        {1,2,0,1,0},
        {3,0,2,0,3},
        {1,2,1,1,2}
    };
    int mat2[N][M]={
        {1,2,0,2,0},
        {3,0,2,0,3},
        {1,2,1,1,2}
    };
    printf("%d", f(mat1, 3, 2));
    printf("\n%d", f(mat2, 3, 2));

}
int conta(int mat[N][M], int r, int c, int x)
    {
    int count=0;
    for(int scorri_r=0; scorri_r<x; scorri_r++)
    {
        for(int scorri_c=0; scorri_c<x; scorri_c++)
            {
                if(mat[r+scorri_r][c+scorri_c]==1)
                    count++;
            }
    }
    return count;
    }
int f(int mat[N][M], int h, int k)
    {
    int vett_h[N*M];
    int vett_k[N*M];
    for(int i=0; i<N*M; i++)
        {
            vett_h[i]=-1;
            vett_k[i]=-1;
        }
    int j_k=0;
    int j_h=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<M; c++)
                {
                    if(r+k<=N && c+k<=M)
                        {
                            vett_k[j_k]=conta(mat, r, c, k);
                            j_k++;
                        }
                    if(r+h<=N && c+h<=M)
                        {
                            vett_h[j_h]=conta(mat, r, c, h);
                            j_h++;
                        }
                }
        }
    for(int i=0; i<j_h; i++)
        {
            for(int s=0; s<j_k; s++)
            {
                if(vett_h[i]==vett_k[s] && vett_h[i]!=-1)
                    return 1;
            }
        }
    return 0;
    }
