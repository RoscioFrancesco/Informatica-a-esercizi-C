//
//  main.c
//  tde 8 28
//
//  Created by Francesco Roscio Ricon on 28/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#define N 6
#define M 5

int f(int mat[N][N], int vett[], int len, int k);
int ver_diag(int r, int c, int vett[], int mat[N][N], int segna, int len, int k, int count);
int ver_riga(int r, int c, int vett[], int mat[N][N], int segna, int len, int k, int count);
int ver_colonna(int r, int c, int vett[], int mat[N][N], int segna, int len, int k, int count);

int main() {
    int m[N][N] = {
        { 4,  7,  1,  9,  2,  8 },
        { 6,  3,  5,  0,  7,  1 },
        { 9,  2,  8,  5,  3,  6 },
        { 1,  0,  7,  8,  2,  9 },
        { 5,  6,  3,  1,  9,  4 },
        { 8,  9,  2,  6,  0,  7 }
    };

    /* vettore da cercare (ordine diretto o inverso) */
    int v[M] = { 7, 5, 8, 2, 9 };

    /* numero di eccezioni consentite */
    int k = 1;

    /* stampa di controllo */
    printf("Matrice:\n");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++) printf("%3d", m[i][j]);
        printf("\n");
    }

    printf("\nVettore v: ");
    for(int i=0;i<M;i++) printf("%d ", v[i]);
    printf("\nk = %d\n", k);

    printf("Risultato: %d\n", f(m, v,5, k));

    return 0;
}
void gira(int vett[], int ris[], int len)
    {
    for(int i=0; i<len; i++)
        {
            ris[len-1-i]=vett[i];
        }
    }
int ver_riga(int r, int c, int vett[], int mat[N][N], int segna, int len, int k, int count)
    {
        if(len==segna)
            {
                if(count<=k)
                    return 1;
            }
        if(mat[r][c]!=vett[segna])
            {
                count++;
            }
        if(r==N-1 || c==N-1)
            return 1;
    return ver_riga(r, c+1, vett, mat, segna+1, len, k, count);
    }
int ver_colonna(int r, int c, int vett[], int mat[N][N], int segna, int len, int k, int count)
    {
    if(len==segna)
        {
            if(count<=k)
                return 1;
        }
    if(mat[r][c]!=vett[segna])
        {
            count++;
        }
        if(r==N-1 || c==N-1)
            return 1;
        return ver_colonna(r+1, c, vett, mat, segna+1, len, k, count);
    }
int ver_diag(int r, int c, int vett[], int mat[N][N], int segna, int len, int k, int count)
    {
        if(len==segna)
            {
                if(count<=k)
                    return 1;
            }
        if(mat[r][c]!=vett[segna])
        {
            count++;
        }
        if(r==N || c==N)
            return 0;
        return ver_diag(r+1, c+1, vett, mat, segna+1, len, k, count);
    }
int f(int mat[N][N], int vett[], int len, int k)
    {
    int *cop=malloc(sizeof(int)*len);
    gira(vett, cop, len);
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(ver_diag(r, c, vett, mat, 0, len, k, 0) ||
                       ver_diag(r, c, cop, mat, 0, len, k, 0) ||
                       ver_riga(r, c, vett, mat, 0, len, k, 0) ||
                       ver_riga(r, c, cop, mat, 0, len, k, 0) ||
                       ver_colonna(r, c, vett, mat, 0, len, k, 0) ||
                       ver_colonna(r, c, cop, mat, 0, len, k, 0)
                       )
                        return 1;
                }
        }
    return 0;
    }
