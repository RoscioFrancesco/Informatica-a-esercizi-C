//
//  main.c
//  es 1
//
//  Created by Francesco Roscio Ricon on 24/02/26.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUM_STUDENTI 5
#define NUM_VERIFICHE 5
typedef struct {
    char cognome[50];
    int voti[NUM_VERIFICHE];
    int n; // numero di verifiche effettivo
} Studente;

char * studentiBravi(Studente array[], int num);
int media_totale(Studente array[], int num);
int calcolamedia(int array[], int num);
int media_massima(Studente array[], int numero_stud);

int main() {
    // dichiarazione ed inizializzazione classe
    Studente classe[NUM_STUDENTI] = {
        {"Boracchi", {7, 8, 9, 6}, 4},
        {"Campi", {8, 8, 8, 8, 8}, 5},
        {"Peretti", {4, 6, 7, 5}, 4},
        {"Conti", {9, 8, 8}, 3},
        {"Valoriani", {4, 6, 7, 3}, 4}
    };
    
    
    printf("media massima: %d", media_massima(classe, NUM_STUDENTI));
    printf("\nmedia tot: %d", media_totale(classe, NUM_STUDENTI));
    char *punt=studentiBravi(classe, NUM_STUDENTI);
    printf("%s", punt);
    free(punt);

    return 0;
}
int calcolamedia(int array[], int num)
    {
    float somma=0;
    int count=0;
    for(int i=0; i<num; i++)
        {
            somma=somma+array[i];
            count++;
        }
    return somma/count;
    }
int media_massima(Studente array[], int numero_stud)
    {
    int max=0;
    for(int i=0; i<numero_stud; i++)
        {
            int m=calcolamedia(array[i].voti, array[i].n);
            if(m>max)
                {
                    max=m;
                }
        }
    return max;
    }
//media_totale: la media delle medie di tutti gli studenti nel vettore.
int media_totale(Studente array[], int num)
    {
    float somma=0;
    int count=0;
    for(int i=0; i<num; i++)
        {
            somma=somma+calcolamedia(array[i].voti, array[i].n);
            count++;
        }
    return somma/count;
    }
char * studentiBravi(Studente array[], int num)
    {
    char *nomi=malloc(sizeof(char)*5*NUM_STUDENTI);
    float mediatot=media_totale(array, num);
    int segna=0;
    for(int i=0; i<num; i++)
        {
            if(calcolamedia(array[i].voti, array[i].n)>mediatot)
                {
                    for(int j=0; j<strlen(array[i].cognome); j++)
                        {
                            nomi[segna]=array[i].cognome[j];
                            segna++;
                        }
                    nomi[segna]=' ';
                    segna++;
                }
        }
    nomi[segna]='\0';
    return nomi;
    }
