//
//  main.c
//  es 3 7mz
//
//  Created by Francesco Roscio Ricon on 07/03/26.
//

//Esercizio 1 — Allocazione dinamica di un array


#include <stdio.h>
#include <stdlib.h>
void stampa(int vett[], int dim);
void crearray(int dim, int **punt);
int main() {
    int *punt=NULL;
    crearray(5, &punt);
    stampa(punt, 5);
}
void crearray(int dim, int **punt)
    {
        int *vett=malloc(sizeof(int)*dim);
    for(int i=0; i<dim; i++)
        {
            printf("inserire numero");
            scanf("%d", &vett[i]);
        }
    *punt=vett;
    }
void stampa(int vett[], int dim)
    {
    for(int i=0; i<dim; i++)
    {
        printf("%d," , vett[i]);
    }
    }
