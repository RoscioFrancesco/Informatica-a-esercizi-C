//  Created by Francesco Roscio Ricon on 09/02/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct Date {
    int giorno, mese, anno;
} Data;

typedef struct Item {
    int matricola;
    char *cognome, *nome, *ruolo;
    int bonus;
    struct Item *next;
} Cartellino;

typedef Cartellino *ListaDiCartellini;

typedef struct Node {
    int matricola;
    Data data;
    struct Node *next;
} Assenza;

typedef Assenza *ListaDiAssenze;

/* =========================
   FUNZIONI DATE (fornite)
   ========================= */

int distanza(Data d1, Data d2);


void aggiornaBonus(ListaDiCartellini cartellini, ListaDiAssenze assenze, Data oggi);

/* =========================
   UTILITY STRINGHE
   ========================= */
static char *dupstr(const char *s) {
    char *p = (char *)malloc(strlen(s) + 1);
    if (!p) { perror("malloc"); exit(1); }
    strcpy(p, s);
    return p;
}

/* =========================
   UTILITY: CREA / INSERISCI CARTELLINI
   ========================= */
static ListaDiCartellini nuovoCartellino(int matricola, const char *cognome,
                                         const char *nome, const char *ruolo,
                                         int bonus) {
    ListaDiCartellini c = (ListaDiCartellini)malloc(sizeof(Cartellino));
    if (!c) { perror("malloc"); exit(1); }
    c->matricola = matricola;
    c->cognome = dupstr(cognome);
    c->nome = dupstr(nome);
    c->ruolo = dupstr(ruolo);
    c->bonus = bonus;
    c->next = NULL;
    return c;
}

static ListaDiCartellini inserisciCartellinoInCoda(ListaDiCartellini head, ListaDiCartellini x) {
    if (head == NULL) return x;
    ListaDiCartellini cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = x;
    return head;
}

/* =========================
   UTILITY: CREA / INSERISCI ASSENZE (lista ordinata per data)
   (qui le inseriamo già in ordine nel main, senza ordinamento automatico)
   ========================= */
static ListaDiAssenze nuovaAssenza(int matricola, Data d) {
    ListaDiAssenze a = (ListaDiAssenze)malloc(sizeof(Assenza));
    if (!a) { perror("malloc"); exit(1); }
    a->matricola = matricola;
    a->data = d;
    a->next = NULL;
    return a;
}

static ListaDiAssenze inserisciAssenzaInCoda(ListaDiAssenze head, ListaDiAssenze x) {
    if (head == NULL) return x;
    ListaDiAssenze cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = x;
    return head;
}

/* =========================
   STAMPE DI DEBUG
   ========================= */
static void stampaData(Data d) {
    printf("%02d/%02d/%04d", d.giorno, d.mese, d.anno);
}

static void stampaCartellini(ListaDiCartellini C) {
    printf("=== CARTELLINI ===\n");
    while (C != NULL) {
        printf("Matricola %d | %s %s | Ruolo: %s | Bonus: %d\n",
               C->matricola, C->nome, C->cognome, C->ruolo, C->bonus);
        C = C->next;
    }
}

static void stampaAssenze(ListaDiAssenze A) {
    printf("=== ASSENZE (ordinate per data) ===\n");
    while (A != NULL) {
        printf("Matricola %d | Data: ", A->matricola);
        stampaData(A->data);
        printf("\n");
        A = A->next;
    }
}

/* =========================
   FREE
   ========================= */
static void freeCartellini(ListaDiCartellini C) {
    while (C != NULL) {
        ListaDiCartellini nxt = C->next;
        free(C->cognome);
        free(C->nome);
        free(C->ruolo);
        free(C);
        C = nxt;
    }
}

static void freeAssenze(ListaDiAssenze A) {
    while (A != NULL) {
        ListaDiAssenze nxt = A->next;
        free(A);
        A = nxt;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    ListaDiCartellini cartellini = NULL;
    ListaDiAssenze assenze = NULL;

    /* OGGI (usata per “ultimi 30 giorni”) */
    Data oggi = {9, 2, 2026};

    /* Cartellini */
    cartellini = inserisciCartellinoInCoda(cartellini, nuovoCartellino(1001, "Rossi", "Mario", "Impiegato", 500));
    cartellini = inserisciCartellinoInCoda(cartellini, nuovoCartellino(1002, "Bianchi", "Luca", "Dirigente", 1200));
    cartellini = inserisciCartellinoInCoda(cartellini, nuovoCartellino(1003, "Verdi", "Anna", "Tecnico", 200));

    /* Assenze (lista ordinata per data: dal più vecchio al più recente) */
    assenze = inserisciAssenzaInCoda(assenze, nuovaAssenza(1002, (Data){1, 1, 2026}));
    assenze = inserisciAssenzaInCoda(assenze, nuovaAssenza(1002, (Data){15, 1, 2026}));
    assenze = inserisciAssenzaInCoda(assenze, nuovaAssenza(1002, (Data){20, 1, 2026}));
    assenze = inserisciAssenzaInCoda(assenze, nuovaAssenza(1003, (Data){25, 1, 2026}));
    assenze = inserisciAssenzaInCoda(assenze, nuovaAssenza(1003, (Data){5, 2, 2026}));

    printf("Oggi = ");
    stampaData(oggi);
    printf("\n\n");

    printf(">>> STATO INIZIALE\n");
    stampaCartellini(cartellini);
    printf("\n");
    stampaAssenze(assenze);
    printf("\n");

    printf(">>> CHIAMATA FUNZIONE DA IMPLEMENTARE\n");
    printf("ATTENZIONE: aggiornaBonus(...) NON e' implementata in questo file.\n");
    printf("Implementala tu (usando distanza(d1,d2)) e poi scommenta la chiamata qui sotto.\n\n");

    aggiornaBonus(cartellini, assenze, oggi);

    printf(">>> STATO DOPO aggiornaBonus\n");
    stampaCartellini(cartellini);


    freeAssenze(assenze);
    freeCartellini(cartellini);
    return 0;
}



/* giorni per mese (non bisestile) */
static int giorniMese(int mese) {
    int g[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    return g[mese - 1];
}

/* converte una data in "giorni assoluti" */
static int dataInGiorni(Data d) {
    int tot = 0;

    /* anni */
    for (int a = 0; a < d.anno; a++)
        tot += 365;

    /* mesi */
    for (int m = 1; m < d.mese; m++)
        tot += giorniMese(m);

    /* giorni */
    tot += d.giorno;

    return tot;
}

int distanza(Data d1, Data d2) {
    int g1 = dataInGiorni(d1);
    int g2 = dataInGiorni(d2);

    if (g1 > g2)
        return g1 - g2;
    else
        return g2 - g1;
}

int assenza_ultimigiorni(ListaDiAssenze lista, int matricola)
    {
    Data oggi;
    oggi.anno=2026;
    oggi.mese=2;
    oggi.giorno=9;
        if(lista==NULL)
            return 0;
    int count=0;
    while (lista!=NULL) {
        if(lista->matricola==matricola)
            {
                if(abs(distanza(oggi, lista->data)<30))
                    count++;
            }
        lista=lista->next;
    }
    return count;
    }
void aggiornaBonus(ListaDiCartellini cartellini, ListaDiAssenze assenze, Data oggi)
    {
        if(cartellini==NULL || assenze==NULL)
            return;
    while (cartellini!=NULL) {
        int val=assenza_ultimigiorni(assenze, cartellini->matricola);
        if(val>2)
            {
                cartellini->bonus=cartellini->bonus-1000;
            }
        if(val==0)
            {
                cartellini->bonus=cartellini->bonus+1000;
            }
        cartellini=cartellini->next;
    }
    }
