//
//  main.c
//  es 1 2mz
//
//  Created by Francesco Roscio Ricon on 02/03/26.
//

//1) Registro Temperature per Stazione Meteo (matrice statica dentro struct)
//
//Definisci:

//Una struttura:
//Stazione con:
//char id[20]
//float temp[G][H] (temperatura giorno/ora)
//int anno, mese


#include <stdio.h>
#define G 31
#define H 24

typedef struct EL{
    char id[20];
    float temp[G][H];
    int anno, mese;
    struct EL*next;
}Stazione;
typedef Stazione *Lista;
int giornoPiuCaldo(Stazione s);
int ver(int r, int c, Stazione s, float soglia);

int main() {
    
}
float media(int giorno, Stazione E)
    {
    float somma=0;
    float count=0;
    for(int r=0; r<G; r++)
        {
            for(int c=0; c<G; c++)
                {
                    if(giorno==r)
                        {
                            somma=somma+E.temp[r][c];
                            count++;
                        }
                }
        }
    return somma/count;
    }
int giornoPiuCaldo(Stazione s)
    {
    float max=0;
    int ind=0;
    for(int i=0; i<H; i++)
        {
            if(media(i, s)>max)
            {
                max=media(i, s);
                ind=i;
            }
        }
    return ind;
    }
int contaPicchiOrari(Stazione s, float soglia)
    {
    int count=0;
    for(int r=1; r<G-1; r++)
        {
            for(int c=1; c<G-1; c++)
                {
                    if(ver(r, c, s, soglia))
                        count++;
                }
        }
    return count;;
    }

int ver(int r, int c, Stazione s, float soglia)
    {
        if(s.temp[r][c]<soglia)
            return 0;
    for(int scorri_r=-1; scorri_r<=1; scorri_r++)
        {
            for(int scorri_c=-1; scorri_c<=1; scorri_c++)
                {
                    if(s.temp[r+scorri_r][c+scorri_c]<=s.temp[r][c] && !(scorri_c==0 && scorri_r==0))
                        return 0;
                }
        }
    return 1;
    }
