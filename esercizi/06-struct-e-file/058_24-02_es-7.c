//
//  main.c
//  es 7
//
//  Created by Francesco Roscio Ricon on 24/02/26.
//

#include <stdio.h>
#include <stdlib.h>

#define N 8  // Numero di colonne (per matrici 8x8 o superiori)

typedef struct{
    int x;
    int y;
}coordinata;

coordinata *f(int mat[N][N], int *lung, int K);
int main() {
    int k;
    int M1[N][N] = {
        {1, 2, 3, 4, 50, 6, 7, 8},
        {8, 7, 6, 50, 1, 3, 2, 1},
        {2, 3, 4, 5, 6, 7, 8, 9},
        {9, 8, 7, 6, 5, 4, 3, 2},
        {1, 3, 5, 7, 9, 7, 5, 3},
        {3, 0, 4, 1, 5, 9, 2, 6},
        {6, 2, 90, 5, 1, 4, 9, 3},
        {3, 5, 7, 9, 7, 5, 3, 1}
    };

    
    k = 4;
    coordinata *punt=NULL;
    int len=0;
    punt=f(M1, &len, k);
    for(int i=0; i<len; i++)
        {
            printf("(%d,%d)",punt[i].x, punt[i].y);
        }
    
    k = 35;
    
    k = 200;
    
    k = 90;
    
    return 0;
}
//Per semplicità, le coppie in posizioni "vicine" sono solo
//   - un elemento ed il suo adiacente nella colonna di destra.
//   - un elemento ed il suo adiacente nella nella riga sottostante.
int ver(int K, int mat[N][N], int r, int c, int *trovato)
    {
        if(mat[r][c]*mat[r][c+1]==K)
            {
                *trovato=1;
                return mat[r][c+1];
            }
        if(mat[r][c]*mat[r][c+1]==K)
            {
                *trovato=1;
                return mat[r+1][c];
            }
    *trovato=0;
    return 0;
    }

coordinata *f(int mat[N][N], int *lung, int K)
{
    int len=N*N*N;
    coordinata *vett=malloc(sizeof(coordinata)*len);
    int segna=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    int ris=0;
                    int flag=0;
                    ris=ver(K, mat, r, c, &flag);
                    if(flag==1)
                        {
                            vett[segna].x=mat[r][c];
                            vett[segna].y=ris;
                            segna++;
                        }
                }
        }
    *lung=segna;
    return vett;
}
