//
//  main.c
//  es 11 7mz
//
//  Created by Francesco Roscio Ricon on 07/03/26.
//
//
//Un archivio musicale è organizzato nel seguente modo: gli artisti sono disposti in una lista e sono ordinati per nome; ogni artista ha associata una lista di album organizzati per anno e a parità di anno per ordine alfabetico; ogni album consta di una lista di canzoni ordinate per posizione all’interno dell’album.
//Le strutture dati utilizzate sono le seguenti:

//Si codifichi in C la seguente funzione:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Song { char * titolo;
                                   int durata, pos;
                                   struct Song * next; } Canzone;
typedef Canzone * ListaCanzoni;

typedef struct Album { char * titolo;
                                    int n_canzoni, anno;
                                    ListaCanzoni canzoni;
                                    struct Album * next; } Disco;
typedef Disco * ListaDischi;

typedef struct Singer { char * nome;
                                    int n_dischi;
                                    ListaDischi dischi;
                                    struct Singer * next; } Artista;
typedef Artista * ListaArtisti;

int main() {
}


int sommaCanzoni(ListaCanzoni head)
    {
        if(head==NULL)
            return 0;
    int somma=0;
    while(head!=NULL)
        {
            somma=somma+head->durata;
            head=head->next;
        }
    return somma;
    }

int discoPiuLungo(ListaArtisti artisti, int anno)
    {
    int lenmax=0;
    ListaArtisti scorri=artisti;
    while(scorri!=NULL)
        {
            ListaDischi disco=scorri->dischi;
            while(disco!=NULL)
                {
                    if(sommaCanzoni(disco->canzoni)>lenmax)
                        {
                            lenmax=sommaCanzoni(disco->canzoni);
                        }
                    disco=disco->next;
                }
            scorri=scorri->next;
        }
    return lenmax;
    }
ListaArtisti trovaartista(ListaArtisti head, char artista[])
    {
        if(head==NULL)
            return NULL;
    ListaArtisti scorri=head;
    while(scorri!=NULL)
        {
            if(strcmp(scorri->nome, artista)==0)
                return scorri;
            scorri=scorri->next;
        }
    return NULL;
    }
ListaDischi trovadisco(ListaDischi head, char nome_disco[])
    {
    if(head==NULL)
        return NULL;
ListaDischi scorri=head;
while(scorri!=NULL)
    {
        if(strcmp(scorri->titolo, nome_disco)==0)
            return scorri;
        scorri=scorri->next;
    }
return NULL;
    }
ListaCanzoni inserisci_incoda_canzone(ListaCanzoni head, char titolo[], int durata, int posizione)
    {
        if(head==NULL)
            {
                ListaCanzoni new=(ListaCanzoni)malloc(sizeof(*new));
                new->durata=durata;
                new->pos=posizione;
                strcpy(new->titolo, titolo);
                return new;
            }
    head->next=inserisci_incoda_canzone(head->next, titolo, durata, posizione);
    return head;
    }
ListaDischi insersici_incoda_disco(ListaDischi head, char titolo[], int durata, int posizione, int anno, char disc[])
    {
        if(head==NULL)
            {
                ListaDischi new=(ListaDischi)malloc(sizeof(*new));
                new->anno=anno;
                strcpy(new->titolo,disc);
                new->n_canzoni=1;
                new->next=NULL;
                new->canzoni=inserisci_incoda_canzone(new->canzoni, titolo, durata, posizione);
                return new;
            }
        head->next=insersici_incoda_disco(head->next, titolo, durata, posizione, anno, disc);
        return head;
    }

int inserisciCanzone(ListaArtisti Lis, char *artista, char *disc, int anno, char *canzone, int durata, int posizione)
    {
        ListaArtisti art=trovaartista(Lis, artista);
        if(art==NULL)
            return -1;
    ListaDischi d=NULL;
    d=trovadisco(art->dischi, disc);
    if(d==NULL)
        {
            art->dischi=insersici_incoda_disco(art->dischi, disc, durata, posizione, anno, disc);
        }
    else
        {
            d->n_canzoni++;
            d->canzoni=inserisci_incoda_canzone(d->canzoni, canzone, durata, posizione);
        }
    return 1;
    }
