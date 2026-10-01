//
//  main.c
//  tde 4 liste -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5   /* numero candidati per lista */

/* ====== TIPI (come da testo) ====== */
typedef char * nome;             // una stringa
typedef nome * elencocandidati;  // puntatore a un vettore di puntatori a char
typedef nome candidati[N];       // un vettore di N puntatori a char

typedef struct lis {
    int numLista;
    elencocandidati elenconomi;  // “punta a” un vettore di tipo candidati
    struct lis * next;
} listacandidati;

typedef listacandidati * lista;  // lista di listacandidati

typedef struct sc {
    int numLista;
    char * preferenza;           // NULL se non espressa o non valida
    struct sc * next;
} scheda;

typedef scheda * listascrutinio;

/* ====== PROTOTIPO RICHIESTO ====== */
int piuVotato(nome n, int numLista, listascrutinio ls, lista L);

/* ====== UTILITY ====== */
static char * dupstr(const char *s) {
    char *p = (char*)malloc(strlen(s) + 1);
    if (!p) { perror("malloc"); exit(1); }
    strcpy(p, s);
    return p;
}

static lista aggiungiListaInCoda(lista head, int numLista, const char *nomi[N]) {
    listacandidati *newn = (listacandidati*)malloc(sizeof(*newn));
    if (!newn) { perror("malloc"); exit(1); }

    newn->numLista = numLista;
    newn->next = NULL;

    /* alloco un array di N puntatori a char */
    newn->elenconomi = (elencocandidati)malloc(sizeof(nome) * N);
    if (!newn->elenconomi) { perror("malloc"); exit(1); }

    for (int i = 0; i < N; i++) {
        newn->elenconomi[i] = dupstr(nomi[i]);
    }

    if (!head) return newn;
    lista t = head;
    while (t->next) t = t->next;
    t->next = newn;
    return head;
}

static listascrutinio aggiungiSchedaInTesta(listascrutinio head, int numLista, const char *pref /* può essere NULL */) {
    scheda *s = (scheda*)malloc(sizeof(*s));
    if (!s) { perror("malloc"); exit(1); }
    s->numLista = numLista;
    s->preferenza = (pref ? dupstr(pref) : NULL);
    s->next = head;
    return s;
}

static void stampaListe(lista L) {
    printf("=== LISTE CANDIDATI ===\n");
    while (L) {
        printf("Lista %d:\n", L->numLista);
        for (int i = 0; i < N; i++) {
            printf("  - %s\n", L->elenconomi[i]);
        }
        L = L->next;
    }
}

static void stampaScrutinio(listascrutinio ls) {
    printf("=== SCHEDE SCRUTINATE ===\n");
    int k = 1;
    while (ls) {
        printf("Scheda %d: lista=%d, pref=%s\n",
               k++, ls->numLista, (ls->preferenza ? ls->preferenza : "NULL"));
        ls = ls->next;
    }
}

static void freeListe(lista L) {
    while (L) {
        lista nx = L->next;
        if (L->elenconomi) {
            for (int i = 0; i < N; i++) free(L->elenconomi[i]);
            free(L->elenconomi);
        }
        free(L);
        L = nx;
    }
}

static void freeScrutinio(listascrutinio ls) {
    while (ls) {
        listascrutinio nx = ls->next;
        free(ls->preferenza); /* ok anche se NULL */
        free(ls);
        ls = nx;
    }
}

/* ====== SUPPORTO per piuVotato ====== */
static lista trovaLista(lista L, int numLista) {
    while (L) {
        if (L->numLista == numLista) return L;
        L = L->next;
    }
    return NULL;
}

static int indiceCandidato(lista unaLista, const char *pref) {
    if (!unaLista || !pref) return -1;
    for (int i = 0; i < N; i++) {
        if (strcmp(unaLista->elenconomi[i], pref) == 0) return i;
    }
    return -1; /* preferenza non valida (nome non in lista) */
}

int trovavoti(char nomecandidato[], listascrutinio ls);
int main(void) {
    lista L = NULL;
    listascrutinio ls = NULL;

    const char *nomi0[N] = {"Rossi", "Bianchi", "Verdi", "Neri", "Gialli"};
    const char *nomi1[N] = {"Conti", "Marini", "Greco", "Costa", "Ferri"};

    L = aggiungiListaInCoda(L, 0, nomi0);
    L = aggiungiListaInCoda(L, 1, nomi1);

    /* Schede (alcune NULL o preferenze non valide) */
    ls = aggiungiSchedaInTesta(ls, 0, "Rossi");
    ls = aggiungiSchedaInTesta(ls, 0, "Rossi");
    ls = aggiungiSchedaInTesta(ls, 0, "Verdi");
    ls = aggiungiSchedaInTesta(ls, 0, NULL);
    ls = aggiungiSchedaInTesta(ls, 0, "NonEsiste"); /* non valida */

    ls = aggiungiSchedaInTesta(ls, 1, "Costa");
    ls = aggiungiSchedaInTesta(ls, 1, "Costa");
    ls = aggiungiSchedaInTesta(ls, 1, "Costa");
    ls = aggiungiSchedaInTesta(ls, 1, "Greco");
    ls = aggiungiSchedaInTesta(ls, 1, NULL);

    stampaListe(L);
    printf("\n");
    stampaScrutinio(ls);
    printf("\n");

    char vincitore[100];

    int pref0 = piuVotato(vincitore, 0, ls, L);
    printf("Lista 0: più votato = '%s' con %d preferenze\n", vincitore, pref0);

    int pref1 = piuVotato(vincitore, 1, ls, L);
    printf("Lista 1: più votato = '%s' con %d preferenze\n", vincitore, pref1);

    freeScrutinio(ls);
    freeListe(L);
    return 0;
}

int piuVotato(nome n, int numLista, listascrutinio ls, lista L)
    {
    lista listaspecifica=trovaLista(L, numLista);
    elencocandidati candidatilista=listaspecifica->elenconomi;
    int max=0;
    for(int i=0; i<N; i++)
        {
            int voti=trovavoti(candidatilista[i], ls);
                if(voti>max)
                {
                    max=voti;
                    strcpy(n, candidatilista[i]);
                }
        }
    return max;
    }
lista trovalista(lista elencoliste, int numlista)
    {
    if(elencoliste==NULL)
        return NULL;
    lista scorri=elencoliste;
    while (scorri!=NULL) {
        if(scorri->numLista==numlista)
            return scorri;
        scorri=scorri->next;
    }
    return NULL;
    }
int trovavoti(char nomecandidato[], listascrutinio ls)
    {
    listascrutinio scorri=ls;
    int count=0;
    while (scorri!=NULL) {
        if(scorri->preferenza!=NULL && strcmp(nomecandidato, scorri->preferenza)==0)
            count++;
        scorri=scorri->next;
    }
    return count;
    }
