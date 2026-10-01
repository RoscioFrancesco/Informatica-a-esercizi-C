//
//  main.c
//  tde liste 1 -11
//
//  Created by Francesco Roscio Ricon on 08/02/26.
//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct D {
    int giorno, mese, anno;
} Data;

typedef struct Es {
    char codice[N], nome[N];
    int voto, crediti;
    Data d;
    struct Es *next;
} Esame;

typedef Esame* ListaEsami;

typedef struct St {
    char nome[N], cognome[N];
    int Media, totaleCrediti;   /* (nota: nel testo sono int, anche se la media pesata spesso è float) */
    ListaEsami esami;
    struct St *next;
} Studente;

typedef Studente* ListaStudenti;
void distruggiesami(ListaEsami esami);


void Calcola(ListaStudenti lis);
ListaStudenti eliminaStudente(ListaStudenti lis);

/* =========================
   UTILITY: creazione nodi
   ========================= */
static Esame* newEsame(const char *cod, const char *nome, int voto, int crediti, Data d) {
    Esame *e = (Esame*)malloc(sizeof(Esame));
    if (!e) { perror("malloc"); exit(1); }
    strncpy(e->codice, cod, N-1); e->codice[N-1] = '\0';
    strncpy(e->nome, nome, N-1); e->nome[N-1] = '\0';
    e->voto = voto;
    e->crediti = crediti;
    e->d = d;
    e->next = NULL;
    return e;
}

static Studente* newStudente(const char *nome, const char *cognome) {
    Studente *s = (Studente*)malloc(sizeof(Studente));
    if (!s) { perror("malloc"); exit(1); }
    strncpy(s->nome, nome, N-1); s->nome[N-1] = '\0';
    strncpy(s->cognome, cognome, N-1); s->cognome[N-1] = '\0';
    s->Media = 0;
    s->totaleCrediti = 0;
    s->esami = NULL;
    s->next = NULL;
    return s;
}

/* inserimento in testa (semplice per costruire esempi) */
static ListaStudenti pushStudente(ListaStudenti head, Studente *s) {
    s->next = head;
    return s;
}

static ListaEsami pushEsame(ListaEsami head, Esame *e) {
    e->next = head;
    return e;
}

/* =========================
   UTILITY: stampa
   ========================= */
static void stampaData(Data d) {
    printf("%02d/%02d/%04d", d.giorno, d.mese, d.anno);
}

static void stampaEsami(ListaEsami e) {
    if (!e) {
        printf("    (nessun esame)\n");
        return;
    }
    while (e) {
        printf("    - [%s] %s | voto=%d | crediti=%d | data=",
               e->codice, e->nome, e->voto, e->crediti);
        stampaData(e->d);
        printf("\n");
        e = e->next;
    }
}

static void stampaStudenti(ListaStudenti s) {
    if (!s) {
        printf("(lista studenti vuota)\n");
        return;
    }
    while (s) {
        printf("Studente: %s %s | Media=%d | totaleCrediti=%d\n",
               s->nome, s->cognome, s->Media, s->totaleCrediti);
        printf("  Esami:\n");
        stampaEsami(s->esami);
        printf("\n");
        s = s->next;
    }
}

/* =========================
   UTILITY: free
   ========================= */
static void freeEsami(ListaEsami e) {
    while (e) {
        ListaEsami nx = e->next;
        free(e);
        e = nx;
    }
}

static void freeStudenti(ListaStudenti s) {
    while (s) {
        ListaStudenti nx = s->next;
        freeEsami(s->esami);
        free(s);
        s = nx;
    }
}


ListaStudenti eliminaStudente(ListaStudenti lis);
int main(void) {
    ListaStudenti studenti = NULL;

    /* Creo 3 studenti */
    Studente *s1 = newStudente("Marco", "Rossi");
    Studente *s2 = newStudente("Giulia", "Bianchi");
    Studente *s3 = newStudente("Luca", "Verdi");

    /* Associo qualche esame (date miste pre/post 01/01/2007) */
    s1->esami = pushEsame(s1->esami, newEsame("INF101", "Informatica A", 28, 10, (Data){15, 2, 2006}));
    s1->esami = pushEsame(s1->esami, newEsame("MAT001", "Analisi 1",     30, 12, (Data){10, 6, 2008}));

    s2->esami = pushEsame(s2->esami, newEsame("FIS010", "Fisica",        18,  8, (Data){20, 1, 2007}));
    s2->esami = pushEsame(s2->esami, newEsame("INF101", "Informatica A", 0,  10, (Data){ 5, 3, 2010})); /* voto 0: solo per test, non assumere regole */

    /* s3 senza esami */
    s3->esami = NULL;

    /* Inserisco in lista studenti */
    studenti = pushStudente(studenti, s3);
    studenti = pushStudente(studenti, s2);
    studenti = pushStudente(studenti, s1);

    printf("=== LISTA INIZIALE ===\n");
    stampaStudenti(studenti);

    printf("=== CHIAMO Calcola(studenti) (STUB, non cambia nulla finché non lo implementi) ===\n");
    Calcola(studenti);
    stampaStudenti(studenti);

    printf("=== CHIAMO eliminaStudente(studenti) (STUB, non cambia nulla finché non lo implementi) ===\n");
    studenti = eliminaStudente(studenti);
    stampaStudenti(studenti);

    freeStudenti(studenti);
    return 0;
}


void dati(ListaEsami esami, float *sommacrediti, float *media)
    {
        if(esami==NULL)
            return;
    ListaEsami scorri=esami;
    float sommavotipercrediti=0;
    float crediti=0;
    while (scorri!=NULL)
    {
        sommavotipercrediti=sommavotipercrediti+(scorri->crediti*scorri->voto);
        crediti=crediti+scorri->crediti;
        scorri=scorri->next;
    }
    if(crediti!=0){
        *media=sommavotipercrediti/crediti;}
    else
        {
            *media=0;
        }
    *sommacrediti=crediti;
    return;
    }
void Calcola(ListaStudenti lis)
    {
        if(lis==NULL)
            return;
    ListaStudenti scorri=lis;
    while (scorri!=NULL) {
        float media=0;
        float totalecrediti=0;
        dati(scorri->esami, &totalecrediti, &media);
        scorri->Media=(int)media;
        scorri->totaleCrediti=(int)totalecrediti;
        scorri=scorri->next;
        }
    }
int ver(ListaStudenti studente) // 1 se vanno eliminati gli esami, altrimenti 0
    {
    Studente singolo=*studente;
    ListaEsami esami=singolo.esami;
    if(esami==NULL)
        return 1;
    while (esami!=NULL) {
        if(esami->d.anno>=2007 && esami->voto>=18)
        {
            return 0;
        }
        esami=esami->next;
        }
    return 1;
    }
ListaStudenti eliminaStudente(ListaStudenti lis)
    {
        if(lis==NULL)
            return lis;
        if(ver(lis))
            {
                ListaStudenti temp=lis->next;
                distruggiesami(lis->esami);
                free(lis);
                return eliminaStudente(temp);
            }
    lis->next=eliminaStudente(lis->next);
    return lis;
    }
void distruggiesami(ListaEsami esami)
    {
    if(esami==NULL)
        return;
    ListaEsami succ=esami->next;
    free(esami);
    distruggiesami(succ);
    }
