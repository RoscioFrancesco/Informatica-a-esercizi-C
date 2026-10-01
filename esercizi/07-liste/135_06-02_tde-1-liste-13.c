//
//  main.c
//  tde 1 liste -13
//
//  Created by Francesco Roscio Ricon on 06/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef struct { int giorno, mese, anno; } Data;

typedef struct FN {
    char targa[8];
    int capienza, cilindrata, costoOrario;
    struct FN *next;
} Furgone;
typedef Furgone *Furgoni;

typedef struct PN {
    char targa[8];
    Data d;
    int durata; // in ore
    struct PN *next;
} Prenotazione;
typedef Prenotazione *Prenotazioni;

/* =========================
   PROTOTIPI (TUOI TODO)
   ========================= */
Furgone f1(Prenotazioni P, Furgoni F);
Furgoni f2(Prenotazioni P, Furgoni F);

/* =========================
   UTILITY DI TEST (OK usare cicli nel main)
   ========================= */
static Furgone* newFurgone(const char *targa, int cap, int cil, int costo, Furgone *next) {
    Furgone *p = (Furgone*)malloc(sizeof(Furgone));
    if(!p){ perror("malloc"); exit(1); }
    strncpy(p->targa, targa, 7);
    p->targa[7] = '\0';
    p->capienza = cap;
    p->cilindrata = cil;
    p->costoOrario = costo;
    p->next = next;
    return p;
}

static Prenotazione* newPren(const char *targa, int g, int m, int a, int durata, Prenotazione *next) {
    Prenotazione *p = (Prenotazione*)malloc(sizeof(Prenotazione));
    if(!p){ perror("malloc"); exit(1); }
    strncpy(p->targa, targa, 7);
    p->targa[7] = '\0';
    p->d.giorno = g; p->d.mese = m; p->d.anno = a;
    p->durata = durata;
    p->next = next;
    return p;
}

static void printData(Data d) {
    printf("%02d/%02d/%04d", d.giorno, d.mese, d.anno);
}

static void printFurgone(const Furgone *f) {
    if(!f){ printf("(NULL)\n"); return; }
    printf("Targa=%s  cap=%d  cil=%d  costoOrario=%d\n",
           f->targa, f->capienza, f->cilindrata, f->costoOrario);
}

static void printFurgoni(Furgoni F) {
    printf("=== Lista Furgoni ===\n");
    for(; F!=NULL; F=F->next) printFurgone(F);
}

static void printPrenotazioni(Prenotazioni P) {
    printf("=== Lista Prenotazioni ===\n");
    for(; P!=NULL; P=P->next) {
        printf("Targa=%s  data=", P->targa);
        printData(P->d);
        printf("  durata=%d\n", P->durata);
    }
}

static void freeFurgoni(Furgoni F) {
    while(F){
        Furgoni tmp = F->next;
        free(F);
        F = tmp;
    }
}

static void freePrenotazioni(Prenotazioni P) {
    while(P){
        Prenotazioni tmp = P->next;
        free(P);
        P = tmp;
    }
}

/* =========================
   MAIN DI PROVA
   ========================= */
int èanno(Data d, int anno);
int costoprenotazione(Prenotazioni P, char targa[], int costoOrario, int anno);
Furgoni inserimentoOrdinato(Furgoni head, Furgone x, Prenotazioni P);
int main(void) {
    /* Creo una lista furgoni (F) */
    Furgoni F = NULL;
    F = newFurgone("AA111AA", 12, 2000, 20, F);
    F = newFurgone("BB222BB",  9, 1600, 18, F);
    F = newFurgone("CC333CC", 15, 2200, 25, F);
    F = newFurgone("DD444DD",  8, 1400, 15, F);

    /* Creo una lista prenotazioni (P) */
    Prenotazioni P = NULL;
    P = newPren("AA111AA", 10,  1, 2016, 5, P);
    P = newPren("BB222BB",  3,  2, 2016, 9, P);
    P = newPren("AA111AA", 12,  2, 2016, 4, P);
    P = newPren("CC333CC",  1,  3, 2016, 2, P);
    P = newPren("CC333CC",  5,  3, 2015, 8, P);  /* fuori anno */
    P = newPren("DD444DD", 20,  4, 2016, 6, P);
    P = newPren("AA111AA",  1, 12, 2016, 1, P);

    printFurgoni(F);
    printf("\n");
    printPrenotazioni(P);
    printf("\n");

    /* ====== CHIAMATE RICHIESTE DALL'ESERCIZIO ====== */

    printf(">>> f1: furgone che ha reso di più nel 2016\n");
    Furgone best = f1(P, F);
    printFurgone(&best);  /* best è una struct, quindi stampo il suo indirizzo */

    printf("\n>>> f2: lista dei 10 furgoni che hanno reso di più nel 2016\n");
    Furgoni top10 = f2(P, F);
    printFurgoni(top10);

    freePrenotazioni(P);
    freeFurgoni(F);

    return 0;
}
int èanno(Data d, int anno)
    {
        if(d.anno==anno)
            return 1;
    return 0;
    }
Furgone f1(Prenotazioni P, Furgoni F)
    {
    Furgone massimo;
    massimo.next=NULL;
    int max=0;
    Furgoni scorri=F;
    while (scorri!=NULL) {
        if(costoprenotazione(P, scorri->targa, scorri->costoOrario, 2016)>max)
            {
                max=costoprenotazione(P, scorri->targa, scorri->costoOrario, 2016);
                massimo=*scorri;
            }
        scorri=scorri->next;
        }
    return massimo;
    }
int costoprenotazione(Prenotazioni P, char targa[], int costoOrario, int anno)
    {
        if(P==NULL)
            return 0;
    Prenotazioni scorri=P;
    int somma=0;
    while (scorri!=NULL) {
        if(strcmp(scorri->targa, targa)==0 && èanno(scorri->d, anno))
            {
                somma=somma+(costoOrario*scorri->durata);
            }
        scorri=scorri->next;
        }
    return somma;
    }
Furgoni f2(Prenotazioni P, Furgoni F);

Furgoni inserimentoOrdinato(Furgoni head, Furgone x, Prenotazioni P)
    {
        if(head==NULL || costoprenotazione(P, x.targa, x.costoOrario, 2016)>costoprenotazione(P, head->targa, head->costoOrario, 2016))
            {
                Furgoni new=(Furgoni)malloc(sizeof(*new));
                *new=x;
                new->next=head;
                return new;
            }
        head->next=inserimentoOrdinato(head->next, x, P);
        return head;
    }
Furgoni crealistaordinata(Prenotazioni P, Furgoni F)
    {
    if (F==NULL) {
        return F;
        }
    Furgoni scorri=F;
    Furgoni new=NULL;
    while (scorri!=NULL) {
        new=inserimentoOrdinato(new, *scorri, P);
        scorri=scorri->next;
        }
        return new;
    }

Furgoni f2(Prenotazioni P, Furgoni F)
    {
    int var=10;
    Furgoni lista=crealistaordinata(P, F);
    Furgoni scorri=lista;
    for(int i=0; scorri!=NULL && i<var-1; i++)
        {
            scorri=scorri->next;
        }
    if(scorri==NULL)
        return lista;
    Furgoni temp=scorri->next;
    scorri->next=NULL;
    while(temp!=NULL)
        {
            Furgoni temp2=temp->next;
            free(temp);
            temp=temp2;
        }
    return lista;
    }
