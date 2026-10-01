//  Created by Francesco Roscio Ricon on 22/11/25.

#include <stdio.h>
typedef struct
{ int V[20];
int C; } STR;
int trovamultiplo(int numerodaverificare, int MATR[20][20], int MATR_r, int MATR_c);
int funzioneprincipale(int MATR[20][20], int MATR_r, int MATR_c, STR X);
int main() {
    STR X;
    int MATR[20][20];
    int MATR_r=20, MATR_c=20;
    // --- Inizializzazione di X ---
        X.C = 5;
        X.V[0] = 12;
        X.V[1] = 30;
        X.V[2] = 18;
        X.V[3] = 7;
        X.V[4] = 60;

        // --- Inizializzazione della matrice 20x20 ---
        // valori diversi da zero e facili da verificare
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                MATR[i][j] = (i + 1) * (j + 1); // semplice prodotto riga*colonna
            }
        }
    int somma;
    somma=funzioneprincipale(MATR, MATR_r, MATR_c, X);
    printf("%d", somma);
}

int trovamultiplo(int numerodaverificare, int MATR[20][20], int MATR_r, int MATR_c)
{
    int i=0;
    int scorri_r,scorri_c;
    int contatore=0;

        for(scorri_r=0; scorri_r<MATR_r;scorri_r++)
        {
            for(scorri_c=0; scorri_c<MATR_c; scorri_c++)
            {
                
                if(MATR[scorri_r][scorri_c]!=0)
                {
                    if(numerodaverificare%MATR[scorri_r][scorri_c]==0)
                    {
                        contatore++;
                        if(contatore==3)
                            return 1;
                    }
                }
            }
        }
    return 0;
}
int funzioneprincipale(int MATR[20][20], int MATR_r, int MATR_c, STR X)
    {
    int somma=0;
    int i=0;
    for(i=0; i<X.C; i++)
        {
            if(trovamultiplo(X.V[i], MATR, MATR_r, MATR_c)==1)
                {
                    somma=somma+X.V[i];
                }
        }
        return somma;
    }

