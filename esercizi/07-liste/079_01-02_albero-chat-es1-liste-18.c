//
//  main.c
//  albero chat es1 liste -18
//
//  Created by Francesco Roscio Ricon on 01/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUTTURE DATI
   ========================= */

typedef struct Node {
    char *word;           // stringa allocata dinamicamente
    struct Node *next;
} Node;

typedef Node* Lista;

typedef struct {
    int blocchi_eliminati;
    int parole_eliminate;
} Stats;

/* =========================
   PROTOTIPI (utility)
   ========================= */

static char* str_dup(const char *s);
static Node* newNode(const char *s, Node *next);

static Lista buildFromArrayRec(const char *arr[], int n, int i);
static void printListaRec(Lista l);
static void freeListaRec(Lista l);

/* =========================
   PROTOTIPO ESERCIZIO (DA FARE)
   =========================
   Elimina ogni blocco massimale di parole con lunghezza in [Lmin, Lmax],
   eliminando il blocco "in un colpo" (saltando tutta la sequenza),
   e ritorna la nuova testa; le statistiche vengono restituite tramite Stats.
*/
Lista eliminaBlocchiPerLunghezza(Lista head, int Lmin, int Lmax, Stats *outStats);

/* =========================
   MAIN DI TEST
   ========================= */
Lista f(Lista start, int Lmin, int Lmax, Stats *stats);
int main(void) {
    /* Esempio: blocchi dentro [Lmin, Lmax] da eliminare
       (scegli tu Lmin/Lmax per far cadere certe parole nell'intervallo).
       Qui sotto hai sequenze consecutive che possono formare blocchi.
    */
    const char *parole[] = {
        "a", "bbb", "cccc",          // possibile blocco
        "X",                         // separatore (fuori intervallo)
        "dddd", "ee", "fffff",       // possibile blocco
        "ok",
        "zz", "yyy",                 // possibile blocco
        "fine"
    };
    int n = (int)(sizeof(parole) / sizeof(parole[0]));

    Lista head = buildFromArrayRec(parole, n, 0);

    int Lmin = 2;
    int Lmax = 4;

    printf("Lista iniziale:\n");
    printListaRec(head);
    printf("\n");

    Stats st = {0, 0};

    
    head = eliminaBlocchiPerLunghezza(head, Lmin, Lmax, &st);

    printf("Lista dopo eliminaBlocchiPerLunghezza(Lmin=%d, Lmax=%d):\n", Lmin, Lmax);
    printListaRec(head);
    printf("\n");

    printf("Statistiche:\n");
    printf(" - blocchi eliminati: %d\n", st.blocchi_eliminati);
    printf(" - parole eliminate : %d\n", st.parole_eliminate);

    freeListaRec(head);
    return 0;
}



static char* str_dup(const char *s) {
    if (s == NULL) return NULL;
    size_t len = strlen(s);
    char *out = (char*)malloc(len + 1);
    if (!out) {
        fprintf(stderr, "malloc fallita\n");
        exit(1);
    }
    memcpy(out, s, len + 1);
    return out;
}

static Node* newNode(const char *s, Node *next) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) {
        fprintf(stderr, "malloc fallita\n");
        exit(1);
    }
    n->word = str_dup(s);
    n->next = next;
    return n;
}

/* Costruisce una lista da un array di stringhe, ricorsivamente */
static Lista buildFromArrayRec(const char *arr[], int n, int i) {
    if (i >= n) return NULL;
    return newNode(arr[i], buildFromArrayRec(arr, n, i + 1));
}

static void printListaRec(Lista l) {
    if (l == NULL) {
        printf("NULL");
        return;
    }
    printf("\"%s\"", l->word ? l->word : "(null)");
    if (l->next != NULL) {
        printf(" -> ");
        printListaRec(l->next);
    } else {
        printf(" -> NULL");
    }
}

static void freeListaRec(Lista l) {
    if (l == NULL) return;
    freeListaRec(l->next);
    free(l->word);
    free(l);
}

/* =========================
   STUB ESERCIZIO (NON SVOLTO)
   ========================= */
/* =========================
   PROTOTIPO ESERCIZIO (DA FARE)
   =========================
   Elimina ogni blocco massimale di parole con lunghezza in [Lmin, Lmax],
   eliminando il blocco "in un colpo" (saltando tutta la sequenza),
   e ritorna la nuova testa; le statistiche vengono restituite tramite Stats.
*/
void blocco(Lista start, Lista *finish, int *count, int Lmin, int Lmax)
    {
        if(*finish==NULL)
            return;
        int len=strlen((*finish)->word);
        if(len<Lmin || len>Lmax)
            return;
    (*count)++;
    (*finish)=(*finish)->next;
    blocco(start,finish, count, Lmin, Lmax);
    }
Lista eliminafinoafinish(Lista head, Lista finish)
    {
        if(head==NULL)
            return head;
        if(head==finish)
            return finish;
        Lista temP=head->next;
        free(head->word);
        free(head);
    return eliminafinoafinish(temP, finish);
    }
Lista f(Lista start, int Lmin, int Lmax, Stats *stats)
    {
        if(start==NULL)
            return start;
    int len=strlen(start->word);
    if(len>=Lmin && len<=Lmax)
        {
            Lista finish=start;
            int count=0;
            blocco(start, &finish, &count, Lmin, Lmax);
            Lista nuova=eliminafinoafinish(start, finish);
            (*stats).blocchi_eliminati++;
            (*stats).parole_eliminate=(*stats).parole_eliminate+count;
            return f(nuova, Lmin, Lmax, stats);
        }
    start->next=f(start->next, Lmin, Lmax, stats);
    return  start;
    }
Lista eliminaBlocchiPerLunghezza(Lista head, int Lmin, int Lmax, Stats *outStats)
    {
    return f(head, Lmin, Lmax, outStats);
    }
