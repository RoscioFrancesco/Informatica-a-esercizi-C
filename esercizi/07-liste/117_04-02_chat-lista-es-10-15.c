//
//  main.c
//  chat lista es 10 -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* =========================
   SOTTOLISTA: Voci
   ========================= */
typedef struct Voce {
    char *nomeVoce;         /* stringa dinamica */
    int valore;             /* dato numerico */
    struct Voce *next;
} Voce;
typedef Voce* ListaVoci;

/* =========================
   LISTA ESTERNA: Gruppi
   ========================= */
typedef struct Gruppo {
    char *nomeGruppo;       /* stringa dinamica */
    int id;                 /* campo extra (solo per "tema") */
    ListaVoci voci;         /* sottolista */
    struct Gruppo *next;
} Gruppo;
typedef Gruppo* ListaGruppi;

/* =========================
   RISULTATO: Report (nuova lista)
   - copia del nome gruppo
   - copia dell'intera sottolista
   - valore aggregato della sottolista
   ========================= */
typedef struct Report {
    char *nomeGruppo;       /* deep copy */
    int id;                 /* copiato */
    int aggregato;          /* es. somma / max / media*100 ecc. (scegli tu) */
    ListaVoci copiaVoci;    /* deep copy della sottolista originale */
    struct Report *next;
} Report;
typedef Report* ListaReport;



/* aggrega una sottolista (es: somma / massimo / media...) */
int aggregaVoci(ListaVoci v);                 /* TODO */

/* copia profonda della sottolista (nomeVoce dinamico + valore) */
ListaVoci copiaSottolista(ListaVoci v);       /* TODO */

/* doppia ricorsione:
   - scorre lista gruppi
   - per ogni gruppo: aggregaVoci + copiaSottolista + crea nodo Report */
ListaReport costruisciReport(ListaGruppi g);  /* TODO */

/* =========================================================
   UTILITY (QUI I CICLI SONO OK PER TEST)
   ========================================================= */
static char* dupstr(const char *s) {
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static ListaVoci push_back_voce(ListaVoci l, const char *nomeVoce, int valore) {
    Voce *n = (Voce*)malloc(sizeof(Voce));
    if (!n) { perror("malloc"); exit(1); }
    n->nomeVoce = dupstr(nomeVoce);
    n->valore = valore;
    n->next = NULL;

    if (!l) return n;
    Voce *c = l;
    while (c->next) c = c->next;
    c->next = n;
    return l;
}

static ListaGruppi push_back_gruppo(ListaGruppi L, const char *nomeGruppo, int id, ListaVoci voci) {
    Gruppo *n = (Gruppo*)malloc(sizeof(Gruppo));
    if (!n) { perror("malloc"); exit(1); }
    n->nomeGruppo = dupstr(nomeGruppo);
    n->id = id;
    n->voci = voci;
    n->next = NULL;

    if (!L) return n;
    Gruppo *c = L;
    while (c->next) c = c->next;
    c->next = n;
    return L;
}

static void printVoci(ListaVoci v) {
    printf("{");
    while (v) {
        printf("(\"%s\",%d)", v->nomeVoce, v->valore);
        if (v->next) printf(" -> ");
        v = v->next;
    }
    printf("}");
}

static void printGruppi(ListaGruppi g) {
    while (g) {
        printf("Gruppo id=%d nome=\"%s\" voci=", g->id, g->nomeGruppo);
        printVoci(g->voci);
        printf("\n");
        g = g->next;
    }
}

static void printReport(ListaReport r) {
    while (r) {
        printf("Report id=%d nome=\"%s\" aggregato=%d copiaVoci=",
               r->id, r->nomeGruppo, r->aggregato);
        printVoci(r->copiaVoci);
        printf("\n");
        r = r->next;
    }
}

static void freeVoci(ListaVoci v) {
    while (v) {
        Voce *t = v->next;
        free(v->nomeVoce);
        free(v);
        v = t;
    }
}

static void freeGruppi(ListaGruppi g) {
    while (g) {
        Gruppo *t = g->next;
        free(g->nomeGruppo);
        freeVoci(g->voci);
        free(g);
        g = t;
    }
}

static void freeReport(ListaReport r) {
    while (r) {
        Report *t = r->next;
        free(r->nomeGruppo);
        freeVoci(r->copiaVoci);
        free(r);
        r = t;
    }
}

/* =========================================================
   MAIN DI TEST (POPOLAZIONE "DA ESAME")
   - include casi limite: sottolista vuota, una voce, più voci, duplicati
   ========================================================= */
ListaReport f(ListaGruppi head);
ListaVoci copiaturavoci(ListaVoci head);
float media(Gruppo gruppo);
int main(void) {
    ListaGruppi db = NULL;

    /* Gruppo 1: più voci */
    ListaVoci v1 = NULL;
    v1 = push_back_voce(v1, "lager",  5);
    v1 = push_back_voce(v1, "ipa",    9);
    v1 = push_back_voce(v1, "stout",  7);
    db = push_back_gruppo(db, "BirrePreferite", 101, v1);

    /* Gruppo 2: voci con nomi ripetuti */
    ListaVoci v2 = NULL;
    v2 = push_back_voce(v2, "gold",  3);
    v2 = push_back_voce(v2, "gold",  8);
    v2 = push_back_voce(v2, "amber", 6);
    db = push_back_gruppo(db, "AssaggiRipetuti", 202, v2);

    /* Gruppo 3: una sola voce (edge) */
    ListaVoci v3 = NULL;
    v3 = push_back_voce(v3, "solo", 42);
    db = push_back_gruppo(db, "SingolaVoce", 303, v3);

    /* Gruppo 4: sottolista vuota (edge) */
    db = push_back_gruppo(db, "Vuoto", 404, NULL);

    /* Gruppo 5: valori anche negativi */
    ListaVoci v5 = NULL;
    v5 = push_back_voce(v5, "penalita", -2);
    v5 = push_back_voce(v5, "bonus",     4);
    v5 = push_back_voce(v5, "bonus2",    1);
    db = push_back_gruppo(db, "Punteggi", 505, v5);

    printf("=== INPUT: LISTA GRUPPI ===\n");
    printGruppi(db);

    
    ListaReport rep = f(db);

    printf("\n=== OUTPUT: LISTA REPORT (NUOVA) ===\n");
    printReport(rep);

    /* cleanup */
    freeGruppi(db);
    freeReport(rep);
    return 0;
}

// come aggregato calcolo la media del valore delle voci
float media(Gruppo gruppo)
    {
    ListaVoci scorri=gruppo.voci;
    float somma=0;
    float count=0;
    if(scorri==NULL)
        return 0;
    while (scorri!=NULL) {
        somma=somma+scorri->valore;
        count++;
        scorri=scorri->next;
        }
    float media=somma/count;
    return media;
    }
ListaVoci copiaturavoci(ListaVoci head)
    {
    if(head==NULL)
        return NULL;
    ListaVoci new=(ListaVoci)malloc(sizeof(*new));
    if(new==NULL)
        return NULL;
    int num=strlen(head->nomeVoce);
    new->nomeVoce=malloc(sizeof(char)*(num+1));
    strcpy(new->nomeVoce, head->nomeVoce);
    new->valore=head->valore;
    new->next=copiaturavoci(head->next);
    return new;
    }
ListaReport f(ListaGruppi head)
    {
        if(head==NULL)
            return NULL;
    ListaReport p=(ListaReport)malloc(sizeof(*p));
    p->id=head->id;
    p->copiaVoci=copiaturavoci(head->voci);
    p->nomeGruppo=malloc(sizeof(char)*(strlen(head->nomeGruppo)+1));
    strcpy(p->nomeGruppo, head->nomeGruppo);
    p->aggregato=media(*head);
    p->next=f(head->next);
    return p;
    }

