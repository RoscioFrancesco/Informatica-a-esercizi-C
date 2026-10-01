//
//  main.c
//  es 7 25 feb
//
//  Created by Francesco Roscio Ricon on 25/02/26.
//

#include <stdlib.h>
#include <stdio.h>
#define N 100
#define M 8

typedef struct {int x,y;} Punto;
void stampaPercorso(Punto per1[], int len1);
void pulisci(Punto per1[], Punto per2[], int len1, int *len2);
char *f(char matr[M][M], Punto array[], int len1);
int main(){
    Punto per1[100]={{0,0},{0,-4},{2,6},{4,5},{3,1},{7,2},{8,2},{2,-4}};
    Punto per2[100];
    int lung1=8,lung2=0;
    char mat[M][M]={'B','R','S','P','E','E','F','A',
                    'Y','V','K','W','F','H','H','W',
                    'J','C','S','I','E','R','R','F',
                    'F','V','C','P','L','N','B','Q',
                    'P','C','D','F','Y','A','O','P',
                    'C','G','W','S','C','Q','O','O',
                    'D','H','H','S','L','L','U','I',
                    'X','R','O','L','E','N','T','Y'};
    
    stampaPercorso(per1, lung1);
    pulisci(per1, per2, lung1, &lung2);
    printf("\n");
    stampaPercorso(per2, lung2);
    char *punt=NULL;
    punt=f(mat, per2, lung2);
    printf("%s", punt);
    
}
void stampaPercorso(Punto per1[], int len1)
    {
    for(int i=0; i<len1; i++)
        {
            printf("(%d,%d) ", per1[i].x, per1[i].y);
        }
    }
void pulisci(Punto per1[], Punto per2[], int len1, int *len2)
    {
    for(int i=0; i<len1; i++)
        {
            if(per1[i].x>=0 && per1[i].y>=0 && per1[i].x<M && per1[i].y<M)
                {
                    per2[*len2]=per1[i];
                    (*len2)++;
                }
        }
    }
char *f(char matr[M][M], Punto array[], int len1)
    {
    char *parola=malloc(sizeof(char)*M*M);
    int segna=0;
    for(int i=0; i<len1; i++)
        {
            parola[segna]=matr[array[i].x][array[i].y];
            segna++;
        }
    parola[segna]='\0';
    return parola;
    }
