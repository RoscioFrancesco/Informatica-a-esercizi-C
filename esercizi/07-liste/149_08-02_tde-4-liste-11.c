//
//  main.c
//  tde 4 liste -11
//
//  Created by Francesco Roscio Ricon on 08/02/26.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct D {
    int giorno, mese, anno;
} Data;

typedef struct Esib {
    char artista[50];
    int costoBiglietto;
    struct Esib *next;
} Esibizione;

typedef Esibizione *ListaEsibizioni;

typedef struct Sera {
    char titolo[50];
    Data data;
    ListaEsibizioni esibizioni;
    struct Sera *next;
} Serata;

typedef Serata *ListaSerate;

/* =========================
   PROTOTIPI FUNZIONI ESERCIZIO (DA FARE)
   ========================= */
int totCostiSerate(ListaSerate serate, Data oggi);
ListaSerate eliminaEsibizione(ListaSerate serate, char *artista, Data oggi);


/* =========================
   UTILITY: confronto date
   ========================= */
/* ritorna <0 se a<b, 0 se a==b, >0 se a>b */
static int cmpData(Data a, Data b) {
    if (a.anno != b.anno) return a.anno - b.anno;
    if (a.mese != b.mese) return a.mese - b.mese;
    return a.giorno - b.giorno;
}

static void stampaData(Data d) {
    printf("%02d/%02d/%04d", d.giorno, d.mese, d.anno);
}

/* =========================
   UTILITY: creazione nodi
   ========================= */
static ListaEsibizioni nuovaEsib(const char *artista, int costo) {
    ListaEsibizioni e = (ListaEsibizioni)malloc(sizeof(*e));
    if (!e) { perror("malloc"); exit(1); }
    strncpy(e->artista, artista, sizeof(e->artista) - 1);
    e->artista[sizeof(e->artista) - 1] = '\0';
    e->costoBiglietto = costo;
    e->next = NULL;
    return e;
}

static ListaSerate nuovaSerata(const char *titolo, Data d) {
    ListaSerate s = (ListaSerate)malloc(sizeof(*s));
    if (!s) { perror("malloc"); exit(1); }
    strncpy(s->titolo, titolo, sizeof(s->titolo) - 1);
    s->titolo[sizeof(s->titolo) - 1] = '\0';
    s->data = d;
    s->esibizioni = NULL;
    s->next = NULL;
    return s;
}

/* inserimenti in testa (semplici per test) */
static ListaEsibizioni pushEsib(ListaEsibizioni head, ListaEsibizioni x) {
    x->next = head;
    return x;
}

static ListaSerate pushSerata(ListaSerate head, ListaSerate x) {
    x->next = head;
    return x;
}

/* =========================
   STAMPA STRUTTURE
   ========================= */
static void stampaEsibizioni(ListaEsibizioni e) {
    while (e) {
        printf("    - %-15s | %d €\n", e->artista, e->costoBiglietto);
        e = e->next;
    }
}

static void stampaSerate(ListaSerate s) {
    printf("=== LISTA SERATE ===\n");
    while (s) {
        printf("Serata: \"%s\"  | Data: ", s->titolo);
        stampaData(s->data);
        printf("\n");
        if (s->esibizioni == NULL) {
            printf("    (nessuna esibizione)\n");
        } else {
            stampaEsibizioni(s->esibizioni);
        }
        printf("\n");
        s = s->next;
    }
}

/* =========================
   FREE
   ========================= */
static void freeEsibizioni(ListaEsibizioni e) {
    while (e) {
        ListaEsibizioni nx = e->next;
        free(e);
        e = nx;
    }
}

static void freeSerate(ListaSerate s) {
    while (s) {
        ListaSerate nx = s->next;
        freeEsibizioni(s->esibizioni);
        free(s);
        s = nx;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    ListaSerate serate = NULL;

    /* Creo alcune serate */
    ListaSerate s1 = nuovaSerata("Rock Night", (Data){10, 2, 2026});
    s1->esibizioni = pushEsib(s1->esibizioni, nuovaEsib("AlphaBand", 30));
    s1->esibizioni = pushEsib(s1->esibizioni, nuovaEsib("DJ Zeta",   25));
    s1->esibizioni = pushEsib(s1->esibizioni, nuovaEsib("BetaSinger",40));

    ListaSerate s2 = nuovaSerata("Jazz Evening", (Data){1,  3, 2026});
    s2->esibizioni = pushEsib(s2->esibizioni, nuovaEsib("BlueTrio",   20));
    s2->esibizioni = pushEsib(s2->esibizioni, nuovaEsib("AlphaBand",  35));

    ListaSerate s3 = nuovaSerata("Old Event", (Data){15, 12, 2025});
    s3->esibizioni = pushEsib(s3->esibizioni, nuovaEsib("DJ Zeta", 10));

    /* Inserisco in lista (testa) */
    serate = pushSerata(serate, s1);
    serate = pushSerata(serate, s2);
    serate = pushSerata(serate, s3);

    printf("Stato iniziale:\n");
    stampaSerate(serate);

    /* TEST totCostiSerate */
    {
        Data oggi = (Data){8, 2, 2026};
        int tot = totCostiSerate(serate, oggi);
        printf("totCostiSerate(oggi=");
        stampaData(oggi);
        printf(") = %d\n\n", tot);
    }

    /* TEST eliminaEsibizione */
    {
        Data oggi = (Data){8, 2, 2022};
        char artista[] = "DJ Zeta";

        serate = eliminaEsibizione(serate, artista, oggi);

        printf("Dopo eliminaEsibizione(artista=\"%s\", oggi=", artista);
        stampaData(oggi);
        printf("):\n");
        stampaSerate(serate);
    }

    freeSerate(serate);
    return 0;
}
//Si codifichi in C la seguente funzione:

//Si codifichi in C la seguente funzione:
//ListaSerata eliminaEsibizione(ListaSerata serate, char * artista, Data oggi)
//che elimina tutte le esibizioni dell’artista passato come parametro da tutte le serate posteriori alla data terzo parametro della funzione. Qualora per una serata l’esibizione cancellata fosse l’unica esibizione anche la serata è eliminata dalla lista delle serate.
int esibizpiùcara(ListaEsibizioni head)
    {
    int max=0;
    ListaEsibizioni scorri=head;
    while (scorri!=NULL)
    {
        if(scorri->costoBiglietto>max)
            max=scorri->costoBiglietto;
        scorri=scorri->next;
    }
    return max;
    }
int dataprec(Data daverificare, Data oggi)
    {
    if (daverificare.anno<oggi.anno)
        {
            return 1;
        }
    if (daverificare.anno==oggi.anno)
        {
            if (daverificare.mese<oggi.mese)
                return 1;
            if(daverificare.mese==oggi.mese)
                {
                    if(daverificare.giorno<oggi.giorno)
                        return 1;
                    return 0;
                }
            return 0;
        }
    return 0;
    }


int totCostiSerate(ListaSerate serate, Data oggi)
    {
        if(serate==NULL)
            return 0;
        int somma=0;
    ListaSerate scorri=serate;
    while (scorri!=NULL)
        {
        ListaEsibizioni scorri_esibiz=scorri->esibizioni;
        if(dataprec(scorri->data, oggi)==0)
            {
                somma=somma+esibizpiùcara(scorri_esibiz);
            }
        scorri=scorri->next;
        }
    return somma;
    }


//che elimina tutte le esibizioni dell’artista passato come parametro da tutte le serate posteriori alla data terzo parametro della funzione. Qualora per una serata l’esibizione cancellata fosse l’unica esibizione anche la serata è eliminata dalla lista delle serate.

ListaEsibizioni eliminaesibiz(ListaEsibizioni head, char artista[])
    {
        if(head==NULL)
            return head;
        if(strcmp(head->artista, artista)==0)
            {
                ListaEsibizioni temp=head->next;
                free(head);
                return eliminaesibiz(temp, artista);
            }
        head->next=eliminaesibiz(head->next, artista);
        return head;
    }
ListaSerate eliminaEsibizione(ListaSerate serate, char * artista, Data oggi)
    {
        if(serate==NULL)
            return serate;
        if(dataprec(serate->data, oggi)==0)
            {
                serate->esibizioni=eliminaesibiz(serate->esibizioni, artista);
                if(serate->esibizioni==NULL)
                    {
                        ListaSerate temp=serate->next;
                        free(serate);
                        return eliminaEsibizione(temp, artista, oggi);
                    }
            }
    serate->next=eliminaEsibizione(serate->next, artista, oggi);
    return serate;
    }
