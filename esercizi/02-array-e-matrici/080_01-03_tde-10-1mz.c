//
//  main.c
//  tde 10 1mz
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
int sommaprima(int r, int M[N][N], int x);
int sommadopo(int r, int M[N][N], int x);

int main()
    {
    int mat[N][N]={
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}
    };
    }

int sommaprima(int r, int M[N][N], int x)
    {
    int somma=0;
    for(int c=0; c<x; c++)
        {
            somma=somma+M[r][c];
        }
    return somma;
    }
int sommadopo(int r, int M[N][N], int x)
    {
    int somma=0;
    for(int c=x+1; c<N; c++)
        {
            somma=somma+M[r][c];
        }
    return somma;
    }
int verifica_riga(int r, int M[N][N])
    {
    for(int c=1; c<N-1; c++)
        {
            int prima=sommaprima(r, M, c);
            int dopo=sommadopo(r, M, c);
            if(M[r][c]==prima && prima==dopo)
                return 1;
        }
    return 0;
    }
int f(int M[][N])
    {
    int count=0;
    for(int r=0; r<N; r++)
        {
            if(verifica_riga(r, M))
                count++;
        }
    return count;
    }
