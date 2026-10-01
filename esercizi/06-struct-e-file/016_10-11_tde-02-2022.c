//
//  main.c
//  tde 02_2022
//
//  Created by Francesco Roscio Ricon on 10/11/25.
// Riferimento: Informatica A (061202), TDE febbraio 2022, a.a. 2021/22: https://forms.office.com/r/9vr3mha1pT
#include<stdio.h>
#include<string.h>
#define N 20


typedef struct{
char nome[N];
int livello;
} Inquinante;

float calcolamedia (Inquinante array[], int len_array);
void analizzaInquinante(Inquinante array[], char piuinquinante[], char vicinomedia[], int len_array);
int main()
{
Inquinante elementi[5];
// TODO aggiungere dichiarazione variabili aggiuntive

    char piuinquinante[N];
    char vicinomedia[N];
strcpy(elementi[0].nome, "PM10");
elementi[0].livello = 65;
strcpy(elementi[1].nome, "Benzene");
elementi[1].livello = 212;
strcpy(elementi[2].nome, "PM7");
elementi[2].livello = 352;
strcpy(elementi[3].nome, "PM5");
elementi[3].livello = 176;
strcpy(elementi[4].nome, "CO2");
elementi[4].livello = 451;


    analizzaInquinante(elementi, piuinquinante, vicinomedia, 5);
    printf("Il più inquinante è :%s il più vincino alla media è :%s", piuinquinante, vicinomedia);


// TODO stampa i nomi dei popoli come richiesto


return 0;
}
void analizzaInquinante(Inquinante array[], char piuinquinante[], char vicinomedia[], int len_array)
{int i;
    int max=-1;
    for(i=0; i<len_array; i++)
        {
            if(array[i].livello>max)
                {
                    max=array[i].livello;
                    strcpy(piuinquinante, array[i].nome);
                }
        }
    int media;
    media=calcolamedia(array, len_array);
    int min[N];
    min[0]=array[0].livello-media;
    if (min[0]<0)
        min[0]=-min[0];
    int min_ass=min[0];
    for(i=0; i<len_array; i++)
        {
            min[i]= array[i].livello-media;
            if(min[i]<0)
                min[i]=-min[i];
            if(min[i]<min_ass)
                {
                    min_ass=min[i];
                    strcpy(vicinomedia, array[i].nome);
                }
        }
    }
float calcolamedia (Inquinante array[], int len_array)
    {
    int somma=0;
    int i=0;
    int media;
    int contatore=0;
    for(i=0; i<len_array;i++)
        {
            somma=somma+array[i].livello;
            contatore++;
        }
    media=(somma*1.0)/contatore;
    return media;
}
