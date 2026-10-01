//
//  main.c
//  tde 4 es struct -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come testo)
   ========================= */
typedef struct Date { int giorno; int mese; int anno; } Data;

typedef struct Item {
    int numeroDiPatente;
    char *cognome;
    char *nome;
    char *professione;
    int punti;
    struct Item *next;
} Patente;

typedef Patente* ListaDiPatenti;

typedef struct Node {
    int numeroDiPatente;
    int puntiTolti;
    Data data;
    struct Node *next;
} Multa;

typedef Multa* ListaDiMulte;


/* distanza(d1,d2) = distanza in giorni tra le due date */
int distanza(Data d1, Data d2);   // si assume esista


void aggiornaPunti(ListaDiPatenti P, ListaDiMulte M);  // TODO

/* =========================
   UTILITY PER TEST
   ========================= */
static Patente* newPatente(int num, const char* cogn, const char* nome, const char* prof, int punti) {
    Patente* p = (Patente*)malloc(sizeof(Patente));
    if(!p){ perror("malloc"); exit(1); }
    p->numeroDiPatente = num;
    p->cognome = strdup(cogn);
    p->nome = strdup(nome);
    p->professione = strdup(prof);
    p->punti = punti;
    p->next = NULL;
    return p;
}

static Multa* newMulta(int num, int tolti, Data d) {
    Multa* m = (Multa*)malloc(sizeof(Multa));
    if(!m){ perror("malloc"); exit(1); }
    m->numeroDiPatente = num;
    m->puntiTolti = tolti;
    m->data = d;
    m->next = NULL;
    return m;
}

static ListaDiPatenti pushPatenteCoda(ListaDiPatenti L, Patente* p) {
    if(L == NULL) return p;
    Patente* t = L;
    while(t->next) t = t->next;
    t->next = p;
    return L;
}

static ListaDiMulte pushMultaCoda(ListaDiMulte L, Multa* m) {
    if(L == NULL) return m;
    Multa* t = L;
    while(t->next) t = t->next;
    t->next = m;
    return L;
}

static void printPatenti(ListaDiPatenti P) {
    printf("Patenti:\n");
    while(P) {
        printf("  #%d %s %s  punti=%d\n", P->numeroDiPatente, P->nome, P->cognome, P->punti);
        P = P->next;
    }
}

static void printMulte(ListaDiMulte M) {
    printf("Multe (ordinate per data):\n");
    while(M) {
        printf("  #%d  -%d punti  data=%02d/%02d/%04d\n",
               M->numeroDiPatente, M->puntiTolti,
               M->data.giorno, M->data.mese, M->data.anno);
        M = M->next;
    }
}

static void freePatenti(ListaDiPatenti P) {
    while(P) {
        Patente* tmp = P;
        P = P->next;
        free(tmp->cognome);
        free(tmp->nome);
        free(tmp->professione);
        free(tmp);
    }
}

static void freeMulte(ListaDiMulte M) {
    while(M) {
        Multa* tmp = M;
        M = M->next;
        free(tmp);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    ListaDiPatenti P = NULL;

    /* 3 patenti */
    P = pushPatenteCoda(P, newPatente(101, "Rossi",  "Mario", "Impiegato", 20));
    P = pushPatenteCoda(P, newPatente(202, "Bianchi","Luca",  "Studente", 20));
    P = pushPatenteCoda(P, newPatente(303, "Verdi",  "Anna",  "Medico",   20));

    /* Multe ordinate per data */
    ListaDiMulte M = NULL;
    /* Mario (101) prende 2 multe entro 30 giorni: la seconda ha -2 extra */
    M = pushMultaCoda(M, newMulta(101, 3, (Data){10, 1, 2020}));  /* 10/01 */
    M = pushMultaCoda(M, newMulta(202, 5, (Data){25, 1, 2020}));  /* Luca 25/01 */
    M = pushMultaCoda(M, newMulta(101, 4, (Data){05, 2, 2020}));  /* Mario 05/02 (entro 30gg dal 10/01) */
    /* Anna (303) due multe lontane: nessun extra */
    M = pushMultaCoda(M, newMulta(303, 2, (Data){01, 3, 2020}));  /* 01/03 */
    M = pushMultaCoda(M, newMulta(303, 2, (Data){10, 4, 2020}));  /* 10/04 (oltre 30gg) */

    printf("=== INPUT ===\n");
    printPatenti(P);
    printf("\n");
    printMulte(M);

    printf("\n=== DOPO aggiornaPunti ===\n");
    aggiornaPunti(P, M);     /* TODO: tua funzione */
    printPatenti(P);

    freePatenti(P);
    freeMulte(M);
    return 0;
}




int bisestile(int anno) {
    return ( (anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0) );
}

int giorniNelMese(int mese, int anno) {
    int giorni[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if(mese == 2 && bisestile(anno))
        return 29;

    return giorni[mese - 1];
}

/* Converte una data in "numero di giorni" da un anno base (es. anno 0) */
long giorniTotali(Data d) {
    long tot = 0;

    /* somma giorni per anni completi precedenti */
    for(int a = 0; a < d.anno; a++) {
        tot += bisestile(a) ? 366 : 365;
    }

    /* somma giorni per mesi completi dell'anno corrente */
    for(int m = 1; m < d.mese; m++) {
        tot += giorniNelMese(m, d.anno);
    }

    /* aggiungi giorni del mese corrente */
    tot += d.giorno;

    return tot;
}

/* =========================
   FUNZIONE RICHIESTA
   ========================= */

int distanza(Data d1, Data d2) {
    long g1 = giorniTotali(d1);
    long g2 = giorniTotali(d2);

    long diff = g1 - g2;
    if(diff < 0) diff = -diff;

    return (int)diff;
}

int ver(ListaDiMulte multe, int numeropatente, Data oggi)
    {
        if(multe==NULL)
            return 0;
    int sommapuntidatogliere=0;
    while (multe!=NULL) {
        if(multe->numeroDiPatente==numeropatente)
            {
                sommapuntidatogliere=sommapuntidatogliere+multe->puntiTolti;
                if(distanza(oggi, multe->data)<=30)
                {
                    sommapuntidatogliere=sommapuntidatogliere+2;
                }
            }
        multe=multe->next;
    }
    return sommapuntidatogliere;
    }
void aggiornaPunti(ListaDiPatenti P, ListaDiMulte M) {
    Data oggi;
    oggi.anno=2026;
    oggi.giorno=14;
    oggi.mese=2;
    if(P==NULL || M==NULL)
        return;
    ListaDiPatenti scorriP=P;
    while(scorriP!=NULL)
        {
            scorriP->punti=scorriP->punti-ver(M, scorriP->numeroDiPatente, oggi);
            scorriP=scorriP->next;
        }
}
