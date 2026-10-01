//
//  main.c
//  tde feb 2024
//
//  Created by Francesco Roscio Ricon on 09/11/25.
// Riferimento: Informatica A (061202), TDE febbraio 2024, a.a. 2023/24: https://forms.office.com/e/9TP0e1k9Dp

#include <stdio.h>
#define N 8
int colonneMassime (int M[][N], int ris[], int num_righe);
int maxProdColonna (int M[][N], int colonna, int num_righe);
int main() {
    int len1, len2, len3, ris[N];
        int M1[8][N] = {
        {1, 2, 3, 4, 5, 6, 7, 8},
        {8, 7, 6, 5, 1, 3, 2, 1},
        {2, 3, 4, 5, 6, 7, 8, 9},
        {9, 8, 7, 6, 5, 4, 3, 2},
        {1, 3, 5, 7, 9, 7, 5, 3},
        {3, 0, 4, 1, 5, 9, 2, 6},
        {6, 2, 9, 5, 1, 4, 9, 3},
        {3, 5, 7, 9, 7, 5, 3, 1}
    };
    int M2[4][N] = {
        {1, 2, 3, 4, 5, 6, 7, 8},
        {8, 7, 6, 5, 1, 3, 2, 1},
        {2, 3, 4, 5, 6, 7, 8, 9},
        {3, 5, 7, 9, 7, 5, 3, 1}
    };
    int M3[2][N] = {
        {1, 2, 3, 4, 5, 6, 7, 8},
        {3, 5, 7, 9, 7, 5, 3, 1}
    };
    int M4[4][N] = {
        {8, 7, 6, 5, 1, 3, 2, 1},
        {1, 3, 5, 7, 9, 7, 5, 3},
        {3, 0, 4, 1, 5, 9, 2, 6},
        {3, 5, 7, 9, 7, 5, 3, 1}
    };
    len1=colonneMassime(M1, ris, 8);
    int i;
    for(i=0; i<len1; i++)
        {
            printf("%d", ris[i]);
        }
    
    return 0;
}
int maxProdColonna (int M[][N], int colonna, int num_righe) // gli devo inserire il lumero di righe
    {
    int i=0, j=0, z=0;
    int array_di_prod[N*N*N];
    for(i=0; i<num_righe; i++)
        {
            for(j=i+1; j<num_righe; j++)
                {
                    array_di_prod[z]= M[i][colonna]*M[j][colonna];
                    z++;
                }
        }
    int max=array_di_prod[0];
    for(i=0; i<z; i++)
        {
            if(array_di_prod[i]>max)
                {
                    max= array_di_prod[i];
                }
        }
    return max;
    }
int colonneMassime (int M[][N], int ris[], int num_righe)
    {
    int i;
    int max;
    int contatore=0;
    int array_prod_colonne[N];
    for(i=0; i<N; i++)
        {
            array_prod_colonne[i]=maxProdColonna(M, i, num_righe);
        }
    max=array_prod_colonne[0];
    for(i=0; i<N; i++)
        {
            if(array_prod_colonne[i]>max)
                max=array_prod_colonne[i];
        }
    for(i=0; i<N; i++)
        {
            if(array_prod_colonne[i]==max)
            {
                ris[contatore]=i;
                contatore++;
            }
        }
    return contatore;
    }
