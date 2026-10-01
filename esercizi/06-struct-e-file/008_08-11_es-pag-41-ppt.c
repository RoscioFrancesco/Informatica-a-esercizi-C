//
//  main.c
//  es pag 41 ppt
//
//  Created by Francesco Roscio Ricon on 08/11/25.
//  I risultati della finale olimpica di nuoto della staffetta 4x100 stile libero sono
//rappresentati mediante una matrice di dimensioni 4x8.
//• Ogni cella rappresenta il risultato di un singolo frazionista tramite la seguente
//struttura:


//• La matrice è dichiarata in questo modo:

#include <stdio.h>
typedef struct { int min,sec,cent;} tempo;
typedef struct {char nome[15],cognome[15],nazionalità[15]; tempo t; int t_centisecondi;} frazione;
int tempo_in_centisecondi(int minuti, int secondi, int centisecondi);
typedef frazione risultato[4][8];
int corsiaVincente(risultato *tabella, int Num_r, int Num_c, int vet_tempi[]);
int recordBattuto(risultato ris, tempo record);
int main() {
    int vet_tempi[8];
    risultato tabella;
    int corsia_vincente;
    corsia_vincente=corsiaVincente(&tabella, 4, 8, vet_tempi);
    printf("%d", corsia_vincente);
    
}
int corsiaVincente(risultato *tabella, int Num_r, int Num_c, int vet_tempi[])
    {
    int r=0, c=0, i=0;
    int corsiavincente;
    int t_minimo_corsia;
    for(r=0; r<Num_r; r++)
        {
            for(c=0; c<Num_c; c++)
            {
                (*tabella)[r][c].t_centisecondi=tempo_in_centisecondi((*tabella)[r][c].t.min, (*tabella)[r][c].t.sec, (*tabella)[r][c].t.cent);
            }
        }
    for(i=0; i<Num_c; i++)
    {
        vet_tempi[i]=0;
    }
    for(c=0;c<Num_c; c++)
        {
            for(r=0; r<Num_r; r++)
            {
                vet_tempi[i]=vet_tempi[i]+(*tabella)[r][c].t_centisecondi;
            }
            i++;
        }
    t_minimo_corsia=vet_tempi[0];
    for(r=0; r<i; r++)
        {
            if(vet_tempi[r]<t_minimo_corsia)
            {
                t_minimo_corsia=vet_tempi[r];
                corsiavincente=r;
            }
        }
    return corsiavincente+1;
    }
int tempo_in_centisecondi(int minuti, int secondi, int centisecondi)
    {
    int tempoeql;
    tempoeql=60*minuti*100+100*secondi+centisecondi;
    return tempoeql;
    }
