//
//  main.c
//  tde 9 liste -11
//
//  Created by Francesco Roscio Ricon on 08/02/26.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE (ordinate correttamente)
   ========================= */
typedef struct { int giorno, mese, anno; } Data;
typedef struct { int ora, min, sec, milli; } Ora;

typedef struct n {
    char link[1000];
    Data d;
    Ora o;
    struct n *next;
} Visita;

typedef Visita *Visite;

typedef struct li {
    char link[1000];
    int visiteTotali;
    struct li *next;
} Statistica;

typedef Statistica *Statistiche;

/* =========================
   PROTOTIPO FUNZIONE ESERCIZIO (DA FARE)
   ========================= */
Statistiche calcola(Visite V);


static Visite nuovaVisita(const char *link, Data d, Ora o) {
    Visite v = (Visite)malloc(sizeof(*v));
    if (!v) { perror("malloc"); exit(1); }
    strncpy(v->link, link, sizeof(v->link) - 1);
    v->link[sizeof(v->link) - 1] = '\0';
    v->d = d;
    v->o = o;
    v->next = NULL;
    return v;
}

static Statistiche nuovaStat(const char *link, int tot) {
    Statistiche s = (Statistiche)malloc(sizeof(*s));
    if (!s) { perror("malloc"); exit(1); }
    strncpy(s->link, link, sizeof(s->link) - 1);
    s->link[sizeof(s->link) - 1] = '\0';
    s->visiteTotali = tot;
    s->next = NULL;
    return s;
}

/* inserimento in coda (comodo per mantenere l’ordine cronologico delle visite) */
static Visite pushVisita(Visite head, Visite x) {
    if (head == NULL) return x;
    Visite p = head;
    while (p->next) p = p->next;
    p->next = x;
    return head;
}

/* =========================
   STAMPA
   ========================= */
static void stampaDataOra(Data d, Ora o) {
    printf("%02d/%02d/%04d %02d:%02d:%02d.%03d",
           d.giorno, d.mese, d.anno, o.ora, o.min, o.sec, o.milli);
}

static void stampaVisite(Visite V) {
    printf("=== VISITE (cronologiche) ===\n");
    while (V) {
        printf("- %-30s | ", V->link);
        stampaDataOra(V->d, V->o);
        printf("\n");
        V = V->next;
    }
    printf("\n");
}

static void stampaStatistiche(Statistiche S) {
    printf("=== STATISTICHE ===\n");
    while (S) {
        printf("- %-30s | visiteTotali = %d\n", S->link, S->visiteTotali);
        S = S->next;
    }
    printf("\n");
}

/* =========================
   FREE
   ========================= */
static void freeVisite(Visite V) {
    while (V) {
        Visite nx = V->next;
        free(V);
        V = nx;
    }
}

static void freeStatistiche(Statistiche S) {
    while (S) {
        Statistiche nx = S->next;
        free(S);
        S = nx;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int trovato(Statistiche head, char link[]);
Statistiche inserisciincoda(Statistiche head, char link[], int visite_tot);
int contavisite(Visite lista_visite, char link[]);
int visitatonel2016(Visite V, char link[]);
int main(void) {
    Visite V = NULL;

    

    V = pushVisita(V, nuovaVisita("example.com", (Data){12, 12, 2015}, (Ora){10, 15,  0, 123}));
    V = pushVisita(V, nuovaVisita("example.com", (Data){ 3,  1, 2016}, (Ora){ 9,  5, 12,  10}));
    V = pushVisita(V, nuovaVisita("openai.com",  (Data){20,  2, 2016}, (Ora){18, 30,  0,   0}));
    V = pushVisita(V, nuovaVisita("example.com", (Data){ 1,  3, 2017}, (Ora){12,  0,  0,   1}));
    V = pushVisita(V, nuovaVisita("uni.it",      (Data){10, 10, 2016}, (Ora){ 8,  0,  0,   0}));
    V = pushVisita(V, nuovaVisita("uni.it",      (Data){11, 10, 2016}, (Ora){ 8,  0,  1,   0}));
    V = pushVisita(V, nuovaVisita("altro.org",   (Data){ 5,  5, 2018}, (Ora){16, 45, 33, 500}));

    stampaVisite(V);

    Statistiche S = calcola(V);
    stampaStatistiche(S);

    printf("(Nota: l’output dipende dalla tua implementazione.\n");
    printf("Con l’interpretazione tipica, dovrebbero comparire almeno:\n");
    printf("- example.com (visitato nel 2016) con visiteTotali=3\n");
    printf("- openai.com  (visitato nel 2016) con visiteTotali=1\n");
    printf("- uni.it      (visitato nel 2016) con visiteTotali=2\n");
    printf("altro.org NON compare perche' mai visitato nel 2016)\n\n");

    freeStatistiche(S);
    freeVisite(V);
    return 0;
}
int visitatonel2016(Visite V, char link[])
    {
        if(V==NULL)
            return 0;
    while (V!=NULL) {
        if(strcmp(V->link, link)==0 && V->d.anno==2016)
            return 1;
        V=V->next;
    }
    return 0;
    }



int contavisite(Visite lista_visite, char link[])
    {
    int count=0;
    if(lista_visite==NULL)
        return 0;
    Visite scorri=lista_visite;
    while (scorri!=NULL) {
        if(strcmp(scorri->link, link)==0)
            count++;
        scorri=scorri->next;
    }
    return count;
    }
Statistiche inserisciincoda(Statistiche head, char link[], int visite_tot)
    {
        if(head==NULL)
            {
                Statistiche new=(Statistiche)malloc(sizeof(*new));
                new->next=head;
                strcpy(new->link, link);
                new->visiteTotali=visite_tot;
                return new;
            }
    head->next=inserisciincoda(head->next, link, visite_tot);
    return head;
    }
int trovato(Statistiche head, char link[])
    {
        if(head==NULL)
            return 0;
    Statistiche scorri=head;
    while (scorri!=NULL) {
        if(strcmp(link, scorri->link)==0)
            return 1;
        scorri=scorri->next;
        }
    return 0;
    }
Statistiche calcola(Visite V)
    {
    Statistiche new=NULL;
    if(V==NULL)
        return new;
    Visite scorri=V;
        while (scorri!=NULL) {
            if(trovato(new, scorri->link)==0 && visitatonel2016(V, scorri->link))
                {
                    int conta=contavisite(V, scorri->link);
                    new=inserisciincoda(new, scorri->link, conta);
                }
            scorri=scorri->next;
        }
    return new;
    }
