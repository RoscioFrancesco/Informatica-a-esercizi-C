//
//  main.c
//  liste 2 pag 84 -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct DataT {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct InterpreteT {
    char *cognome;
    char *nome;
    char *cittadinanza;
    struct InterpreteT *next;   /* lista concatenata di interpreti */
} Interprete;

typedef Interprete *ListaInterpreti;

typedef struct ConcertoT {
    ListaInterpreti Lista;      /* lista interpreti del concerto */
    Data data;
    int prezzoBiglietto;
    struct ConcertoT *next;     /* lista concatenata di concerti */
} Concerto;

typedef Concerto *ListaConcerti;



ListaInterpreti interpretiFeb2009Prezzo50(ListaConcerti concerti);

/* =========================
   UTILITY: DUPLICA STRINGA
   ========================= */
static char *dupstr(const char *s) {
    char *p = (char *)malloc(strlen(s) + 1);
    if (!p) { perror("malloc"); exit(1); }
    strcpy(p, s);
    return p;
}

/* =========================
   UTILITY: INTERPRETI
   ========================= */
static ListaInterpreti nuovoInterprete(const char *cognome, const char *nome, const char *citt) {
    ListaInterpreti x = (ListaInterpreti)malloc(sizeof(Interprete));
    if (!x) { perror("malloc"); exit(1); }
    x->cognome = dupstr(cognome);
    x->nome = dupstr(nome);
    x->cittadinanza = dupstr(citt);
    x->next = NULL;
    return x;
}

static ListaInterpreti inserisciInterpreteInCoda(ListaInterpreti head, ListaInterpreti x) {
    if (head == NULL) return x;
    ListaInterpreti cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = x;
    return head;
}

static void stampaInterpreti(ListaInterpreti L) {
    while (L != NULL) {
        printf("  - %s %s (%s)\n", L->nome, L->cognome, L->cittadinanza);
        L = L->next;
    }
}

static void freeInterpreti(ListaInterpreti L) {
    while (L != NULL) {
        ListaInterpreti nxt = L->next;
        free(L->cognome);
        free(L->nome);
        free(L->cittadinanza);
        free(L);
        L = nxt;
    }
}

/* =========================
   UTILITY: CONCERTI
   ========================= */
static ListaConcerti nuovoConcerto(Data d, int prezzo, ListaInterpreti listaInterpreti) {
    ListaConcerti c = (ListaConcerti)malloc(sizeof(Concerto));
    if (!c) { perror("malloc"); exit(1); }
    c->data = d;
    c->prezzoBiglietto = prezzo;
    c->Lista = listaInterpreti;
    c->next = NULL;
    return c;
}

static ListaConcerti inserisciConcertoInCoda(ListaConcerti head, ListaConcerti x) {
    if (head == NULL) return x;
    ListaConcerti cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = x;
    return head;
}

static void stampaConcerti(ListaConcerti C) {
    int i = 1;
    while (C != NULL) {
        printf("Concerto %d: %02d/%02d/%04d, prezzo=%d\n",
               i, C->data.giorno, C->data.mese, C->data.anno, C->prezzoBiglietto);
        printf("Interpreti:\n");
        stampaInterpreti(C->Lista);
        C = C->next;
        i++;
        printf("\n");
    }
}

static void freeConcerti(ListaConcerti C) {
    while (C != NULL) {
        ListaConcerti nxt = C->next;
        freeInterpreti(C->Lista);
        free(C);
        C = nxt;
    }
}
int ver(ListaConcerti lis);
/* =========================
   MAIN DI TEST
   ========================= */
void copialista(ListaInterpreti head, ListaInterpreti *head_mia);
int main(void) {
    ListaConcerti concerti = NULL;

    /* Concerto A: Febbraio 2009, prezzo 50 (DEVE CONTARE) */
    ListaInterpreti LA = NULL;
    LA = inserisciInterpreteInCoda(LA, nuovoInterprete("Rossi", "Mario", "ITA"));
    LA = inserisciInterpreteInCoda(LA, nuovoInterprete("Smith", "John", "USA"));
    concerti = inserisciConcertoInCoda(concerti, nuovoConcerto((Data){10, 2, 2009}, 50, LA));

    /* Concerto B: Febbraio 2009, prezzo 40 (DEVE CONTARE) */
    ListaInterpreti LB = NULL;
    LB = inserisciInterpreteInCoda(LB, nuovoInterprete("Bianchi", "Luca", "ITA"));
    concerti = inserisciConcertoInCoda(concerti, nuovoConcerto((Data){25, 2, 2009}, 40, LB));

    /* Concerto C: Febbraio 2009, prezzo 60 (NON deve contare: prezzo troppo alto) */
    ListaInterpreti LC = NULL;
    LC = inserisciInterpreteInCoda(LC, nuovoInterprete("Garcia", "Ana", "ESP"));
    concerti = inserisciConcertoInCoda(concerti, nuovoConcerto((Data){5, 2, 2009}, 60, LC));

    /* Concerto D: Marzo 2009, prezzo 30 (NON deve contare: mese sbagliato) */
    ListaInterpreti LD = NULL;
    LD = inserisciInterpreteInCoda(LD, nuovoInterprete("Verdi", "Anna", "ITA"));
    concerti = inserisciConcertoInCoda(concerti, nuovoConcerto((Data){1, 3, 2009}, 30, LD));

    printf("=== INPUT: LISTA CONCERTI ===\n\n");
    stampaConcerti(concerti);

    printf("=== CHIAMATA FUNZIONE DA IMPLEMENTARE ===\n");
    printf("ATTENZIONE: interpretiFeb2009Prezzo50(...) NON e' implementata in questo file.\n");
    printf("Implementala tu (con eventuali ausiliarie) e poi scommenta la chiamata qui sotto.\n\n");

    
    ListaInterpreti ris = interpretiFeb2009Prezzo50(concerti);
    printf("=== OUTPUT: interpreti di concerti Feb 2009 con prezzo <= 50 ===\n");
    stampaInterpreti(ris);

    freeInterpreti(ris); // se la tua funzione alloca una nuova lista

    freeConcerti(concerti);
    return 0;
}

ListaInterpreti interpretiFeb2009Prezzo50(ListaConcerti concerti) {
    ListaInterpreti new=NULL;
    while (concerti!=NULL) {
        if(ver(concerti)){
            copialista(concerti->Lista, &new);
        }
        concerti=concerti->next;
    }
    return new;
}


int ver(ListaConcerti lis)
    {
        if(lis==NULL)
            return 0;
        if(lis->data.anno==2009 && lis->data.mese==2 && lis->prezzoBiglietto<=50)
            return 1;
    return 0;
    }
void copialista(ListaInterpreti head, ListaInterpreti *head_mia)
    {
        if(head==NULL)
            return;
    ListaInterpreti new=(ListaInterpreti)malloc(sizeof(*new));
    new->nome=malloc(sizeof(char)*(strlen(head->nome)+1));
    strcpy(new->nome, head->nome);
    new->cognome=malloc(sizeof(char)*(strlen(head->cognome)+1));
    strcpy(new->cognome, head->cognome);
    new->cittadinanza=malloc(sizeof(char)*(strlen(head->cittadinanza)+1));
    strcpy(new->cittadinanza, head->cittadinanza);
    new->next=*head_mia;
    *head_mia=new;
    copialista(head->next, head_mia);
    }
