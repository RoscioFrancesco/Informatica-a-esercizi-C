//
//  main.c
//  liste tde 3 liste -12
//
//  Created by Francesco Roscio Ricon on 07/02/26.
//
/*
    Template RUNNABILE (main + struct + printf) per l’esercizio.
    NON risolve l’esercizio: le funzioni richieste sono lasciate come TODO.

    Compila:  gcc -Wall -Wextra -O2 catering.c -o catering
    Esegui:   ./catering
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE DATI (come consegna)
   ========================= */
typedef struct Date { int giorno; int mese; int anno; } Data;

typedef struct {
    char *cognome, *nome;
    int eta; /* età della persona */
} Persona;

typedef struct Item {
    Persona p;
    char *gradoParentela;
    struct Item *next;
} Invitato;

typedef Invitato *ListaDiInvitati;

typedef struct Node {
    Data d;
    Persona sposo, sposa;
    ListaDiInvitati L;
    struct Node *next;
} Matrimonio;

typedef Matrimonio *ListaDiMatrimoni;

/* =========================
   PROTOTIPI FUNZIONI RICHIESTE (TODO)
   ========================= */
int copertiInData(ListaDiMatrimoni matrimoni, Data target); /* TODO */
ListaDiInvitati appendiInvitatiDaFile(ListaDiInvitati L, const char *filename); /* TODO */

/* =========================
   UTILITY DI SUPPORTO (per test / stampa / memoria)
   ========================= */
static char *dupstr(const char *s) {
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static int dataUguale(Data a, Data b) {
    return a.giorno == b.giorno && a.mese == b.mese && a.anno == b.anno;
}

static void printData(Data d) {
    printf("%02d/%02d/%04d", d.giorno, d.mese, d.anno);
}

static void printPersona(Persona p) {
    printf("%s %s (eta=%d)", p.cognome ? p.cognome : "(null)",
                            p.nome ? p.nome : "(null)",
                            p.eta);
}

static Invitato *newInvitato(const char *cognome, const char *nome, int eta, const char *grado) {
    Invitato *x = (Invitato*)malloc(sizeof(Invitato));
    if (!x) { perror("malloc"); exit(1); }
    x->p.cognome = dupstr(cognome);
    x->p.nome = dupstr(nome);
    x->p.eta = eta;
    x->gradoParentela = dupstr(grado);
    x->next = NULL;
    return x;
}

static ListaDiInvitati pushBackInvitato(ListaDiInvitati L, Invitato *x) {
    if (!L) return x;
    Invitato *sc = L;
    while (sc->next) sc = sc->next;
    sc->next = x;
    return L;
}

static Matrimonio *newMatrimonio(Data d,
                                const char *cognSposo, const char *nomeSposo, int etaSposo,
                                const char *cognSposa, const char *nomeSposa, int etaSposa) {
    Matrimonio *m = (Matrimonio*)malloc(sizeof(Matrimonio));
    if (!m) { perror("malloc"); exit(1); }
    m->d = d;
    m->sposo.cognome = dupstr(cognSposo);
    m->sposo.nome = dupstr(nomeSposo);
    m->sposo.eta = etaSposo;
    m->sposa.cognome = dupstr(cognSposa);
    m->sposa.nome = dupstr(nomeSposa);
    m->sposa.eta = etaSposa;
    m->L = NULL;
    m->next = NULL;
    return m;
}

static ListaDiMatrimoni pushBackMatrimonio(ListaDiMatrimoni M, Matrimonio *x) {
    if (!M) return x;
    Matrimonio *sc = M;
    while (sc->next) sc = sc->next;
    sc->next = x;
    return M;
}

static void printInvitati(ListaDiInvitati L) {
    int i = 1;
    for (Invitato *sc = L; sc; sc = sc->next, i++) {
        printf("  [%d] ", i);
        printPersona(sc->p);
        printf(" - grado: %s\n", sc->gradoParentela ? sc->gradoParentela : "(null)");
    }
    if (i == 1) printf("  (nessun invitato)\n");
}

static void printMatrimoni(ListaDiMatrimoni M) {
    int i = 1;
    for (Matrimonio *sc = M; sc; sc = sc->next, i++) {
        printf("\n=== Matrimonio %d ===\nData: ", i);
        printData(sc->d);
        printf("\nSposo: ");
        printPersona(sc->sposo);
        printf("\nSposa: ");
        printPersona(sc->sposa);
        printf("\nInvitati:\n");
        printInvitati(sc->L);
    }
    if (i == 1) printf("(nessun matrimonio)\n");
}

static void freeInvitati(ListaDiInvitati L) {
    while (L) {
        Invitato *nx = L->next;
        free(L->p.cognome);
        free(L->p.nome);
        free(L->gradoParentela);
        free(L);
        L = nx;
    }
}

static void freeMatrimoni(ListaDiMatrimoni M) {
    while (M) {
        Matrimonio *nx = M->next;
        free(M->sposo.cognome); free(M->sposo.nome);
        free(M->sposa.cognome); free(M->sposa.nome);
        freeInvitati(M->L);
        free(M);
        M = nx;
    }
}

/* Crea un file di esempio nel formato richiesto:
   cognome nome età
   ...
*/
static void creaFileInvitatiEsempio(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) { perror("fopen"); exit(1); }
    fprintf(fp, "Rossi Marco 35\n");
    fprintf(fp, "Bianchi Lucia 2\n");
    fprintf(fp, "Verdi Anna 12\n");
    fprintf(fp, "Neri Paolo 4\n");
    fclose(fp);
}




ListaDiInvitati appendiInvitatiDaFile(ListaDiInvitati L, const char *filename) {
    
    (void)filename;
    return L; /* placeholder */
}

/* =========================
   MAIN
   ========================= */
int main(void) {
    ListaDiMatrimoni M = NULL;

    Data d1 = (Data){7, 2, 2026};
    Data d2 = (Data){8, 2, 2026};

    /* Creo matrimoni di esempio */
    Matrimonio *m1 = newMatrimonio(d1, "Esposito", "Luca", 30, "Russo", "Giulia", 29);
    Matrimonio *m2 = newMatrimonio(d1, "Ferrari", "Marco", 3,  "Gallo", "Sara", 28);
    Matrimonio *m3 = newMatrimonio(d2, "Costa", "Davide", 40,   "Romano", "Elena", 39);

    /* Aggiungo qualche invitato "a mano" */
    m1->L = pushBackInvitato(m1->L, newInvitato("Rossi", "Marta", 25, "amica"));
    m1->L = pushBackInvitato(m1->L, newInvitato("Bianchi", "Piero", 1, "cugino"));

    m2->L = pushBackInvitato(m2->L, newInvitato("Verdi", "Carlo", 10, "zio"));

    /* Inserisco i matrimoni nella lista */
    M = pushBackMatrimonio(M, m1);
    M = pushBackMatrimonio(M, m2);
    M = pushBackMatrimonio(M, m3);

    printf("=== STATO INIZIALE ARCHIVIO MATRIMONI ===\n");
    printMatrimoni(M);

    /* File invitati di esempio e chiamata alla funzione 2 (TODO) */
    const char *fileInv = "invitati.txt";
    creaFileInvitatiEsempio(fileInv);

    printf("\n\n=== TEST: appendiInvitatiDaFile su matrimonio 1 (file: %s) ===\n", fileInv);
    printf("Prima:\n");
    printInvitati(m1->L);

    m1->L = appendiInvitatiDaFile(m1->L, fileInv); /* TODO */

    printf("Dopo (atteso: stessa lista + invitati del file in fondo, quando implementi):\n");
    printInvitati(m1->L);

    /* Chiamata alla funzione 1 (TODO) */
    Data target = d1;
    printf("\n=== TEST: copertiInData per la data ");
    printData(target);
    printf(" ===\n");

    int coperti = copertiInData(M, target); /* TODO */
    printf("Coperti da preparare (eta>3, inclusi sposi): %d\n", coperti);

    /* Cleanup */
    freeMatrimoni(M);

    return 0;
}

int calcolapersone(ListaDiInvitati head)
    {
        int somma=2;
        if(head==NULL)
            return somma;
    ListaDiInvitati scorri=head;
    while(scorri!=NULL)
        {
            if(scorri->p.eta>3)
            {
                somma++;
            }
            scorri=scorri->next;
        }
    return somma;
    }
int copertiInData(ListaDiMatrimoni head, Data oggi)
    {
        if(head==NULL)
            return 0;
        int somma=0;
    ListaDiMatrimoni scorri=head;
    while(scorri!=NULL)
        {
            if(scorri->d.anno==oggi.anno && scorri->d.mese==oggi.mese && scorri->d.giorno==oggi.giorno)
                {
                    somma=somma+calcolapersone(scorri->L);
                }
            scorri=scorri->next;
        }
        return somma;
    }
