//
//  main.c
//  E2 iterativo  -16
//
//  Created by Francesco Roscio Ricon on 03/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    char *word;
    struct Node *next;
} Node;

typedef Node* Lista;

/* =======================
   UTILITY: creazione / stampa / free
   ======================= */

static Node* newNodeDup(const char *s, Node* next) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }

    n->word = (char*)malloc(strlen(s) + 1);
    if (!n->word) { perror("malloc"); exit(1); }
    strcpy(n->word, s);

    n->next = next;
    return n;
}

/* crea lista da array di stringhe (mantiene l'ordine) */
static Lista fromArray(const char* a[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; i--) {
        l = newNodeDup(a[i], l);
    }
    return l;
}

static void printLista(Lista l) {
    printf("[");
    while (l) {
        printf("\"%s\"", l->word);
        if (l->next) printf(" -> ");
        l = l->next;
    }
    printf("]\n");
}

static void freeLista(Lista l) {
    while (l) {
        Node* tmp = l;
        l = l->next;
        free(tmp->word);
        free(tmp);
    }
}
int FINE(char parola[]);
int PRE(char parola[]);

/* =======================
   HELPERS: prefisso / uguaglianza (per debug/test)
   ======================= */

static int startsWith(const char *s, const char *pref) {
    if (!s || !pref) return 0;
    while (*pref) {
        if (*s == '\0') return 0;
        if (*s != *pref) return 0;
        s++; pref++;
    }
    return 1;
}

static int strEq(const char *a, const char *b) {
    if (!a || !b) return 0;
    return strcmp(a, b) == 0;
}

/* =======================
   ESERCIZIO E2 (STUB)
   ======================= */
/*
Lista eliminaBlocchi(Lista head, const char *PREF, const char *SENT, int *removed);

/* STUB: non svolgo l’esercizio */
Lista eliminaBlocchi(Lista head, const char *PREF, const char *SENT, int *removed) {
    (void)head; (void)PREF; (void)SENT;
    if (removed) *removed = -1; /* sentinel */
    return NULL;
}

/* =======================
   MAIN DI TEST
   ======================= */
Lista f(Lista head);
Lista eliminafinoafinish(Lista head, Lista finish);
void blocco(Lista head, Lista *finish);
Lista trovaFINE(Lista pre);

static void runTest(const char* name, const char* PREF, const char* SENT, const char* arr[], int n) {
    printf("====================================\n");
    printf("Test %s\n", name);
    printf("PREF=\"%s\"  SENT=\"%s\"\n", PREF, SENT);

    Lista l = fromArray(arr, n);
    printf("Lista iniziale:\n");
    printLista(l);

//    /* Debug: stampa quali nodi matchano PREF o SENT */
//    printf("Debug match (PREF/SENT): ");
//    for (Lista p = l; p != NULL; p = p->next) {
//        int mp = startsWith(p->word, PREF);
//        int ms = strEq(p->word, SENT);
//        printf("[%s:%c%c] ", p->word, mp ? 'P' : '-', ms ? 'S' : '-');
//    }
//    printf("\n");
//
//    int removed = 0;
    Lista out = f(l);

    printf("\nLista finale:\n");
    printLista(out);
}
void distruggi(Lista a, Lista b);
int main(void) {
    const char *PREF = "PRE";
    const char *SENT = "FINE";

    /* Caso A: un blocco completo (PRE...FINE) */
    const char* A[] = { "uno", "due", "PREstart", "aaa", "bbb", "FINE", "tre", "quattro" };

    /* Caso B: PREF in testa, blocco singolo (PREF...SENT immediatamente) */
    const char* B[] = { "PREX", "FINE", "ok", "ok2" };

    /* Caso C: PREF trovato, ma SENT non compare -> elimina fino a fine lista */
    const char* C[] = { "aa", "bb", "PREtag", "xx", "yy", "zz" };

    /* Caso D: più blocchi disgiunti nella stessa lista */
    const char* D[] = { "a", "PRE1", "x", "FINE", "b", "c", "PRE2", "FINE", "d", "PRE3", "q", "w", "a", "m" };

    /* Caso E: lista vuota */
    const char** E = NULL;
    int nE = 0;

    runTest("A", PREF, SENT, A, (int)(sizeof(A)/sizeof(A[0])));
    runTest("B", PREF, SENT, B, (int)(sizeof(B)/sizeof(B[0])));
    runTest("C", PREF, SENT, C, (int)(sizeof(C)/sizeof(C[0])));
    runTest("D", PREF, SENT, D, (int)(sizeof(D)/sizeof(D[0])));
    runTest("E (vuota)", PREF, SENT, E, nE);

    printf("====================================\n");
    return 0;
}
//E2 - Elimina blocchi fino a parola sentinella (inclusiva)
//
//- Se incontri un nodo la cui word inizia con prefisso PREF,
//  elimina il blocco da quel nodo fino al primo nodo con word == SENT (incluso).
//- Se SENT non compare dopo l'inizio del blocco, elimina fino a fine lista.
//- Può eliminare più blocchi disgiunti in una sola scansione ricorsiva.
//- Vietati cicli nella soluzione (qui è stub).
//- Gestire casi limite: lista vuota, PREF in testa, blocco singolo, ecc.
//
//Firma suggerita:
//- ritorna la nuova testa
//- (opzionale) conta quanti nodi elimina
//*/
Lista f(Lista head)
    {
    Lista scorri=head;
    Lista prec=NULL;
    while(scorri!=NULL)
        {
            Lista succ=scorri->next;
            if(PRE(scorri->word))
                {
                    if(head==scorri)
                        {
                            Lista a=scorri;
                            Lista fine=trovaFINE(scorri);
                            if(fine!=NULL)
                            {
                                head=fine->next;
                                distruggi(a, fine);
                            }
                            scorri=head;
                        }
                    else{
                        
                        Lista a=scorri;
                        Lista fine=trovaFINE(scorri);
                        if(fine!=NULL)
                        {
                            prec->next=fine->next;
                            distruggi(a, fine);
                            scorri=prec->next;
                        }
                        else
                        {
                            prec=scorri;
                            scorri=succ;
                        }
                        
                    }
                }
            else
                {
                    prec=scorri;
                    scorri=succ;
                }
        }
        return head;
    }
Lista trovaFINE(Lista pre)
    {
    Lista scorri=pre;
    while (scorri!=NULL && FINE(scorri->word)==0)
        {
            if(scorri->next==NULL && FINE(scorri->word)==0)
                {
                    return NULL;
                }
            scorri=scorri->next;
        }
        return scorri;
    }
void distruggi(Lista a, Lista b)
    {
        if(a==NULL)
            return;
        while (a!=b) {
            Lista temp=a->next;
            free(a->word);
            free(a);
            a=temp;
        }
    free(b->word);
    free(b);
    }
int PRE(char parola[])
    {
        if(parola[0]=='P' && parola[1]=='R' && parola[2]=='E')
            return 1;
    return 0;
    }
int FINE(char parola[])
    {
        if(parola[0]=='F' && parola[1]=='I' && parola[2]=='N' && parola[3]=='E')
            return 1;
        return 0;
    }
