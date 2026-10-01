//
//  main.c
//  es 5.2
//
//  Created by Francesco Roscio Ricon on 24/02/26.
//

//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 4
#define MAX_ISOLATI 16

typedef struct{
    int r;
    int c;
}Coordinanta;

typedef char cella[3];

int vince(cella matr[N][N]);
void f(cella matr[N][N], int *len, Coordinanta **p);

int main() {
    int i,k;
    cella s[N][N];
    char vincitore;


    printf("=== ESEMPIO 1 ===\n");
    cella matrice1[N][N] = {
        {"v", "Xa", "v", "xb"},
        {"v", "v",  "xb", "xb"},
        {"xb", "xb", "xb", "xb"},
        {"v", "v",  "Xb", "xb"}};
    for(i=0;i<N;i++){
        for(k=0;k<N;k++){
            printf("%4s",matrice1[i][k]);
        }
        printf("\n");
    }
    printf("\n%d", vince(matrice1));
    int len1=0;
    Coordinanta *p=malloc(sizeof(*p)*N*N);
    f(matrice1, &len1, &p);
    Coordinanta *temp=p;
    for(int i=0; i<len1; i++)
        {
            printf("(%d, %d) ", (*p).c, (*p).r);
            p++;
        }
    free(temp);
    
    printf("\n=== ESEMPIO 2 ===\n");
    cella matrice2[N][N] = {
        {"v", "Xa", "v", "v"},
        {"v", "v",  "v", "Xa"},
        {"xa", "xa", "v", "v"},
        {"v", "v",  "Xa", "v"}};

    for(i=0;i<N;i++){
        for(k=0;k<N;k++){
            printf("%4s",matrice2[i][k]);
        }
        printf("\n");
    }
    int len2=0;
    Coordinanta *p2=malloc(sizeof(Coordinanta)*N*N);
    f(matrice2, &len2, &p2);
    printf("entra");
    Coordinanta *temp2=p2;
    for(int i=0; i<len2; i++)
        {
            printf("(%d, %d) ", (*p2).c, (*p2).r);
            p2++;
        }
    free(temp2);
}


int vince(cella matr[N][N])
    {
    char gruppo='a';
    int hasprec=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(hasprec==0 && matr[r][c][0]!='v')
                        {
                            hasprec=1;
                            gruppo=matr[r][c][1];
                        }
                    if(strlen(matr[r][c])==2 && matr[r][c][0]!='v' && matr[r][c][1]!=gruppo)
                        return 0;
                }
        }
    return 1;
    }

int ver(cella matr[N][N], int r, int c)
    {
    for(int scorri_r=-1; scorri_r<=1; scorri_r++)
        {
            for(int scorri_c=-1; scorri_c<=1; scorri_c++)
                {
                    if(scorri_r+r>=0 && scorri_c+c>=0 && scorri_r+r<N && scorri_c+c<N && !(scorri_c==0&&scorri_r==0) && matr[scorri_r+r][scorri_c+c][0]!='v')
                    {
                        return 0;
                    }
                }
        }
    return 1;
    }
void f(cella matr[N][N], int *len, Coordinanta **p)
    {
    int segna=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(ver(matr, r, c))
                        {
                            (*p)[segna].c = c;
                            (*p)[segna].r = r;
                            segna++;
                        }
                }
        }
    *len=segna;
    }
