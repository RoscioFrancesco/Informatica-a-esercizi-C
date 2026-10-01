//  Created by Francesco Roscio Ricon on 08/11/25.

#include <stdio.h>
#define N 100
int analizzaMatrice(int fighi[], int M[N][N], int n_reale);
int riga(int M[N][N], int r, int c, int n_reale);
void acquisici_matrice(int M[N][N], int n_reale);
int colonna(int M[N][N], int r, int c, int n_reale);
int d1(int M[N][N], int r, int c, int n_reale);
int d2(int M[N][N], int r, int c, int n_reale);
int main() {
    int n_reale, r, c, fighi[N*N];
    int M[N][N];
    int k;
    int i;
    printf("Inserisci dimensioni reali matrice n*n");
    scanf("%d", &n_reale);
    acquisici_matrice(M, n_reale);
    k= analizzaMatrice(fighi, M, n_reale);
    for(i=0; i<k;i++)
        printf("%d", fighi[i]);
}
void acquisici_matrice(int M[N][N], int n_reale)
    {
    int r,c;
    for(r=0; r<n_reale; r++)
        {
            for(c=0; c<n_reale; c++)
            {
                printf("Inserisci l'elemento [%d][%d]", r,c);
                scanf("%d", &M[r][c]);
            }
        }
    }
int analizzaMatrice(int fighi[], int M[N][N], int n_reale)
    {
    int r=0 , c=0, k=0;
    for(r=0; r<n_reale; r++)
        {
            for(c=0; c<n_reale; c++)
                {
                    if(riga(M,r,c,n_reale) && colonna(M,r,c,n_reale) && d1(M,r,c,n_reale) && d2(M,r,c,n_reale))
                    {
                        fighi[k]=M[r][c];
                        k++;
                    }
                }
        }
    return k;
    }
int riga(int M[N][N], int r, int c, int n_reale)
    {
    int flag=1;
    int cs; // colonne search (cs)     righe serch(rs)
    for(cs=0; cs<n_reale && flag==1; cs++)
        {
            if (M[r][c]<M[r][cs])
                {
                flag=0;
                }
        }
    return flag; // è quindi vero che è maggiore di tutti gli elementi della riga
    }
int colonna(int M[N][N], int r, int c, int n_reale)
    {
    int flag=1;
    int rs;
    for(rs=0; rs<n_reale && flag==1; rs++)
        {
            if (M[r][c]<M[rs][c])
                {
                flag=0;
                }
        }
    return flag; // è quindi vero che è maggiore di tutti gli elementi della colonna
    }
int d1(int M[N][N], int r, int c, int n_reale)
{
    int flag=1;
    int cs=c, rs=r;
    for(cs=r, rs=r; cs<n_reale && rs>=0; cs++, rs--)
    {
        
        if (M[r][c]<M[rs][cs])
        {
            flag=0;
        }
    }
    cs=c;
    rs=r;
    for(cs=r, rs=r; cs>=0 && rs<n_reale; cs--, rs++)
    {
        
        if (M[r][c]<M[rs][cs])
        {
            flag=0;
        }
    }
    return flag;
}
int d2(int M[N][N], int r, int c, int n_reale)
{
    int flag=1;
    int cs=c, rs=r;
    for(cs=r, rs=r; cs>=0 && rs>=0; cs--, rs--)
    {
        
        if (M[r][c]<M[rs][cs])
        {
            flag=0;
        }
    }
    cs=c;
    rs=r;
    for(cs=r, rs=r; cs<n_reale && rs<n_reale; cs++, rs++)
    {
        
        if (M[r][c]<M[rs][cs])
        {
            flag=0;
        }
    }
    return flag;
}
