//
//  main.c
//  liste rifaccio n2 chat
//
//  Created by Francesco Roscio Ricon on 30/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =======================
   STRUTTURA LISTA PAROLE
   ======================= */
typedef struct Node {
    char *word;          // stringa allocata dinamicamente
    struct Node *next;
} Node;

typedef Node* Lista;
Lista EliminadaAA(Lista l);
Lista EliminafinoaBB(Lista l);
int SENT(char parola[]);
int PREF(char parola[]);
/* =======================
   UTILITY (per test)
   - Qui i cicli sono OK (serve solo per costruire/stampare)
   ======================= */

static char* my_strdup(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s);
    char *d = (char*)malloc(n + 1);
    if (!d) { perror("malloc"); exit(1); }
    memcpy(d, s, n + 1);
    return d;
}

static Node* newNode(const char *w, Node *next) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->word = my_strdup(w);
    n->next = next;
    return n;
}

static Lista buildListFromArray(const char *arr[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; --i) {
        l = newNode(arr[i], l);
    }
    return l;
}

static void printList(Lista l) {
    printf("[");
    for (Node *p = l; p != NULL; p = p->next) {
        printf("\"%s\"", p->word);
        if (p->next) printf(" -> ");
    }
    printf("]\n");
}

static void freeList(Lista l) {
    while (l != NULL) {
        Node *tmp = l;
        l = l->next;
        free(tmp->word);
        free(tmp);
    }
}

/* =======================
   ESERCIZIO E2 (TODO)
   ======================= */
/*
  TODO: Quando incontri una parola che inizia con PREF,
  elimina il blocco da quel nodo fino alla prima parola uguale a SENT (inclusa).
  Se SENT non compare, elimina fino a fine lista.
  Deve poter eliminare più blocchi disgiunti.
  Vietati cicli nella soluzione.
*/
Lista eliminaBlocchiPrefSentina(Lista l, const char *PREF, const char *SENT);

/* =======================
   FUNZIONE DI TEST
   ======================= */
static void testCase(const char *title, const char *PREF, const char *SENT,
                     const char *arr[], int n) {
    printf("=== %s ===\n", title);
    printf("PREF=\"%s\"  SENT=\"%s\"\n", PREF, SENT);

    Lista L = buildListFromArray(arr, n);

    printf("Prima : ");
    printList(L);

    L=EliminadaAA(L);

    printf("Dopo  : ");
    printList(L);

    freeList(L);
    printf("\n");
}



int main(void) {
    const char *PREF = "PRE";
    const char *SENT = "STOP";

    /* Caso 0: lista vuota */
    {
        const char **arr = NULL;
        testCase("Caso 0: lista vuota", PREF, SENT, arr, 0);
    }

    /* Caso 1: PREF in testa, SENT presente dopo */
    {
        const char *arr[] = {"PREstart", "x", "y", "STOP", "tail1", "tail2"};
        testCase("Caso 1: PREF in testa, SENT presente", PREF, SENT, arr, 6);
    }

    /* Caso 2: blocco minimo (PREF subito seguito da SENT) */
    {
        const char *arr[] = {"a", "PREone", "STOP", "b"};
        testCase("Caso 2: blocco minimo PRE... STOP", PREF, SENT, arr, 4);
    }

    /* Caso 3: SENT non compare dopo l'inizio del blocco -> elimina fino a fine lista */
    {
        const char *arr[] = {"a", "b", "PREcut", "x", "y", "z"};
        testCase("Caso 3: SENT assente dopo PREF (taglia fino a fine)", PREF, SENT, arr, 6);
    }

    /* Caso 4: più blocchi disgiunti (due blocchi completi) */
    {
        const char *arr[] = {
            "a", "PRE1", "m", "STOP", "keep",
            "PRE2", "x", "y", "STOP", "end"
        };
        testCase("Caso 4: due blocchi disgiunti completi", PREF, SENT, arr, 10);
    }

    /* Caso 5: PREF appare dentro la parola ma NON come prefisso (non deve attivare) */
    {
        const char *arr[] = {"a", "XPREfake", "b", "PREreal", "STOP", "c"};
        testCase("Caso 5: PREF deve essere prefisso vero (XPREfake non vale)", PREF, SENT, arr, 6);
    }

    /* Caso 6: STOP prima di un PREF (STOP fuori blocco non conta) */
    {
        const char *arr[] = {"STOP", "a", "PREgo", "x", "STOP", "tail"};
        testCase("Caso 6: STOP prima del PREF, poi blocco normale", PREF, SENT, arr, 6);
    }

    /* Caso 7: due PREF consecutivi prima della sentinella:
       il blocco parte dal primo PREF e si chiude al primo STOP */
    {
        const char *arr[] = {"a", "PREa", "PREb", "x", "STOP", "tail"};
        testCase("Caso 7: PREF consecutivi nello stesso blocco", PREF, SENT, arr, 6);
    }

    /* Caso 8: PREF come unico elemento (SENT mancante, taglia tutto) */
    {
        const char *arr[] = {"PREsolo"};
        testCase("Caso 8: solo PREF (SENT mancante, elimina fino a fine)", PREF, SENT, arr, 1);
    }

    return 0;
}

/*
  TODO: Quando incontri una parola che inizia con PREF,
  elimina il blocco da quel nodo fino alla prima parola uguale a SENT (inclusa).
  Se SENT non compare, elimina fino a fine lista.
  Deve poter eliminare più blocchi disgiunti.
  Vietati cicli nella soluzione.
*/

int PREF(char parola[])
    {
        if(strlen(parola)<3)
            return 0;
        if(parola[0]=='P' && parola[1]=='R' && parola[2]=='E')
            return 1;
        return 0;
    }
int SENT(char parola[])
    {
    int len=strlen(parola);
        if(len<4)
            return 0;
    if(parola[len-1]=='P' && parola[len-2]=='O' && parola[len-3]=='T' && parola[len-4]=='S')
        return 1;
    return 0;
    }
Lista EliminafinoaBB(Lista l)
    {
        if(l==NULL)
            return NULL;
        int stop=SENT(l->word);
        Lista next=l->next;
        free(l->word);
        free(l);
        if(stop)
            return next;
    return EliminafinoaBB(next);
    }
Lista EliminadaAA(Lista l)
    {
        if(l==NULL)
            return l;
        if(PREF(l->word))
            {
                l->next=EliminafinoaBB(l->next);
                if(l->next!=NULL)
                    return EliminadaAA(l->next);
                return l;
            }
        l->next=EliminadaAA(l->next);
        return l;
    }
