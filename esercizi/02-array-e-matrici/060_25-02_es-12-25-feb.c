//  Created by Francesco Roscio Ricon on 25/02/26.


#include <stdio.h>
#define N 8
int f(char matr[N][N]);
int main(){
    int i,k;
    char M1[N][N]={'B','W','B','W','B','W','B','W','W','B','W','B','W','B','W','B','B','W','B','W','B','W','B','W','W','B','W','B','W','B','W','B','B','W','B','W','B','W','B','W','W','B','W','B','W','B','W','B','B','W','B','W','B','W','B','W','W','B','W','B','W','B','W','B',};
    char M2[N][N]={'B','W','B','W','B','W','B','W','W','B','W','B','W','B','W','B','W','B','W','B','W','B','W','B','W','B','W','B','W','B','W','B','B','W','B','W','B','W','B','W','W','B','W','B','W','B','W','B','B','W','B','W','B','W','B','W','W','B','W','B','W','B','W','B',};
    char M3[N][N]={'B','C','B','W','B','W','B','W','W','B','W','B','W','B','W','B','B','W','B','W','B','W','B','W','W','B','W','B','W','B','W','B','B','W','B','W','B','W','B','W','W','B','W','B','W','B','W','B','B','W','B','W','B','W','B','W','W','B','W','B','W','B','W','B',};
    
    printf("M1\n");
    for(i=0;i<N;i++){for(k=0;k<N;k++){printf("%c ",M1[i][k]);}printf("\n");}
    printf("\nM2\n");
    for(i=0;i<N;i++){for(k=0;k<N;k++){printf("%c ",M2[i][k]);}printf("\n");}
    printf("\nM3\n");
    for(i=0;i<N;i++){for(k=0;k<N;k++){printf("%c ",M3[i][k]);}printf("\n");}
    
    printf("%d", f(M1));
    
    return 0;
}
int verifica_diagonale(int r, int c, char colore, char matr[N][N])
    {
    for(int scorri_r=0; scorri_r<N; scorri_r++)
        {
            for(int scorri_c=0; scorri_c<N; scorri_c++)
                {
                        if(matr[r][c]!='B' && matr[r][c]!='W')
                            return 0;
                        if(scorri_c-scorri_r==r-c && colore!=matr[scorri_r][scorri_c])
                            return 0;
                        if(scorri_c+scorri_r==r+c && colore!=matr[scorri_r][scorri_c])
                            return 0;
                }
        }
    return 1;
    }
int f(char matr[N][N])
    {
    for(int r=0; r<N-1; r++)
        {
            for(int c=0; c<N-1; c++)
                {
                    if(verifica_diagonale(r, c, matr[r][c], matr)==0)
                        return 0;
                }
        }
    return 1;
    }
