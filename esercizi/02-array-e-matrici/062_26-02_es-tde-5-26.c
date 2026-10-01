//
//  main.c
//  es tde 5 26
//
//  Created by Francesco Roscio Ricon on 26/02/26.
//

#include <stdio.h>

#define N 6   /* numero massimo colonne */

int f(int M[][N], int R, int C);
void stampa(int M[][N], int R, int C)
{
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            printf("%3d", M[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    /* =========================
       MATRICE 1 (SPARSA)
       ========================= */
    int M1[5][N] = {
        {3,3,3,2},
        {3,1,3,3},
        {5,3,3,4},
        {1,2,3,3},
        {3,3,3,3}
    };

    int R1 = 5;
    int C1 = 4;

    printf("=== MATRICE 1 ===\n");
    stampa(M1, R1, C1);

    int ris1 = f(M1, R1, C1);

    printf("Risultato f: %d\n\n", ris1);


    /* =========================
       MATRICE 2 (NON SPARSA)
       ========================= */
    int M2[4][N] = {
        {1,2,3,4},
        {2,3,4,1},
        {3,4,1,2},
        {4,1,2,3}
    };

    int R2 = 4;
    int C2 = 4;

    printf("=== MATRICE 2 ===\n");
    stampa(M2, R2, C2);

    int ris2 = f(M2, R2, C2);

    printf("Risultato f: %d\n", ris2);

    return 0;
}
int trova(int x, int mat[N][N])
    {
    int count=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(mat[r][c]==x)
                        count++;
                }
        }
    return count;
    }
int f(int M[][N], int R, int C)
    {
    int max=0;
    int num_occ=0;
    for(int r=0; r<R; r++)
        {
            for(int c=0; c<C; c++)
                {
                    int occ=trova(M[r][c], M);
                    if(occ>num_occ)
                        {
                            occ=num_occ;
                            max=M[r][c];
                        }
                }
        }
    return max;
    }
