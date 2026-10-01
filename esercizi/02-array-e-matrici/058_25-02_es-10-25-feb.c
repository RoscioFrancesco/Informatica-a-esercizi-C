//
//  main.c
//  es 10 25 feb
//
//  Created by Francesco Roscio Ricon on 25/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#define N 4

void stampa(int z, int v[], int M[][4]);

int f(int mat[][N], int num_righe, int array[], int len);
int sommariga(int mat[][N], int r);
int main() {
    int v1[] = {14, 6, 10, 8};
    int M1[][4] = {{1, 2, 3, 4},
                   {0, 1, 2, 3},
                   {4, 3, 6, 1},
                   {2, 2, 2, 2}};
    int v2[] = {4, 6, 8};
    int M2[][4] = {{1, 1, 1, 1},
                   {0, 2, 2, 2},
                   {1, 2, 3, 2}};
    int v3[] = {10, 20};
    int M3[][4] = {{1, 2, 3, 4},
                   {2, 4, 6, 8}};
    int v4[] = {3, 5, 9};
    int M4[][4] = {{1, 1, 1, 1},
                   {0, 2, 2, 2},
                   {1, 2, 7, 2}};
    int v5[] = {10, 6, 16, 8};
    int M5[][4] = {{1, 2, 3, 4},
                   {0, 1, 2, 3},
                   {5, 3, 2, 1},
                   {2, 2, 2, 2}};


    stampa(4,v1,M1);
    stampa(3,v2,M2);
    stampa(2,v3,M3);
    stampa(3,v4,M4);
    stampa(4,v5,M5);
    
    
    printf("%d", f(M5, 4, v5, 4));
}


void stampa(int z, int v[], int M[][4]) {
    int i,j;
    printf("Vettore\n");
    for (i = 0; i < z; i++) {
        printf("%d ",v[i]);
    }
    printf("\nMatrice\n");
    for (i = 0; i < z; i++) {
        for (j = 0; j < 4; j++) {
            printf("%d ",M[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

int sommariga(int mat[][N], int r)
{
    int somma=0;
    for(int c=0; c<N; c++)
        {
            somma=somma+mat[r][c];
        }
    return somma;
}
int f(int mat[][N], int num_righe, int array[], int len)
    {
    int *vett=malloc(sizeof(int)*num_righe);
    for(int i=0; i<num_righe; i++)
        {
            vett[i]=sommariga(mat, i);
        }
    for(int i=0; i<len; i++)
        {
            for(int j=0; j<len; j++)
                {
                    if(vett[i]==array[j])
                        {
                            vett[i]=0;
                        }
                }
        }
    for(int i=0; i<len; i++)
        {
            if(vett[i]!=0)
                return 0;
            
        }
    return 1;
    }
