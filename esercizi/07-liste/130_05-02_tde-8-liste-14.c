//
//  main.c
//  tde 8 liste -14
//
//  Created by Francesco Roscio Ricon on 05/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

/* =========================
   STRUTTURE DATI (date nel testo)
   ========================= */
typedef struct d {
    int giorno, mese, anno;
} Data;

typedef struct job {
    char codice[N], descrizione[N], titoloStudioRichiesto[N];
    int stipendio;
    Data dataInserimento;
    struct job *next;
} offertaDiLavoro;

typedef offertaDiLavoro *ListaOfferte;


int offertaMigliore(ListaOfferte offerte, char titolo[]);
int eliminaOfferteVecchie(ListaOfferte Lis, Data oggi);

/* =========================
   UTILITY per test (cicli OK nel main)
   ========================= */
static Data makeData(int g, int m, int a) {
    Data d; d.giorno = g; d.mese = m; d.anno = a;
    return d;
}

static void stampaData(Data d) {
    printf("%02d/%02d/%04d", d.giorno, d.mese, d.anno);
}

static offertaDiLavoro* newJob(const char *cod, const char *desc, const char *titolo,
                              int stipendio, Data inserimento) {
    offertaDiLavoro *n = (offertaDiLavoro*)malloc(sizeof(offertaDiLavoro));
    if (!n) { perror("malloc"); exit(1); }

    strncpy(n->codice, cod, N-1); n->codice[N-1] = '\0';
    strncpy(n->descrizione, desc, N-1); n->descrizione[N-1] = '\0';
    strncpy(n->titoloStudioRichiesto, titolo, N-1); n->titoloStudioRichiesto[N-1] = '\0';

    n->stipendio = stipendio;
    n->dataInserimento = inserimento;
    n->next = NULL;
    return n;
}

/* Inserimento in coda (per comodità nel main).
   NOTA: il testo dice che la lista è ordinata per codice: nel main puoi inserire già in ordine. */
static ListaOfferte inserisciInCoda(ListaOfferte head, offertaDiLavoro *node) {
    if (!head) return node;
    offertaDiLavoro *p = head;
    while (p->next) p = p->next;
    p->next = node;
    return head;
}

static void stampaLista(ListaOfferte head) {
    printf("=== Lista offerte ===\n");
    if (!head) { printf("(vuota)\n"); return; }
    for (offertaDiLavoro *p = head; p != NULL; p = p->next) {
        printf("- Codice: %s | Titolo: %s | Stipendio: %d | Data: ",
               p->codice, p->titoloStudioRichiesto, p->stipendio);
        stampaData(p->dataInserimento);
        printf("\n  Descrizione: %s\n", p->descrizione);
    }
    printf("=====================\n");
}

static void distruggiLista(ListaOfferte head) {
    while (head) {
        offertaDiLavoro *tmp = head->next;
        free(head);
        head = tmp;
    }
}

/* =========================
   MAIN di test (chiama le funzioni richieste)
   ========================= */
int eliminaOfferteVecchie(ListaOfferte Lis, Data oggi);
int calcolagiorni(Data oggi, Data offerta);
int offertaMigliore(ListaOfferte offerte, char titolo[]);

int main(void) {
    ListaOfferte offerte = NULL;

    /* Costruzione lista (in ordine di codice, come da testo) */
    offerte = inserisciInCoda(offerte, newJob("A001", "Junior Dev C", "Diploma", 1400, makeData(10, 10, 2025)));
    offerte = inserisciInCoda(offerte, newJob("A010", "Backend Intern", "Diploma", 900, makeData( 1, 11, 2025)));
    offerte = inserisciInCoda(offerte, newJob("B002", "Data Analyst", "Laurea", 1800, makeData(15,  9, 2025)));
    offerte = inserisciInCoda(offerte, newJob("C005", "Software Engineer", "Laurea", 2300, makeData(20, 11, 2025)));
    offerte = inserisciInCoda(offerte, newJob("D100", "Project Manager", "Laurea", 2600, makeData( 5,  8, 2025)));

    printf("\nSTATO INIZIALE:\n");
    stampaLista(offerte);

    /* ====== TEST offertaMigliore ====== */
    char titolo1[N] = "Laurea";
    char titolo2[N] = "Diploma";
    char titolo3[N] = "Dottorato"; /* magari assente */

    printf("\nTest offertaMigliore:\n");
    printf("Titolo richiesto: \"%s\" -> stipendio migliore = %d\n", titolo1, offertaMigliore(offerte, titolo1));
    printf("Titolo richiesto: \"%s\" -> stipendio migliore = %d\n", titolo2, offertaMigliore(offerte, titolo2));
    printf("Titolo richiesto: \"%s\" -> stipendio migliore = %d\n", titolo3, offertaMigliore(offerte, titolo3));

    /* ====== TEST eliminaOfferteVecchie ====== */
    Data oggi = makeData(1, 12, 2025);
    printf("\nTest eliminaOfferteVecchie (oggi = ");
    stampaData(oggi);
    printf("):\n");

    int rimossi = eliminaOfferteVecchie(offerte, oggi);
    printf("Numero offerte eliminate: %d\n", rimossi);

    printf("\nSTATO DOPO eliminazione:\n");
    stampaLista(offerte);

    /* Cleanup (se la tua eliminaOfferteVecchie libera correttamente, qui liberi solo i rimanenti) */
    distruggiLista(offerte);

    return 0;
}
int offertaMigliore(ListaOfferte offerte, char titolo[])
    {
        if(offerte==NULL)
            return 0;
        int max=0;
    while (offerte!=NULL) {
        if(strcmp(offerte->titoloStudioRichiesto, titolo)==0)
                {
                    if(offerte->stipendio>max)
                        max=offerte->stipendio;
                }
        offerte=offerte->next;
        }
    return max;
    }
//Si codifichi in C la seguente funzione:
//int eliminaOfferteVecchie(ListaOfferte Lis, Data oggi)
//che elimina le offerte di lavoro più vecchie di 90 giorni rispetto alla data passata nel parametro oggi [2 punti].
int calcolagiorni(Data oggi, Data offerta) // 1 se vanno eliminate, 0 se no
    {
    int somma=0;
    somma=somma+365*(oggi.anno-offerta.anno);
    somma=somma+31*(oggi.mese-offerta.mese);
    somma=somma+oggi.giorno-offerta.giorno;
    if(somma>90)
        return 1;
    return 0;
    }

int eliminaOfferteVecchie(ListaOfferte Lis, Data oggi)
    {
        if(Lis==NULL)
            return 0;
        if(calcolagiorni(oggi, Lis->dataInserimento))
            {
                ListaOfferte temp=Lis->next;
                free(Lis);
                return 1+eliminaOfferteVecchie(Lis->next, oggi);
            }
    return eliminaOfferteVecchie(Lis->next, oggi);
    }
