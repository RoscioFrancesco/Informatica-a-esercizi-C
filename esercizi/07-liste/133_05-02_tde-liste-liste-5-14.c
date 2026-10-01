//  Created by Francesco Roscio Ricon on 05/02/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

/* =========================
   STRUTTURE DATI
   ========================= */
typedef struct { int giorno, mese, anno; } Data;

typedef struct P {
    char nome[N], cognome[N];
    Data dataNascita;
    struct P *next;
} Persona;

typedef struct Li {
    char ISBN[N], titolo[N];
    Persona *autore;          /* testa lista autori */
    Data dataPubblicazione;
    Data dataUltimoPrestito;
    int prezzo;
    struct Li *next;          /* next libro */
} Libro;

typedef Libro* Biblioteca;

/* =========================
   PROTOTIPO FUNZIONE ESERCIZIO
   ========================= */
Biblioteca f(Biblioteca bib);   /* DA SVOLGERE */

/* =========================
   UTILITY per il main (creazione dati)
   ========================= */
static Persona* newAutore(const char *nome, const char *cognome, Data nasc, Persona *next) {
    Persona *p = (Persona*)malloc(sizeof(Persona));
    if (!p) { perror("malloc"); exit(1); }
    strncpy(p->nome, nome, N);
    strncpy(p->cognome, cognome, N);
    p->nome[N-1] = '\0';
    p->cognome[N-1] = '\0';
    p->dataNascita = nasc;
    p->next = next;
    return p;
}

static Libro* newLibro(const char *isbn, const char *titolo,
                       Persona *autori,
                       Data pub, Data ultPrest, int prezzo,
                       Libro *next) {
    Libro *l = (Libro*)malloc(sizeof(Libro));
    if (!l) { perror("malloc"); exit(1); }
    strncpy(l->ISBN, isbn, N);
    strncpy(l->titolo, titolo, N);
    l->ISBN[N-1] = '\0';
    l->titolo[N-1] = '\0';
    l->autore = autori;
    l->dataPubblicazione = pub;
    l->dataUltimoPrestito = ultPrest;
    l->prezzo = prezzo;
    l->next = next;
    return l;
}

static void printData(Data d) {
    printf("%02d/%02d/%04d", d.giorno, d.mese, d.anno);
}

static void printAutori(Persona *a) {
    if (a == NULL) {
        printf("(nessun autore)");
        return;
    }
    while (a != NULL) {
        printf("%s %s (nato ", a->nome, a->cognome);
        printData(a->dataNascita);
        printf(")");
        if (a->next) printf(" -> ");
        a = a->next;
    }
}

static void printBiblioteca(Biblioteca b) {
    printf("=== BIBLIOTECA ===\n");
    if (b == NULL) {
        printf("(vuota)\n");
        return;
    }
    while (b != NULL) {
        printf("ISBN: %s | Titolo: %s | Prezzo: %d\n", b->ISBN, b->titolo, b->prezzo);
        printf("  Pubblicazione: "); printData(b->dataPubblicazione);
        printf(" | Ultimo prestito: "); printData(b->dataUltimoPrestito);
        printf("\n  Autori: ");
        printAutori(b->autore);
        printf("\n\n");
        b = b->next;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
Persona *copiaAutore(Persona *x);
void distruggiautore(Persona * autori);
int main() {
    /*
      Creo una biblioteca (lista) con qualche libro.
      Nota: l'ordine per ISBN "dovrebbe" essere crescente (come da consegna).
    */

    Data n1 = {10, 5, 2010};   /* autore nato nel 2010 */
    Data n2 = {3,  9, 2005};   /* autore nato nel 2005 */
    Data n3 = {1,  1, 1980};   /* autore nato nel 1980 */

    Data pub1 = {1, 6, 2022};  /* nel 2022, età: 12 e 16 -> entrambi minorenni */
    Data pub2 = {1, 6, 2022};  /* include autore 1980 -> maggiorenne */
    Data pub3 = {1, 6, 2018};  /* autore 2005 -> 12/13 anni */

    Data prest = {10, 1, 2026};

    /* lista autori per libro 1: (2010) -> (2005) */
    Persona *autori1 = newAutore("Luca", "Rossi", n1,
                         newAutore("Anna", "Bianchi", n2, NULL));

    /* lista autori per libro 2: (1980) */
    Persona *autori2 = newAutore("Mario", "Verdi", n3, NULL);

    /* libro 3: autore singolo (2005) */
    Persona *autori3 = newAutore("Giulia", "Neri", n2, NULL);

    Biblioteca bib = NULL;
    bib = newLibro("0003", "Libro C (autore 2005)", autori3, pub3, prest, 25, bib);
    bib = newLibro("0002", "Libro B (autore 1980)", autori2, pub2, prest, 30, bib);
    bib = newLibro("0001", "Libro A (autori 2010+2005)", autori1, pub1, prest, 20, bib);

    printf("BIBLIOTECA IN INGRESSO:\n");
    printBiblioteca(bib);

    Biblioteca ris = f(bib);   /* DA SVOLGERE */
    printf("RISULTATO f(bib) (libri con autori TUTTI minorenni alla pubblicazione):\n");
    printBiblioteca(ris);

    return 0;
}
Biblioteca inserisciincoda(Biblioteca head, Libro x)
    {
        if(head==NULL)
            {
                Biblioteca new=(Biblioteca)malloc(sizeof(*new));
                *new=x;
                new->autore=copiaAutore(x.autore);
                new->next=NULL;
                return new;
            }
    head->next=inserisciincoda(head->next, x);
    return head;
    }
Persona *copiaAutore(Persona *x)
{
    if(x==NULL)
        return NULL;
    Persona *new=(Persona *)malloc(sizeof(*new));
    strcpy(new->cognome,x->cognome);
    strcpy(new->nome, x->nome);
    new->dataNascita = x->dataNascita;
    
    new->next=copiaAutore(x->next);
    return new;
}
int ver(Libro x) // se ritorna 1 allora copio il libro
    {
    Persona* scorri=x.autore;
    while(scorri!=NULL)
        {
            if(-scorri->dataNascita.anno+x.dataPubblicazione.anno>18)
                return 0;
            scorri=scorri->next;
        }
        return 1;
    }
Biblioteca f(Biblioteca head)
    {
        if(head==NULL)
            return NULL;
    Biblioteca new=NULL;
    Biblioteca scorri=head;
    while (scorri!=NULL) {
        if(ver(*scorri))
            {
                new=inserisciincoda(new, *scorri);
            }
        scorri=scorri->next;
        }
    return new;
    }
//Si codifichi in C la funzione:
//Biblioteca eliminaLibriInutilizzati(Biblioteca libri, Data oggi)
//che elimina i libri che non vengono prestati da 10 anni.

int verifica_inutili(Libro l, Data oggi) // mi ridà si se deve essereeliminato
    {
        if(oggi.anno-l.dataUltimoPrestito.anno>10)
            return 1;
    return 0;
    }
Biblioteca eliminaLibriInutilizzati(Biblioteca libri, Data oggi)
{
    if(libri==NULL)
        return libri;
    if(verifica_inutili(*libri, oggi))
    {
        Biblioteca temp=libri->next;
        distruggiautore(libri->autore);
        free(libri);
        return eliminaLibriInutilizzati(temp, oggi);
    }
    libri->next=eliminaLibriInutilizzati(libri->next, oggi);
    return libri;
}
void distruggiautore(Persona * autori)
    {
        if(autori==NULL)
            return;
        Persona *temp=autori->next;
        free(autori);
        distruggiautore(temp);
    }
