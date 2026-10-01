//
//  main.c
//  esercitaz
//
//  Created by Francesco Roscio Ricon on 08/11/25.
//


#include <stdio.h>
#define N 8
void creavettore(int M[N][N], int v[], int len_vett,int v_nuovo[], int * len_vnuovo);
int sommavettore(int v_nuovo[], int len_v_nuovo);
int main(){
    int i,k;
    int v_nuovo[N], len_vnuovo, somma;
    int M[N][N]={1,4,6,8,9,3,2,6,
        4,7,2,4,1,8,1,1,
        5,7,3,9,1,2,0,3,
        3,7,7,5,5,3,8,0,
        2,1,5,5,7,3,5,7,
        2,4,9,3,7,5,8,9,
        3,5,7,8,9,5,7,8,
        1,2,6,4,8,9,9,0};
    int v[]={4,7,2,4,1,8,1,1};
    int len_vet=N;
    printf("M\n");
    for(i=0;i<N;i++){for(k=0;k<N;k++){printf("%d ",M[i][k]);}printf("\n");}
    printf("v\n");
    for(i=0;i<N;i++){printf("%d ",v[i]);}
    printf("\n");
    creavettore(M, v, len_vet, v_nuovo, &len_vnuovo);
    somma=sommavettore(v_nuovo, len_vnuovo);
    for(i=0; i<len_vnuovo; i++)
    {
        printf("%d", v_nuovo[i]);
    }
    printf("\n%d\n", somma);
}

void creavettore(int M[N][N], int v[], int len_vett,int v_nuovo[], int * len_vnuovo)
{
    int i, k=0;
    for(i=0; i<len_vett; i++)
    {
        v_nuovo[k]=M[i][v[i]-1];
        k++;
    }
    *len_vnuovo=k;
    
}
int sommavettore(int v_nuovo[], int len_v_nuovo)
{
    int i=0, somma=0;
    for(i=0; i<len_v_nuovo; i++)
    {
        somma=somma+v_nuovo[i];
    }
    return somma;
}
