//  Created by Francesco Roscio Ricon on 04/02/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ======================================================
   STRUTTURE DATI (TESTO D'ESAME)
   ====================================================== */

typedef struct Painting {
    char nome[1000];
    char codice[100];
    int prezzo;
    struct Painting *next;
} Quadro;

typedef Quadro *ListaQuadri;

typedef struct Painter {
    char cognome[1000];
    char nome[1000];
    char statodiNascita[1000];
    ListaQuadri quadr;
    struct Painter *next;
} Pittore;

typedef Pittore *ListaPittori;

/* ======================================================
   STRUCT DI SUPPORTO (TIPICA DA ESAME)
   ====================================================== */
ListaQuadri nuovoQuadro(char *nome, char *codice, int prezzo, ListaQuadri next) {
    Quadro *q = malloc(sizeof(Quadro));
    strcpy(q->nome, nome);
    strcpy(q->codice, codice);
    q->prezzo = prezzo;
    q->next = next;
    return q;
}

ListaPittori nuovoPittore(char *nome, char *cognome, char *nazione,
                          ListaQuadri quadri, ListaPittori next) {
    Pittore *p = malloc(sizeof(Pittore));
    strcpy(p->nome, nome);
    strcpy(p->cognome, cognome);
    strcpy(p->statodiNascita, nazione);
    p->quadr = quadri;
    p->next = next;
    return p;
}

/* ======================================================
   STAMPA (VERIFICA)
   ====================================================== */

void stampaQuadri(ListaQuadri q) {
    while (q != NULL) {
        printf("    - %s (%s): %d euro\n",
               q->nome, q->codice, q->prezzo);
        q = q->next;
    }
}

void stampaPittori(ListaPittori p) {
    while (p != NULL) {
        printf("Pittore: %s %s [%s]\n",
               p->nome, p->cognome, p->statodiNascita);
        stampaQuadri(p->quadr);
        p = p->next;
    }
}
float medianazione(ListaPittori pittori, char nazione[]);
void f(char nazione[], ListaPittori pittori, float *count, float *somma);
void funz(ListaPittori pittori, float *count, float *somma);
float mediatot(ListaPittori pittori);
int ver(float media, int prezzo);

/* ======================================================
   MAIN
   ====================================================== */
ListaPittori eliminaPittori(ListaPittori head, float media);
ListaQuadri eliminalistaquadri(ListaQuadri head, float media);
int ver(float media, int prezzo);

int main() {

    /* --- Spagna --- */
    ListaQuadri q_picasso = NULL;
    q_picasso = nuovoQuadro("Guernica", "S1", 1000, q_picasso);
    q_picasso = nuovoQuadro("Les Demoiselles", "S2", 1500, q_picasso);

    /* --- Olanda --- */
    ListaQuadri q_vangogh = NULL;
    q_vangogh = nuovoQuadro("Notte stellata", "O1", 2000, q_vangogh);

    /* --- Italia --- */
    ListaQuadri q_caravaggio = NULL;
    q_caravaggio = nuovoQuadro("Giuditta", "I1", 1800, q_caravaggio);
    q_caravaggio = nuovoQuadro("Bacco", "I2", 1600, q_caravaggio);

    /* --- Francia --- */
    ListaQuadri q_monet = NULL;
    q_monet = nuovoQuadro("Ninfee", "F1", 1700, q_monet);
    q_monet = nuovoQuadro("Impressione", "F2", 1400, q_monet);

    ListaPittori pittori = NULL;
    pittori = nuovoPittore("Claude", "Monet", "Francia", q_monet, pittori);
    pittori = nuovoPittore("Michelangelo", "Caravaggio", "Italia", q_caravaggio, pittori);
    pittori = nuovoPittore("Vincent", "Van Gogh", "Olanda", q_vangogh, pittori);
    pittori = nuovoPittore("Pablo", "Picasso", "Spagna", q_picasso, pittori);

    printf("=== ARCHIVIO GALLERIA ===\n");
    stampaPittori(pittori);

    printf("\n=== MEDIE PER NAZIONE ===\n");
    printf("Spagna  : %.2f\n", medianazione(pittori, "Spagna"));
    printf("Italia  : %.2f\n", medianazione(pittori, "Italia"));
    printf("Francia : %.2f\n", medianazione(pittori, "Francia"));
    printf("Olanda  : %.2f\n", medianazione(pittori, "Olanda"));
    
    float media=500;
    pittori = eliminaPittori(pittori, media);

        printf("\n=== LISTA DOPO eliminaQuadro ===\n");
        stampaPittori(pittori);
    
}


void f(char nazione[], ListaPittori pittori, float *count, float *somma)
    {
        if(pittori==NULL)
            return;
    ListaPittori scorri=pittori;
    while (scorri!=NULL) {
        if(strcmp(scorri->statodiNascita, nazione)==0)
            {
                ListaQuadri scorriquadri=scorri->quadr;
                while(scorriquadri!=NULL)
                    {
                        *somma=*somma+scorriquadri->prezzo;
                        (*count)++;
                        scorriquadri=scorriquadri->next;
                    }
            }
        scorri=scorri->next;
        }
    }
float medianazione(ListaPittori pittori, char nazione[])
    {
    float somma=0;
    float count=0;
    f(nazione, pittori, &count, &somma);
    return (somma)/count;
    }
float mediatot(ListaPittori pittori)
    {
    float somma=0;
    float count=0;
    funz(pittori, &count, &somma);
    return (somma)/count;
    }
void funz(ListaPittori pittori, float *count, float *somma)
    {
        if(pittori==NULL)
            return;
    ListaPittori scorri=pittori;
    while (scorri!=NULL) {
        
                ListaQuadri scorriquadri=scorri->quadr;
                while(scorriquadri!=NULL)
                    {
                        *somma=*somma+scorriquadri->prezzo;
                        (*count)++;
                        scorriquadri=scorriquadri->next;
                    }
        scorri=scorri->next;
        }
    }

ListaQuadri eliminalistaquadri(ListaQuadri head, float media)
    {
        if(head==NULL)
            return head;
        if(ver(media, head->prezzo))
            {
                ListaQuadri temp=head->next;
                free(head);
                return eliminalistaquadri(temp, media);
            }
        head->next=eliminalistaquadri(head->next, media);
        return head;
    }
int ver(float media, int prezzo)
    {
        if(prezzo>2*media)
            return 1;
    return 0;
    }
ListaPittori eliminaPittori(ListaPittori head, float media)
    {
        if(head==NULL)
            return head;
        head->quadr=eliminalistaquadri(head->quadr, media);
        if(head->quadr==NULL)
            {
                ListaPittori temp=head->next;
                free(head);
                return eliminaPittori(temp, media);
            }
        head->next=eliminaPittori(head->next, media);
        return head;
    }
