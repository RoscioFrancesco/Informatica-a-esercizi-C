//
//  main.c
//  es 6 7mz
//
//  Created by Francesco Roscio Ricon on 07/03/26.
//

#include <stdio.h>
#include <stdlib.h>

void stampa(int **p, int righe, int  colonne);
int **creaMatrice(int righe, int colonne);
int main() {
    int **punt;
    punt=NULL;
    punt=creaMatrice(5, 5);
    stampa(punt, 5, 5);
}

int **creaMatrice(int righe, int colonne)
    {
    int **r=malloc(sizeof(int *)*righe);
    for(int i=0; i<righe; i++)
        {
            r[i]=malloc(sizeof(int)*colonne);
        }
    int num=0;
    for(int i=0; i<righe; i++)
        {
            for(int j=0; j<colonne; j++)
                {
                    r[i][j]=num;
                    num++;
                }
        }
    return r;
    }
void stampa(int **p, int righe, int  colonne)
    {
    for(int r=0; r<righe; r++)
        {
            printf("\n");
            for(int c=0; c<colonne; c++)
                {
                    printf("%d  ", *(*(p+r)+c));
                }
        }
    }
