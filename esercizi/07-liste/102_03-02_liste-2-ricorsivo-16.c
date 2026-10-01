//
//  main.c
//  liste 2  ricorsivo -16
//
//  Created by Francesco Roscio Ricon on 03/02/26.
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

/* =========================
   UTILITY: strdup "sicura"
   ========================= */

static char* my_strdup(const char *s) {
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

/* crea un nodo copiando la stringa */
static Node* newNodeDup(const char *s, Node *next) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->word = my_strdup(s);
    n->next = next;
    return n;
}

/* costruisce una lista da array (mantiene l'ordine) */
static Lista fromArray(const char *a[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; --i) {
        l = newNodeDup(a[i], l);
    }
    return l;
}

/* stampa lista */
static void printLista(Lista l) {
    printf("[");
    while (l) {
        printf("\"%s\"", l->word);
        if (l->next) printf(" -> ");
        l = l->next;
    }
    printf("]\n");
}

/* libera tutta la lista */
static void freeLista(Lista l) {
    while (l) {
        Node *tmp = l->next;
        free(l->word);
        free(l);
        l = tmp;
    }
}
/* helper: lunghezza parola (gestione NULL) */
static int lenWord(const char *s) {
    return (s ? (int)strlen(s) : 0);
}





Lista eliminaNonLocale(Lista head);               /* TODO: tua funzione */
static Lista eliminaNonLocaleRec(Node *prev, Node *curr); /* TODO: tua ricorsione */
int ver(char prev[], char curr[], char next[]);
/* =========================
   MAIN DI TEST
   ========================= */
Lista f(Lista head);

int main(void) {
    /* caso costruito per vedere bene eliminazioni interne */
    const char *A[] = {
        "elefante",  // 8
        "a",         // 1  (probabile da eliminare: molto più corta dei vicini)
        "casa",      // 4
        "xx",        // 2
        "montagna",  // 8
        "zio",       // 3
        "sole"       // 4
    };
    int nA = (int)(sizeof(A)/sizeof(A[0]));

    Lista l = fromArray(A, nA);

    printf("Lista iniziale:\n");
    printLista(l);

    printf("\nApplico eliminaNonLocale(...) (DA IMPLEMENTARE):\n");
    l = f(l);

    printf("Lista finale:\n");
    printLista(l);

    freeLista(l);
    return 0;
}
/* =========================
   PROPRIETA' NON LOCALE (ESEMPIO)
   =========================
   Elimina curr se:
     len(curr) < (len(prev)+len(next))/2
   - prev e next sono i vicini immediati nella lista originale
   - per primo/ultimo nodo: NON eliminare
*/


int ver(char prev[], char curr[], char next[])
    {
        if(strlen(curr)<(strlen(prev)+strlen(next))/2)
            return 1;
    return 0;
    }
Lista f(Lista prec)
    {
        if(prec==NULL || prec->next==NULL || prec->next->next==NULL)
            return prec;
        Lista mid=prec->next;
        Lista last=mid->next;
        if(ver(prec->word, mid->word, last->word))
            {
                free(mid->word);
                free(mid);
                prec->next=last;
                return f(prec);
            }
        prec->next=f(prec->next);
        return prec;
    }
