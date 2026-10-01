//
//  main.c
//  tde 4 28
//
//  Created by Francesco Roscio Ricon on 28/02/26.
//
#include <stdio.h>
#define N 8
int potenza(int base, int exp);
int converti(int vett[], int len);
float f(char mat[N][N]);

int main()
{
char M[N][N] = {
    /* riga 0: "1011"  -> termina con '\0' */
    {'1','0','1','1','\0','\0','\0','\0'},

    /* riga 1: "0" */
    {'0','\0','\0','\0','\0','\0','\0','\0'},

    /* riga 2: "1111111" */
    {'1','1','1','1','1','1','1','\0'},

    /* riga 3: "100000" */
    {'1','0','0','0','0','0','\0','\0'},

    /* riga 4: "" (stringa vuota, rappresenta 0 se la gestisci così) */
    {'\0','\0','\0','\0','\0','\0','\0','\0'},

    /* riga 5: "10" */
    {'1','0','\0','\0','\0','\0','\0','\0'},

    /* riga 6: "11001" */
    {'1','1','0','0','1','\0','\0','\0'},

    /* riga 7: "101010" */
    {'1','0','1','0','1','0','\0','\0'}
    
    };
    printf("%f", f(M));
    
}
int converti(int vett[], int len)
    {
    int somma=0;
    int j=0;
    for(int i=len-1; i>=0; i--)
        {
            somma=somma+vett[j]*(potenza(2, i));
            j++;
        }
    return somma;
    }
int potenza(int base, int exp)
    {
    int prod=1;
    for(int i=0; i<exp; i++)
        {
            prod=prod*base;
        }
    return prod;
    }
float f(char mat[N][N])
    {
    float somma=0;
    for(int r=0; r<N; r++)
        {
            int vett[N];
            int len=0;
            for(int c=0; c<N; c++)
                {
                    if(mat[r][c]=='\0')
                        break;
                    vett[c]=mat[r][c]-'0';
                    len++;
                }
            printf("\n");
            for(int i=0; i<len; i++)
                {
                    printf("%d", vett[i]);
                }
            printf("\n%d", len);
            int num=converti(vett, len);
            printf("\n num:%d", num);
            somma=somma+num;
        }
    return somma/N;
    }
