//
//  main.c
//  es 2 7mz
//
//  Created by Francesco Roscio Ricon on 07/03/26.
//Esercizio 1 — Allocazione dinamica di un array


#include <stdio.h>
#include <stdlib.h>
void stampa(int vett[], int dim);
int *crearray(int dim);
int main() {
    int *punt=crearray(5);
    stampa(punt, 5);
}
int *crearray(int dim)
    {
        int *vett=malloc(sizeof(int)*dim);
    for(int i=0; i<dim; i++)
        {
            printf("inserire numero");
            scanf("%d", &vett[i]);
        }
    return vett;
    }
void stampa(int vett[], int dim)
    {
    for(int i=0; i<dim; i++)
    {
        printf("%d," , vett[i]);
    }
    }
