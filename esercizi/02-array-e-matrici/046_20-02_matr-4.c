//
//  main.c
//  matr 4
//
//  Created by Francesco Roscio Ricon on 20/02/26.
//
#include <stdio.h>
#define N 4
int funz(int M[N][N], int r_target, int c_target);
int ver(int M[N][N], int r_target, int c_target,int num);
int main(){
    int M[N][N]={1,12,0,7,4,3,5,5,6,4,3,8,7,5,2,4};
    int r=2, c=3;
    printf("\n%d", funz(M, r, c));
}

int ver(int M[N][N], int r_target, int c_target,int num)
    {
    int count=0;
    for(int r=0; r<N; r++)
        {
            if(M[r][c_target]>=num && r!=r_target)
                return 0;
        }
    for(int c=0; c<N; c++)
        {
            if(M[r_target][c]>=num && c!=c_target)
                    return 0;
        }
    if(count>1)
        return 0;
    return 1;
    }
int funz(int M[N][N], int r_target, int c_target)
    {
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(c==c_target && r==r_target)
                        {
                            return ver(M, r_target, c_target, M[r_target][c_target]);
                        }
                }
        }
        return 0;
    }
