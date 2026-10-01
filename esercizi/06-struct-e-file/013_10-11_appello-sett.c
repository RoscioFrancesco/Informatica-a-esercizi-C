//
//  main.c
//  appello sett
//
//  Created by Francesco Roscio Ricon on 10/11/25.
//

#include <stdio.h>
#define N 10

typedef struct{
    int posiz_in_vettore;
    int numero;
    int numero_occorrenze;
}coppia_numero;
void trovaFrequenti(int mat[N][N], int len_r, int len_c, coppia_numero j[], int len_j, int *Nmax1, int *Nmax2, int *Nmax3, int *Occmax1, int *Occmax2, int *Occmax3);
int main(){
    int i;
    int vettore[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int len_vettore=10;
    coppia_numero j[N];
    for(i=0; i<len_vettore; i++)
        {
            j[i].numero=vettore[i];
            j[i].posiz_in_vettore=i;
            j[i].numero_occorrenze=0;
        }

    int M1[N][N] = {
        {1, 1, 3, 3, 5, 6, 8, 8, 8, 10},
        {2, 3, 3, 1, 5, 8, 6, 8, 8, 10},
        {10, 9, 3, 2, 5, 6, 7, 8, 1, 4},
        {4, 5, 5, 8, 8, 9, 10, 1, 2, 3},
        {7, 6, 5, 4, 3, 2, 1, 0, 8, 8},
        {2, 4, 5, 8, 10, 1, 3, 5, 7, 9},
        {10, 8, 5, 4, 2, 9, 8, 5, 3, 1},
        {1, 3, 2, 5, 4, 5, 5, 8, 8, 0},
        {0, 1, 2, 3, 4, 5, 6, 8, 8, 8},
        {9, 7, 5, 3, 1, 2, 4, 6, 8, 10}
    };


    int M2[N][N] = {
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {7, 7, 1, 2, 2, 3, 3, 3, 10,10},
        {7, 7, 5, 5, 5, 5, 5, 10, 7,10},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 4},
        {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8}
    };


    int M3[N][N] = {
        {5, 5, 6, 6, 6, 6, 6, 5, 5, 5},
        {1, 2, 2, 2, 9, 3, 4, 4, 4, 4},
        {10, 9, 8, 7, 3, 4, 4, 2, 1, 6},
        {6, 7, 8, 9, 10, 1, 2, 3, 4, 4},
        {10, 10, 10, 10, 10, 1, 1, 1, 10, 10},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5}
    };
    int max1, max2, max3;
    int freqmax1, freqmax2, freqmax3;
    trovaFrequenti(M1, N, N, j, len_vettore, &max1, &max2, &max3, &freqmax1, &freqmax2, &freqmax3);
    printf("valore %d, occorrenze %d\n", max1, freqmax1);
    printf("valore %d, occorrenze %d\n", max2, freqmax2);
    printf("valore %d, occorrenze %d\n", max3, freqmax3);
    
    return 0;
}
void trovaFrequenti(int mat[N][N], int len_r, int len_c, coppia_numero j[], int len_j, int *Nmax1, int *Nmax2, int *Nmax3, int *Occmax1, int *Occmax2, int *Occmax3)
    {
    int i, r,c;
    for(i=0; i<len_j; i++)
        {
            for(r=0; r<len_r; r++)
                {
                    for(c=0; c<len_c; c++)
                        {
                            if(mat[r][c]==j[i].numero)
                                j[i].numero_occorrenze++;
                        }
                }
        }
    int maxtemp=0;
    for(i=0; i<len_j; i++)
        {
            if(j[i].numero_occorrenze>maxtemp)
                {
                    maxtemp=j[i].numero_occorrenze;
                    *Nmax1=j[i].numero;
                    *Occmax1=j[i].numero_occorrenze;
                }
        }
    maxtemp=0;
    for(i=0; i<len_j; i++)
        {
            if(j[i].numero_occorrenze>maxtemp && j[i].numero_occorrenze<*Occmax1)
                {
                    maxtemp=j[i].numero_occorrenze;
                    *Nmax2=j[i].numero;
                    *Occmax2=j[i].numero_occorrenze;
            
                }
        }
    maxtemp=0;
    for(i=0; i<len_j; i++)
        {
            if(j[i].numero_occorrenze>maxtemp && j[i].numero_occorrenze<*Occmax1 && j[i].numero_occorrenze<*Occmax2)
                {
                    maxtemp=j[i].numero_occorrenze;
                    *Nmax3=j[i].numero;
                    *Occmax3=j[i].numero_occorrenze;
                }
        }
    
    
    
    }
