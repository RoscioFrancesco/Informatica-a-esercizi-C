//  Created by Francesco Roscio Ricon on 05/02/26.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
   STRUTTURE DATI (come da testo, con fix del puntatore next)
   ========================================================= */
typedef struct Date {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct Cli {
    int  CodiceCliente;
    char cognome[100], nome[100];
    int  puntiAccumulati;
} Cliente;

typedef struct CliN {
    Cliente C;
    struct CliN *next;
} ClienteNodo;

typedef ClienteNodo *ListaDiClienti;

typedef struct ES {
    char nomeProdotto[100];
    int  prezzoUnitario;
    int  quantitaAcquistata;
    struct ES *next;
} ElementoScontrino;

typedef ElementoScontrino *Scontrino;

typedef struct Sp {
    int CodiceCliente;
    Scontrino s;
    Data data;
    struct Sp *next;   /* NEL TESTO c'era "struct Vi *next": qui è corretto */
} Spesa;

typedef Spesa *ListaDiSpese;

/* =========================================================
   PROTOTIPO ESERCIZIO (NON RISOLTO)
   ========================================================= */
Cliente clienteMigliore(ListaDiSpese spese, ListaDiClienti clienti);

/* =========================================================
   UTILITY per costruire e stampare (solo per test)
   ========================================================= */
static ClienteNodo *newCliente(int cod, const char *cognome, const char *nome, int punti, ClienteNodo *next) {
    ClienteNodo *n = (ClienteNodo*)malloc(sizeof(ClienteNodo));
    if (!n) { perror("malloc"); exit(1); }
    n->C.CodiceCliente = cod;
    strncpy(n->C.cognome, cognome, sizeof(n->C.cognome)-1);
    n->C.cognome[sizeof(n->C.cognome)-1] = '\0';
    strncpy(n->C.nome, nome, sizeof(n->C.nome)-1);
    n->C.nome[sizeof(n->C.nome)-1] = '\0';
    n->C.puntiAccumulati = punti;
    n->next = next;
    return n;
}

static ElementoScontrino *newRiga(const char *prod, int prezzo, int qta, ElementoScontrino *next) {
    ElementoScontrino *r = (ElementoScontrino*)malloc(sizeof(ElementoScontrino));
    if (!r) { perror("malloc"); exit(1); }
    strncpy(r->nomeProdotto, prod, sizeof(r->nomeProdotto)-1);
    r->nomeProdotto[sizeof(r->nomeProdotto)-1] = '\0';
    r->prezzoUnitario = prezzo;
    r->quantitaAcquistata = qta;
    r->next = next;
    return r;
}

static Spesa *newSpesa(int codCliente, Data d, Scontrino s, Spesa *next) {
    Spesa *sp = (Spesa*)malloc(sizeof(Spesa));
    if (!sp) { perror("malloc"); exit(1); }
    sp->CodiceCliente = codCliente;
    sp->data = d;
    sp->s = s;
    sp->next = next;
    return sp;
}

static void stampaClienti(ListaDiClienti l) {
    printf("=== LISTA CLIENTI ===\n");
    while (l) {
        printf("Cod:%d  %s %s  punti:%d\n",
               l->C.CodiceCliente, l->C.cognome, l->C.nome, l->C.puntiAccumulati);
        l = l->next;
    }
}

static void stampaScontrino(Scontrino s) {
    printf("  Scontrino:\n");
    while (s) {
        printf("   - %-12s prezzo:%d qta:%d\n", s->nomeProdotto, s->prezzoUnitario, s->quantitaAcquistata);
        s = s->next;
    }
}

static void stampaSpese(ListaDiSpese l) {
    printf("=== LISTA SPESE (cronologica) ===\n");
    while (l) {
        printf("Cliente:%d  Data:%02d/%02d/%04d\n",
               l->CodiceCliente, l->data.giorno, l->data.mese, l->data.anno);
        stampaScontrino(l->s);
        l = l->next;
    }
}

static void freeScontrino(Scontrino s) {
    while (s) {
        Scontrino tmp = s->next;
        free(s);
        s = tmp;
    }
}

static void freeSpese(ListaDiSpese l) {
    while (l) {
        ListaDiSpese tmp = l->next;
        freeScontrino(l->s);
        free(l);
        l = tmp;
    }
}

static void freeClienti(ListaDiClienti l) {
    while (l) {
        ListaDiClienti tmp = l->next;
        free(l);
        l = tmp;
    }
}

/* =========================================================
   MAIN DI TEST (con printf richieste)
   ========================================================= */

ListaDiClienti eliminaClienti(ListaDiClienti head, ListaDiSpese spese);
int ver(int codicecliente, ListaDiSpese spese);
int main(void) {
    /* 1) Creo una lista di clienti (test) */
    ListaDiClienti clienti = NULL;
    clienti = newCliente(103, "Verdi",  "Luca",  10, clienti);
    clienti = newCliente(102, "Bianchi","Sara",  35, clienti);
    clienti = newCliente(101, "Rossi",  "Mario", 20, clienti);

    /* 2) Creo una lista di spese (test), ordinata cronologicamente */
    ListaDiSpese spese = NULL;

    /* spesa 1: cliente 101 */
    Data d1 = {10, 1, 2024};
    Scontrino s1 = NULL;
    s1 = newRiga("Pane",   2, 3, s1);
    s1 = newRiga("Latte",  1, 2, s1);
    spese = newSpesa(101, d1, s1, spese);

    /* spesa 2: cliente 102 */
    Data d2 = {12, 1, 2024};
    Scontrino s2 = NULL;
    s2 = newRiga("Pasta",  2, 5, s2);
    spese = newSpesa(102, d2, s2, spese);

    /* spesa 3: cliente 101 */
    Data d3 = {20, 1, 2017};
    Scontrino s3 = NULL;
    s3 = newRiga("Carne",  8, 1, s3);
    s3 = newRiga("Acqua",  1, 6, s3);
    spese = newSpesa(101, d3, s3, spese);

    /* NOTA: ho inserito in testa: per renderla "cronologica" davvero,
       in un compito useresti inserimento in coda o costruzione ordinata.
       Qui è solo scaffolding. */

    /* 3) Stampo dati iniziali */
    stampaClienti(clienti);
    printf("\n");
    stampaSpese(spese);
    printf("\n");

    /* 4) Chiamata alla funzione dell’esercizio */
    printf("=== CHIAMATA clienteMigliore ===\n");
    Cliente best = clienteMigliore(spese, clienti); 
    printf("Cliente migliore (per totale speso): Cod:%d  %s %s  punti:%d\n",
           best.CodiceCliente, best.cognome, best.nome, best.puntiAccumulati);

    clienti=eliminaClienti(clienti, spese);
    stampaClienti(clienti);
    freeSpese(spese);
    freeClienti(clienti);

    return 0;
}


//typedef struct Date { int giorno; int mese; int anno; } Data;
//
//typedef struct Cli { int CodiceCliente;
//                     char cognome[100], nome[100];
//                     int puntiAccumulati; } Cliente;
//
//typedef struct CliN { Cliente C;
//                      struct CliN * next; } ClienteNodo;
//
//typedef ClienteNodo * ListaDiClienti;
//
//typedef struct ES { char nomeProdotto[100];
//                    int prezzoUnitario;
//                    int quantitaAcquistata;
//                   struct ES * next; } ElementoScontrino;
//
//typedef ElementoScontrino * Scontrino;
//
//typedef struct Sp { int CodiceCliente;
//                    Scontrino s;
//                    Data data;
//                   struct Vi * next; } Spesa;
//
//typedef Spesa * ListaDiSpese;
//

int calcolascontrino(Scontrino head)
    {
        if(head==NULL)
            return 0;
        Scontrino scorri=head;
        int somma=0;
        while (scorri!=NULL) {
            somma=somma+(scorri->prezzoUnitario*scorri->quantitaAcquistata);
            scorri=scorri->next;
        }
    return somma;
    }
int calcolaspesatotCliente(ListaDiSpese head, int codcliente)
    {
        if(head==NULL)
            return 0;
    ListaDiSpese scorri=head;
    int sommacliente=0;
    while (scorri!=NULL) {
        if(scorri->CodiceCliente==codcliente)
            {
                sommacliente=sommacliente+calcolascontrino(scorri->s);
            }
        scorri=scorri->next;
        }
    return sommacliente;
    }
int trovamax(ListaDiSpese spese, ListaDiClienti clienti)
    {
    int max=0;
    int codliente_max=0;
    if(spese==NULL)
        return 0;
    ListaDiClienti scorri_clienti=clienti;
    while (scorri_clienti!=NULL) {
        if (calcolaspesatotCliente(spese, scorri_clienti->C.CodiceCliente)>max) {
            codliente_max=scorri_clienti->C.CodiceCliente;
            max=calcolaspesatotCliente(spese, scorri_clienti->C.CodiceCliente);
        }
        scorri_clienti=scorri_clienti->next;
    }
    return codliente_max;
    }
Cliente clienteMigliore(ListaDiSpese spese, ListaDiClienti clienti)
    {
    int codmigliore=trovamax(spese, clienti);
    Cliente massimo;
    massimo.CodiceCliente=0;
    massimo.puntiAccumulati=0;
    ListaDiClienti scorri=clienti;
    while (scorri!=NULL) {
            if(scorri->C.CodiceCliente==codmigliore)
                {
                    massimo=(scorri->C);
                    return massimo;
                }
            scorri=scorri->next;
        }
    return massimo;
    }
int ver(int codicecliente, ListaDiSpese spese)
    {
        if(spese==NULL)
            return 0;
    ListaDiSpese scorri=spese;
    while (scorri!=NULL) {
        if(codicecliente==scorri->CodiceCliente && scorri->data.anno<=2019 && scorri->data.anno>=2015)
            return 0;
        scorri=scorri->next;
    }
    return 1;
    }
// mi ridà 1 se lo devo eliminare, 0 altrimenti

ListaDiClienti eliminaClienti(ListaDiClienti head, ListaDiSpese spese)
    {
        if(head==NULL)
            return head;
        if(ver(head->C.CodiceCliente, spese))
            {
                ListaDiClienti temp=head->next;
                head->next=NULL;
                free(head);
                return eliminaClienti(temp, spese);
            }
    head->next=eliminaClienti(head->next, spese);
    return head;
    }
