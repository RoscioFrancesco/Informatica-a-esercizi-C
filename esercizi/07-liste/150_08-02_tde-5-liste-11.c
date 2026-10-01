//
//  main.c
//  tde 5 liste -11
//
//  Created by Francesco Roscio Ricon on 08/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct Date {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    char *citta;
    char *stato;
} Destinazione;

typedef struct Imp {
    int matricola;
    char *cognome, *nome;
    int giorniDiFerieMaturati;
    struct Imp *next;
} Impiegato;

typedef Impiegato *ListaDiImpiegati;

typedef struct Vi {
    int matricola;
    Destinazione d;
    Data dataInizio, dataFine;
    struct Vi *next;
} Viaggio;

typedef Viaggio *ListaDiViaggi;




/* =========================
   UTILITY (creazione/stampa/free)
   ========================= */

static char *dupstr(const char *s) {
    char *p = (char *)malloc(strlen(s) + 1);
    if (!p) { perror("malloc"); exit(1); }
    strcpy(p, s);
    return p;
}

static Data makeData(int g, int m, int a) {
    Data d; d.giorno = g; d.mese = m; d.anno = a;
    return d;
}

static ListaDiImpiegati newImp(int matricola, const char *cognome, const char *nome, int ferie) {
    Impiegato *n = (Impiegato *)malloc(sizeof(*n));
    if (!n) { perror("malloc"); exit(1); }
    n->matricola = matricola;
    n->cognome = dupstr(cognome);
    n->nome = dupstr(nome);
    n->giorniDiFerieMaturati = ferie;
    n->next = NULL;
    return n;
}

static void pushImp(ListaDiImpiegati *head, ListaDiImpiegati node) {
    node->next = *head;
    *head = node;
}

static ListaDiViaggi newViaggio(int matricola,
                                const char *citta, const char *stato,
                                Data inizio, Data fine) {
    Viaggio *v = (Viaggio *)malloc(sizeof(*v));
    if (!v) { perror("malloc"); exit(1); }
    v->matricola = matricola;
    v->d.citta = dupstr(citta);
    v->d.stato = dupstr(stato);
    v->dataInizio = inizio;
    v->dataFine = fine;
    v->next = NULL;
    return v;
}

static void pushViaggio(ListaDiViaggi *head, ListaDiViaggi node) {
    node->next = *head;
    *head = node;
}

static void stampaImpiegati(ListaDiImpiegati l) {
    printf("=== IMPIEGATI ===\n");
    for (; l != NULL; l = l->next) {
        printf("Matricola: %d | %s %s | ferie: %d\n",
               l->matricola, l->nome, l->cognome, l->giorniDiFerieMaturati);
    }
    printf("\n");
}

static void stampaViaggi(ListaDiViaggi v) {
    printf("=== VIAGGI ===\n");
    for (; v != NULL; v = v->next) {
        printf("Matricola: %d | %s (%s) | %02d/%02d/%04d -> %02d/%02d/%04d\n",
               v->matricola,
               v->d.citta, v->d.stato,
               v->dataInizio.giorno, v->dataInizio.mese, v->dataInizio.anno,
               v->dataFine.giorno,  v->dataFine.mese,  v->dataFine.anno);
    }
    printf("\n");
}

static void freeImpiegati(ListaDiImpiegati l) {
    while (l) {
        ListaDiImpiegati tmp = l->next;
        free(l->cognome);
        free(l->nome);
        free(l);
        l = tmp;
    }
}

static void freeViaggi(ListaDiViaggi v) {
    while (v) {
        ListaDiViaggi tmp = v->next;
        free(v->d.citta);
        free(v->d.stato);
        free(v);
        v = tmp;
    }
}

/* =========================
   FUNZIONE RICHIESTA (STUB)
   ========================= */


/* =========================
   MAIN DI TEST
   ========================= */
void aggiornaFerie(ListaDiViaggi viaggi, ListaDiImpiegati impiegati);
int ver(ListaDiViaggi viaggi, int matricola);
int main(void) {
    ListaDiImpiegati imp = NULL;
    ListaDiViaggi viaggi = NULL;

    /* Impiegati di esempio */
    pushImp(&imp, newImp(1001, "Rossi", "Mario", 10));
    pushImp(&imp, newImp(1002, "Bianchi", "Luca", 7));
    pushImp(&imp, newImp(1003, "Verdi", "Anna", 12));

    /* Viaggi di esempio
       Nota: qui ci sono viaggi in Italia e all'estero con varie durate
       (la logica vera la farai in aggiornaFerie)
    */
    pushViaggio(&viaggi, newViaggio(1001, "Roma", "Italia",
                                    makeData(1, 2, 2026), makeData(10, 2, 2026)));   /* 9 giorni (Italia) */
    pushViaggio(&viaggi, newViaggio(1001, "Parigi", "Francia",
                                    makeData(1, 1, 2026), makeData(12, 1, 2026)));  /* 11 giorni (estero) */
    pushViaggio(&viaggi, newViaggio(1002, "Berlino", "Germania",
                                    makeData(5, 1, 2026), makeData(9, 1, 2026)));   /* 4 giorni (estero) */
    pushViaggio(&viaggi, newViaggio(1003, "Madrid", "Spagna",
                                    makeData(1, 12, 2025), makeData(20, 12, 2025)));/* 19 giorni (estero) */

    printf("PRIMA di aggiornaFerie()\n");
    stampaImpiegati(imp);
    stampaViaggi(viaggi);

    /* Chiamata funzione richiesta */
    aggiornaFerie(viaggi, imp);

    printf("DOPO aggiornaFerie() (quando la implementi, qui vedrai le ferie cambiare)\n");
    stampaImpiegati(imp);

    freeImpiegati(imp);
    freeViaggi(viaggi);
    return 0;
}

int calcolagiorni(Data inizio, Data fine) // suumo che tutti i mesi abbiano 30 giorni
    {
        int somma=0;
        somma=somma+(-inizio.anno+fine.anno)*365;
        somma=somma+(-inizio.mese+fine.mese)*30;
        somma=somma+(-inizio.giorno+fine.giorno);
        return somma;
    }
void aggiornaFerie(ListaDiViaggi viaggi, ListaDiImpiegati impiegati)
    {
        if(viaggi==NULL || impiegati==NULL)
            return;
    ListaDiImpiegati scorri=impiegati;
    while (scorri!=NULL) {
        int num_viaggi=ver(viaggi, scorri->matricola);
        scorri->giorniDiFerieMaturati=(scorri->giorniDiFerieMaturati)+num_viaggi;
        scorri=scorri->next;
        }
    }
int ver(ListaDiViaggi viaggi, int matricola)
    {
    ListaDiViaggi scorri=viaggi;
    int count=0;
    while (scorri!=NULL) {
        if(matricola==scorri->matricola)
            {
                if(calcolagiorni(scorri->dataInizio, scorri->dataFine)>=7 && strcmp(scorri->d.stato,"Italia")!=0)
                    count++;
            }
        scorri=scorri->next;
        }
    return count;
    }
