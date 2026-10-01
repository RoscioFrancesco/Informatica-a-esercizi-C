//
//  main.c
//  tde conti
//
//  Created by Francesco Roscio Ricon on 07/11/25.

#define N 4
#include <stdio.h>
#include <math.h>
void rimuoviValori(int mat[N][N], int val, int len_r, int len_c, int utente_value);
void rimuovidiagonale(int mat[N][N], int val_min, int len_r, int len_c);
int trova_valmin(int mat[N][N], int utente_value, int len_r, int len_c);
int main()
{
    int utente_value;
    int val_min;
    int M[N][N] = {3, 3, 5, 3, 5, 6, 7, 5, 5, 6, 2, 1, 3, 6, 9, 4};
    scanf("%d", &utente_value);
    int len_c=N, len_r=N;
    
    val_min=trova_valmin(M, utente_value, len_r, len_c);
    printf("%d\n", val_min);
    rimuoviValori(M,val_min, len_r, len_c, utente_value);
    int i=0, j=0;
    for(i=0; i<len_c; i++)
        {
            for(j=0; j<len_r; j++)
            {
                printf("%d", M[i][j]);
                
            }
            printf("\n");
          }
}
void rimuoviValori(int mat[N][N], int val, int len_r, int len_c, int utente_value)
    {
    int r,c, val_min;
    val_min = trova_valmin(mat, utente_value, len_r, len_c);
    for(c=0; c<len_c; c++)
        {
            for(r=0; r<len_r; r++)
                {
                    if(mat[r][c]==val)
                        rimuovidiagonale(mat, val_min, len_r, len_c);
                }
        }
    }
void rimuovidiagonale(int mat[N][N], int val_min, int len_r, int len_c)
    {
    int r=0, c=0;
    int x,y;
    for(r=0; r<len_r; r++)
        {
            for(c=0; c<len_c; c++)
                {
                    if(mat[r][c]==val_min)
                        {
                            x=c;
                            y=r;
                        
                            for(x=c; x<len_c && y<len_r; x++)
                                {
                                    mat[y][x]=0;
                                    y++;
                                
                                    
                                }
                            x=c;
                            y=r;
                            for(x=c;x>=0 && y>=0; x--)
                                {
                                    mat[y][x]=0;
                                    y--;
                                }
                        }
                }
        }
    }
int trova_valmin(int mat[N][N], int utente_value, int len_r, int len_c)
{
    int val_min;
    int i=0,j=0;
    int delta=utente_value-mat[0][0];
    if (delta<0) delta=-delta;
    for(i=0; i<len_c; i++)
    {
        for(j=0; j<len_r; j++)
        {
            if(fabs(mat[i][j]-utente_value)<=delta)
            {
                delta=mat[i][j]-utente_value;
                if (delta<0) delta=-delta;
                val_min= mat[i][j];
            }
        }
    }
    return val_min;
    
}

