//  Created by Francesco Roscio Ricon on 09/11/25.
#include <stdio.h>
#define N 3
// Definizione del tipo Tavolo
typedef struct {
    int commensali; // Numero di persone sedute al tavolo
    float prezzo;     // Prezzo totale del cibo ordinato dal tavolo
} Tavolo;
void tavoliPiccoli(Tavolo M[N][N], int num_r, int num_c, int *riga_min, int *colonna_min, int *min);
void speseMedie(Tavolo M[N][N], float array[], int num_r, int num_c, int *len_array);

int main() {
    int r, i, c, num_r, num_c, riga_min, colonna_min, min, len_array=0;
    float array[10];
    Tavolo M[N][N] = {
        {{2, 100}, {3, 150}, {4, 200}},
        {{2,  80}, {4, 180}, {3, 120}},
        {{4, 250}, {2,  90}, {3, 140}}
    };
    tavoliPiccoli(M, 3, 3, &riga_min, &colonna_min, &min);
    printf("Il tavolo minimo è nella riga %d e nella colonna %d\n", riga_min, colonna_min);
    speseMedie(M, array, 3, 3, &len_array);
    for(i=0; i<len_array; i++)
        {
            printf("%.2f\n", array[i]);
        }
    

}
void tavoliPiccoli(Tavolo M[N][N], int num_r, int num_c, int *riga_min, int *colonna_min, int *min)
    {
    int i, j;;
    *min=M[0][0].commensali;
    *riga_min=0;
    *colonna_min=0;
    for(i=0; i<num_r; i++)
        {
            for(j=0; j<num_c; j++)
                {
                    if(*min>M[i][j].commensali)
                        {
                            *min=M[i][j].commensali;
                            *riga_min=i;
                            *colonna_min=j;
                        }
                }
        }
    for(i=0; i<num_r; i++)
        {
            for(j=0; j<num_c; j++)
                {
                    if(*min==M[i][j].commensali)
                        {
                            if(M[*riga_min][*colonna_min].prezzo<M[i][j].prezzo)
                                {
                                    *colonna_min=j;
                                    *riga_min=i;
                                }
                        }
                }
        }
    }
void speseMedie(Tavolo M[N][N], float array[], int num_r, int num_c, int *len_array)
    {
    int r,c, i;
    float somma2=0, somma3=0, somma4=0;
    int conta2=0, conta3=0, conta4=0;
    float media2, media3, media4;
    for(r=0;r<num_r; r++)
        {
            for(c=0; c<num_c; c++)
                {
                    if(M[r][c].commensali==2)
                        {
                            somma2=M[r][c].prezzo+somma2;
                            conta2++;
                        }
                    if(M[r][c].commensali==3)
                        {
                            somma3=M[r][c].prezzo+somma3;
                            conta3++;
                        }
                    if(M[r][c].commensali==4)
                        {
                            somma4=M[r][c].prezzo+somma4;
                            conta4++;
                        }
//                    if(M[r][c].commensali!=2 && M[r][c].commensali!=3 && M[r][c].commensali!=4)
//                        {
//                            sommaelse=0;
//                            
//                        }
                }
        }
    media2=somma2/conta2;
    media3=somma3/conta3;
    media4=somma4/conta4;
    for(i=0;i<10; i++)
        {
            if(i==0)
            {
                array[0]=media2;
                (*len_array)++;
            }
            if(i==1)
            {
                array[1]=media3;
                (*len_array)++;
            }
            if(i==2)
            {
                array[2]=media4;
                (*len_array)++;
                }
            if(i!=0 && i!=1 && i!=2)
            {
                array[i]=0;
                (*len_array)++;
                
            }
        }
}
