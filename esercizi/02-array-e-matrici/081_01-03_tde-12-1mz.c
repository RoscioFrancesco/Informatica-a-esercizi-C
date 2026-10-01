//
//  main.c
//  tde 12 1mz
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//


#include <stdio.h>
#define N 5
int f(int mat1[N][N], int mat2[N][N], int ecc);
int main()
{
    
}

int verifica_riga(int vett[], int mat[N][N], int r, int ecc)
    {
    int count=0;
    for(int c=0; c<N; c++)
        {
            if(vett[c]!=mat[r][c])
                count++;
        }
    if(count>ecc)
        return 0;
    return 1;
    }

int verifica_colonna(int vett[], int mat[N][N], int c, int ecc)
    {
    int count=0;
    for(int r=0; r<N; r++)
        {
            if(vett[r]!=mat[r][c])
                count++;
        }
    if(count==ecc)
        return 0;
    return 1;
    }
void riempi_vett_riga(int vett[], int mat[N][N], int r)
    {
    for(int c=0; c<N; c++)
        {
            vett[c]=mat[r][c];
            
        }
    return;
    }
void riempi_vett_colonna(int vett[], int mat[N][N], int c)
    {
    for(int r=0; r<N; r++)
        {
            vett[r]=mat[r][c];
            
        }
    return;
    }
int verifica_matrice(int mat2[N][N], int vett[], int ecc)
    {
    for(int r=0; r<N; r++)
        {
            if(verifica_riga(vett, mat2, r, ecc))
                return 1;
        }
    for(int c=0; c<N; c++)
        {
            if(verifica_colonna(vett, mat2, c, ecc))
                return 1;
        }
    return 0;
    }

int f(int mat1[N][N], int mat2[N][N], int ecc)
    {
    for(int r=0; r<N; r++)
        {
            int vett[N];
            riempi_vett_riga(vett, mat1, r);
            if(verifica_matrice(mat2, vett, ecc))
                return 1;
        }
    for(int c=0; c<N; c++)
        {
            int vett2[N];
            riempi_vett_colonna(vett2, mat1, c);
            if(verifica_matrice(mat2, vett2, ecc))
                return 1;
        }
    return 0;
    }
