//
//  main.c
//  itinere 2023
//
//  Created by Francesco Roscio Ricon on 10/11/25.
//
// Riferimento: Informatica A (061202), prova in itinere, a.a. 2023/24: https://forms.office.com/e/GdxfxP3mBM
#include <stdio.h>
#include <string.h>
#define N 8
#define M 9
#define L 100
typedef struct
{
    int r1;
    int c1;
    int orizzotale;
    int verticale;
    int travata;
}parolatrovata;
typedef struct {
    char lettere[L];
}paroladamatrice;
void cercaparola(char parola[], int len_parola, parolatrovata *a, char mat[N][N], int num_r, int num_c);
int cercariga(int r0, int c0, char mat[N][N], int len_parola, char parola[], int num_r, int num_c);
int cercacolonna(int r0, int c0, char mat[N][N], int len_parola, char parola[], int num_r, int num_c);
void gioca(char matG[N][N], char matP[M][M], int len_rG, int len_cG, paroladamatrice elenco[], int len_rP);
int main(){
    int i,k;
    char G[N][N]={  'B','R','I','S','A','T','A','B',
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
    parolatrovata corrispondente_elenco[N];
    paroladamatrice elenco[N];
    char parola[L];
    int len_parola;
    len_parola=strlen(parola);
    for(i=0;i<N;i++)
        {
            corrispondente_elenco[i].c1=0;
            corrispondente_elenco[i].orizzotale=0;
            corrispondente_elenco[i].r1=0;
            corrispondente_elenco[i].travata=0;
            corrispondente_elenco[i].verticale=0;
        }
    gioca(G, P, N, N, elenco, M);
    int r,c;
    printf("\n");
    for(r=0; r<N; r++)
        {
            for(c=0; c<N; c++)
            {
                printf("%c", G[r][c]);
            }
            printf("\n");
        }
    
}
void cercaparola(char parola[], int len_parola, parolatrovata *a, char mat[N][N], int num_r, int num_c)
{
    int r, c;
    int rint, cint;
    for(r=0; r<num_r; r++)
        {
            for(c=0; c<num_c; c++)
            {
                if(mat[r][c]==parola[0] &&(cercariga(r, c, mat, len_parola, parola, num_r, num_c)||cercacolonna(r, c, mat, len_parola, parola, num_r, num_c)))
                    {
                        rint=r;
                        cint=c;
                        if(cercariga(r, c, mat, len_parola, parola, num_r, num_c))
                            {
                                a->travata=1;
                                a->orizzotale=1;
                                a->verticale=0;
                                a->r1=rint;
                                a->c1=cint;
                            }
                        if(cercacolonna(r, c, mat, len_parola, parola, num_r, num_c))
                            {
                                a->travata=1;
                                a->orizzotale=0;
                                a->verticale=1;
                                a->r1=rint;
                                a->c1=cint;
                            }
                    }
    
            }
        }
}
int cercariga(int r0, int c0, char mat[N][N], int len_parola, char parola[], int num_r, int num_c)
    {// restituisce 1 se trova
    int scorri_mat;
    int scorri_parola=0;
    int flag=1;
    if(c0 + len_parola > num_c) return 0;  // per la riga
    for(scorri_mat=c0; scorri_mat<num_c && flag==1 &&scorri_parola<len_parola; scorri_mat++)
        {
            if(parola[scorri_parola]!=mat[r0][scorri_mat])
                flag=0;
            scorri_parola++;
        }
    if(flag==1) return 1;
        return 0;
    }
int cercacolonna(int r0, int c0, char mat[N][N], int len_parola, char parola[], int num_r, int num_c)
    {// restituisce 1 se trova
    int scorri_mat;
    int scorri_parola=0;
    int flag=1;
    if(r0 + len_parola > num_r) return 0;
    for(scorri_mat=r0; scorri_mat<num_r && flag==1 &&scorri_parola<len_parola; scorri_mat++)
        {
            if(parola[scorri_parola]!=mat[scorri_mat][c0])
                flag=0;
            scorri_parola++;
        }
    if(flag==1) return 1;
        return 0;
    }
void gioca(char matG[N][N], char matP[M][M], int len_rG, int len_cG, paroladamatrice elenco[], int len_rP)
    {
    int r=0, c=0, j=0, i;
    int counter_lettereparola=0;
    int len[N];
    int numparoleinelenco=0;
    do
    {
        do{
            elenco[j].lettere[counter_lettereparola]=matP[r][c];
            counter_lettereparola++;
            c++;
        }while(matP[r][c]!='\0');
        elenco[j].lettere[counter_lettereparola]='\0';
        len[j]=counter_lettereparola;
        counter_lettereparola=0;
        j++;
        c=0;
        r++;
        numparoleinelenco++;
    }while(r<len_rP);
    parolatrovata elencoparoletrovate[N];
    
    for(i=0; i<numparoleinelenco; i++)
        {
            cercaparola(elenco[i].lettere, len[i], &elencoparoletrovate[i], matG, len_rG, len_cG);
            if(elencoparoletrovate[i].travata==1)
            {
                if(elencoparoletrovate[i].orizzotale==1)
                    {
                        for(c=elencoparoletrovate[i].c1; c<elencoparoletrovate[i].c1+len[i]; c++)
                            {
                                matG[elencoparoletrovate[i].r1][c]='*';
                            }
                        c=0;
                    }
                if(elencoparoletrovate[i].verticale==1)
                    {
                        for(c=elencoparoletrovate[i].r1; c<elencoparoletrovate[i].r1+len[i]; c++)
                            {
                                matG[c][elencoparoletrovate[i].c1]='*';
                            }
                        c=0;
                    }
            }
        }
    
}
