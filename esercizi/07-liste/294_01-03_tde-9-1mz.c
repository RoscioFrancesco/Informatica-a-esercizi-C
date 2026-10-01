//
//  main.c
//  tde 9 1mz
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//


#include <stdlib.h>
#include <string.h>
#define N 5
typedef char * nome;             //una stringa
typedef nome * elencocandidati;  //il tipo di un vettore di puntatori a carattere
typedef nome candidati[N];       //un vettore di N puntatori a carattere
typedef struct lis { int numLista;
                     elencocandidati elenconomi; //”punta a” un vettore di tipo candidati
                     struct lis * next; } listacandidati;
typedef listacandidati * lista;  //una lista di listacandidati (una per lista)

typedef struct sc { int numLista;
                    char * preferenza;
                    struct sc * next; } scheda;
typedef scheda * listascrutinio;  // una lista di schede scrutinate
int numvoti(char nome[], listascrutinio L);
int piuVotato(nome n, int numLista, listascrutinio ls, lista L)
    {
    int num_max;
    char nome[100];
    elencocandidati elenco;
    lista scorri=L;
    while(scorri!=NULL)
        {
            if(scorri->numLista==numLista)
                {
                    elenco=scorri->elenconomi;
                    break;
                }
            scorri=scorri->next;
        }
    int max=0;
    for(int i=0; i<N; i++)
        {
            if(numvoti(elenco[i], ls)>max)
                {
                    max=numvoti(elenco[i], ls);
                    strcpy(nome, elenco[i]);
                }
        }
    strcpy(n,nome);
    return max;
    }

int numvoti(char nome[], listascrutinio L)
    {
    int count=0;
    while(L!=NULL)
        {
            if(strcmp(nome, L->preferenza)==0)
                count++;
            L=L->next;
        }
    return count;
    }
