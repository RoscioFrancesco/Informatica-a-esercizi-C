//
//  main.c
//  tentativo 1
//
//  Created by Francesco Roscio Ricon on 16/11/25.
//
#include <math.h>
#include <stdio.h>
#define N 100
typedef struct  {
    float S_t;
    float valor_opz;
    int colonna;
    int riga;
    int num_p;
    int num_q;
} nodo;

int main() {
    float delta_t, f_0; // f_0 è cio che volgiamo trovare
    nodo elenco_nodi[N];
    int num_reale_nodi;
    float tot_tempo;
    int num_intervalli;
    float u,d;
    float p;
    float S_t[N];
    float var_processo_stocastico;
    num_reale_nodi=0;
    int i;
    printf("Inserire numero intervalli");
    scanf("%d", &num_intervalli);
    int num_intervalli2=num_intervalli;
    for(i=0; i<num_intervalli; i++)
        {
            num_reale_nodi=num_reale_nodi+num_intervalli2;
            num_intervalli2--;
        }
    printf("Inserire tempo totale");
    scanf("%f", &tot_tempo);
    delta_t=tot_tempo/num_intervalli;
    printf("Inserire la varianza del processo stocastico");
    scanf("%f", &var_processo_stocastico);
    u=exp(var_processo_stocastico*sqrtf(delta_t));
    d=1/u;
    p=(0.9917-d)/(u-d);
    
}
