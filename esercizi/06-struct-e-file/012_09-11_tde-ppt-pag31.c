//  Created by Francesco Roscio Ricon on 09/11/25.
typedef struct {
    int valore;
    int numero_tentativo;
    int num_occorrenze;
}singolo_lancio;
void lanciadado (int numero_lanci, int facce, singolo_lancio array[], int *ricorrenze_max);
#include <stdlib.h>
#include <stdio.h>
#define N 100
#include <time.h>
int main() {
    srand(time(NULL));
    int numero_lanci;
    int numero_facce;
    int i=0;
    int ricorrenze_max;
    singolo_lancio array[N];
    printf("Inserire numero lanci");
    scanf("%d", &numero_lanci);
    printf("Inserire numero facce");
    scanf("%d", &numero_facce);
    lanciadado(numero_lanci, numero_facce, array, &ricorrenze_max);
    int num=1;
    do{
            for(i=0;i<numero_lanci;i++)
            {
                if(array[i].valore!=-1 && array[i].num_occorrenze==num)
                {
                    if(array[i].num_occorrenze==1)
                    {
                        printf("La faccia %d è uscita %d volta\n", array[i].valore, array[i].num_occorrenze);
                    }
                    if(array[i].num_occorrenze!=1)
                    {
                        printf("La faccia %d è uscita %d volte\n", array[i].valore, array[i].num_occorrenze);
                    }
                }
            }
        num++;
    } while(num<=ricorrenze_max);
}
void lanciadado (int numero_lanci, int facce, singolo_lancio array[], int *ricorrenze_max)
{
    int i;
    *ricorrenze_max=-1;
    for(i=0; i<numero_lanci; i++)
    {
        array[i].num_occorrenze=1;
        array[i].numero_tentativo=i+1;
        array[i].valore= (rand()%facce)+1;
        }
    
    for(i = 0; i < numero_lanci; i++) {
            int conta = 1;
            for(int j = i+1; j < numero_lanci; j++) {
                if(array[j].valore == array[i].valore)
                {
                    conta++;
                    array[j].valore=-1;
                }
            }
            array[i].num_occorrenze = conta;
        if(array[i].num_occorrenze>*ricorrenze_max)
            {
                *ricorrenze_max=array[i].num_occorrenze;
            }
        }
}
