//
//  main.c
//  tde 5 1mz
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//


typedef struct {
int min,sec,cent;
} tempo;
typedef struct {
char nome[15],cognome[15],nazionalità[15];
tempo t;
} frazione;

typedef frazione risultato[4][8]; // existing new

int somma_colonna(risultato F, int c)
    {
    int somma_min=0;
    int somma_cent=0;
    int somma_sec=0;
    int tot=0;
    for(int r=0; r<4; r++)
        {
            somma_min=somma_min+F[r][c].t.min;
            somma_sec=somma_sec+F[r][c].t.sec;
            somma_cent=somma_cent+F[r][c].t.cent;
            
        }
    tot=somma_cent+somma_min*60*100+somma_sec*100;
    return tot;
    }
int conv(tempo t)
    {
    int ris=t.cent+t.min*60*100+t.sec*100;
    return ris;
    }
int corsiaVincente(risultato ris)
    {
    int min=somma_colonna(ris, 0);
    int num_corsia=0;
    for(int i=0; i<8; i++)
        {
            if(somma_colonna(ris, i)<min)
                {
                    min=somma_colonna(ris, i);
                    num_corsia=i;
                }
        }
    return num_corsia;
    }
int record(risultato ris, tempo t)
    {
        int mondo=conv(t);
        int min=somma_colonna(ris, 0);
    for(int i=0; i<8; i++)
        {
            if(somma_colonna(ris, i)<min)
                {
                    min=somma_colonna(ris, i);
                }
        }
    if(min<mondo)
        return 1;
    return 0;
    }
