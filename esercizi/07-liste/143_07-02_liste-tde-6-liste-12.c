//
//  main.c
//  liste tde 6 liste -12
//
//  Created by Francesco Roscio Ricon on 07/02/26.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_MAX 100
#define TITOLO_MAX 1000

/* =========================
   STRUTTURE DATE E PERSONE
   ========================= */
typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    char cognome[NOME_MAX], nome[NOME_MAX];
    int eta;
} Persona;

/* =========================
   LISTA AUTORI
   ========================= */
typedef struct Aut {
    Persona p;
    struct Aut *next;
} Autore;

typedef Autore *ListaAutori;

/* =========================
   LISTA ARTICOLI
   ========================= */
typedef struct Art {
    ListaAutori autori;         /* ogni articolo contiene lista autori */
    char Titolo[TITOLO_MAX];
    int pagina;
    struct Art *next;
} Articolo;

typedef Articolo *ListaArticoli;

/* =========================
   LISTA RIVISTE (come da traccia)
   ========================= */
typedef struct Riv {
    int numero;
    Data dataPubblicazione;
    char Titolo[TITOLO_MAX];
    struct Riv *next;
} Rivista;

typedef Rivista *ListaDiRiviste;

/* =========================
   WRAPPER PER INPUT REALISTICO:
   numero rivista + lista articoli contenuti nel numero
   (serve perché nella traccia non c'è il puntatore agli articoli)
   ========================= */
typedef struct NumRiv {
    Rivista info;           /* contiene numero, dataPubblicazione, titolo */
    ListaArticoli articoli; /* articoli di quel numero */
    struct NumRiv *next;
} NumeroRivista;

typedef NumeroRivista *ArchivioRiviste;

/* =========================
   PROTOTIPO FUNZIONE DELL'ESERCIZIO (TODO)
   =========================
   Input: lista di riviste ordinata per data decrescente
   Output: lista degli autori (senza duplicati) ordinati per data del primo articolo pubblicato
*/
ListaAutori autoriSenzaDuplicatiOrdinati(ArchivioRiviste riviste);

/* =========================
   UTILITY: confronto date
   ========================= */
static int cmpData(Data a, Data b) {
    /* ritorna <0 se a < b, 0 se uguali, >0 se a > b */
    if (a.anno != b.anno) return a.anno - b.anno;
    if (a.mese != b.mese) return a.mese - b.mese;
    return a.giorno - b.giorno;
}

static void stampaData(Data d) {
    printf("%02d/%02d/%04d", d.giorno, d.mese, d.anno);
}

/* =========================
   CREAZIONE NODI
   ========================= */
static Persona makePersona(const char *cognome, const char *nome, int eta) {
    Persona p;
    strncpy(p.cognome, cognome, NOME_MAX - 1);
    p.cognome[NOME_MAX - 1] = '\0';
    strncpy(p.nome, nome, NOME_MAX - 1);
    p.nome[NOME_MAX - 1] = '\0';
    p.eta = eta;
    return p;
}

static ListaAutori pushAutore(ListaAutori head, Persona p) {
    Autore *n = (Autore*)malloc(sizeof(Autore));
    if (!n) { perror("malloc"); exit(1); }
    n->p = p;
    n->next = head;
    return n;
}

static ListaArticoli pushArticolo(ListaArticoli head, const char *titolo, int pagina, ListaAutori autori) {
    Articolo *a = (Articolo*)malloc(sizeof(Articolo));
    if (!a) { perror("malloc"); exit(1); }
    strncpy(a->Titolo, titolo, TITOLO_MAX - 1);
    a->Titolo[TITOLO_MAX - 1] = '\0';
    a->pagina = pagina;
    a->autori = autori;
    a->next = head;
    return a;
}

static ArchivioRiviste pushNumeroRivista(ArchivioRiviste head, int numero, Data dataPub, const char *titoloRiv, ListaArticoli articoli) {
    NumeroRivista *nr = (NumeroRivista*)malloc(sizeof(NumeroRivista));
    if (!nr) { perror("malloc"); exit(1); }

    nr->info.numero = numero;
    nr->info.dataPubblicazione = dataPub;
    strncpy(nr->info.Titolo, titoloRiv, TITOLO_MAX - 1);
    nr->info.Titolo[TITOLO_MAX - 1] = '\0';
    nr->info.next = NULL; /* non usato nel wrapper */

    nr->articoli = articoli;
    nr->next = head;
    return nr;
}

/* =========================
   STAMPE
   ========================= */
static void stampaListaAutori(ListaAutori a) {
    int i = 1;
    while (a) {
        printf("      Autore %d: %s %s (eta=%d)\n", i, a->p.cognome, a->p.nome, a->p.eta);
        a = a->next;
        i++;
    }
    if (i == 1) printf("      [nessun autore]\n");
}

static void stampaListaArticoli(ListaArticoli art) {
    int i = 1;
    while (art) {
        printf("    Articolo %d: \"%s\" (pag. %d)\n", i, art->Titolo, art->pagina);
        stampaListaAutori(art->autori);
        art = art->next;
        i++;
    }
    if (i == 1) printf("    [nessun articolo]\n");
}

static void stampaArchivio(ArchivioRiviste r) {
    printf("\n========== ARCHIVIO RIVISTE (input) ==========\n");
    int i = 1;
    while (r) {
        printf("\nRivista %d:\n", i);
        printf("  Numero: %d\n", r->info.numero);
        printf("  Data pubblicazione: ");
        stampaData(r->info.dataPubblicazione);
        printf("\n");
        printf("  Titolo rivista: \"%s\"\n", r->info.Titolo);
        printf("  Articoli nel numero:\n");
        stampaListaArticoli(r->articoli);
        r = r->next;
        i++;
    }
    if (i == 1) printf("[archivio vuoto]\n");
    printf("\n==============================================\n");
}

/* =========================
   FREE (per non perdere memoria nei test)
   ========================= */
static void freeAutori(ListaAutori a) {
    while (a) {
        ListaAutori nxt = a->next;
        free(a);
        a = nxt;
    }
}

static void freeArticoli(ListaArticoli art) {
    while (art) {
        ListaArticoli nxt = art->next;
        freeAutori(art->autori);
        free(art);
        art = nxt;
    }
}

static void freeArchivio(ArchivioRiviste r) {
    while (r) {
        ArchivioRiviste nxt = r->next;
        freeArticoli(r->articoli);
        free(r);
        r = nxt;
    }
}
Data primoarticolo(ArchivioRiviste head, Persona cercautore);
int trovato(ListaAutori autori, ListaAutori chech);
int main(void) {
    ArchivioRiviste archivio = NULL;

    /* ---------- CASO A: archivio vuoto ---------- */
    printf("CASO A: archivio vuoto\n");
    stampaArchivio(archivio);
    ListaAutori outA = autoriSenzaDuplicatiOrdinati(archivio);
    printf("Output funzione (atteso: lista autori; per ora e' NULL): %s\n", outA ? "NON-NULL" : "NULL");
    freeAutori(outA);

    /* ---------- CASO B: 1 rivista, 0 articoli ---------- */
    printf("\nCASO B: 1 rivista, 0 articoli\n");
    Data dB = (Data){10, 1, 2024};
    archivio = pushNumeroRivista(archivio, 101, dB, "Numero Speciale: Zero Articoli", NULL);
    stampaArchivio(archivio);
    ListaAutori outB = autoriSenzaDuplicatiOrdinati(archivio);
    printf("Output funzione: %s\n", outB ? "NON-NULL" : "NULL");
    freeAutori(outB);
    freeArchivio(archivio);
    archivio = NULL;

    /* ---------- CASO C: 1 rivista, 1 articolo, 1 autore ---------- */
    printf("\nCASO C: 1 rivista, 1 articolo, 1 autore\n");
    ListaAutori autC = NULL;
    autC = pushAutore(autC, makePersona("Rossi", "Mario", 40));
    ListaArticoli artC = NULL;
    artC = pushArticolo(artC, "Introduzione alla Rivista", 1, autC);

    Data dC = (Data){5, 2, 2024};
    archivio = pushNumeroRivista(archivio, 102, dC, "Numero 102", artC);

    stampaArchivio(archivio);
    ListaAutori outC = autoriSenzaDuplicatiOrdinati(archivio);
    printf("Output funzione: %s\n", outC ? "NON-NULL" : "NULL");
    freeAutori(outC);
    freeArchivio(archivio);
    archivio = NULL;

    /* ---------- CASO D: 1 rivista, piu' articoli, autori ripetuti nello stesso numero ---------- */
    printf("\nCASO D: 1 rivista, piu' articoli, duplicati nello stesso numero\n");
    ListaArticoli artD = NULL;

    ListaAutori aD1 = NULL;
    aD1 = pushAutore(aD1, makePersona("Bianchi", "Luca", 35));
    aD1 = pushAutore(aD1, makePersona("Rossi", "Mario", 40));
    artD = pushArticolo(artD, "Articolo 1", 10, aD1);

    ListaAutori aD2 = NULL;
    aD2 = pushAutore(aD2, makePersona("Rossi", "Mario", 40)); /* dup */
    aD2 = pushAutore(aD2, makePersona("Verdi", "Anna", 29));
    artD = pushArticolo(artD, "Articolo 2", 20, aD2);

    Data dD = (Data){20, 3, 2024};
    archivio = pushNumeroRivista(archivio, 103, dD, "Numero 103", artD);

    stampaArchivio(archivio);
    ListaAutori outD = autoriSenzaDuplicatiOrdinati(archivio);
    printf("Output funzione: %s\n", outD ? "NON-NULL" : "NULL");
    freeAutori(outD);
    freeArchivio(archivio);
    archivio = NULL;

    /* ---------- CASO E: piu' riviste (date decrescenti), stessi autori in numeri diversi ---------- */
    printf("\nCASO E: piu' riviste, autori ripetuti su date diverse\n");
    /*
      Inseriamo in lista in modo che le date siano decrescenti (test):
      - 2025-11-15 (piu' recente)
      - 2025-06-02
      - 2024-12-01 (piu' vecchia)
    */

    /* Numero più vecchio (inserito per ultimo nel push head, quindi lo creiamo per primo ma lo pushiamo per ultimo) */
    ListaArticoli artE_old = NULL;
    ListaAutori aEold1 = NULL;
    aEold1 = pushAutore(aEold1, makePersona("Neri", "Sara", 50));
    aEold1 = pushAutore(aEold1, makePersona("Rossi", "Mario", 40));
    artE_old = pushArticolo(artE_old, "Speciale 2024", 5, aEold1);

    /* Numero medio */
    ListaArticoli artE_mid = NULL;
    ListaAutori aEmid1 = NULL;
    aEmid1 = pushAutore(aEmid1, makePersona("Bianchi", "Luca", 35));
    aEmid1 = pushAutore(aEmid1, makePersona("Neri", "Sara", 50)); /* ripete Sara Neri */
    artE_mid = pushArticolo(artE_mid, "Estate 2025", 12, aEmid1);

    ListaAutori aEmid2 = NULL;
    aEmid2 = pushAutore(aEmid2, makePersona("Verdi", "Anna", 29));
    artE_mid = pushArticolo(artE_mid, "Rubrica", 30, aEmid2);

    /* Numero più recente */
    ListaArticoli artE_new = NULL;
    ListaAutori aEnew1 = NULL;
    aEnew1 = pushAutore(aEnew1, makePersona("Rossi", "Mario", 40)); /* ripete Mario Rossi */
    aEnew1 = pushAutore(aEnew1, makePersona("Gialli", "Paolo", 33));
    artE_new = pushArticolo(artE_new, "Novembre 2025", 3, aEnew1);

    /* Costruiamo lista riviste in ordine data decrescente: push head in ordine new -> mid -> old */
    archivio = pushNumeroRivista(archivio, 203, (Data){1, 12, 2024}, "Numero 203 (vecchio)", artE_old);
    archivio = pushNumeroRivista(archivio, 305, (Data){2, 6, 2025},  "Numero 305 (medio)",  artE_mid);
    archivio = pushNumeroRivista(archivio, 411, (Data){15, 11, 2025},"Numero 411 (recente)",artE_new);

    stampaArchivio(archivio);
    printf("Check veloce ordine date (devono scendere):\n");
    if (archivio && archivio->next) {
        printf("  ");
        stampaData(archivio->info.dataPubblicazione);
        printf(" >= ");
        stampaData(archivio->next->info.dataPubblicazione);
        printf(" ? %s\n", (cmpData(archivio->info.dataPubblicazione, archivio->next->info.dataPubblicazione) >= 0) ? "OK" : "NO");
    }

    ListaAutori outE = autoriSenzaDuplicatiOrdinati(archivio);
    printf("Output funzione: %s\n", outE ? "NON-NULL" : "NULL");
    freeAutori(outE);

    freeArchivio(archivio);
    archivio = NULL;

    printf("\nFine test.\n");
    return 0;
}

ListaAutori inserisciordinato(ListaAutori head, Autore x, ArchivioRiviste archivioriviste)
    {
    Data datax=primoarticolo(archivioriviste, x.p);
    if(head==NULL || datax.anno>primoarticolo(archivioriviste, head->p).anno)
            {
                ListaAutori new=(ListaAutori)malloc(sizeof(*new));
                *new=x;
                new->next=head;
                return new;
            }
        head->next=inserisciordinato(head->next, x, archivioriviste);
        return head;
    }
Data primoarticolo(ArchivioRiviste head, Persona cercautore)
    {
    Data ris;
    ArchivioRiviste scorri=head;
    while (scorri!=NULL) {
        
        ListaArticoli scorri_articoli=scorri->articoli;
        while (scorri_articoli!=NULL)
        {
            ListaAutori scorriautori =scorri_articoli->autori;
            while (scorriautori!=NULL) {
                if(strcmp(scorriautori->p.cognome,cercautore.cognome)==0 && scorriautori->p.eta==cercautore.eta && strcmp(scorriautori->p.nome,cercautore.nome)==0)
                {
                    ris=scorri->info.dataPubblicazione;
                }
                scorriautori=scorriautori->next;
            }
            scorri_articoli=scorri_articoli->next;
        }
        scorri=scorri->next;
        }
    return ris;
    }

ListaAutori autoriSenzaDuplicatiOrdinati(ArchivioRiviste riviste) {
    ListaAutori new=NULL;
    if(riviste==NULL)
        return new;
    ArchivioRiviste scorri_riviste=riviste;
    while (scorri_riviste!=NULL) {
        ListaArticoli scorriarticoli=scorri_riviste->articoli;
        while (scorriarticoli!=NULL) {
            ListaAutori scorriautori=scorriarticoli->autori;
            while (scorriautori!=NULL) {
                    if(trovato(new, scorriautori)==0)
                        {
                            new=inserisciordinato(new, *scorriautori, riviste);
                        }
                scorriautori=scorriautori->next;
            }
            scorriarticoli=scorriarticoli->next;
        }
        scorri_riviste=scorri_riviste->next;
    }
    return new;
}
int trovato(ListaAutori autori, ListaAutori chech)
    {
    if(autori==NULL)
        return 0;
    ListaAutori scorri=autori;
    while (scorri!=NULL) {
        if(strcmp(scorri->p.cognome,chech->p.cognome)==0 && strcmp(scorri->p.nome,chech->p.nome)==0 && scorri->p.eta==chech->p.eta)
            return 1;
        scorri=scorri->next;
        }
    return 0;
    }
