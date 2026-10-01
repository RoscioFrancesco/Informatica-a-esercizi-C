//
//  Untitled.h
//  tde struct 2
//
//  Created by Francesco Roscio Ricon on 07/11/25.
//
//
//  main.c
//  tde struct 2
//
//  Created by Francesco Roscio Ricon on 07/11/25.
#define N 100
#include <stdio.h>
#include <string.h>
typedef struct d { int giorno, mese, anno; } Data;
typedef struct job
    { char codice[N], descrizione[N], titoloStudioRichiesto[N];
    int stipendio;
    Data dataInserimento;
    int valido; } OffertaDiLavoro;
typedef OffertaDiLavoro Offerte[10000];
int confrontadata(Data data_i, Data data_j);
void invalida_lista(Offerte lista, int len_lista);
int confrontaofferta(OffertaDiLavoro lista[], int i, int j);
int main(void) {
    int num, i;
    Offerte J;
    printf("Quante offerte vuoi inserire?");
    if (scanf("%d", &num) != 1 || num < 0 || num > 10000)
        return 1;
    for(i=0; i<num; i++)
        {
            printf("Inserire il codice");
            scanf("%99s", J[i].codice);
            printf("Inserire descrizione");
            scanf("%99s", J[i].descrizione);
            printf("Inserire il titolo di studio richiesto");
            scanf("%99s", J[i].titoloStudioRichiesto);
            printf("Inserire lo stipendio");
            if (scanf("%d", &J[i].stipendio) != 1)
                return 1;
            printf("Inserire il giorno");
            if (scanf("%d", &J[i].dataInserimento.giorno) != 1)
                return 1;
            printf("Inserire il mese");
            if (scanf("%d", &J[i].dataInserimento.mese) != 1)
                return 1;
            printf("Inserire il anno");
            if (scanf("%d", &J[i].dataInserimento.anno) != 1)
                return 1;
            J[i].valido=1;
        }
    invalida_lista(J, num);
    return 0;
}
void invalida_lista(Offerte lista, int len_lista)
    {
    int i=0, j=0;
    for(i=0; i<len_lista; i++)
        {
            for(j=0; j<len_lista; j++)
            {
                if(confrontadata(lista[i].dataInserimento, lista[j].dataInserimento)==0 && confrontaofferta(lista, i, j)==1 && i!=j)
                    {
                        lista[i].valido=0;
                    }
                    
            }
        }
    }
int confrontadata(Data data_i, Data data_j)
    {
    if(data_i.anno>data_j.anno) return 1; // 1 significa i valida, 0 significa i invalida
    if(data_i.anno<data_j.anno) return 0;
    if(data_i.mese>data_j.mese) return 1;
    if(data_i.mese<data_j.mese) return 0;
    if(data_i.giorno>data_j.giorno) return 1;
    return 0;
    }
int confrontaofferta(OffertaDiLavoro lista[], int i, int j)
    {
    if(strcmp(lista[j].codice, lista[i].codice)==0
       && strcmp(lista[j].descrizione, lista[i].descrizione)==0
       && strcmp(lista[j].titoloStudioRichiesto, lista[i].titoloStudioRichiesto)==0
       && lista[i].stipendio==lista[j].stipendio)
    return 1;
    
    return 0;
    }
