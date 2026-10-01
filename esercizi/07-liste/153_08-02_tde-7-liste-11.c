//  Created by Francesco Roscio Ricon on 08/02/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct Driver {
    char *codice, *nome, *patente;
    int annoDiNascita;
    int anniDiEsperienza;
    struct Driver *next;
} Autista;

typedef Autista *Autisti;

typedef struct Bus {
    char *targa;
    int NumeroPosti;
    struct Bus *next;
} Autobus;

typedef Autobus *Veicoli;

typedef struct Ride {
    char *targaBus, *codiceAutista;
    char tipoCorsa;           /* 'U', 'S', 'E' */
    struct Ride *next;
} Corsa;

typedef Corsa *Corse;

/* =========================
   PROTOTIPO FUNZIONE ESERCIZIO (DA FARE)
   ========================= */
int AutistiEsperti(Corse C, Autisti A);

static char *dupstr(const char *s) {
    size_t n = strlen(s);
    char *p = (char *)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

/* =========================
   CREAZIONE NODI
   ========================= */
static Autisti nuovoAutista(const char *cod, const char *nome, const char *pat, int annoN, int exp) {
    Autisti a = (Autisti)malloc(sizeof(*a));
    if (!a) { perror("malloc"); exit(1); }
    a->codice = dupstr(cod);
    a->nome = dupstr(nome);
    a->patente = dupstr(pat);
    a->annoDiNascita = annoN;
    a->anniDiEsperienza = exp;
    a->next = NULL;
    return a;
}

static Veicoli nuovoBus(const char *targa, int posti) {
    Veicoli b = (Veicoli)malloc(sizeof(*b));
    if (!b) { perror("malloc"); exit(1); }
    b->targa = dupstr(targa);
    b->NumeroPosti = posti;
    b->next = NULL;
    return b;
}

static Corse nuovaCorsa(const char *targaBus, const char *codAutista, char tipo) {
    Corse c = (Corse)malloc(sizeof(*c));
    if (!c) { perror("malloc"); exit(1); }
    c->targaBus = dupstr(targaBus);
    c->codiceAutista = dupstr(codAutista);
    c->tipoCorsa = tipo;
    c->next = NULL;
    return c;
}

/* inserimento in testa (comodo per test) */
static Autisti pushAutista(Autisti head, Autisti x) { x->next = head; return x; }
static Veicoli pushBus(Veicoli head, Veicoli x) { x->next = head; return x; }
static Corse pushCorsa(Corse head, Corse x) { x->next = head; return x; }

/* =========================
   STAMPA
   ========================= */
static void stampaAutisti(Autisti a) {
    printf("=== AUTISTI ===\n");
    while (a) {
        printf("- [%s] %s | patente=%s | nascita=%d | exp=%d\n",
               a->codice, a->nome, a->patente, a->annoDiNascita, a->anniDiEsperienza);
        a = a->next;
    }
    printf("\n");
}

static void stampaBus(Veicoli v) {
    printf("=== AUTOBUS ===\n");
    while (v) {
        printf("- targa=%s | posti=%d\n", v->targa, v->NumeroPosti);
        v = v->next;
    }
    printf("\n");
}

static const char *tipoToStr(char t) {
    if (t == 'U') return "Urbano";
    if (t == 'S') return "Servizio scuole";
    if (t == 'E') return "Extraurbano";
    return "???";
}

static void stampaCorse(Corse c) {
    printf("=== CORSE ===\n");
    while (c) {
        printf("- bus=%s | autista=%s | tipo=%c (%s)\n",
               c->targaBus, c->codiceAutista, c->tipoCorsa, tipoToStr(c->tipoCorsa));
        c = c->next;
    }
    printf("\n");
}

/* =========================
   FREE
   ========================= */
static void freeAutisti(Autisti a) {
    while (a) {
        Autisti nx = a->next;
        free(a->codice);
        free(a->nome);
        free(a->patente);
        free(a);
        a = nx;
    }
}

static void freeBus(Veicoli b) {
    while (b) {
        Veicoli nx = b->next;
        free(b->targa);
        free(b);
        b = nx;
    }
}

static void freeCorse(Corse c) {
    while (c) {
        Corse nx = c->next;
        free(c->targaBus);
        free(c->codiceAutista);
        free(c);
        c = nx;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    Autisti A = NULL;
    Veicoli V = NULL;
    Corse C = NULL;

    /* Autisti */
    A = pushAutista(A, nuovoAutista("A01", "Mario Rossi",  "D", 1980, 12));
    A = pushAutista(A, nuovoAutista("A02", "Luca Bianchi", "D", 1990,  9));  /* <10 */
    A = pushAutista(A, nuovoAutista("A03", "Anna Verdi",   "D", 1975, 20));

    /* Autobus (non serve alla funzione, ma completezza scenario) */
    V = pushBus(V, nuovoBus("AB123CD", 50));
    V = pushBus(V, nuovoBus("ZZ999YY", 30));

    /* Corse: metto almeno una 'S' guidata da A02 (exp=9) per testare caso 0 */
    C = pushCorsa(C, nuovaCorsa("AB123CD", "A01", 'U'));
    C = pushCorsa(C, nuovaCorsa("ZZ999YY", "A02", 'S'));  /* scuola con autista NON esperto */
    C = pushCorsa(C, nuovaCorsa("AB123CD", "A03", 'E'));
    C = pushCorsa(C, nuovaCorsa("AB123CD", "A01", 'S'));  /* scuola con autista esperto */

    /* Stampa dati */
    stampaAutisti(A);
    stampaBus(V);
    stampaCorse(C);

    /* Test funzione */
    {
        int ok = AutistiEsperti(C, A);
        printf("AutistiEsperti(...) = %d\n", ok);
        printf("(atteso: 0 con questi dati, perche' A02 fa corse 'S' ma ha exp=9)\n");
    }

    /* Cleanup */
    freeCorse(C);
    freeBus(V);
    freeAutisti(A);

    return 0;
}
int autistacon10anni(Autisti listaautisti, char codice[])
    {
        if(listaautisti==NULL)
            return 0;
    Autisti scorri=listaautisti;
    while(scorri!=NULL)
        {
            if(strcmp(scorri->codice, codice)==0)
                {
                    if(scorri->anniDiEsperienza>=10)
                        return 1;
                    return 0;
                }
            scorri=scorri->next;
        }
        return 0;
    }
int AutistiEsperti(Corse C, Autisti A)
    {
        if(A==NULL || C==NULL)
            return 0;
    while (C!=NULL) {
        if (C->tipoCorsa=='S') {
            int val=autistacon10anni(A, C->codiceAutista);
            if(val==0)
                return 0;
        }
        C=C->next;
        }
    return 1;
    }
//Si codifichi in C la seguente funzione:
//che elimina tutte le corse che utilizzano l’autobus con la targa passata come parametro.


int eliminaCorsa(Corse *C, char targa[])
    {
        if(C==NULL || *C==NULL)
            return 0;
        if(strcmp((*C)->targaBus, targa)==0)
            {
                Corse daeliminare=(*C);
                (*C)=(*C)->next;
                free((daeliminare)->codiceAutista);
                free((daeliminare)->targaBus);
                free((daeliminare));
                return 1+eliminaCorsa(C, targa);
            }
    return eliminaCorsa(&((*C)->next), targa);
    }
