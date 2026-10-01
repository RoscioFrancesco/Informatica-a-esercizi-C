//
//  main.c
//  tde carta tde 3 liste -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct { int giorno, mese, anno; } Data;

typedef struct BEL {
    char nome[N];          /* unico per ogni birra */
    int gradoAlcolico;
    char descrizione[N];
    struct BEL *next;
} Birra;

typedef struct DEL {
    char nome[N];
    Data data;
    Birra *Birre;          /* lista birre della degustazione */
    struct DEL *next;
} Degustazione;

typedef Degustazione* Degustazioni;



Degustazioni f(Degustazioni *D, int limite); /* TODO */

/* =========================
   UTILITY (per test: cicli OK)
   ========================= */
static Birra* newBirra(const char *nome, int grado, const char *desc, Birra *next) {
    Birra *b = (Birra*)malloc(sizeof(Birra));
    if (!b) { perror("malloc"); exit(1); }
    strncpy(b->nome, nome, N-1); b->nome[N-1] = '\0';
    b->gradoAlcolico = grado;
    strncpy(b->descrizione, desc, N-1); b->descrizione[N-1] = '\0';
    b->next = next;
    return b;
}

static Degustazione* newDeg(const char *nome, Data d, Birra *birre, Degustazione *next) {
    Degustazione *x = (Degustazione*)malloc(sizeof(Degustazione));
    if (!x) { perror("malloc"); exit(1); }
    strncpy(x->nome, nome, N-1); x->nome[N-1] = '\0';
    x->data = d;
    x->Birre = birre;
    x->next = next;
    return x;
}

static void printBirre(Birra *b) {
    printf("[");
    while (b != NULL) {
        printf("%s(%d)", b->nome, b->gradoAlcolico);
        if (b->next) printf(", ");
        b = b->next;
    }
    printf("]");
}

static void printDegustazioni(const char *title, Degustazioni d) {
    printf("%s\n", title);
    if (d == NULL) { printf("(vuota)\n"); return; }
    while (d != NULL) {
        printf("- %s | %02d/%02d/%04d | birre=",
               d->nome, d->data.giorno, d->data.mese, d->data.anno);
        printBirre(d->Birre);
        printf("\n");
        d = d->next;
    }
}

static void freeBirre(Birra *b) {
    while (b != NULL) {
        Birra *tmp = b->next;
        free(b);
        b = tmp;
    }
}

/* libera UNA degustazione (e la sua lista birre) */
static void freeDegustazioneNode(Degustazione *d) {
    if (!d) return;
    freeBirre(d->Birre);
    free(d);
}

/* libera un'intera lista degustazioni (con birre) */
static void freeDegustazioni(Degustazioni d) {
    while (d != NULL) {
        Degustazione *tmp = d->next;
        freeDegustazioneNode(d);
        d = tmp;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int ver_tasso(Degustazione singola, int max);
int ver_data(Degustazione singola);
void distruggibirre(Degustazioni temp);
Birra *copiabirre(Birra *lista, Birra x);
Degustazioni inserisciincoda(Degustazioni head, Degustazione x);
int main(void) {
    int limite = 8;

    /* Costruisco alcune degustazioni (inserimento in testa per comodità) */

    /* Degustazione A: GEN 2016, contiene birra > limite -> deve essere estratta */
    Birra *birreA = NULL;
    birreA = newBirra("StoutX", 10, "stout strong", birreA);
    birreA = newBirra("LagerA", 5, "lager", birreA);
    Degustazioni A = newDeg("Deg-A", (Data){10, 1, 2016}, birreA, NULL);

    /* Degustazione B: GEN 2016, ma tutte <= limite -> resta in D */
    Birra *birreB = NULL;
    birreB = newBirra("PilsB", 6, "pils", birreB);
    Degustazioni B = newDeg("Deg-B", (Data){20, 1, 2016}, birreB, NULL);

    /* Degustazione C: FEB 2016, anche se > limite -> NON è gennaio -> resta in D */
    Birra *birreC = NULL;
    birreC = newBirra("TripelC", 9, "tripel", birreC);
    Degustazioni C = newDeg("Deg-C", (Data){5, 2, 2016}, birreC, NULL);

    /* Degustazione D: GEN 2015, > limite -> NON anno 2016 -> resta in D */
    Birra *birreD = NULL;
    birreD = newBirra("BarleyD", 12, "barley wine", birreD);
    Degustazioni Dd = newDeg("Deg-D", (Data){15, 1, 2015}, birreD, NULL);

    /* Lista D totale */
    Degustazioni D = NULL;
    D = newDeg("Deg-D", (Data){15, 1, 2015}, birreD, D);
    D = newDeg("Deg-C", (Data){ 5, 2, 2016}, birreC, D);
    D = newDeg("Deg-B", (Data){20, 1, 2016}, birreB, D);
    D = newDeg("Deg-A", (Data){10, 1, 2016}, birreA, D);

    printDegustazioni("PRIMA (lista D):", D);

    
    Degustazioni estratte = f(&D, limite);

    printf("\nLimite grado alcolico = %d\n\n", limite);
    printDegustazioni("ESTRATTE (gennaio 2016 con almeno una birra > limite):", estratte);
    printDegustazioni("\nDOPO (lista D rimanente):", D);

    /* Importante: ora ci sono D e estratte, entrambe da liberare */
    freeDegustazioni(D);
    freeDegustazioni(estratte);

    return 0;
}

//typedef struct BEL {
//    char nome[N];          /* unico per ogni birra */
//    int gradoAlcolico;
//    char descrizione[N];
//    struct BEL *next;
//} Birra;
//
//typedef struct DEL {
//    char nome[N];
//    Data data;
//    Birra *Birre;          /* lista birre della degustazione */
//    struct DEL *next;
//} Degustazione;
//
//typedef Degustazione* Degustazioni;

// quindi restituisco una sita di quelle che non vanno bene ed elimino ognuna di queste dalla degustazioni

Degustazioni f(Degustazioni * D, int limite)
    {
    Degustazioni elencodegustaz=*D;
    Degustazioni scorri_degustazioni=elencodegustaz;
    Degustazioni prec=NULL;
    Degustazioni new=NULL;
    while(scorri_degustazioni!=NULL)
        {
            Degustazioni succ=scorri_degustazioni->next;
            if(ver_data(*scorri_degustazioni) && ver_tasso(*scorri_degustazioni, limite))
                {
                    new=inserisciincoda(new, *scorri_degustazioni);
                    if(prec==NULL)
                        {
                            *D=succ;
                            Degustazioni temp=scorri_degustazioni;
                            distruggibirre(temp);
                            free(scorri_degustazioni);
                            scorri_degustazioni=succ;
                        }
                    else
                        {
                            prec->next=succ;
                            Degustazioni temp=scorri_degustazioni;
                            distruggibirre(temp);
                            free(scorri_degustazioni);
                            scorri_degustazioni=succ;
                        }
                }
            else
                {
                    prec=scorri_degustazioni;
                    scorri_degustazioni=succ;
                }
        }
        return new;
    }

int ver_tasso(Degustazione singola, int max)
    {
    Birra   *scorribirre=singola.Birre;
    while (scorribirre!=NULL) {
        if(scorribirre->gradoAlcolico>max)
            {
                return 1;
            }
        scorribirre=scorribirre->next;
        }
    return 0;
    }
int ver_data(Degustazione singola)
    {
        if(singola.data.anno==2016 && singola.data.mese==01)
            return 1;
    return 0;
    }
void distruggibirre(Degustazioni temp)
    {
    Birra *scorri=temp->Birre;
    while(scorri!=NULL)
        {
            Birra * temp2=scorri->next;
            free(scorri);
            scorri=temp2;
        }
        temp->Birre = NULL;
    }
Birra *copiaListaBirre(Birra *b)
{
    if (b == NULL) return NULL;

    Birra *n = (Birra*)malloc(sizeof(*n));
    *n = *b;                 // copia i campi
    n->next = copiaListaBirre(b->next);
    return n;
}

Degustazioni inserisciincoda(Degustazioni head, Degustazione x)
{
    if (head == NULL) {
        Degustazioni new = (Degustazioni)malloc(sizeof(*new));
        new->data = x.data;
        strcpy(new->nome, x.nome);
        new->Birre = copiaListaBirre(x.Birre);
        new->next = NULL;
        return new;
    }
    head->next = inserisciincoda(head->next, x);
    return head;
}
