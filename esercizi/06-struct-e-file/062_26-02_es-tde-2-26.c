//
//  main.c
//  es tde 2 26
//
//  Created by Francesco Roscio Ricon on 26/02/26.
//
#include <stdio.h>
#define N 3
#define M 5

/* (Opzionale) struct solo per “impacchettare” i parametri di test */
typedef struct {
    int k;
    int h;
    int atteso;
    const char *nome;
} Test;


int CercaUniSottomatrici(int m[N][M], int k, int h);
int cercaval(int x, int k, int mat[N][M], int r, int c);

static void stampaMatrice(int a[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%3d", a[i][j]);
        }
        printf("\n");
    }
}
int CercaUniSottomatrici(int m[N][M], int k, int h);
int main(void) {

    /* === MATRICE ESEMPIO 1 (atteso 0 per k=2, h=3) === */
    int mat1[N][M] = {
        {1, 2, 0, 1, 0},
        {3, 0, 2, 0, 3},
        {1, 2, 1, 1, 2}
    };

    /* === MATRICE ESEMPIO 2 (atteso 1 per k=2, h=3) === */
    int mat2[N][M] = {
        {1, 2, 0, 2, 0},
        {3, 0, 2, 0, 3},
        {1, 2, 1, 1, 2}
    };

    Test t = { .k = 2, .h = 3, .atteso = -1, .nome = "k=2, h=3" };

    int res;

    printf("=== TEST 1 (%s) ===\n", t.nome);
    stampaMatrice(mat1);
    res = CercaUniSottomatrici(mat1, t.k, t.h);
    printf("Risultato: %d (atteso: 0)\n\n", res);

    printf("=== TEST 2 (%s) ===\n", t.nome);
    stampaMatrice(mat2);
    res = CercaUniSottomatrici(mat2, t.k, t.h);
    printf("Risultato: %d (atteso: 1)\n\n", res);

    return 0;
}
int cercaval(int x, int k, int mat[N][M], int r, int c)
    {
    int count=0;
    for(int scorri_r=0; r+scorri_r<N && scorri_r<k; scorri_r++)
        {
            for(int scorri_c=0; c+scorri_c<M && scorri_c<k; scorri_c++)
                {
                    if(mat[r+scorri_r][c+scorri_c]==x)
                        count++;
                }
        }
    return count;
    }
int CercaUniSottomatrici(int m[N][M], int k, int h)
    {
    int array_k[N*M];
    int array_h[N*M];
    int segna=0;
    for(int r=0; r<N && r<=N-k; r++)
        {
            for(int c=0; c<M && c<=M-k; c++)
                {
                    array_k[segna]=cercaval(1, k, m, r, c);
                    segna++;
                }
        }
    int segna2=0;
    for(int r=0; r<N && r<=N-h; r++)
        {
            for(int c=0; c<M && c<=M-h; c++)
                {
                    array_h[segna2]=cercaval(1, h, m, r, c);
                    segna2++;
                }
        }
    for(int i=0;i<segna; i++)
        {
            for(int j=0;j<segna2; j++)
                {
                    if(array_h[j]==array_k[i])
                        return 1;
                }
        }
    return 0;
    }
