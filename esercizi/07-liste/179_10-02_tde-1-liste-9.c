//
//  main.c
//  tde 1 liste -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */

typedef struct Hotel Albergo;  /* forward declaration */

typedef struct Room {
    Albergo *albergo;
    int numero;
    char doppiaOSingola; /* 'd' doppia, 's' singola */
    struct Room *next;
} Stanza;

typedef Stanza *Stanze;

typedef struct Hotel {
    char *nome;
    char *indirizzo;
    char *citta;
    int numSingole;
    int numDoppie;
    Stanze s;              /* lista stanze dell'hotel */
    struct Hotel *next;    /* prossimo albergo */
} Albergo;

typedef Albergo *Alberghi;


void dati(int *doppie, int *singole, Stanze head);
int HotelCapienti(Alberghi A, int N);
int correggiDatiAlberghi(Alberghi A);
int capienza(Alberghi hotel);
/* =========================
   FUNZIONI DI SUPPORTO (per costruire e stampare dati)
   ========================= */

static char *dupstr(const char *src) {
    if (!src) return NULL;
    size_t len = strlen(src);
    char *p = (char *)malloc(len + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, src, len + 1);
    return p;
}

static Albergo *creaAlbergo(const char *nome, const char *indirizzo, const char *citta,
                            int numSingole, int numDoppie) {
    Albergo *h = (Albergo *)malloc(sizeof(*h));
    if (!h) { perror("malloc"); exit(1); }

    h->nome = dupstr(nome);
    h->indirizzo = dupstr(indirizzo);
    h->citta = dupstr(citta);
    h->numSingole = numSingole; /* valori iniziali (potrebbero essere sbagliati) */
    h->numDoppie  = numDoppie;  /* valori iniziali (potrebbero essere sbagliati) */
    h->s = NULL;
    h->next = NULL;
    return h;
}

static void aggiungiAlbergoInCoda(Alberghi *lista, Albergo *h) {
    if (!lista || !h) return;
    if (*lista == NULL) {
        *lista = h;
        return;
    }
    Albergo *cur = *lista;
    while (cur->next) cur = cur->next;
    cur->next = h;
}

static Stanza *creaStanza(Albergo *h, int numero, char tipo) {
    Stanza *r = (Stanza *)malloc(sizeof(*r));
    if (!r) { perror("malloc"); exit(1); }
    r->albergo = h;
    r->numero = numero;
    r->doppiaOSingola = tipo; /* 's' o 'd' */
    r->next = NULL;
    return r;
}

static void aggiungiStanzaInCoda(Albergo *h, int numero, char tipo) {
    if (!h) return;
    Stanza *r = creaStanza(h, numero, tipo);
    if (h->s == NULL) {
        h->s = r;
        return;
    }
    Stanza *cur = h->s;
    while (cur->next) cur = cur->next;
    cur->next = r;
}

static void stampaStanze(const Stanze s) {
    const Stanza *cur = s;
    while (cur) {
        printf("    - Stanza %d (%c)\n", cur->numero, cur->doppiaOSingola);
        cur = cur->next;
    }
}

static void stampaAlberghi(const Alberghi A) {
    const Albergo *cur = A;
    while (cur) {
        printf("Albergo: %s | %s | %s\n", cur->nome, cur->indirizzo, cur->citta);
        printf("  numSingole=%d  numDoppie=%d\n", cur->numSingole, cur->numDoppie);
        printf("  Stanze:\n");
        stampaStanze(cur->s);
        printf("\n");
        cur = cur->next;
    }
}

static void liberaStanze(Stanze s) {
    while (s) {
        Stanza *nx = s->next;
        free(s);
        s = nx;
    }
}

static void liberaAlberghi(Alberghi A) {
    while (A) {
        Albergo *nx = A->next;
        liberaStanze(A->s);
        free(A->nome);
        free(A->indirizzo);
        free(A->citta);
        free(A);
        A = nx;
    }
}

int main(void) {
    Alberghi catena = NULL;

    /* Creo 2 alberghi (con contatori anche volutamente "sballati") */
    Albergo *h1 = creaAlbergo("Hotel Roma Centro", "Via Alfa 10", "Roma", 99, 99);
    Albergo *h2 = creaAlbergo("Hotel Milano Nord", "Viale Beta 22", "Milano", 0, 0);

    aggiungiAlbergoInCoda(&catena, h1);
    aggiungiAlbergoInCoda(&catena, h2);

    /* Aggiungo stanze a h1 */
    aggiungiStanzaInCoda(h1, 101, 's');
    aggiungiStanzaInCoda(h1, 102, 'd');
    aggiungiStanzaInCoda(h1, 103, 'd');

    /* Aggiungo stanze a h2 */
    aggiungiStanzaInCoda(h2, 1, 's');
    aggiungiStanzaInCoda(h2, 2, 's');
    aggiungiStanzaInCoda(h2, 3, 'd');

    printf("=== STATO INIZIALE CATENA ===\n");
    stampaAlberghi(catena);

    /* Chiamate alle funzioni dell'esercizio (al momento stubs) */
    int N = 5;
    int capienti = HotelCapienti(catena, N);
    printf("HotelCapienti(A, %d) = %d (stub)\n", N, capienti);

    int corretti = correggiDatiAlberghi(catena);
    printf("correggiDatiAlberghi(A) = %d (stub)\n", corretti);

    printf("\n=== STATO FINALE CATENA (dopo stubs) ===\n");
    stampaAlberghi(catena);

    liberaAlberghi(catena);
    return 0;
}
//Si codifichi in C la seguente funzione:

int HotelCapienti(Alberghi A, int N)
    {
    int count=0;
    while (A!=NULL) {
        if(capienza(A)>N)
            count++;
        A=A->next;
    }
    return count;
    }
int capienza(Alberghi hotel)
    {
    int somma=0;
    somma=somma+hotel->numSingole;
    somma=somma+2*(hotel->numDoppie);
    return somma;
    }
int correggiDatiAlberghi(Alberghi A)
    {
        if(A==NULL)
            return 0;
    Alberghi scorriA=A;
    int count=0;
    while (scorriA!=NULL) {
        int doppie=0;
        int singole=0;
        dati(&doppie, &singole, scorriA->s);
        if(doppie!=scorriA->numDoppie || singole!=scorriA->numSingole)
            {
                count++;
                scorriA->numDoppie=doppie;
                scorriA->numSingole=singole;
            }
        scorriA=scorriA->next;
        }
    return count;
    }
void dati(int *doppie, int *singole, Stanze head)
    {
        if(head==NULL)
            return;
    while (head!=NULL) {
        if(head->doppiaOSingola=='d')
            (*doppie)++;
        else
            (*singole)++;
        head=head->next;
        }
    return;
    }
