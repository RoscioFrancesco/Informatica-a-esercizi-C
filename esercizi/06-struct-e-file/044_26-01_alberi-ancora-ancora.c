//
//  main.c
//  alberi ancora ancora
//
//  Created by Francesco Roscio Ricon on 26/01/26.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct AP {
   int oraInizio, minutoInizio;
   int oraFine, minutoFine;
   struct AP *prox;
} appuntamento;


typedef appuntamento *ListaAppuntamenti;


ListaAppuntamenti costruisci();
ListaAppuntamenti InsInFondo(ListaAppuntamenti lista, int oraInizio, int minutoInizio, int oraFine, int minutoFine);
void VisualizzaLista(ListaAppuntamenti lista);
int calcolaorari(ListaAppuntamenti a);
int * Riassumi(ListaAppuntamenti lista , int *dim);

int main() {


    ListaAppuntamenti lista = costruisci();
    printf("Lista di partenza:\n");
    VisualizzaLista(lista);
    int i=0;
    int dim=0;
    int *v=Riassumi(lista, &dim);
    for(i=0; i<dim; i++)
        {
            printf("%d\n", v[i]);
        }
    
}

ListaAppuntamenti costruisci() {
    int i, M[8][4] = {8, 20, 9, 56,
                     9, 30, 10, 20,
                     10, 30, 11, 45,
                     11, 57, 12, 20,
                     14, 40, 15, 20,
                     15, 20, 16, 12,
                     16, 30, 17, 15,
                     17, 10, 18, 30};


    ListaAppuntamenti lista = NULL;
    for (i = 0; i < 8; i++) {
        lista = InsInFondo(lista, M[i][0], M[i][1], M[i][2], M[i][3]);
    }


    return lista;
}


ListaAppuntamenti InsInFondo(ListaAppuntamenti lista, int oraInizio, int minutoInizio, int oraFine, int minutoFine){
    ListaAppuntamenti punt;
    if (lista == NULL) {
        punt = malloc(sizeof(appuntamento));
        punt->prox = NULL;
        punt->oraInizio = oraInizio;
        punt->minutoInizio = minutoInizio;
        punt->oraFine = oraFine;
        punt->minutoFine = minutoFine;
        return punt;
    } else {
        lista->prox = InsInFondo(lista->prox, oraInizio, minutoInizio, oraFine, minutoFine);
        return lista;
    }
}


void VisualizzaLista(ListaAppuntamenti lista) {
    while (lista != NULL) {
        printf("%02d:%02d - %02d:%02d\n", lista->oraInizio, lista->minutoInizio, lista->oraFine, lista->minutoFine);
        lista = lista->prox;
    }
}

int calcolaorari(ListaAppuntamenti a)
    {
    int val=60*(a->oraFine-a->oraInizio)+ (a->minutoFine-a->minutoInizio);
    return val;
    }
int * Riassumi(ListaAppuntamenti lista , int *dim)
    {
    int i=0;
    ListaAppuntamenti scorri=lista;
    while(scorri!=NULL)
        {
            i++;
            scorri=scorri->prox;
        }
    scorri=lista;
    int *v=malloc(sizeof(int)*i);
    *dim=i;
    for(int j=0; j<i; j++)
        {
            v[j]=calcolaorari(scorri);
            scorri=scorri->prox;
        }
    return v;
    }
int sovrappongono(ListaAppuntamenti a, ListaAppuntamenti b)
    {
        if(a->oraFine>b->oraInizio)
            return 1;
        if(a->oraFine==b->oraInizio)
            {
                if(a->minutoFine>b->minutoInizio)
                    return 1;
                return 0;
            }
    return 0;
    }

