//  Created by Francesco Roscio Ricon on 20/02/26.

#include <stdio.h>
#include <string.h>

#define N 3


int verifica(char M[N][N], const char *S, int i, int j);

int wrapper(char parola[],char mat[N][N]);
int cerca(char parola[], int segna, int r, int c, char mat[N][N], int *trovato_r, int *trovato_c);
void stampaMatrice(char M[N][N]) {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            printf("%c ", M[r][c]);
        }
        printf("\n");
    }
}

int main(void) {
    char M[N][N] = {
        {'a','c','k'},
        {'s','m','o'},
        {'d','f','t'}
    };

    const char *S1 = "amo";
    int i1 = 0, j1 = 0;

    const char *S2 = "doc";
    int i2 = 2, j2 = 0;

    printf("Matrice M (%dx%d):\n", N, N);
    stampaMatrice(M);
    printf("\n");

    printf("Test 1: S=\"%s\", start=(%d,%d)\n", S1, i1, j1);
    printf("verifica(...) = %d\n\n", verifica(M, S1, i1, j1));

    printf("Test 2: S=\"%s\", start=(%d,%d)\n", S2, i2, j2);
    printf("verifica(...) = %d\n\n", verifica(M, S2, i2, j2));

    return 0;
}
int cerca(char parola[], int segna, int r, int c, char mat[N][N], int *trovato_r, int *trovato_c)
    {
    for(int scorri_c=-1; scorri_c<=1; scorri_c++)
        {
            for(int scorri_r=-1;scorri_r<=1; scorri_r++)
                {
                    if(c+scorri_c>=0 && r+scorri_r>=0 && r+scorri_r<N && c+scorri_c<N && mat[r+scorri_r][c+scorri_c]==parola[segna]&& !(scorri_c==0 && scorri_r==0))
                    {
                        *trovato_c=c+scorri_c;
                        *trovato_r=r+scorri_r;
                        return 1;
                    }
                }
        }
        return 0;
    }
int f(char parola[], char mat[N][N], int segna, int r, int c)
    {
    int new_r=0;
    int new_c=0;
    if(segna==strlen(parola)-1)
        return 1;
    int ris=cerca(parola, segna+1, r, c, mat, &new_r, &new_c);
    if(ris==0)
        return 0;
    if(ris==1)
        {
                {
                    return f(parola, mat, segna+1, new_r, new_c);
                }
        }
    return 0;
    }

int wrapper(char parola[],char mat[N][N])
    {
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(parola[0]==mat[r][c])
                        {
                            if(f(parola, mat, 0, r, c))
                                return 1;
                        }
                }
        }
    return 0;
    }
int verifica(char M[N][N], const char *S, int i, int j)
{
    return wrapper(S, M);
}
