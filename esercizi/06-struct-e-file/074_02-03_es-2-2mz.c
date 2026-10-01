//
//  main.c
//  es 2 2mz
//
//  Created by Francesco Roscio Ricon on 02/03/26.
//
//  4) Torneo: Tabellone Risultati (array di struct che contengono matrici)

//Definisci:


#define N 8
#include <stdio.h>


typedef char parola[30];

typedef struct{
    parola elenco[N];
    int goal[N][N];
}Torneo;

int main() {
}
int trovavincitore(Torneo t)
    {
    int max=0;
    int indice=0;
    for(int r=0; r<N; r++)
        {
            int sum=0;
            for(int c=0; c<N; c++)
                {
                    if(t.goal[r][c]==t.goal[c][r])
                        sum++;
                    if(t.goal[r][c]>t.goal[c][r])
                        sum=sum+3;
                }
            if(sum>max)
                {
                    indice=r;
                }
        }
    return indice;
    }
void classifica(Torneo t, int punti[])
    {
    for(int r=0; r<N; r++)
        {
            int sum=0;
            for(int c=0; c<N; c++)
                {
                    if(t.goal[r][c]==t.goal[c][r])
                        sum++;
                    if(t.goal[r][c]>t.goal[c][r])
                        sum=sum+3;
                }
            punti[r]=sum;
        }
    }
