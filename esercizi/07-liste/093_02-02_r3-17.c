//
//  main.c
//  R3 -17
//
//  Created by Francesco Roscio Ricon on 02/02/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =======================
   STRUTTURE DATI
   ======================= */

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

/* crea lista da array di stringhe (mantiene l’ordine) */
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

/* =======================
   PROTOTIPI (E1)
   ======================= */

Lista eliminaP(Lista head, int *removed);
Lista elimina_P(Lista head, int *removed);

/* STUB: non svolgo l’esercizio */
Lista elimina_P(Lista head, int *removed) {
    head=eliminaP(head, removed);
    return head;
}

/* =======================
   MAIN DI TEST
   ======================= */
int main(void) {
    /* Lista di test (parole varie per coprire casi: lunghezza pari/dispari, vocali doppie, ecc.) */
    const char* a1[] = {
        "casa",     /* len 4 (pari), no doppia vocale consecutiva */
        "cooperare",/* contiene "oo" (2 vocali uguali consecutive) */
        "sole",     /* len 4 (pari) */
        "aiuola",   /* vocali varie, controlla doppie */
        "bello",    /* contiene "ll" (non vocale), vocali non consecutive uguali */
        "zoo",      /* contiene "oo" */
        "idea",     /* len 4 (pari) */
        "queue",    /* tante vocali, ma vedi se ci sono uguali consecutive */
        "aereo",    /* vocali, ma consecutive uguali? */
        "uo"        /* len 2 (pari), due vocali ma non uguali consecutive */
    };

    Lista l1 = fromArray(a1, (int)(sizeof(a1)/sizeof(a1[0])));

    printf("====================================\n");
    printf("E1 - Test lista iniziale\n");
    printf("Lista: ");
    printLista(l1);

    int removed = 0;
    Lista out = elimina_P(l1, &removed);

    printf("\nDopo elimina_P:\n");
    printf("Nuova testa: ");
    printLista(out);
    printf("Nodi rimossi = %d\n", removed);
    printf("====================================\n");

    /* Se la tua elimina_P libera correttamente i nodi eliminati,
       qui devi liberare solo la lista risultante. */
    freeLista(out);

    return 0;
}



/* ritorna 1 se c è una vocale, 0 altrimenti */
static int isVowel(char c) {
    if (c >= 'A' && c <= 'Z') c = (char)(c - 'A' + 'a');
    return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u');
}

/* ritorna 1 se la parola contiene almeno 2 vocali uguali consecutive */
static int hasTwoEqualConsecutiveVowels(const char *w) {
    if (w == NULL) return 0;

    for (int i = 0; w[i] != '\0' && w[i+1] != '\0'; i++) {
        if (isVowel(w[i]) &&
            isVowel(w[i+1]) &&
            w[i] == w[i+1]) {
            return 1;
        }
    }
    return 0;
}

/* P(word) = (lunghezza pari) XOR (due vocali uguali consecutive) */
int P(const char *word) {
    if (word == NULL) return 0;

    int len_pari = (strlen(word) % 2 == 0);
    int doppia_vocale = hasTwoEqualConsecutiveVowels(word);

    /* XOR logico */
    return (len_pari && !doppia_vocale) ||
           (!len_pari && doppia_vocale);
}

Lista eliminaP(Lista head, int *removed)
    {
        if(head==NULL)
            return head;
        if(P(head->word))
            {
                Lista temp=head->next;
                free(head->word);
                free(head);
                (*removed)++;
                return eliminaP(temp, removed);
            }
    head->next=eliminaP(head->next, removed);
    return head;
    }
