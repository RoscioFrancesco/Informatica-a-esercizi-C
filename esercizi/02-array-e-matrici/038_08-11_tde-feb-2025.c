//
//  main.c
//  tde feb 2025
//
//  Created by Francesco Roscio Ricon on 08/11/25.
// Riferimento: Informatica A (061202), TDE febbraio 2025, a.a. 2024/25: https://forms.office.com/e/Z4QRAS2ZuL

#include <stdio.h>
#include <stdlib.h>
#define N 4  // Dimensione della matrice NxN
void funzione (int M1[N][N], int M2[N][N], int M3[N][N], int len_m1e2, int *len_m3, int vett[], int dim_vett);
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
    int M3[N][N], len_m3=N;
    int vett[N], dim_vett=N,r,c;
    funzione(M1, M2, M3, N, &len_m3, vett, dim_vett);
    for(r=0; r<len_m3; r++)
    {
        for(c=0; c<len_m3;c++)
        {
            printf("%d  ", M3[r][c]);
        }
        printf("\n");
    }
    printf("\n");
    for(r=0;r<dim_vett; r++)
        printf(" %d ", vett[r]);
    printf("\n");
}
void funzione (int M1[N][N], int M2[N][N], int M3[N][N], int len_m1e2, int *len_m3, int vett[], int dim_vett)
{
    int r=0, c;
    for(r=0;r<len_m1e2; r++)
        {
            for(c=0;c<len_m1e2;c++)
            {
                if(M1[r][c]==M2[r][c])
                    {
                        M3[r][c]=0;
                    }
                if (M1[r][c]>M2[r][c]) {
                    M3[r][c]=1;
                }
                if (M1[r][c]<M2[r][c]) {
                    M3[r][c]=-1;
                }
            }
        }
    *len_m3=len_m1e2;
    int i=0;
    for(i=0; i<dim_vett; i++)
        vett[i]=0;
    for(i=0; i<*len_m3; i++)
        {
            for(c=0;c<*len_m3;c++)
            {
                for(r=0; r<*len_m3; r++)
                    {
                        vett[i] = vett[i] + M3[r][c];
                    }
                i++;
            }
        }
}
