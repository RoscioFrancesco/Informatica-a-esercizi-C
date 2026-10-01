//  Created by Francesco Roscio Ricon on 07/02/26.

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

typedef struct Item {
    int           matricola;
    char *        cognome;
    char *        nome;
    char *        corsoDiStudi;
    int           numEsamiSuperati;
    float         media;
    struct Item * next;
} Studente;

typedef Studente * ListaDiStudenti;

typedef struct Node {
    int           matricola;
    char *        corso;
    int           voto;
    Data          data;
    struct Node * next;
} Esame;

typedef Esame * ListaDiEsami;


void aggiornaStatisticheStudenti(ListaDiStudenti studenti, ListaDiEsami esami);

/* Elimina dagli studenti e dagli esami quelli che non hanno superato esami dopo il 31-12-2003 */
void eliminaStudentiSenzaEsamiDopo2003(ListaDiStudenti *studenti, ListaDiEsami *esami);

/* =========================
   UTILITY PER TEST
   ========================= */
static char* dupstr(const char *s) {
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static Data mkData(int g, int m, int a) {
    Data d; d.giorno = g; d.mese = m; d.anno = a; return d;
}

static Studente* nuovoStudente(int matr, const char *cogn, const char *nome, const char *cds) {
    Studente *s = (Studente*)malloc(sizeof(Studente));
    if (!s) { perror("malloc"); exit(1); }
    s->matricola = matr;
    s->cognome = dupstr(cogn);
    s->nome = dupstr(nome);
    s->corsoDiStudi = dupstr(cds);
    s->numEsamiSuperati = 0;   /* verrà calcolato */
    s->media = 0.0f;           /* verrà calcolata */
    s->next = NULL;
    return s;
}

static Esame* nuovoEsame(int matr, const char *corso, int voto, Data d) {
    Esame *e = (Esame*)malloc(sizeof(Esame));
    if (!e) { perror("malloc"); exit(1); }
    e->matricola = matr;
    e->corso = dupstr(corso);
    e->voto = voto;
    e->data = d;
    e->next = NULL;
    return e;
}

static ListaDiStudenti pushStudenteFront(ListaDiStudenti head, Studente *s) {
    s->next = head;
    return s;
}

/* Inserimento "semplice" in coda (per creare esempi); la lista esami del testo è ordinata per data */
static ListaDiEsami pushEsameBack(ListaDiEsami head, Esame *e) {
    if (!head) return e;
    Esame *p = head;
    while (p->next) p = p->next;
    p->next = e;
    return head;
}

static void stampaStudenti(ListaDiStudenti s) {
    printf("=== LISTA STUDENTI ===\n");
    for (; s != NULL; s = s->next) {
        printf("Matricola: %d | %s %s | CdS: %s | Superati: %d | Media: %.2f\n",
               s->matricola,
               s->cognome ? s->cognome : "(null)",
               s->nome ? s->nome : "(null)",
               s->corsoDiStudi ? s->corsoDiStudi : "(null)",
               s->numEsamiSuperati,
               s->media);
    }
    printf("\n");
}

static void stampaEsami(ListaDiEsami e) {
    printf("=== LISTA ESAMI (ordinata per data) ===\n");
    for (; e != NULL; e = e->next) {
        printf("Matricola: %d | Corso: %s | Voto: %d | Data: %02d-%02d-%04d\n",
               e->matricola,
               e->corso ? e->corso : "(null)",
               e->voto,
               e->data.giorno, e->data.mese, e->data.anno);
    }
    printf("\n");
}

static void freeStudenti(ListaDiStudenti s) {
    while (s) {
        Studente *nx = s->next;
        free(s->cognome);
        free(s->nome);
        free(s->corsoDiStudi);
        free(s);
        s = nx;
    }
}

static void freeEsami(ListaDiEsami e) {
    while (e) {
        Esame *nx = e->next;
        free(e->corso);
        free(e);
        e = nx;
    }
}

/* =========================
   MAIN (runnabile)
   ========================= */
void dati(ListaDiEsami esami, int matricola, float *count, float * somma);
ListaDiEsami eliminaesame(ListaDiEsami esami, int matricola);
ListaDiStudenti eliminastudente(ListaDiStudenti stud, int matricola);

int main(void) {

    /* Creo una lista studenti (non necessariamente ordinata) */
    ListaDiStudenti studenti = NULL;
    studenti = pushStudenteFront(studenti, nuovoStudente(1003, "Neri",   "Luca",  "Informatica"));
    studenti = pushStudenteFront(studenti, nuovoStudente(1002, "Rossi",  "Anna",  "Informatica"));
    studenti = pushStudenteFront(studenti, nuovoStudente(1001, "Bianchi","Marco", "Matematica"));

    /* Creo una lista esami (qui la inserisco già in ordine di data per semplicità) */
    ListaDiEsami esami = NULL;
    esami = pushEsameBack(esami, nuovoEsame(1001, "Analisi 1", 28, mkData(10,  7, 2002)));
    esami = pushEsameBack(esami, nuovoEsame(1002, "Prog 1",    30, mkData(15,  2, 2003)));
    esami = pushEsameBack(esami, nuovoEsame(1001, "Algebra",   25, mkData(20, 11, 2003)));
    esami = pushEsameBack(esami, nuovoEsame(1002, "Prog 2",    27, mkData(10,  1, 2004)));
    esami = pushEsameBack(esami, nuovoEsame(1003, "BasiDati",  18, mkData( 5,  6, 2005)));

    printf("STATO INIZIALE:\n");
    stampaStudenti(studenti);
    stampaEsami(esami);

    
    printf("Chiamo aggiornaStatisticheStudenti(studenti, esami)...\n");
    aggiornaStatisticheStudenti(studenti, esami);

    printf("\nDOPO aggiornaStatisticheStudenti (ATTESO: campi aggiornati se implementata):\n");
    stampaStudenti(studenti);

    
    printf("Chiamo eliminaStudentiSenzaEsamiDopo2003(&studenti, &esami)...\n");
    eliminaStudentiSenzaEsamiDopo2003(&studenti, &esami);

    printf("\nDOPO eliminaStudentiSenzaEsamiDopo2003 (ATTESO: liste filtrate se implementata):\n");
    stampaStudenti(studenti);
    stampaEsami(esami);

    /* Cleanup */
    freeStudenti(studenti);
    freeEsami(esami);

    return 0;
}

/* =========================
   STUB: NON SVOLGE L'ESERCIZIO
   ========================= */
void aggiornaStatisticheStudenti(ListaDiStudenti studenti, ListaDiEsami esami)
{
    ListaDiStudenti scorristudenti=studenti;
    while (scorristudenti!=NULL) {
        float somma=0;
        float count=0;
        dati(esami, scorristudenti->matricola, &count, &somma);
        if(count!=0)scorristudenti->media=somma/count;
        scorristudenti->numEsamiSuperati=count;
        scorristudenti=scorristudenti->next;
    }
}
void dati(ListaDiEsami esami, int matricola, float *count, float * somma)
    {
        if(esami==NULL)
            return;
    ListaDiEsami scorri=esami;
    while (scorri!=NULL) {
        if(scorri->matricola==matricola)
            {
                (*count)++;
                (*somma)=(*somma)+scorri->voto;
            }
        scorri=scorri->next;
        }
    }
int ver(int matricola, ListaDiEsami esami) // se se lo studente non ha superato esami dop il 2003
    {
        if(esami==NULL)
            return 1;
        ListaDiEsami scorri=esami;
        while (scorri!=NULL) {
            if(scorri->matricola==matricola && scorri->data.anno>=2004)
                return 0;
            scorri=scorri->next;
        }
        return 1; // se non l'ho trovato allora lo elimino
    }
ListaDiEsami eliminaesame(ListaDiEsami esami, int matricola)
    {
        if(esami==NULL)
            return esami;
        if(esami->matricola==matricola)
            {
                ListaDiEsami temp=esami->next;
                free(esami->corso);
                free(esami);
                return eliminaesame(temp, matricola);
            }
        esami->next=eliminaesame(esami->next, matricola);
        return esami;
    }
ListaDiStudenti eliminastudente(ListaDiStudenti stud, int matricola)
    {
        if(stud==NULL)
            return  stud;
        if(stud->matricola==matricola)
            {
                ListaDiStudenti temp=stud->next;
                free(stud->cognome);
                free(stud->corsoDiStudi);
                free(stud->nome);
                free(stud);
                return eliminastudente(temp, matricola);
            }
    stud->next=eliminastudente(stud->next, matricola);
    return stud;
    }
void eliminaStudentiSenzaEsamiDopo2003(ListaDiStudenti *studenti, ListaDiEsami *esami)
    {
        if(studenti==NULL)
            return;
        ListaDiStudenti scorristudenti=*studenti;
        while (scorristudenti!=NULL)
            {
                ListaDiStudenti next = scorristudenti->next;
                if(ver(scorristudenti->matricola, *esami))
                {
                    *esami=eliminaesame(*esami, scorristudenti->matricola);
                    *studenti=eliminastudente(*studenti, scorristudenti->matricola);
                }
                scorristudenti=next;
            }
    }
