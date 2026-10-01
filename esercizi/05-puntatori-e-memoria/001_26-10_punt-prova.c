//
//  main.c
//  punt prova
//
//  Created by Francesco Roscio Ricon on 26/10/25.
//

#include <stdio.h>
#define N 5

int main(int argc, char* argv[]) {
    // Variabili
    int v[N], *pv, i, somma, min, max;
    
    // Inizializzazione puntatore
    pv = v;
    
    // Acquisizione valori
    somma = 0;
    for(i=0; i<N; i++){
        printf("Inserisci l'elemento in posizione %d: ", i);
        scanf("%d", pv+i);
        
        if(i == 0){
            max = *(pv+i);
            min = max;
        }
        else{
            if(max < *(pv+i)) max = *(pv+i);
            if(min > *(pv+i)) min = *(pv+i);
        }
        
        somma += *(pv+i);
    }
    
    // Stampa
    printf("Somma elementi: %d\n", somma);
    printf("MASSIMO: %d\n", max);
    printf("minimo: %d\n", min);
    
    return 0;
}
