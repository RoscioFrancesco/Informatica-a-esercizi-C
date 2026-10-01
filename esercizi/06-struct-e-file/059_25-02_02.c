//
//  main.c
//  02
//
//  Created by Francesco Roscio Ricon on 25/02/26.
//

#include <stdio.h>
#include <math.h>
#define N 3

typedef struct{
    int d_righe;
    int d_colonne;
    float media_diag;
}struttura;

struttura f(float mat[N][N]);

int main() {


    float M1[N][N] = {5,-2,1,
                      1,4,2,
                      -1,2,-4};
    float M2[N][N] = {-4,-1.5,-1,
                      2,10,-2.5,
                      -1,-3,6};
    float M3[N][N] = {2,-2,1,
                      1,4,2,
                      -1,2,-4};


    struttura n=f(M1);
    printf("colonne: %d, righe: %d, media: %f", n.d_colonne,n.d_righe, n.media_diag);


    return 0;
}


float somma_riga(int r, int c, float mat[N][N])
    {
    float somma=0;
    for(int sc=0; sc<N; sc++)
        {
            if(sc!=c)
            {
                somma=somma+fabsf(mat[r][sc]);
            }
        }
    return somma;
    }
float somma_colonna(int r, int c, float mat[N][N])
    {
    float somma=0;
    for(int sc_r=0; sc_r<N; sc_r++)
        {
            if(sc_r!=r)
                {
                    somma=somma+fabsf(mat[sc_r][c]);
                }
        }
    return somma;
    }
struttura f(float mat[N][N])
    {
    struttura new;
    new.d_colonne=1;
    new.d_righe=1;
    new.media_diag=0;
    float somma=0;
    int count=0;
    for(int r=0; r<N; r++)
        {
            if(!(fabs(mat[r][r])>somma_riga(r, r, mat)))
                new.d_righe=0;
            if(!(fabs(mat[r][r])>somma_colonna(r, r, mat)))
                new.d_colonne=0;
            somma=somma+fabsf(mat[r][r]);
            count++;
        }
    new.media_diag=somma/count;
    return new;
    }
