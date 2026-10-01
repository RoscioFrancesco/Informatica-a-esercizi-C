//
//  main.c
//  tde 4 alberi -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

/* =====================
   STRUTTURE DATI (da testo)
   ===================== */
typedef struct Date { int giorno; int mese; int anno; } Data;

typedef struct {
    char cognome[N], nome[N];
    int eta; /* età della persona */
} Persona;

typedef struct Item {
    Persona p;
    int punti;              /* iniziale indefinito nel testo */
    struct Item *next;
} Socio;

typedef Socio *ListaDiSoci;

typedef struct Node {
    Data d;
    Persona *ordineDiArrivo; /* nel testo è Persona*, ma è "lista" */
    struct Node *next;
} Maratona;

typedef Maratona *ListaDiMaratone;

/* =====================
   RAPPRESENTAZIONE "LISTA" PER ordineDiArrivo (solo per test)
   - nel campo ordineDiArrivo salviamo (Persona*)headArrivi
   ===================== */
typedef struct PersonaNode {
    Persona p;
    struct PersonaNode *next;
} PersonaNode;

typedef PersonaNode *ListaArrivi;

/* helper cast per chiarezza */
static ListaArrivi asListaArrivi(Persona *x) { return (ListaArrivi)x; }
static Persona *asPersonaPtr(ListaArrivi x) { return (Persona *)x; }


int assegnaPuntiEetaMax(ListaDiSoci soci, ListaDiMaratone maratone);

/* =====================
   UTILITY PER CREARE DATI DI TEST
   ===================== */
static Socio *nuovoSocio(const char *cognome, const char *nome, int eta) {
    Socio *s = (Socio *)malloc(sizeof(Socio));
    if (!s) { perror("malloc"); exit(1); }
    strncpy(s->p.cognome, cognome, N-1); s->p.cognome[N-1] = '\0';
    strncpy(s->p.nome, nome, N-1); s->p.nome[N-1] = '\0';
    s->p.eta = eta;
    s->punti = -999; /* valore finto per vedere se la funzione li assegna */
    s->next = NULL;
    return s;
}

static ListaDiSoci inserisciSocioInCoda(ListaDiSoci head, Socio *s) {
    if (head == NULL) return s;
    Socio *cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = s;
    return head;
}

static PersonaNode *nuovoArrivo(const char *cognome, const char *nome, int eta) {
    PersonaNode *n = (PersonaNode *)malloc(sizeof(PersonaNode));
    if (!n) { perror("malloc"); exit(1); }
    strncpy(n->p.cognome, cognome, N-1); n->p.cognome[N-1] = '\0';
    strncpy(n->p.nome, nome, N-1); n->p.nome[N-1] = '\0';
    n->p.eta = eta;
    n->next = NULL;
    return n;
}

static ListaArrivi inserisciArrivoInCoda(ListaArrivi head, PersonaNode *n) {
    if (head == NULL) return n;
    PersonaNode *cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return head;
}

static Maratona *nuovaMaratona(int g, int m, int a, ListaArrivi arrivi) {
    Maratona *mar = (Maratona *)malloc(sizeof(Maratona));
    if (!mar) { perror("malloc"); exit(1); }
    mar->d.giorno = g; mar->d.mese = m; mar->d.anno = a;
    mar->ordineDiArrivo = asPersonaPtr(arrivi); /* cast per rispettare il tipo del testo */
    mar->next = NULL;
    return mar;
}

static ListaDiMaratone inserisciMaratonaInCoda(ListaDiMaratone head, Maratona *m) {
    if (head == NULL) return m;
    Maratona *cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = m;
    return head;
}

/* =====================
   STAMPE
   ===================== */
static void stampaSoci(ListaDiSoci s) {
    printf("=== SOCI ===\n");
    while (s != NULL) {
        printf("%s %s (eta %d) | punti=%d\n", s->p.nome, s->p.cognome, s->p.eta, s->punti);
        s = s->next;
    }
}

static void stampaArrivi(ListaArrivi a) {
    int pos = 1;
    while (a != NULL) {
        printf("  %2d) %s %s (eta %d)\n", pos, a->p.nome, a->p.cognome, a->p.eta);
        a = a->next;
        pos++;
    }
}

static void stampaMaratone(ListaDiMaratone m) {
    printf("=== MARATONE ===\n");
    while (m != NULL) {
        printf("Maratona %02d/%02d/%04d\n", m->d.giorno, m->d.mese, m->d.anno);
        printf("Ordine di arrivo:\n");
        stampaArrivi(asListaArrivi(m->ordineDiArrivo));
        m = m->next;
    }
}

/* =====================
   FREE
   ===================== */
static void liberaArrivi(ListaArrivi a) {
    while (a != NULL) {
        PersonaNode *tmp = a;
        a = a->next;
        free(tmp);
    }
}

static void liberaMaratone(ListaDiMaratone m) {
    while (m != NULL) {
        Maratona *tmp = m;
        m = m->next;
        liberaArrivi(asListaArrivi(tmp->ordineDiArrivo));
        free(tmp);
    }
}

static void liberaSoci(ListaDiSoci s) {
    while (s != NULL) {
        Socio *tmp = s;
        s = s->next;
        free(tmp);
    }
}

/* =====================
   MAIN DI TEST
   ===================== */
int main() {
    ListaDiSoci soci = NULL;
    ListaDiMaratone maratone = NULL;

    /* Soci */
    soci = inserisciSocioInCoda(soci, nuovoSocio("Rossi",   "Mario", 30));
    soci = inserisciSocioInCoda(soci, nuovoSocio("Bianchi", "Luca",  24));
    soci = inserisciSocioInCoda(soci, nuovoSocio("Verdi",   "Anna",  28));
    soci = inserisciSocioInCoda(soci, nuovoSocio("Neri",    "Paolo", 35));

    /* Maratona 1: 10 punti al 1°, ... 1 punto al 10° (qui metto 4 arrivi) */
    ListaArrivi a1 = NULL;
    a1 = inserisciArrivoInCoda(a1, nuovoArrivo("Rossi",   "Mario", 30)); /* 1° */
    a1 = inserisciArrivoInCoda(a1, nuovoArrivo("Verdi",   "Anna",  28)); /* 2° */
    a1 = inserisciArrivoInCoda(a1, nuovoArrivo("Bianchi", "Luca",  24)); /* 3° */
    a1 = inserisciArrivoInCoda(a1, nuovoArrivo("Neri",    "Paolo", 35)); /* 4° */
    maratone = inserisciMaratonaInCoda(maratone, nuovaMaratona(10, 3, 2025, a1));

    /* Maratona 2 */
    ListaArrivi a2 = NULL;
    a2 = inserisciArrivoInCoda(a2, nuovoArrivo("Verdi",   "Anna",  28)); /* 1° */
    a2 = inserisciArrivoInCoda(a2, nuovoArrivo("Neri",    "Paolo", 35)); /* 2° */
    a2 = inserisciArrivoInCoda(a2, nuovoArrivo("Rossi",   "Mario", 30)); /* 3° */
    maratone = inserisciMaratonaInCoda(maratone, nuovaMaratona(21, 4, 2025, a2));

    printf("\nPRIMA:\n");
    stampaSoci(soci);
    printf("\n");
    stampaMaratone(maratone);

    /* Funzione da svolgere */
    int etaMax = assegnaPuntiEetaMax(soci, maratone);

    printf("\nDOPO assegnaPuntiEetaMax:\n");
    stampaSoci(soci);
    printf("\nEta del socio con piu' punti (stub ora): %d\n", etaMax);

    liberaMaratone(maratone);
    liberaSoci(soci);
    return 0;
}

/* =====================
   STUB (NON SVOLTO)
   ===================== */
int assegnaPuntiEetaMax(ListaDiSoci soci, ListaDiMaratone maratone) {
    
    (void)soci;
    (void)maratone;
    return -1; /* valore finto */
}
ListaDiSoci aggiungiputialsocio(ListaDiSoci head, int punteggio, Persona socio)
    {
        if(head==NULL)
            return head;
    ListaDiSoci scorri=head;
    while (scorri!=NULL) {
        if(strcmp(scorri->p.cognome,socio.cognome)==0 && strcmp(scorri->p.nome, socio.nome)==0 && socio.eta==scorri->p.eta)
            {
                scorri->punti=scorri->punti+punteggio;
            }
        scorri=scorri->next;
    }
    return head;
    }
int etàsocioconpiùpunti(ListaDiSoci head)
    {
        if(head==NULL)
            return 0;
    ListaDiSoci scorri=head;
    int maxpunti=0;
    int età=0;
    while (scorri!=NULL) {
        if(scorri->punti>maxpunti)
            {
                maxpunti=scorri->punti;
                età=scorri->p.eta;
            }
        scorri=scorri->next;
    }
    return età;
    }

int f(ListaDiSoci soci, ListaDiMaratone maratone)
    {
        if(soci==NULL || maratone==NULL)
            return 0;
    ListaDiMaratone scorri_maratone=maratone;
    while (scorri_maratone!=NULL) {
        Persona *scorriarrivi=scorri_maratone->ordineDiArrivo;
        for(int i=10; i>0; i--)
            {
                soci=aggiungiputialsocio(soci, i, *scorriarrivi);
            }
        scorri_maratone=scorri_maratone->next;
    }
    }
