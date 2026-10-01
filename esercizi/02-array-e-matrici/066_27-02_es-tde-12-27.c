//
//  main.c
//  es tde 12 27
//
//  Created by Francesco Roscio Ricon on 27/02/26.
//
#include <stdio.h>

#define N 6

void f(float M2[3][3], int m1[N][N]);
int main(void) {

    int M1[N][N] = {
        { 10, 11, 12, 13, 14, 15 },
        { 16, 17, 18, 19, 20, 21 },
        { 22, 23, 24, 25, 26, 27 },
        { 28, 29, 30, 31, 32, 33 },
        { 34, 35, 36, 37, 38, 39 },
        { 40, 41, 42, 43, 44, 45 }
    };

    int M2[N/2][N/2] = {0};   // qui la tua f dovrà scrivere la matrice compressa

    // f(M1, M2);

    // (facoltativo) stampa M1 per controllo
    printf("M1:\n");
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) printf("%4d", M1[r][c]);
        printf("\n");
    }

    float comp[3][3];
    f(comp, M1);
    for(int r=0; r<3; r++)
        {
            printf("\n");
            for(int c=0; c<3; c++)
                {
                    printf("%f  ", comp[r][c]);
                }
        }
}
float media(int r, int c, int M2[N][N])
    {
    float somma=0;
    somma=M2[r][c]+M2[r+1][c]+M2[r][c+1]+M2[r+1][c+1];
    return somma/4;
    }
void f(float M2[3][3], int m1[N][N])
    {
    for(int r=0; r<3; r++)
        {
            for(int c=0; c<3; c++)
                {
                    M2[r][c]=media(r*2, c*2, m1);
                }
        }
    }
