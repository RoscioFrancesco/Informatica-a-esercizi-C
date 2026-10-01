//
//  main.c
//  tde 2 liste -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo, con FIX refusi)
   ========================= */

typedef struct Date {
    int giorno, mese, anno;
} Data;

typedef struct Cli {
    int CodiceCliente;
    char *cognome, *nome;
    int puntiAccumulati;
    struct Cli *next;
} Cliente;

typedef Cliente *ListaDiClienti;

typedef struct ES {
    char *nomeProdotto;
    int prezzoUnitario;
    int quantitaAcquistata;
    struct ES *next;
} ElementoScontrino;

typedef ElementoScontrino *Scontrino;

typedef struct Sp {
    int CodiceCliente;
    Scontrino s;
    Data data;
    struct Sp *next;          /* FIX: era "struct Vi * next" */
} Spesa;

typedef Spesa *ListaDiSpese;  /* FIX: era "ListaDiViaggi" */


/*
  Aggiorna i punti dei clienti dopo ogni spesa:
  - 1 punto ogni 10 euro spesi (floor)
  - se un cliente in un mese spende > 5000 euro, raddoppia i punti di TUTTE le spese di quel mese
*/
void aggiornaPunti(ListaDiClienti clienti, ListaDiSpese spese);

/* =========================
   UTILITY STRINGHE / MEMORIA
   ========================= */
static char *dupstr(const char *src) {
    if (!src) return NULL;
    size_t n = strlen(src);
    char *p = (char *)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, src, n + 1);
    return p;
}

/* =========================
   UTILITY CLIENTI
   ========================= */
static Cliente *creaCliente(int codice, const char *cognome, const char *nome, int punti) {
    Cliente *c = (Cliente *)malloc(sizeof(*c));
    if (!c) { perror("malloc"); exit(1); }
    c->CodiceCliente = codice;
    c->cognome = dupstr(cognome);
    c->nome = dupstr(nome);
    c->puntiAccumulati = punti;
    c->next = NULL;
    return c;
}

static void aggiungiClienteInCoda(ListaDiClienti *L, Cliente *c) {
    if (!L || !c) return;
    if (*L == NULL) { *L = c; return; }
    Cliente *cur = *L;
    while (cur->next) cur = cur->next;
    cur->next = c;
}

static void stampaClienti(ListaDiClienti L) {
    printf("=== CLIENTI ===\n");
    while (L) {
        printf("Cod=%d | %s %s | punti=%d\n",
               L->CodiceCliente, L->cognome, L->nome, L->puntiAccumulati);
        L = L->next;
    }
    printf("\n");
}

static void liberaClienti(ListaDiClienti L) {
    while (L) {
        Cliente *nx = L->next;
        free(L->cognome);
        free(L->nome);
        free(L);
        L = nx;
    }
}

/* =========================
   UTILITY SCONTRINO
   ========================= */
static ElementoScontrino *creaVoce(const char *nomeProdotto, int prezzoUnitario, int quantita) {
    ElementoScontrino *e = (ElementoScontrino *)malloc(sizeof(*e));
    if (!e) { perror("malloc"); exit(1); }
    e->nomeProdotto = dupstr(nomeProdotto);
    e->prezzoUnitario = prezzoUnitario;
    e->quantitaAcquistata = quantita;
    e->next = NULL;
    return e;
}

static void aggiungiVoceInCoda(Scontrino *s, ElementoScontrino *e) {
    if (!s || !e) return;
    if (*s == NULL) { *s = e; return; }
    ElementoScontrino *cur = *s;
    while (cur->next) cur = cur->next;
    cur->next = e;
}

static void stampaScontrino(Scontrino s) {
    while (s) {
        printf("    - %s: %d x %d\n", s->nomeProdotto, s->prezzoUnitario, s->quantitaAcquistata);
        s = s->next;
    }
}

static void liberaScontrino(Scontrino s) {
    while (s) {
        ElementoScontrino *nx = s->next;
        free(s->nomeProdotto);
        free(s);
        s = nx;
    }
}

/* =========================
   UTILITY SPESE
   ========================= */
static Spesa *creaSpesa(int codiceCliente, Data d, Scontrino s) {
    Spesa *sp = (Spesa *)malloc(sizeof(*sp));
    if (!sp) { perror("malloc"); exit(1); }
    sp->CodiceCliente = codiceCliente;
    sp->data = d;
    sp->s = s;
    sp->next = NULL;
    return sp;
}

static void aggiungiSpesaInCoda(ListaDiSpese *L, Spesa *sp) {
    if (!L || !sp) return;
    if (*L == NULL) { *L = sp; return; }
    Spesa *cur = *L;
    while (cur->next) cur = cur->next;
    cur->next = sp;
}

static void stampaSpese(ListaDiSpese L) {
    printf("=== SPESE ===\n");
    while (L) {
        printf("Cliente=%d | Data=%02d/%02d/%04d\n", L->CodiceCliente, L->data.giorno, L->data.mese, L->data.anno);
        printf("  Scontrino:\n");
        stampaScontrino(L->s);
        printf("\n");
        L = L->next;
    }
}

static void liberaSpese(ListaDiSpese L) {
    while (L) {
        Spesa *nx = L->next;
        liberaScontrino(L->s);
        free(L);
        L = nx;
    }
}
Data prima(int codicecliente, ListaDiSpese spese);
int prezzoscontrino(Scontrino head);
int calcolapunti(ListaDiSpese spese, int codicecliente, Data primaspesa, Data oggi);
int main(void) {
    ListaDiClienti clienti = NULL;
    ListaDiSpese spese = NULL;

    /* Creo alcuni clienti */
    aggiungiClienteInCoda(&clienti, creaCliente(10, "Rossi", "Mario", 0));
    aggiungiClienteInCoda(&clienti, creaCliente(20, "Bianchi", "Luca", 100));
    aggiungiClienteInCoda(&clienti, creaCliente(30, "Verdi", "Anna", 50));

    /* Creo alcune spese con scontrini */
    {
        Scontrino s = NULL;
        aggiungiVoceInCoda(&s, creaVoce("Pasta", 2, 10));         /* 20 */
        aggiungiVoceInCoda(&s, creaVoce("Vino", 15, 2));          /* 30 */
        Data d = {5, 1, 2026};
        aggiungiSpesaInCoda(&spese, creaSpesa(10, d, s));
    }
    {
        Scontrino s = NULL;
        aggiungiVoceInCoda(&s, creaVoce("TV", 1200, 1));          /* 1200 */
        aggiungiVoceInCoda(&s, creaVoce("Cavo HDMI", 20, 2));     /* 40 */
        Data d = {12, 1, 2026};
        aggiungiSpesaInCoda(&spese, creaSpesa(20, d, s));
    }
    {
        Scontrino s = NULL;
        aggiungiVoceInCoda(&s, creaVoce("Laptop", 2600, 2));      /* 5200 (supera 5000 nel mese se sommi anche altre) */
        Data d = {20, 2, 2026};
        aggiungiSpesaInCoda(&spese, creaSpesa(30, d, s));
    }

    printf("=== PRIMA DELL'AGGIORNAMENTO ===\n");
    stampaClienti(clienti);
    stampaSpese(spese);

    printf("Chiamo aggiornaPunti(clienti, spese) (stub)...\n\n");
    aggiornaPunti(clienti, spese);

    printf("=== DOPO L'AGGIORNAMENTO (stub: invariato) ===\n");
    stampaClienti(clienti);

    liberaSpese(spese);
    liberaClienti(clienti);
    return 0;
}
void aggiornaPunti(ListaDiClienti clienti, ListaDiSpese spese)
{
    Data oggi;
    oggi.anno=2026;
    oggi.giorno=10;
    oggi.mese=2;
    if(clienti==NULL || spese==NULL)
        return;
    ListaDiClienti scorriclienti=clienti;
    while (scorriclienti!=NULL) {
        Data primaspesa=prima(scorriclienti->CodiceCliente, spese);
        scorriclienti->puntiAccumulati=calcolapunti(spese, scorriclienti->CodiceCliente, primaspesa, oggi);
        scorriclienti=scorriclienti->next;
    }
    
}
int prezzoscontrino(Scontrino head)
{
    if(head==NULL)
        return 0;
    int somma=0;
    while (head!=NULL) {
        somma=somma+(head->prezzoUnitario*head->quantitaAcquistata);
        head=head->next;
    }
    return somma;
}
int spesecliente(ListaDiSpese spese, int codiceCliente)
    {
        if(spese==NULL)
            return 0;
    int somma=0;
    while (spese!=NULL) {
        if(spese->CodiceCliente==codiceCliente)
            somma=somma+prezzoscontrino(spese->s);
        spese=spese->next;
    }
    return somma;
    }
int calcolapunti(ListaDiSpese spese, int codicecliente, Data primaspesa, Data oggi)
    {
    int sommapunti=0;
    Data scorri=primaspesa;
    while (scorri.mese!=oggi.mese+1 || scorri.anno!=oggi.anno) {
        
        ListaDiSpese scorrispese=spese;
        int sommamensile=0;
        while (scorrispese!=NULL) {
            if(scorrispese->data.anno==scorri.anno && scorrispese->data.mese==scorri.mese && scorrispese->CodiceCliente==codicecliente)
                {
                    sommamensile=sommamensile+prezzoscontrino(scorrispese->s);
                }
                scorrispese=scorrispese->next;
        }
        sommapunti=sommapunti+sommamensile/10;
        if(sommamensile>5000)
            {
                sommapunti=sommapunti+sommamensile/10;
            }
        scorri.mese++;
        if(scorri.mese==13)
            {
                scorri.anno++;
                scorri.mese=1;
            }
        }
    return sommapunti;
    }
Data prima(int codicecliente, ListaDiSpese spese)
    {    int mese=13;
    int anno=2026;
    Data prima;
    prima.giorno=1;
    prima.anno=anno;
    prima.mese=mese;

    if(spese==NULL)
        {
            return prima;
        }
    ListaDiSpese scorri=spese;
    while (scorri!=NULL) {
        if(scorri->CodiceCliente==codicecliente)
            {
                if(scorri->data.anno<anno)
                    anno=scorri->data.anno;
                if(scorri->data.anno==anno)
                    {
                        if(scorri->data.mese<mese)
                            mese=scorri->data.mese;
                    }
            }
        scorri=scorri->next;
    }
    prima.anno=anno;
    prima.mese=mese;
    return prima;
    }
