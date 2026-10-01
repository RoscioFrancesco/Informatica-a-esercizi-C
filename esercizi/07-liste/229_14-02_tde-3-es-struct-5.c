//
//  main.c
//  tde 3 es struct -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int giorno, mese, anno; } Data;

typedef struct Driver {
    char codice[100], nome[100], patente[100];
    Data dataDiNascita;
    struct Driver *next;
} Autista;

typedef Autista* Autisti;

typedef struct Bus {
    char *targa;
    int NumeroPosti;
    Data dataImmatricolazione;
    struct Bus *next;
} Autobus;

typedef Autobus* Veicoli;

typedef struct Ride {
    char targaBus[100];
    char codiceAutista[100];
    char tipoCorsa;      /* 'U', 'S', 'E' */
    struct Ride *next;
} Corsa;

typedef Corsa* Corse;

/* =========================
   PROTOTIPI RICHIESTI
   ========================= */

int AutistiEsperti(Corse C, Autisti A);     /* TODO */
Corse eliminaCorsa(Corse C, Veicoli V);     /* TODO */

/* =========================
   UTILITY CREAZIONE NODI
   ========================= */

static Data mkData(int g, int m, int a) {
    Data d; d.giorno=g; d.mese=m; d.anno=a; return d;
}

static Autista* newAutista(const char *cod, const char *nome, const char *pat, Data nasc) {
    Autista *x = (Autista*)malloc(sizeof(Autista));
    if(!x){ perror("malloc"); exit(1); }
    strncpy(x->codice, cod, sizeof(x->codice)-1); x->codice[99]='\0';
    strncpy(x->nome, nome, sizeof(x->nome)-1); x->nome[99]='\0';
    strncpy(x->patente, pat, sizeof(x->patente)-1); x->patente[99]='\0';
    x->dataDiNascita = nasc;
    x->next = NULL;
    return x;
}

static Autobus* newBus(const char *targa, int posti, Data imm) {
    Autobus *b = (Autobus*)malloc(sizeof(Autobus));
    if(!b){ perror("malloc"); exit(1); }
    b->targa = (char*)malloc(strlen(targa)+1);
    if(!b->targa){ perror("malloc"); exit(1); }
    strcpy(b->targa, targa);
    b->NumeroPosti = posti;
    b->dataImmatricolazione = imm;
    b->next = NULL;
    return b;
}

static Corsa* newCorsa(const char *targa, const char *codAut, char tipo) {
    Corsa *c = (Corsa*)malloc(sizeof(Corsa));
    if(!c){ perror("malloc"); exit(1); }
    strncpy(c->targaBus, targa, sizeof(c->targaBus)-1); c->targaBus[99]='\0';
    strncpy(c->codiceAutista, codAut, sizeof(c->codiceAutista)-1); c->codiceAutista[99]='\0';
    c->tipoCorsa = tipo;
    c->next = NULL;
    return c;
}

static Autisti pushAutista(Autisti A, Autista *x) {
    x->next = A;
    return x;
}

static Veicoli pushBus(Veicoli V, Autobus *b) {
    b->next = V;
    return b;
}

static Corse pushCorsa(Corse C, Corsa *c) {
    c->next = C;
    return c;
}

/* =========================
   STAMPA
   ========================= */

static void printAutisti(Autisti A) {
    printf("Autisti:\n");
    while(A){
        printf("  [%s] %s (nato %02d/%02d/%04d)\n",
               A->codice, A->nome,
               A->dataDiNascita.giorno, A->dataDiNascita.mese, A->dataDiNascita.anno);
        A = A->next;
    }
}

static void printVeicoli(Veicoli V) {
    printf("Veicoli:\n");
    while(V){
        printf("  [%s] imm %02d/%02d/%04d\n",
               V->targa,
               V->dataImmatricolazione.giorno, V->dataImmatricolazione.mese, V->dataImmatricolazione.anno);
        V = V->next;
    }
}

static void printCorse(Corse C) {
    printf("Corse:\n");
    while(C){
        printf("  bus=%s autista=%s tipo=%c\n", C->targaBus, C->codiceAutista, C->tipoCorsa);
        C = C->next;
    }
}

/* =========================
   FREE
   ========================= */

static void freeAutisti(Autisti A) {
    while(A){
        Autista *tmp=A; A=A->next; free(tmp);
    }
}

static void freeVeicoli(Veicoli V) {
    while(V){
        Autobus *tmp=V; V=V->next;
        free(tmp->targa);
        free(tmp);
    }
}

static void freeCorse(Corse C) {
    while(C){
        Corsa *tmp=C; C=C->next; free(tmp);
    }
}
int meno60anni(char codiceautista[], Autisti A);

int main(void) {
    /* Autisti (nota: check semplificato: nato dopo il 1955 => anno >= 1956) */
    Autisti A = NULL;
    A = pushAutista(A, newAutista("A1","Mario Rossi","D", mkData(10,2,1960))); /* ok */
    A = pushAutista(A, newAutista("A2","Luca Bianchi","D", mkData(1,5,1954))); /* NO (prima del 1956) */
    A = pushAutista(A, newAutista("A3","Anna Verdi","D", mkData(20,9,1970))); /* ok */

    /* Veicoli */
    Veicoli V = NULL;
    V = pushBus(V, newBus("BUS111", 50, mkData(1,1,2004)));  /* da eliminare (prima del 2005) */
    V = pushBus(V, newBus("BUS222", 40, mkData(1,6,2005)));  /* ok (non eliminare) */
    V = pushBus(V, newBus("BUS333", 30, mkData(15,3,2010))); /* ok */

    /* Corse: metto un extraurbano guidato da A2 (nato 1954) -> AutistiEsperti deve dare 0 */
    Corse C = NULL;
    C = pushCorsa(C, newCorsa("BUS333","A3",'U'));
    C = pushCorsa(C, newCorsa("BUS111","A1",'S')); /* bus del 2004 -> verrà eliminata */
    C = pushCorsa(C, newCorsa("BUS222","A2",'E')); /* extraurbano con autista troppo vecchio -> fail */
    C = pushCorsa(C, newCorsa("BUS111","A2",'E')); /* extraurbano + bus vecchio -> verrà eliminata */
    C = pushCorsa(C, newCorsa("BUS333","A1",'E')); /* extraurbano ok */

    printf("=== DATI IN INPUT ===\n");
    printAutisti(A);
    printVeicoli(V);
    printCorse(C);

    printf("\n=== TEST AutistiEsperti ===\n");
    int ok = AutistiEsperti(C, A);
    printf("AutistiEsperti = %d\n", ok);

    printf("\n=== TEST eliminaCorsa (bus immatricolati prima del 2005) ===\n");
    Corse C2 = eliminaCorsa(C, V);
    printCorse(C2);

    freeAutisti(A);
    freeVeicoli(V);
    freeCorse(C2);

    return 0;
}

int AutistiEsperti(Corse C, Autisti A) {
    if(C==NULL)
        return 0;
    Corse scorricorse=C;
    while (scorricorse!=NULL) {
        if(scorricorse->tipoCorsa=='E' && meno60anni(scorricorse->codiceAutista, A)==0)
            return 0;
        scorricorse=scorricorse->next;
    }
    return 1;
}
int meno60anni(char codiceautista[], Autisti A)
    {
        if(A==NULL)
            return 0;
    Autisti scorri=A;
    while (scorri!=NULL) {
        if(strcmp(scorri->codice,codiceautista)==0)
            {
                if(scorri->dataDiNascita.anno>1995)
                    return 1;
                return 0;
            }
        scorri=scorri->next;
    }
    return 0;
    }
//cancella dalla lista C tutte le corse che utilizzano autobus immatricolati prima del 2005.
int ver(Veicoli V, char targa[]) // 1 se deve cancellare
    {
        if(V==NULL)
            return 0;
        Veicoli scorriV=V;
        while (scorriV!=NULL) {
            if(strcmp(scorriV->targa, targa)==0)
                {
                    if (scorriV->dataImmatricolazione.anno<2005) {
                        return 1;
                    }
                    return 0;
                }
            scorriV=scorriV->next;
        }
        return 0;
    }
Corse eliminaCorsa(Corse C, Veicoli V)
    {
        if(C==NULL)
            return C;
        if(ver(V, C->targaBus))
            {
                Corse succ=C->next;
                free(C);
                C=succ;
                return eliminaCorsa(C, V);
            }
    C->next=eliminaCorsa(C->next, V);
    return C;
    }
