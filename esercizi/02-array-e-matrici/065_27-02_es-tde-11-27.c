//
//  main.c
//  es tde 11 27
//
//  Created by Francesco Roscio Ricon on 27/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#define N 5
int funzione(int m1[N][N], int m2[N][N], int ecc);
int main(void) {

    int m1[N][N] = {
        { 11, 12, 13, 14, 15 },
        {  1,  2,  3,  4,  5 },   // <- riga "pulita" comoda da confrontare
        { 21, 22, 23, 24, 25 },
        { 31, 32, 33, 34, 35 },
        { 41, 42, 43, 44, 45 }
    };

    int m2[N][N] = {
        { 90, 91,  1, 93, 94 },
        { 80, 81,  2, 83, 84 },
        { 70, 71, 99, 73, 74 },   // <- nella colonna 2 (0-based) c’è una "quasi-copia"
        { 60, 61,  4, 63, 64 },
        { 50, 51, 88, 53, 54 }
    };

    printf("%d", funzione(m1, m2, 3));

    return 0;
}
//se esistono una riga o una colonna nelle due matrici che contengono tutti gli elementi nello stesso ordine con esattamente k eccezioni, 0 altrimenti.
int verifica_riga(int vett[], int mat[N][N], int R, int ecc)
    {
    int count=0;
    int segna=0;
        for(int c=0; c<N; c++)
            {
                if(mat[R][c]!=vett[segna])
                    {
                        count++;
                    }
                segna++;
            }
        if(count>ecc)
            return 0;
    return 1;
    }
int verificacolonna(int vett[], int mat[N][N], int C, int ecc)
    {
    int count=0;
    int segna=0;
        for(int r=0; r<N; r++)
            {
                if(mat[r][C]!=vett[segna])
                    {
                        count++;
                    }
                segna++;
            }
        if(count>ecc)
            return 0;
    return 1;
    }
int formariga(int mat[N][N], int R, int ecc, int m2[N][N])
{
    int *vett=malloc(sizeof(int)*N);
    for(int c=0; c<N; c++)
        {
            vett[c]=mat[R][c];
        }
    for(int R=0; R<N; R++)
        {
            if(verifica_riga(vett, m2, R, ecc))
                return 1;
        }
    for(int C=0; C<N; C++)
        {
            if(verificacolonna(vett, m2, C, ecc))
                return 1;
        }
    return 0;
}
int formacolonna(int mat[N][N], int C, int ecc, int m2[N][N])
{
    int *vett=malloc(sizeof(int)*N);
    for(int r=0; r<N; r++)
        {
            vett[r]=mat[r][C];
        }
    for(int R=0; R<N; R++)
        {
            if(verifica_riga(vett, m2, R, ecc))
                return 1;
        }
    for(int C=0; C<N; C++)
        {
            if(verificacolonna(vett, m2, C, ecc))
                return 1;
        }
    return 0;
}
int funzione(int m1[N][N], int m2[N][N], int ecc)
    {
    for(int R=0; R<N; R++)
        {
            if(formariga(m1, R, ecc, m2))
                return 1;
        }
    for(int C=0; C<N; C++)
        {
            if(formacolonna(m1, C, ecc, m2))
                return 1;
        }
    return 0;
    }
