//
//  main.c
//  popoli indiani
//
//  Created by Francesco Roscio Ricon on 30/10/25.
//  Il tipo Popolo definisce un popolo con nome e numero di abitanti.

    

#include <stdio.h>
#include <string.h>
#define N 100
#include <math.h>

typedef struct{
char nome[N];
int pop;
} Popolo;
void analizzaPopoli(int len_array, Popolo array[], char ris[], char nome_media[]);
int main() {
    Popolo indiani[100];
    char popolonome[N];
    char medianome[N];
    int len_array=5; // qs variabile tiene traccia del numero reale di elementi nell'array indiani.
    strcpy(indiani[0].nome, "Cayuga");
    indiani[0].pop = 652;
    strcpy(indiani[1].nome, "Oneida");
    indiani[1].pop = 2123;
    strcpy(indiani[2].nome, "Seneca");
    indiani[2].pop = 3521;
    strcpy(indiani[3].nome, "Onondaga");
    indiani[3].pop = 1763;
    strcpy(indiani[4].nome, "Mohawak");
    indiani[4].pop = 4512;
    analizzaPopoli(len_array, indiani, popolonome, medianome);
    printf("Nome popolo con più abitanti %s\n", popolonome);
    printf("Nome popolo più vicino alla media %s\n", medianome);
    
}
void analizzaPopoli(int len_array, Popolo array[], char ris[], char nome_media[])
        {
            int i=0, max=-1, somma=0, media_num, a_min, a;
    a_min=array[0].pop-array[1].pop;
    if (a_min<0)
        a_min=-a_min;
            for(i=0; i<len_array; i++)
            {
                if (array[i].pop>max)
                {
                    max=array[i].pop;
                    strcpy(ris , array[i].nome);
                }
            }
            for(i=0; i<len_array; i++)
            {
                somma= somma+ array[i].pop;
            }
            media_num= somma/len_array;
            for(i=0; i<len_array; i++)
            {
                a= array[i].pop-media_num;
                if(a<0) a=-a;
                if(a<a_min)
                {
                    a_min=a;
                    strcpy(nome_media, array[i].nome);
                }
            }
        }
