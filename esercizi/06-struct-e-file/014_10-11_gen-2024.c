//
//  main.c
//  gen 2024
//
//  Created by Francesco Roscio Ricon on 10/11/25.
//
// Riferimento: Informatica A (061202), TDE gennaio 2024, a.a. 2023/24: https://forms.office.com/e/REVRfR3pbc
#include <stdio.h>
#define N 8  // Numero di colonne (per matrici 8x8 o superiori)

typedef struct{
    int num1;
    int num2;
}coppia;
int analizzaMatrice(int k, int M[N][N], int num_righe, int num_colonne);
int analizzaMatrice2(int k, int M[N][N], int num_righe, int num_colonne, coppia array[], int *num_array);
int main() {
    int k;
    int M1[N][N] = {
        {1, 2, 3, 4, 50, 6, 7, 8},
        {8, 7, 6, 50, 1, 3, 2, 1},
        {2, 3, 4, 5, 6, 7, 8, 9},
        {9, 8, 7, 6, 5, 4, 3, 2},
        {1, 3, 5, 7, 9, 7, 5, 3},
        {3, 0, 4, 1, 5, 9, 2, 6},
        {6, 2, 90, 5, 1, 4, 9, 3},
        {3, 5, 7, 9, 7, 5, 3, 1}
    };
    coppia array[N*N*N*N];
    int lung_array;
    int i;
    
// k = 35;
//
 k = 200;
//
//    k = 90;
    analizzaMatrice(k, M1, N, N);
    analizzaMatrice2(k, M1, N, N, array, &lung_array);
    int ris=analizzaMatrice(k, M1, N, N);;
    printf("%d", ris);
    for(i=0;i<lung_array; i++)
        {
            printf("(%d,%d) ", array[i].num1, array[i].num2);
        }
    
}
int analizzaMatrice(int k, int M[N][N], int num_righe, int num_colonne)
    {
    int r,c;
    int counter=0;
    for(r=0; r<num_righe; r++)
        {
            for(c=0; c<num_colonne; c++)
                {
                    if(M[r][c]*M[r][c+1]==k && r!=num_righe-1 &&c!=num_colonne-1)
                        {
                            counter++;
                        }
                    if(M[r][c]*M[r+1][c]==k && r!=num_righe-1 && c!=num_colonne-1)
                       {
                            counter++;
                        }
                    if(M[r][c]*M[r+1][c]==k && r!=num_righe-1 && c==num_colonne-1)
                        {
                            counter++;
                        }
                    if(M[r][c+1]*M[r][c]==k && r==num_righe-1 && c!=num_colonne-1)
                        {
                            counter++;
                        }
                }
        }
        return counter;
    
    }
int analizzaMatrice2(int k, int M[N][N], int num_righe, int num_colonne, coppia array[], int *num_array)
    {
    int r=0,c=0;
    int counter=0;
    int scorri_array=0;
    for(r=0; r<num_righe; r++)
        {
            for(c=0; c<num_colonne; c++)
                {
                    if(M[r][c]*M[r][c+1]==k && r!=num_righe-1 && c!=num_colonne-1)
                    {
                        counter++;
                        array[scorri_array].num1=M[r][c];
                        array[scorri_array].num2=M[r][c+1];
                        scorri_array++;
                    }
                    if(M[r+1][c]*M[r][c]==k && r!=num_righe-1 && c!=num_colonne-1)
                    {
                        counter++;
                        array[scorri_array].num1=M[r][c];
                        array[scorri_array].num2=M[r+1][c];
                        scorri_array++;
                    }
                    if(M[r][c]*M[r+1][c]==k && r!=num_righe-1 && c==num_colonne-1)
                        {
                            counter++;
                            array[scorri_array].num1=M[r][c];
                            array[scorri_array].num2=M[r+1][c];
                            scorri_array++;
                        }
                    if(M[r][c+1]*M[r][c]==k && r==num_righe-1 && c!=num_colonne-1)
                        {
                            counter++;
                            array[scorri_array].num1=M[r][c];
                            array[scorri_array].num2=M[r][c+1];
                            scorri_array++;
                        }
                    
                }
        }
    *num_array=counter;
    return counter;
}
