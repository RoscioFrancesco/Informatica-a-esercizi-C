//
//  main.c
//  es 6
//
//  Created by Francesco Roscio Ricon on 24/02/26.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 8
#define M 9
char f(char parola[], char matr[N][N], int *riga, int *colonna);
void funz(char P[M][M], char G[N][N]);
int main(){
    int i,k;
    char G[N][N]={'B','R','I','S','A','T','A','B',
                    'A','A','R','A','N','C','I','A',
                    'N','C','I','P','O','L','L','A',
                    'A','V','I','O','L','I','N','O',
                    'N','R','A','T','O','R','T','A',
                    'A','V','O','L','A','N','T','E',
                    'D','I','S','C','O','R','S','O',
                    'A','N','A','T','R','A','V','O'};
    char P[M][M]={'R','I','S','A','T','A','\0','\0','\0',
              'A','R','A','N','C','I','A','\0','\0',
              'B','A','N','A','N','A','\0','\0','\0',
              'C','I','P','O','L','L','A','\0','\0',
              'V','I','O','L','I','N','O','\0','\0',
              'T','O','R','T','A','\0','\0','\0','\0',
              'V','O','L','A','N','T','E','\0','\0',
              'D','I','S','C','O','R','S','O','\0',
              'A','N','A','T','R','A','\0','\0','\0'};
                    
    printf("Matrice caratteri\n");
    for(i=0;i<N;i++){
        for(k=0;k<N;k++){
            printf("%c ",G[i][k]);
        }
        printf("\n");
    }
    printf("\nParole\n");
    for(i=0;i<M;i++){
        printf("%s",P[i]);
        printf("\n");
    }
    funz(P, G);
    printf("Matrice caratteri\n");
    for(i=0;i<N;i++){
        for(k=0;k<N;k++){
            printf("%c ",G[i][k]);
        }
        printf("\n");
    }
    
    
    return 0;
}



// Riferimento: Informatica A (061202), prova in itinere, a.a. 2023/24: https://forms.office.com/e/GdxfxP3mBM
int trova_vert(char parola[], int segna, char matr[N][N], int r, int c)
    {
        if(segna+1==strlen(parola))
            return 1;
        if(r>=N || c>=N)
            return 0;
        if(matr[r][c]!=parola[segna])
            return 0;
    return trova_vert(parola, segna+1, matr, r+1, c);
    }
int trova_orizz(char parola[], int segna, char matr[N][N], int r, int c)
    {
        if(segna+1==strlen(parola))
            return 1;
        if(r>=N || c>=N)
            return 0;
        if(matr[r][c]!=parola[segna])
            return 0;
    return trova_orizz(parola, segna+1, matr, r, c+1);
    }
char f(char parola[], char matr[N][N], int *riga, int *colonna)
    {
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(matr[r][c]==parola[0])
                        {
                            if(trova_orizz(parola, 0, matr, r, c))
                            {
                                *riga=r;
                                *colonna=c;
                                return 'o';
                            }
                            if(trova_vert(parola, 0, matr, r, c))
                            {
                                *riga=r;
                                *colonna=c;
                                return 'v';
                            }
                        }
                }
        }
    return 'n';
    }
void funz(char P[M][M], char G[N][N])
    {
    for(int i=0; i<M; i++)
        {
            char *parola=malloc(sizeof(char)*M);
            int j=0;
            while(P[i][j]!='\0')
                {
                    parola[j]=P[i][j];
                    j++;
                }
            parola[j]='\0';
            int r=0;
            int c=0;
            if(f(parola, G, &r, &c)=='o')
                {
                    for(int i=0; i<strlen(parola); i++)
                        {
                            G[r][c+i]='*';
                        }
                }
            if(f(parola, G, &r, &c)=='v')
                {
                    for(int i=0; i<strlen(parola); i++)
                        {
                            G[r+i][c]='*';
                        }
                }
            free(parola);
        }
    
    }
