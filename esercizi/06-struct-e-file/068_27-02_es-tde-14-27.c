//
//  main.c
//  es tde 14 27
//
//  Created by Francesco Roscio Ricon on 27/02/26.
//

#include <stdio.h>

#define N 6

/* ====== STRUTTURA (non necessaria strettamente, ma la mettiamo come richiesto) ====== */
typedef struct {
    int M[N][N];
} Matrix;

/* ====== PROTOTIPO ====== */
int f(int M[][N]);   // NON IMPLEMENTATA

int funz(int M[N][N], int r, int c, int expected);
int main() {

    /* ====== MATRICE 1 (CHESSBOARD) ====== */
    Matrix m1 = { {
        { 0,  5,  0, 21,  0,  7 },
        { 6,  0,  4,  0,  2,  0 },
        { 0,  4,  0, 11,  0,  8 },
        {55,  0, 33,  0, 55,  0 },
        { 0,  5,  0, 21,  0,  9 },
        {22,  0,  1,  0, 32,  0 }
    } };

    /* ====== MATRICE 2 (CHESSBOARD) ====== */
    Matrix m2 = { {
        {22,  0,  1,  0, 32,  0 },
        { 0,  5,  0, 21,  0,  7 },
        { 6,  0,  4,  0,  2,  0 },
        { 0,  4,  0, 11,  0,  8 },
        {55,  0, 33,  0, 55,  0 },
        { 0,  5,  0, 21,  0,  9 }
    } };

    /* ====== MATRICE 3 (NON CHESSBOARD) ====== */
    Matrix m3 = { {
        { 0,  5,  0, 21,  0,  7 },
        { 0,  4,  0,  2,  0,  4 },
        { 0,  4,  0, 11,  0,  8 },
        {55,  0, 33,  0, 55,  0 },
        { 0,  5,  0, 21,  0,  9 },
        {22,  0,  1,  0, 32,  0 }
    } };


    /* ====== STAMPA E TEST ====== */
    Matrix *matrici[3] = { &m1, &m2, &m3 };

    for(int k = 0; k < 3; k++) {
        printf("\n=== MATRICE %d ===\n", k+1);

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                printf("%4d", matrici[k]->M[i][j]);
            }
            printf("\n");
        }

        printf("Risultato f: %d\n", f(matrici[k]->M));
    }

    return 0;
}



int f(int M[][N]) {
    int expected=0;
    if(M[0][0]==0)
        expected=0;
    else
        {
            expected=1;
        }
    return funz(M, 0, 0, expected);
}
int funz(int M[N][N], int r, int c, int expected) // 1 =diverso da 0
    {
        int num=0;
        if(M[r][c]!=0)
            num=1;
        if(num!=expected)
            return 0;
        if (r == N-1 || c == N-1)
            return 1;
        int new_expected=0;
        if(expected==0)
            new_expected=1;
        return funz(M, r+1, c, new_expected) && funz(M, r, c+1, new_expected);
    }
