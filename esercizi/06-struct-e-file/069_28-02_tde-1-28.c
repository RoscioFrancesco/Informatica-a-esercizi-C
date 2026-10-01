//
//  main.c
//  tde 1 28
//
//  Created by Francesco Roscio Ricon on 28/02/26.
//

#include <stdio.h>

#define N 5


int f(int M[][N]);

/* ====== STRUCT SOLO PER ORGANIZZARE I TEST ====== */
typedef struct {
    const char *nome;
    int M[N][N];
    int atteso;
} TestCase;

/* ====== STAMPA MATRICE ====== */
void stampaMatrice(const char *titolo, int M[][N]) {
    printf("%s\n", titolo);
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            printf("%4d", M[r][c]);
        }
        printf("\n");
    }
}

int main(void) {
    TestCase tests[] = {
        {
            "TEST 1 (atteso: 1)",
            /* somme righe: 9, 5, 1, 6, 10  -> (matrice costruita per essere "a V") */
            {
                {2,2,2,2,1},   /* 9  */
                {1,1,1,1,1},   /* 5  */
                {1,0,0,0,0},   /* 1  */
                {2,1,1,1,1},   /* 6  */
                {2,2,2,2,2}    /* 10 */
            },
            1
        },
        {
            "TEST 2 (atteso: 0)",
            /* somme righe: 1, 2, 3, 4, 5  -> (crescente: NON può fare una 'V') */
            {
                {1,0,0,0,0},   /* 1 */
                {1,1,0,0,0},   /* 2 */
                {1,1,1,0,0},   /* 3 */
                {1,1,1,1,0},   /* 4 */
                {1,1,1,1,1}    /* 5 */
            },
            0
        },
        {
            "TEST 3 (atteso: 1)",
            /* somme righe: 6, 1, 4, 7, 9 -> (matrice costruita per essere "a V") */
            {
                {2,1,1,1,1},   /* 6 */
                {1,0,0,0,0},   /* 1 */
                {2,1,1,0,0},   /* 4 */
                {2,2,1,1,1},   /* 7 */
                {2,2,2,2,1}    /* 9 */
            },
            1
        }
    };

    int ntests = (int)(sizeof(tests) / sizeof(tests[0]));

    for (int t = 0; t < ntests; t++) {
        printf("====================================\n");
        printf("%s\n", tests[t].nome);
        stampaMatrice("Matrice:", tests[t].M);

        int ris = f(tests[t].M);  
        printf("Risultato f(M) = %d\n", ris);
        printf("Atteso          = %d\n", tests[t].atteso);
    }

    return 0;
}
int sommariga(int R, int mat[N][N])
    {
    int somma=0;
    for(int c=0; c<N; c++)
        {
            somma=somma+mat[R][c];
        }
    return somma;
    }
int f(int M[N][N])
    {
    int array[N];
    for(int R=0; R<N; R++)
        {
            array[R]=sommariga(R, M);
        }
    int min=array[0];
    int i=0;
    for (int s=0; s<N; s++)
        {
            if(array[s]<min)
                {
                    min=array[s];
                    i=s;
                }
        }
    for(int s=0; s<N-1; s++)
        {
            if(s<i)
                {
                    if(!(array[s]>array[s+1]))
                        return 0;
                }
            if(s>i)
                {
                    if(!(array[s+1]>array[s]))
                        return 0;
                }
        }
    return 1;
    }
