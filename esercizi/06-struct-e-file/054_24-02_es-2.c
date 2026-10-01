//
//  main.c
//  es 2
//
//  Created by Francesco Roscio Ricon on 24/02/26.
//

#include <stdio.h>


#define N 3


// Definizione del tipo Tavolo
typedef struct {
    int commensali; // Numero di persone sedute al tavolo
    float prezzo;     // Prezzo totale del cibo ordinato dal tavolo
} Tavolo;
void tavolipiccoli(Tavolo M[N][N], int *r, int *c);
void speseMedie(float array[], Tavolo M[N][N], int len);
int main() {
    // Matrice di tavoli
    Tavolo M[N][N] = {
        {{2, 100}, {3, 150}, {4, 200}},
        {{2,  80}, {4, 180}, {3, 120}},
        {{4, 250}, {2,  90}, {3, 140}}
    };

    int r=0;
    int c=0;
    tavolipiccoli(M, &r, &c);
    printf("\n(%d, %d)", r,c);
    
    float array[3];
    speseMedie(array, M, 3);
    for(int i=0; i<3; i++)
        {
            printf("%f, ", array[i]);
        }

    return 0;
}
void tavolipiccoli(Tavolo M[N][N], int *r, int *c)
    {
    int min=M[0][0].commensali;
    int min_spesa=M[0][0].prezzo;
    int r_min=0;
    int c_min=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(M[r][c].commensali==min)
                        {
                            if(M[r][c].prezzo>min_spesa)
                                {
                                    min=M[r][c].commensali;
                                    min_spesa=M[r][c].prezzo;
                                    r_min=r;
                                    c_min=c;
                                }
                        }
                    if(M[r][c].commensali<min)
                        {
                            min=M[r][c].commensali;
                            min_spesa=M[r][c].prezzo;
                            r_min=r;
                            c_min=c;
                        }
                }
        }
    *r=r_min;
    *c=c_min;
    }
float calcolamedia(int num_comm, Tavolo M[N][N])
    {
    float somma=0;
    int count=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(M[r][c].commensali==num_comm)
                        {
                            somma=somma+M[r][c].prezzo;
                            count++;
                        }
                }
        }
    if(count==0)
        return 0;
    return somma/count;
    }
void speseMedie(float array[], Tavolo M[N][N], int len)
    {
    int j=0;
    for(int i=2; i<=len+2; i++)
        {
            array[j]=calcolamedia(i, M);
            j++;
        }
    }
