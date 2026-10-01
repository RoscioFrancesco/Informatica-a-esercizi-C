//
//  main.c
//  es 3
//
//  Created by Francesco Roscio Ricon on 24/02/26.
//

#include <stdio.h>
#include <stdlib.h>


#define N 4  // Dimensione della matrice NxN

int valuta(int M1, int M2);
int *f(int M1[N][N], int M2[N][N], int **p);
int somma(int x, int M[]);
int main() {
    int M1[N][N] = {
        {3, 5, 2, 8},
        {6, 1, 4, 7},
        {9, 2, 5, 3},
        {4, 7, 6, 1}
    };
    int M2[N][N] = {
        {3, 2, 2, 9},
        {5, 1, 7, 6},
        {8, 3, 5, 4},
        {4, 8, 5, 0}
    };
    int *p=NULL;
    int *punt=f(M1, M2, &p);
    for(int r=0; r<N; r++)
        {
            printf("\n");
            for(int c=0; c<N; c++)
                {
                    printf("%d ", (*punt));
                    punt++;
                }
        }
    printf("\n");
    for(int i=0; i<N; i++)
        {
            printf("%d  ", p[i]);
        }
    free(punt);
    
}
int *f(int M1[N][N], int M2[N][N], int **p)
    {
    int *M3=malloc(sizeof(int)*N*N);
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    M3[r*N+c]=valuta(M1[r][c], M2[r][c]);
                }
        }
    int *vett=malloc(sizeof(int)*N);
    for(int j=0; j<N; j++)
        {
            vett[j]=vett[j]+somma(j,M3);
        }
    *p=vett;
    return M3;
    }
int valuta(int M1, int M2)
    {
        if(M1>M2)
            return 1;
        if(M1==M2)
            return 0;
    return -1;
    }
int somma(int x, int M[])
{
    int sum=0;
    for(int i=0; i<N; i++)
        {
            if(i==x || i%N==x)
                sum=sum+M[i];
        }
    return sum;
}
