//
//  main.c
//  tde 3 liste -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =====================
   STRUTTURE DATI (da testo)
   ===================== */
typedef struct Date {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct Item {
    int matricola;
    char cognome[100];
    char nome[100];
    char corsoDiStudi[100];
    char borsaDiStudio[100];
    struct Item *next;
} Studente;

typedef Studente *ListaDiStudenti;

typedef struct Node {
    int matricola;
    char *corso;
    int voto;
    Data data;
    struct Node *next;
} Esame;

typedef Esame *ListaDiEsami;


void assegnaBorsaDiStudio(ListaDiStudenti studenti, ListaDiEsami esami);

/* =====================
   UTILITY DI SUPPORTO
   ===================== */
static Studente *nuovoStudente(int matr, const char *cognome, const char *nome, const char *cds) {
    Studente *s = (Studente *)malloc(sizeof(Studente));
    if (!s) { perror("malloc"); exit(1); }
    s->matricola = matr;
    strncpy(s->cognome, cognome, sizeof(s->cognome) - 1); s->cognome[99] = '\0';
    strncpy(s->nome, nome, sizeof(s->nome) - 1); s->nome[99] = '\0';
    strncpy(s->corsoDiStudi, cds, sizeof(s->corsoDiStudi) - 1); s->corsoDiStudi[99] = '\0';
    strcpy(s->borsaDiStudio, "NO"); /* default */
    s->next = NULL;
    return s;
}

static ListaDiStudenti inserisciStudenteInCoda(ListaDiStudenti head, Studente *s) {
    if (head == NULL) return s;
    Studente *cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = s;
    return head;
}

static Esame *nuovoEsame(int matr, const char *corso, int voto, int g, int m, int a) {
    Esame *e = (Esame *)malloc(sizeof(Esame));
    if (!e) { perror("malloc"); exit(1); }
    e->matricola = matr;
    e->corso = (char *)malloc(strlen(corso) + 1);
    if (!e->corso) { perror("malloc"); exit(1); }
    strcpy(e->corso, corso);
    e->voto = voto;
    e->data.giorno = g;
    e->data.mese = m;
    e->data.anno = a;
    e->next = NULL;
    return e;
}

/* Inserimento in coda: qui assumiamo che tu costruisca già la lista ordinata per data */
static ListaDiEsami inserisciEsameInCoda(ListaDiEsami head, Esame *e) {
    if (head == NULL) return e;
    Esame *cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = e;
    return head;
}

static void stampaStudenti(ListaDiStudenti s) {
    printf("=== STUDENTI ===\n");
    while (s != NULL) {
        printf("Matricola: %d | %s %s | CdS: %s | Borsa: %s\n",
               s->matricola, s->nome, s->cognome, s->corsoDiStudi, s->borsaDiStudio);
        s = s->next;
    }
}

static void stampaEsami(ListaDiEsami e) {
    printf("=== ESAMI (ordinati per data) ===\n");
    while (e != NULL) {
        printf("Matricola: %d | Corso: %s | Voto: %d | Data: %02d/%02d/%04d\n",
               e->matricola, e->corso, e->voto, e->data.giorno, e->data.mese, e->data.anno);
        e = e->next;
    }
}

static void liberaStudenti(ListaDiStudenti s) {
    while (s != NULL) {
        Studente *tmp = s;
        s = s->next;
        free(tmp);
    }
}

static void liberaEsami(ListaDiEsami e) {
    while (e != NULL) {
        Esame *tmp = e;
        e = e->next;
        free(tmp->corso);
        free(tmp);
    }
}

/* =====================
   MAIN DI TEST
   ===================== */
int main() {
    ListaDiStudenti studenti = NULL;
    ListaDiEsami esami = NULL;

    /* Creo studenti */
    studenti = inserisciStudenteInCoda(studenti, nuovoStudente(1001, "Rossi",  "Mario", "Informatica"));
    studenti = inserisciStudenteInCoda(studenti, nuovoStudente(1002, "Bianchi","Luca",  "Informatica"));
    studenti = inserisciStudenteInCoda(studenti, nuovoStudente(1003, "Verdi",  "Anna",  "Matematica"));

    /* Creo esami (già in ordine di data) */
    esami = inserisciEsameInCoda(esami, nuovoEsame(1001, "Programmazione", 30, 10, 2, 2024));
    esami = inserisciEsameInCoda(esami, nuovoEsame(1002, "Programmazione", 18, 11, 2, 2024));
    esami = inserisciEsameInCoda(esami, nuovoEsame(1001, "Basi di Dati",    27,  5, 3, 2024));
    esami = inserisciEsameInCoda(esami, nuovoEsame(1003, "Analisi 1",       28, 20, 3, 2024));
    esami = inserisciEsameInCoda(esami, nuovoEsame(1002, "Architettura",    30,  1, 4, 2024));
    esami = inserisciEsameInCoda(esami, nuovoEsame(1003, "Geometria",       26, 10, 4, 2024));

    printf("\nPRIMA:\n");
    stampaStudenti(studenti);
    printf("\n");
    stampaEsami(esami);

    /* Funzione da svolgere */
    assegnaBorsaDiStudio(studenti, esami);

    printf("\nDOPO assegnaBorsaDiStudio:\n");
    stampaStudenti(studenti);

    liberaEsami(esami);
    liberaStudenti(studenti);
    return 0;
}

float calcolamedia(ListaDiEsami esami, int matricola_stud)
    {
        if(esami==NULL)
            return 0;
    ListaDiEsami scorri=esami;
    float somma=0;
    float count=0;
    while (scorri!=NULL) {
        if(matricola_stud==scorri->matricola)
            {
                somma=somma+scorri->voto;
                count++;
            }
        scorri=scorri->next;
    }
    if(count==0)
        return 0;
    return somma/count;
    }

void assegnaBorsaDiStudio(ListaDiStudenti studenti, ListaDiEsami esami)
    {
        if(studenti==NULL || esami==NULL)
            return;
    ListaDiStudenti scorri=studenti;
    while (scorri!=NULL) {
        float media=calcolamedia(esami, scorri->matricola);
        if(media>=27)
            {
                strcpy(scorri->borsaDiStudio, "SI");
            }
        scorri=scorri->next;
        }
    }
