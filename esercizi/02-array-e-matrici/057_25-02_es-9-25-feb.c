//
//  main.c
//  es 9 25 feb
//
//  Created by Francesco Roscio Ricon on 25/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#define N 4
void stampaMatrice(int m[][N]);
int *f(int mat[N][N]);
int main() {
    int matrice1[N][N] = { {9, 3, 4, 5}, {1, 7, 5, 2}, {8, 1, 5, 3}, {4, 2, 4, 4} };
    int matrice2[N][N] = { {9, 3, 4, 5}, {1, 1, 5, 2}, {8, 1, 3, 3}, {4, 2, 4, 4} };
    //spazio per variabili aggiuntive
    
    stampaMatrice(matrice1);
    int *punt=f(matrice1);
    for(int i=0; i<N; i++)
        {
            printf("%d,", punt[i]);
        }
    printf("\n\n");
    stampaMatrice(matrice2);
    int *punt2=f(matrice2);
    for(int i=0; i<N; i++)
        {
            printf("%d,", punt2[i]);
        }
    printf("\n\n");
    
    
    return 0;
}


void stampaMatrice(int m[][N]){
    int i,k;
    for(i=0;i<N;i++){
        for(k=0;k<N;k++){
            printf("%d ",m[i][k]);
        }
        printf("\n");
    }
}

int verifica(int mat[][N], int r, int c)
    {
    int num=mat[r][c];
    if(r==N-1)
        return 1;
    for(int scorri_riga=0; scorri_riga+r<N; scorri_riga++)
        {
            for(int scorri_colonna=0; scorri_colonna+c<N; scorri_colonna++)
                {
                    if(!(num>=mat[scorri_riga+r][scorri_colonna+c]))
                        return 0;
                }
        }
    return 1;
    }
int *f(int mat[N][N])
    {
    int *vett=malloc(sizeof(int)*N);
    for(int r=0; r<N; r++)
        {
            vett[r]=verifica(mat, r, r);
        }
    return vett;
    }
