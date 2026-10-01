//
//  main.c
//  tde 2 1mz
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//

#include <stdio.h>
#include <stdlib.h>
#define N 4
int expo(int base, int exp);
int converti(int bin[], int len);
int main()
    {
    int M[N][N]={
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}
    };
    int array[N]={1,1,1,1}; // ovvero 15
    }
int media_matr(int mat[N][N])
    {
    int somma=0;
    int count=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    somma=somma+mat[r][c];
                    count++;
                }
        }
    return somma/count;
    }
int converti(int bin[], int len)
    {
    int j=len;
    int sum=0;
    for(int i=0; i<N; i++)
        {
            sum=sum+bin[i]*expo(2, len-1-i);
        }
    return sum;
    }
int expo(int base, int exp)
    {
    int ris=0;
    for(int i=0; i<exp; i++)
        {
            ris=ris*base;
        }
    return ris;
    }
