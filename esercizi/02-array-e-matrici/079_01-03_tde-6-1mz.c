//
//  main.c
//  tde 6 1mz
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//

#include <stdio.h>
#define N 6
#include <math.h>
/* Caso A: doppiamente primi sparsi (utile per testare f) */
int MA[N][N] = {
    {  4,  10,  12,  15,   8,   9 },
    { 11,   2,  18,  21,  14,  16 },
    { 22,  19,  23,  26,  20,  24 },
    { 25,  28,  30,  37,  32,  33 },
    { 34,  35,  36,  38,   5,  40 },
    { 41,  42,  43,  44,  45,   7 }
};
/* Caso B: doppiamente primi tutti connessi (utile per testare g)
   (qui li metto in un “serpentone” 8-connesso) */
int MB[N][N] = {
    {  6,  23,  10,  12,  14,  16 },
    { 18,  37,  19,  21,  22,  24 },
    { 26,  53,  28,  30,  31,  33 },
    { 35,  73,  36,  38,  39,  40 },
    { 41, 233,  42,  44,  45,  46 },
    { 48, 257,  50,  51,  52,  54 }
};

int isola(int r, int c, int mat[N][N]);
int f(int M[N][N]);
int count(int M[N][N]);
void funz(int mat[N][N], int r, int c, int *count);
int puntoB(int mat[N][N]);

int main() {
    // stampa veloce per controllare
    printf("MA:\n");
    for(int i=0;i<N;i++){ for(int j=0;j<N;j++) printf("%4d", MA[i][j]); printf("\n"); }
    printf("\n %d\n", f(MA));
    
    printf("\nMB:\n");
    for(int i=0;i<N;i++){ for(int j=0;j<N;j++) printf("%4d", MB[i][j]); printf("\n"); }
    
    printf("\n%d", puntoB(MB));
    return 0;
}
int primo(int n) {
    if (n <= 1)
        return 0;

    if (n == 2)
        return 1;

    if (n % 2 == 0)
        return 0;

    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0)
            return 0;
    }

    return 1;
}
int ver(int x)
{
    if (!primo(x))
        return 0;

    while (x > 0)
    {
        int cifra = x % 10;

        if (!(cifra == 2 || cifra == 3 || cifra == 5 || cifra == 7))
            return 0;

        x /= 10;
    }

    return 1;
}
int isola(int r, int c, int mat[N][N])
    {
    for(int scorri_r=-1; scorri_r<=1; scorri_r++)
        {
            for(int scorri_c=-1; scorri_c<=1; scorri_c++)
                {
                    if(r+scorri_r>=0 && c+scorri_c>=0 && r+scorri_r<N && c+scorri_c<N && !(scorri_c==0 && scorri_r==0) && ver(mat[r+scorri_r][c+scorri_c]))
                        return 0;
                }
        }
    return 1;
    }
int f(int M[N][N])
    {
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(ver(M[r][c]))
                        {
                            if(isola(r, c, M)==0)
                                return 0;
                        }
                }
        }
    return 1;
    }

int count(int M[N][N])
    {
    int c=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(ver(M[r][c]))
                        {
                            c++;
                        }
                }
        }
    return c;
    }
void funz(int mat[N][N], int r, int c, int *count)
    {
        if(r>=N-1 || c>=N-1 || r<=0 || c<=0)
            return;
        if(ver(mat[r][c]))
            {
                (*count)++;
            }
        else
            {
                return;
            }
    funz(mat, r, c-1, count);
    funz(mat, r, c+1, count);
    funz(mat, r-1, c, count);
    funz(mat, r+1, c, count);
    funz(mat, r+1, c+1, count);
    funz(mat, r-1, c-1, count);
    funz(mat, r+1, c-1, count);
    funz(mat, r-1, c+1, count);
    }
int puntoB(int mat[N][N])
    {
    int cont=count(mat);
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(ver(mat[r][c]))
                        {
                            int num=0;
                            funz(mat, r, c, &num);
                            if(num==cont)
                                return 1;
                            return 0;
                        }
                }
        }
    return 0;
    }
