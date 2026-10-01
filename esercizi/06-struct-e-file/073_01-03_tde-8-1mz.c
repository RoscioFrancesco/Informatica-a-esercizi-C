//
//  main.c
//  tde 8 1mz
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int giorno, mese, anno;
} data;

typedef struct {
    int ora, minuto;
} orario;

typedef struct {
    char codiceFiscale[100], cognome[100], nome[100];
    data DataNascita;
} persona;

typedef struct {
    persona pazienti[1000];
    int numPazienti; //dice quante caselle dell’array contengono dati validi
} listaPazienti;

typedef struct {
    char CFPaziente[100];
    data d;
    orario o;
} visita;

typedef struct {
    visita visite[1000];
    int numVisite; //dice quante caselle dell’array contengono dati validi
} listaVisite;

listaPazienti f(listaPazienti P, listaVisite V);

int ver(persona paziente, listaVisite l)
    {
    int g_compl=paziente.DataNascita.giorno;
    int anno_compl=paziente.DataNascita.anno;
    int mese_compl=paziente.DataNascita.mese;
    for(int i=0; i<l.numVisite; i++)
        {
            if(strcmp(l.visite[i].CFPaziente,paziente.codiceFiscale)==0 && l.visite[i].d.giorno==g_compl && l.visite[i].d.mese==mese_compl)
                {
                    return 1;
                }
        }
    return 0;
    }
listaPazienti f(listaPazienti P, listaVisite V)
    {
    int segna=0;
    listaPazienti new;
    new.numPazienti=0;
    for(int i=0; i<P.numPazienti; i++)
        {
            if(ver(P.pazienti[i], V))
                {
                    new.numPazienti++;
                    new.pazienti[segna]=P.pazienti[i];
                }
        }
    return new;
    }
