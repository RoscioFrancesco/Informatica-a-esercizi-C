//
//  main.c
//  tde  6 liste -14
//
//  Created by Francesco Roscio Ricon on 05/02/26.
//
//I dati di un’università sono organizzati nel seguente modo: gli studenti, i corsi e gli esami sono disposti in liste. Le strutture dati utilizzate sono le seguenti:
//#define N 1000

//typedef struct { int giorno, mese, anno; } Data;
//typedef struct S { char matricola[7], nome[N], cognome[N];
//                          Data dataNascita;
//                          S * next; } Studente;
//typedef Studente * ListaStudenti;

//typedef struct C { char codice[11], titolo[N];
//                          int numCrediti;
//                          C * next; } Corso;
//typedef Corso * ListaCorsi;


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

/* =========================
   STRUTTURE DATI (come da testo)
   Nota: ho corretto solo la sintassi dei puntatori "struct S *next" ecc.
   ========================= */
typedef struct { int giorno, mese, anno; } Data;

typedef struct S {
    char matricola[7], nome[N], cognome[N];
    Data dataNascita;
    struct S *next;
} Studente;
typedef Studente* ListaStudenti;

typedef struct C {
    char codice[11], titolo[N];
    int numCrediti;
    struct C *next;
} Corso;
typedef Corso* ListaCorsi;

typedef struct E {
    char codiceCorso[11], matricolaStudente[N]; /* nel testo è N: lo lascio così */
    int voto;
    Data data;
    struct E *next;
} Esame;
typedef Esame* ListaEsami;

//Si codifichi in C la funzione:
//ListaEsami eliminaStudentiFalsi(ListaEsami es, ListaStudenti stu)
//che elimina da es i dati di studenti non presenti nella lista stu.



/* =========================
   UTILITY per creare/gestire liste (solo per test)
   ========================= */
static Studente* newStudente(const char *mat, const char *nome, const char *cognome, Data dn) {
    Studente *s = (Studente*)malloc(sizeof(Studente));
    if (!s) { perror("malloc"); exit(1); }
    strncpy(s->matricola, mat, sizeof(s->matricola));
    s->matricola[sizeof(s->matricola)-1] = '\0';
    strncpy(s->nome, nome, N); s->nome[N-1] = '\0';
    strncpy(s->cognome, cognome, N); s->cognome[N-1] = '\0';
    s->dataNascita = dn;
    s->next = NULL;
    return s;
}

static Corso* newCorso(const char *cod, const char *titolo, int cfu) {
    Corso *c = (Corso*)malloc(sizeof(Corso));
    if (!c) { perror("malloc"); exit(1); }
    strncpy(c->codice, cod, sizeof(c->codice));
    c->codice[sizeof(c->codice)-1] = '\0';
    strncpy(c->titolo, titolo, N); c->titolo[N-1] = '\0';
    c->numCrediti = cfu;
    c->next = NULL;
    return c;
}

static Esame* newEsame(const char *codCorso, const char *matStud, int voto, Data d) {
    Esame *e = (Esame*)malloc(sizeof(Esame));
    if (!e) { perror("malloc"); exit(1); }
    strncpy(e->codiceCorso, codCorso, sizeof(e->codiceCorso));
    e->codiceCorso[sizeof(e->codiceCorso)-1] = '\0';
    strncpy(e->matricolaStudente, matStud, N);
    e->matricolaStudente[N-1] = '\0';
    e->voto = voto;
    e->data = d;
    e->next = NULL;
    return e;
}

static void pushBackStudenti(ListaStudenti *head, Studente *node) {
    if (!*head) { *head = node; return; }
    Studente *p = *head;
    while (p->next) p = p->next;
    p->next = node;
}

static void pushBackCorsi(ListaCorsi *head, Corso *node) {
    if (!*head) { *head = node; return; }
    Corso *p = *head;
    while (p->next) p = p->next;
    p->next = node;
}

static void pushBackEsami(ListaEsami *head, Esame *node) {
    if (!*head) { *head = node; return; }
    Esame *p = *head;
    while (p->next) p = p->next;
    p->next = node;
}

static void stampaStudenti(const char *titolo, ListaStudenti l) {
    printf("\n=== %s ===\n", titolo);
    if (!l) { printf("(vuota)\n"); return; }
    for (; l; l = l->next) {
        printf("Matricola=%s | %s %s | Nascita=%02d/%02d/%04d\n",
               l->matricola, l->nome, l->cognome,
               l->dataNascita.giorno, l->dataNascita.mese, l->dataNascita.anno);
    }
}

static void stampaCorsi(const char *titolo, ListaCorsi l) {
    printf("\n=== %s ===\n", titolo);
    if (!l) { printf("(vuota)\n"); return; }
    for (; l; l = l->next) {
        printf("Cod=%s | Titolo=%s | CFU=%d\n", l->codice, l->titolo, l->numCrediti);
    }
}

static void stampaEsami(const char *titolo, ListaEsami l) {
    printf("\n=== %s ===\n", titolo);
    if (!l) { printf("(vuota)\n"); return; }
    for (; l; l = l->next) {
        printf("Stud=%s | Corso=%s | Voto=%d | Data=%02d/%02d/%04d\n",
               l->matricolaStudente, l->codiceCorso, l->voto,
               l->data.giorno, l->data.mese, l->data.anno);
    }
}

static void freeStudenti(ListaStudenti l) {
    while (l) {
        Studente *t = l->next;
        free(l);
        l = t;
    }
}
static void freeCorsi(ListaCorsi l) {
    while (l) {
        Corso *t = l->next;
        free(l);
        l = t;
    }
}
static void freeEsami(ListaEsami l) {
    while (l) {
        Esame *t = l->next;
        free(l);
        l = t;
    }
}

/* =========================
   MAIN DI TEST (runnabile)
   ========================= */
ListaStudenti f(ListaCorsi corsi, ListaEsami esami, ListaStudenti studenti);
void datimedia(char numero_matricola[], ListaEsami esami, int *somma, int *sommacrediti, ListaCorsi corsi);
int main(void) {
    ListaStudenti stu = NULL;
    ListaCorsi cor = NULL;
    ListaEsami es = NULL;

    /* --- costruzione dati di esempio --- */
    pushBackStudenti(&stu, newStudente("123456", "Mario", "Rossi", (Data){1, 1, 2000}));
    pushBackStudenti(&stu, newStudente("234567", "Luisa", "Bianchi", (Data){2, 2, 2001}));
    pushBackStudenti(&stu, newStudente("345678", "Anna",  "Verdi", (Data){3, 3, 2002}));

    pushBackCorsi(&cor, newCorso("INF001", "Informatica A", 12));
    pushBackCorsi(&cor, newCorso("MAT001", "Analisi 1",      9));
    pushBackCorsi(&cor, newCorso("FIS001", "Fisica 1",       6));

    pushBackEsami(&es, newEsame("INF001", "123456", 28, (Data){10, 6, 2020}));
    pushBackEsami(&es, newEsame("MAT001", "123456", 30, (Data){12, 7, 2020}));
    pushBackEsami(&es, newEsame("FIS001", "123456", 27, (Data){1,  9, 2020}));

    pushBackEsami(&es, newEsame("INF001", "234567", 26, (Data){10, 6, 2020}));
    pushBackEsami(&es, newEsame("MAT001", "234567", 28, (Data){12, 7, 2020}));

    pushBackEsami(&es, newEsame("INF001", "345678", 30, (Data){10, 6, 2020}));
    pushBackEsami(&es, newEsame("FIS001", "345678", 30, (Data){1,  9, 2020}));

    /* --- stampe liste input --- */
    stampaStudenti("LISTA STUDENTI (input)", stu);
    stampaCorsi("LISTA CORSI (input)", cor);
    stampaEsami("LISTA ESAMI (input)", es);

    
    printf("\nChiamo f(es, cor, stu) per ottenere studenti con media > 27...\n");
    ListaStudenti risultato = f(cor, es, stu);   

    /* --- stampa risultato --- */
    stampaStudenti("RISULTATO f(...) (NUOVA LISTA)", risultato);

    /* --- dimostrazione che gli input non devono essere intaccati: ristampo --- */
    stampaStudenti("LISTA STUDENTI (dopo chiamata, deve essere invariata)", stu);
    stampaEsami("LISTA ESAMI (dopo chiamata, deve essere invariata)", es);

    /* --- free: attenzione! risultato è una NUOVA lista (da liberare separatamente) --- */
    freeStudenti(risultato);
    freeEsami(es);
    freeCorsi(cor);
    freeStudenti(stu);

    return 0;
}

int trovacrediti(ListaCorsi head, char codicecorso[])
    {
        if(head==NULL)
            return 0;
        if(strcmp(head->codice, codicecorso)==0)
            return 1;
        return trovacrediti(head->next, codicecorso);
    }
void datimedia(char numero_matricola[], ListaEsami esami, int *somma, int *sommacrediti, ListaCorsi corsi)
    {
        if(esami==NULL)
            return;
    if(strcmp(esami->matricolaStudente,numero_matricola)==0)
            {
                *somma=*somma+esami->voto;
                *sommacrediti=*sommacrediti+trovacrediti(corsi, esami->codiceCorso);
            }
    datimedia(numero_matricola, esami->next, somma, sommacrediti, corsi);
    }
int ver(char numero_matricola[], ListaEsami esami, ListaCorsi corsi)
    {
    int somma=0;
    int sommacrediti=0;
    datimedia(numero_matricola, esami, &somma, &sommacrediti, corsi);
    if(somma/sommacrediti>27)
        return 1;
    return 0;
    }

ListaStudenti inserisciincoda(ListaStudenti head, Studente x)
    {
        if(head==NULL)
            {
                ListaStudenti new=(ListaStudenti)malloc(sizeof(*new));
                *new=x;
                new->next=NULL;
                return new;
            }
        head->next=inserisciincoda(head->next, x);
        return head;
    }
ListaStudenti trovastudente(ListaStudenti head, char matricola[])
    {
        if(head==NULL)
            return NULL;
        if(strcmp(head->matricola, matricola)==0)
            return head;
    return trovastudente(head->next, matricola);
    }
ListaStudenti f(ListaCorsi corsi, ListaEsami esami, ListaStudenti studenti)
    {
        if(studenti==NULL)
            return NULL;
    ListaStudenti scorri=studenti;
    ListaStudenti new=NULL;
    while(scorri!=NULL)
        {
            if(ver(scorri->matricola, esami, corsi))
                {
                    ListaStudenti studente=trovastudente(studenti, scorri->matricola);
                    new=inserisciincoda(new, *studente);
                }
            scorri=scorri->next;
        }
    return new;
    }
int verifica_mancanza(char matricola[], ListaStudenti studenti) // 1 se va eliminato, 0 altrimenti (non presenti 1)
    {
        if(studenti==NULL)
            return 1;
        ListaStudenti scorri=studenti;
        while (scorri!=NULL) {
            if(strcmp(scorri->matricola, matricola)==0)
                return 0;
            scorri=scorri->next;
        }
        return 1;
    }
ListaEsami eliminaStudentiFalsi(ListaEsami es, ListaStudenti stu)
    {
        if(es==NULL)
            return NULL;
        if(verifica_mancanza(es->matricolaStudente, stu))
            {
                ListaEsami temp=es->next;
                free(es);
                return eliminaStudentiFalsi(temp, stu);
            }
    es->next=eliminaStudentiFalsi(es->next, stu);
    return es;
    }
