//  Created by Francesco Roscio Ricon on 27/02/26.

#include <stdio.h>

#define N 6
#define M 7

int f(float mat[N][M]);
int ver(float mat[N][M], int r, int c);
int main(void) {

    float A[N][M] = {
        // 7 colonne
        { 20.0,  1.0,  2.0,  1.0,  2.0,  1.0, 18.0 },
        {  1.0,  3.0,  1.0,  2.0,  1.0,  3.0,  1.0 },
        {  2.0,  1.0, 14.0,  1.0, 12.0,  1.0,  2.0 },
        {  1.0,  2.0,  1.0,  4.0,  1.0,  2.0,  1.0 },
        {  2.0,  1.0, 10.0,  1.0, 16.0,  1.0,  2.0 },
        { 17.0,  1.0,  2.0,  1.0,  2.0,  1.0, 19.0 }
    };

    // stampa di controllo (solo per vedere i valori caricati)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%6.1f", A[i][j]);
        }
        printf("\n");
    }

    printf("\n%d", f(A));
    return 0;
}
int ver(float mat[N][M], int r, int c)
    {
    for(int scorri_r=-1; scorri_r<=1 && r+scorri_r>=0 && r+scorri_r<N; scorri_r++)
        {
            for(int scorri_c=-1; scorri_c<=1 && c+scorri_c>=0 && c+scorri_c<M; scorri_c++)
                {
                    if(!(scorri_c==0 && scorri_r==0) && !(mat[r][c]/2>mat[r+scorri_r][c+scorri_c]))
                        return 0;
                }
        }
    return 1;
    }
int f(float mat[N][M])
    {
    int count=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<M; c++)
                {
                    if(ver(mat, r, c))
                        count++;
                }
        }
    return count;
    }
