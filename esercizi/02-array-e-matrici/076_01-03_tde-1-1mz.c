//  Created by Francesco Roscio Ricon on 01/03/26.
#include <stdio.h>
#define N 5

int f(int M[][N], int r, int c);
int main() {
    int M[N][N]={
        {1,2,3,4,5},
        {6,7,8,9,10},
        {11,2000,13,14,15},
        {16,17,18,19,20},
        {21,22,23,24,25}
    };
    printf("%d\n", f(M, 3, 1));
}
int f(int M[][N], int r, int c)
    {
    for(int scorri_r=0; scorri_r+r<N; scorri_r++)
        {
            for(int scorri_c=0; scorri_c+c<N; scorri_c++)
                {
                    if(!(M[r+scorri_r][c+scorri_c]<M[r][c]) && !(scorri_c==0 && scorri_r==0))
                        return 0;
                }
        }
    return 1;
    }
