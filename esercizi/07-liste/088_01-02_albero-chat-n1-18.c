//
//  main.c
//  albero chat n1 -18
//
//  Created by Francesco Roscio Ricon on 01/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* =========================
   STRUTTURE DATI
   ========================= */

typedef struct Node {
    char *word;           /* stringa dinamica */
    struct Node *next;
} Node;

typedef Node* Lista;

/* restituisci entrambe le teste */
typedef struct {
    Lista yes;  /* soddisfa P */
    Lista no;   /* non soddisfa P */
} Partizione;

/* =========================
   UTILITY STRINGHE / LISTE
   ========================= */

static char *dupstr(const char *s) {
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static Lista push_back(Lista l, const char *w) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->word = dupstr(w);
    n->next = NULL;

    if (l == NULL) return n;

    Node *cur = l;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return l;
}

static void printLista(const char *label, Lista l) {
    printf("%s", label);
    if (l == NULL) {
        printf("(vuota)\n");
        return;
    }
    while (l != NULL) {
        printf("%s", l->word);
        if (l->next) printf(" -> ");
        l = l->next;
    }
    printf("\n");
}

static void freeLista(Lista l) {
    while (l != NULL) {
        Node *tmp = l->next;
        free(l->word);
        free(l);
        l = tmp;
    }
}

/* =========================
   PREDICATO ESEMPIO P
   "contiene almeno una cifra"
   ========================= */

static int contieneCifra(const char *s) {
    if (s == NULL) return 0;
    while (*s) {
        if (isdigit((unsigned char)*s)) return 1;
        s++;
    }
    return 0;
}

/* =========================
   ESERCIZIO: PROTOTIPO (DA FARE TU)
   - stable partition
   - NO nuovi nodi
   - NO cicli
   ========================= */


Partizione partizionaStableRic(Lista head, int (*P)(const char*));

/* =========================
   MAIN DI TEST
   ========================= */
Lista inserisciincoda(Lista head, char parola[]);
int main(void) {
    /* lista di esempio */
    Lista l = NULL;
    l = push_back(l, "ciao");
    l = push_back(l, "a1");
    l = push_back(l, "bbb");
    l = push_back(l, "x9y");
    l = push_back(l, "zero");
    l = push_back(l, "42");
    l = push_back(l, "pippo");

    printLista("Lista originale: ", l);

    
    Partizione r = partizionaStableRic(l, contieneCifra);

    /* stampa risultato */
    printLista("Soddisfa P:     ", r.yes);
    printLista("Non soddisfa P: ", r.no);

    /* IMPORTANTE:
       Dopo la partizione NON devi fare free di 'l' (perché i nodi
       sono stati riagganciati). Libera invece entrambe le liste. */
    freeLista(r.yes);
    freeLista(r.no);

    return 0;
}

/*
OUTPUT ATTESO (con P = "contiene almeno una cifra"):

Lista originale: ciao -> a1 -> bbb -> x9y -> zero -> 42 -> pippo
Soddisfa P:     a1 -> x9y -> 42
Non soddisfa P: ciao -> bbb -> zero -> pippo
*/

void f(Lista head, Partizione *p)
    {
    Lista scorri=head;
    if(head==NULL) return;
    if(contieneCifra(scorri->word))
        {
            p->yes=inserisciincoda(p->yes, scorri->word);
        }
    else
    {
        p->no=inserisciincoda(p->no, scorri->word);
    }
    f(head->next, p);
    
    }
Lista inserisciincoda(Lista head, char parola[])
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=NULL;
                new->word = (char*)malloc(strlen(parola) + 1);
                strcpy(new->word, parola);
                return new;
            }
    head->next=inserisciincoda(head->next, parola);
    return head;
    }

Partizione partizionaStableRic(Lista head, int (*P)(const char*))
    {
    Partizione p;
    p.no=NULL;
    p.yes=NULL;
    f(head, &p);
    return p;
    }
