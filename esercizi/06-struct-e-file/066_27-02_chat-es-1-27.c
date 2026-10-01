//
//  main.c
//  chat es 1 27
//
//  Created by Francesco Roscio Ricon on 27/02/26.
//
#include <stdio.h>
#include <stdlib.h>

#define N 6

typedef struct {
    int lato;   // lato massimo trovato
    int r0;     // riga in alto a sinistra del quadrato (se vuoi anche la posizione)
    int c0;     // colonna in alto a sinistra
} Risultato;

/* =========================
   PROTOTIPI (DA FARE TU)
   ========================= */
int latoMaxQuadratoPari(int M[][N]);

Risultato latoMaxQuadratoPariPos(int M[][N]);

void stampaMatrice(const char *titolo, int M[][N]) {
    printf("\n%s\n", titolo);
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            printf("%4d", M[r][c]);
        }
        printf("\n");
    }
}
int f(int mat[N][N]);
int isola(int r,int c, int mat[N][N]);
int verifica(int r, int c, int k, int mat[N][N]);

int main(void) {
    /* Caso 1: c'è un 3x3 di pari (lato massimo atteso: 3) */
    int M1[N][N] = {
        { 2,  4,  6,  9,  8,  2},
        {10, 12, 14,  7,  6,  4},
        { 8, 16, 18,  5,  2,  2},
        { 3,  2,  4,  6,  8, 10},
        { 5,  6,  8, 12, 14, 16},
        { 7,  2,  2,  2,  4,  6}
    };

    /* Caso 2: tutti dispari -> nessun quadrato di pari (lato massimo atteso: 0) */
    int M2[N][N] = {
        { 1, 3, 5, 7, 9, 1},
        { 3, 5, 7, 9, 1, 3},
        { 5, 7, 9, 1, 3, 5},
        { 7, 9, 1, 3, 5, 7},
        { 9, 1, 3, 5, 7, 9},
        { 1, 3, 5, 7, 9, 1}
    };

    /* Caso 3: tutti pari -> lato massimo atteso: N */
    int M3[N][N] = {
        { 2,  2,  2,  2,  2,  2},
        { 4,  4,  4,  4,  4,  4},
        { 6,  6,  6,  6,  6,  6},
        { 8,  8,  8,  8,  8,  8},
        {10, 10, 10, 10, 10, 10},
        {12, 12, 12, 12, 12, 12}
    };

    stampaMatrice("M1:", M1);
    printf("\nLato max quadrato di soli pari in M1 = %d\n", latoMaxQuadratoPari(M1));
    Risultato r1 = latoMaxQuadratoPariPos(M1);
    printf("Dettaglio (facoltativo): lato=%d, top-left=(%d,%d)\n", r1.lato, r1.r0, r1.c0);

    stampaMatrice("M2:", M2);
    printf("\nLato max quadrato di soli pari in M2 = %d\n", latoMaxQuadratoPari(M2));
    Risultato r2 = latoMaxQuadratoPariPos(M2);
    printf("Dettaglio (facoltativo): lato=%d, top-left=(%d,%d)\n", r2.lato, r2.r0, r2.c0);

    stampaMatrice("M3:", M3);
    printf("\nLato max quadrato di soli pari in M3 = %d\n", latoMaxQuadratoPari(M3));
    Risultato r3 = latoMaxQuadratoPariPos(M3);
    printf("Dettaglio (facoltativo): lato=%d, top-left=(%d,%d)\n", r3.lato, r3.r0, r3.c0);

    return 0;
}

/* =========================
   STUB (NON RISOLVO)
   ========================= */
int latoMaxQuadratoPari(int M[][N]) {
    return f(M);
}

Risultato latoMaxQuadratoPariPos(int M[][N]) {
    (void)M;
    Risultato out;
    out.lato = -1;  // placeholder
    out.r0 = -1;
    out.c0 = -1;
    return out;
}
int verifica(int r, int c, int k, int mat[N][N]) // verifca che una sottomatrice di lato k sia fatta di pari
    {
    for(int scorri_r=0; scorri_r<=k && r+scorri_r<N; scorri_r++)
        {
            for(int scorri_c=0; scorri_c<=k && c+scorri_c<N; scorri_c++)
                {
                    if(mat[r+scorri_r][c+scorri_c]%2==1)
                        return 0;
                }
        }
    return 1;
    }
int min(int a, int b)
    {
        if(a<b)
            return a;
    return b;
    }
int isola(int r,int c, int mat[N][N])
    {
    int k=0;
    for(k=1; k<min(N-r, N-c);)
        {
            if(verifica(r, c, k, mat)==0)
                break;
            k++;
        }
    return k;
    }
int f(int mat[N][N])
    {
    int max=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    int num=0;
                    if(mat[r][c]%2==0)
                    {
                        num=isola(r, c, mat);
                    }
                    if(num>max)
                        max=num;
                }
        }
    return max;
    }
