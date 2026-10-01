//
//  main.c
//  es 6 6mz
//
//  Created by Francesco Roscio Ricon on 06/03/26.
//

#include <stdio.h>
#include <stdlib.h>
#define N 3
int sommaDiag(int *mat);
int sommaDiag2(int **mat);
int main() {
    int **mat;
    mat = malloc(N * sizeof(int *));
    for(int i=0; i<N; i++)
    {
        mat[i] = malloc(N * sizeof(int));
    }
    int f=1;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    mat[r][c]=f;
                    f++;
                }
        }
    printf("%d", sommaDiag2(mat));
}
//int sommaDiag(int *mat)
//    {
//    int somma=0;
//    for(int r=0; r<N; r++)
//        {
//            for(int c=0; c<N; c++)
//                {
//                    if(r==c)
//                        {
//                            somma=somma+*(mat+r*N+c);
//                        }
//                }
//        }
//    return somma;
//    }
int sommaDiag2(int **mat)
    {
    int somma=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(r==c)
                        {
                            somma=somma+*(*(mat+r)+c);
                        }
                }
        }
    return somma;
    }
