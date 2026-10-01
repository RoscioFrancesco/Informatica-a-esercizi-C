//  Created by Francesco Roscio Ricon on 10/11/25.

#include <stdio.h>

#include <stdio.h>
#define N 100
#define M 8
typedef struct {int x,y;} Punto;
void stampaPercorso(Punto percorso[], int lunghezza);
void pulisci(Punto percorso[], int len_perc, int *lung2, Punto percorso2[]);
void funzionefinale(char mat[M][M], Punto percorso[], int len_percorso, char stringa_ris[]);
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
    stampaPercorso(per1, 8);
    pulisci(per1, lung1, &lung2, per2);
    printf("\n");
    stampaPercorso(per2, lung2);
    char stringa_ris[N];
    funzionefinale(mat, per2, lung2, stringa_ris);
    printf("\n");
    printf("%s", stringa_ris);
    
}
void stampaPercorso(Punto percorso[], int lunghezza)
    {
    int i=0;
    for(i=0;i<lunghezza;i++)
        {
            printf("(%d,%d)", percorso[i].x, percorso[i].y);
        }
}
void pulisci(Punto percorso[], int len_perc, int *lung2, Punto percorso2[])
    {
    int i;
    int conta_temp=0;
    for(i=0; i<len_perc; i++)
        {
            if(percorso[i].x<8 && percorso[i].x>=0 && percorso[i].y>=0 && percorso[i].y<8)
                {
                    percorso2[conta_temp].x=percorso[i].x;
                    percorso2[conta_temp].y=percorso[i].y;
                    conta_temp++;
                }
            
        }
    *lung2=conta_temp;
    }
void funzionefinale(char mat[M][M], Punto percorso[], int len_percorso, char stringa_ris[])
    {
    int i=0;
        int contatore=0;
    for(i=0; i<len_percorso; i++)
        {
            stringa_ris[contatore]=mat[percorso[i].x][percorso[i].y];
            contatore++;
        }
        
  stringa_ris[contatore]='\0';
    }
