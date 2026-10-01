//  Created by Francesco Roscio Ricon on 30/01/26.

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

/* =======================
   UTILITY (NO VINCOLI QUI)
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

/* Costruisce una lista da array di stringhe (usa ciclo SOLO nel main/utility) */
static Lista buildListFromArray(const char *arr[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; --i) {
        l = newNode(arr[i], l);
    }
    return l;
}

static void printList(Lista l) {
    printf("[");
    while (l != NULL) {
        printf("\"%s\"", l->word);
        l = l->next;
        if (l) printf(" -> ");
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
  TODO (DA SVOLGERE): elimina blocchi da nodo che inizia con prefisso PREF
  fino alla prima parola uguale a SENT (inclusa). Se SENT non c’è, fino a fine.
  Deve poter eliminare più blocchi disgiunti in una sola scansione ricorsiva.
  Vietati cicli nella soluzione.
*/
Lista eliminaBlocchiPrefSentina(Lista l, const char *PREF, const char *SENT);

/* =======================
   MAIN + CASI DI TEST
   ======================= */
Lista eliminaFinoASent(Lista l);
int main(void) {
    const char *PREF = "PRE";
    const char *SENT = "STOP";

    /* Caso 0: lista vuota */
    {
        Lista L = NULL;
        printf("Caso 0 (lista vuota)\nIN : "); printList(L);
        /* L = eliminaBlocchiPrefSentina(L, PREF, SENT); */
        printf("OUT: "); printList(L);
        freeList(L);
        printf("\n");
    }

    
    {
        const char *arr[] = {"PREstart", "x", "y", "STOP", "tail1", "tail2"};
        Lista L = buildListFromArray(arr, 6);
        printf("Caso 1 (PREF in testa, SENT presente)\nIN : "); printList(L);
        /* L = eliminaBlocchiPrefSentina(L, PREF, SENT); */
        printf("OUT: "); printList(L);
        freeList(L);
        printf("\n");
    }

    /*
      Caso 2: blocco di un solo elemento (PREF e SENT coincidono come nodo singolo?)
      Qui il nodo con prefisso è anche la sentinella esatta? NO, sentinella richiede parola uguale a SENT.
      Quindi usiamo: "PRE..." seguito subito da "STOP" -> blocco di 2 nodi
    */
    {
        const char *arr[] = {"a", "PREone", "STOP", "b", "c"};
        Lista L = buildListFromArray(arr, 5);
        printf("Caso 2 (blocco minimo: PRE... poi STOP)\nIN : "); printList(L);
        /* L = eliminaBlocchiPrefSentina(L, PREF, SENT); */
        printf("OUT: "); printList(L);
        freeList(L);
        printf("\n");
    }

    /*
      Caso 3: SENT non compare dopo l’inizio del blocco -> elimina fino a fine lista
    */
    {
        const char *arr[] = {"a", "b", "PREcut", "x", "y", "z"};
        Lista L = buildListFromArray(arr, 6);
        printf("Caso 3 (SENT assente dopo PREF -> elimina fino a fine)\nIN : "); printList(L);
        /* L = eliminaBlocchiPrefSentina(L, PREF, SENT); */
        printf("OUT: "); printList(L);
        freeList(L);
        printf("\n");
    }

    
    {
        const char *arr[] = {
            "a", "PRE1", "m", "STOP", "keep",
            "PRE2", "x", "y", "STOP", "end"
        };
        Lista L = buildListFromArray(arr, 10);
        printf("Caso 4 (piu blocchi disgiunti)\nIN : "); printList(L);
        /* L = eliminaBlocchiPrefSentina(L, PREF, SENT); */
        printf("OUT: "); printList(L);
        freeList(L);
        printf("\n");
    }

    /*
      Caso 5: parola che contiene "PRE" ma NON come prefisso (non deve scattare)
      Es: "XPRE..." non inizia con PREF.
    */
    {
        const char *arr[] = {"a", "XPREfake", "b", "PREreal", "STOP", "c"};
        Lista L = buildListFromArray(arr, 6);
        printf("Caso 5 (PREF deve essere prefisso vero)\nIN : "); printList(L);
        /* L = eliminaBlocchiPrefSentina(L, PREF, SENT); */
        printf("OUT: "); printList(L);
        freeList(L);
        printf("\n");
    }

    /*
      Caso 6: STOP prima di PRE (STOP fuori blocco non conta)
    */
    {
        const char *arr[] = {"a", "STOP", "b", "PREgo", "x", "STOP", "c"};
        Lista L = buildListFromArray(arr, 7);
        printf("Caso 6 (STOP prima di PRE, poi blocco normale)\nIN : "); printList(L);
        /* L = eliminaBlocchiPrefSentina(L, PREF, SENT); */
        printf("OUT: "); printList(L);
        freeList(L);
        printf("\n");
    }

    /*
      Caso 7: due PREF consecutivi prima della sentinella
      Deve partire dal primo PREF e cancellare tutto fino al primo STOP incluso.
    */
    {
        const char *arr[] = {"a", "PREa", "PREb", "x", "STOP", "tail"};
        Lista L = buildListFromArray(arr, 6);
        printf("Caso 7 (PREF consecutivi nello stesso blocco)\nIN : "); printList(L);
        /* L = eliminaBlocchiPrefSentina(L, PREF, SENT); */
        printf("OUT: "); printList(L);
        freeList(L);
        printf("\n");
    }

    return 0;
}

int PREF(char parola[])
    {
        if(strlen(parola)<4)
            return 0;
        if(parola[0]=='P' && parola[1]=='R' && parola[2]=='E' && parola[3]=='F')
            return 1;
        return 0;
    }
int SENT(char parola[])
    {
    int len=strlen(parola);
    if(len<4)
        return 0;
    if(parola[len-1]=='T' && parola[len-2]=='N' && parola[len-3]=='E' && parola[len-4]=='S')
        return 1;
    return 0;
    }
Lista f(Lista l)
    {
        if(l==NULL)
            return l;
        if(PREF(l->word))
            {
                Lista res=eliminaFinoASent(l->next);
                return f(res);
            }
    l->next=f(l->next);
    return l;
    }
Lista eliminaFinoASent(Lista l)
{
    if (l == NULL) return NULL;

    Lista next = l->next;
    int stop = SENT(l->word);

    free(l->word);
    free(l);

    if (stop) return next;          // eliminata anche la sentinella (inclusiva)
    return eliminaFinoASent(next);  // continua a eliminare
}

