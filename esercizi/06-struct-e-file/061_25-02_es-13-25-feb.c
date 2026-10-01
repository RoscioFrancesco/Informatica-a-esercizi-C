//  Created by Francesco Roscio Ricon on 25/02/26.

#include <stdio.h>
#include <string.h>

#define N 3

typedef struct
    {
    int r;
    int c;
}Coordinate;

/* Utility: stampa matrice */
void stampaMatrice(char M[N][N]) {
    int r, c;
    for (r = 0; r < N; r++) {
        for (c = 0; c < N; c++) {
            printf("%c ", M[r][c]);
        }
        printf("\n");
    }
}
int cerca(char matr[N][N], char parola[], int segna, Coordinate prec);
int f(char parola[], char matr[N][N]);
int main(void) {
    char M[N][N] = {
        {'a','c','k'},
        {'s','m','o'},
        {'d','f','t'}
    };
    
    printf("Matrice M (%dx%d):\n", N, N);
    stampaMatrice(M);
    printf("%d", f("dftz", M));
}
int cerca(char matr[N][N], char parola[], int segna, Coordinate now)
    {
    if(segna==strlen(parola))
        return 1;
    for(int scorri_r=-1; scorri_r<=1; scorri_r++)
        {
            for(int scorri_c=-1; scorri_c<=1; scorri_c++)
                {
                    if(!(scorri_c==0 && scorri_r==0))
                        {
                            if(parola[segna]==matr[now.r+scorri_r][now.c+scorri_c])
                                {
                                    Coordinate new;
                                    new.c=now.c+scorri_c;
                                    new.r=now.r+scorri_r;
                                    return cerca(matr, parola, segna+1, new);
                                }
                        }
                }
        }
    return 0;
    }
int f(char parola[], char matr[N][N])
    {
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(matr[r][c]==parola[0])
                    {
                        Coordinate new;
                        new.c=c;
                        new.r=r;
                        return cerca(matr, parola, 1, new);
                    }
                }
        }
    return 0;
    }
