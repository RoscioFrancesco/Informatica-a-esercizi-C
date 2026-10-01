//
//  main.c
//  E3 iterativo chat -17
//
//  Created by Francesco Roscio Ricon on 03/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

/* ========= STRUTTURE ========= */

typedef struct nodo {
    char *word;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

/* ========= UTILITY LISTA ========= */

static char *dupstr(const char *s) {
    size_t n = strlen(s) + 1;
    char *p = malloc(n);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n);
    return p;
}

Lista push_back(Lista head, const char *w) {
    Lista n = malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->word = dupstr(w);
    n->next = NULL;

    if (!head) return n;

    Lista cur = head;
    while (cur->next) cur = cur->next;
    cur->next = n;
    return head;
}

Lista build_from_array(const char *arr[], int n) {
    Lista head = NULL;
    for (int i = 0; i < n; i++)
        head = push_back(head, arr[i]);
    return head;
}

void print_list(const char *label, Lista head) {
    printf("%s", label);
    for (Lista cur = head; cur != NULL; cur = cur->next) {
        printf("%s", cur->word);
        if (cur->next) printf(" -> ");
    }
    printf("\n");
}

void free_list(Lista head) {
    while (head) {
        Lista next = head->next;
        free(head->word);
        free(head);
        head = next;
    }
}

/* ========= REGEX ========= */

static int regex_match(const char *pattern, const char *text) {
    regex_t re;
    regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB);
    int ok = (regexec(&re, text, 0, NULL, 0) == 0);
    regfree(&re);
    return ok;
}

int match_REGEX_A(const char *w) { return regex_match("^PRE.*$", w); }
int match_REGEX_B(const char *w) { return regex_match("^.*FINE$", w); }

/* ========= FUNZIONE ESAME ========= */
/* Elimina i nodi tra A e il successivo B (ESCLUSI).
   Se B non esiste, non elimina nulla. */

Lista elimina_intervalli(Lista head)
{
    Lista *pp = &head;   /* puntatore al link corrente */

    while (*pp != NULL)
    {
        Lista a = *pp;

        if (!match_REGEX_A(a->word))
        {
            pp = &a->next;
            continue;
        }

        /* cerco il primo B dopo A */
        Lista b = a->next;
        while (b != NULL && !match_REGEX_B(b->word))
            b = b->next;

        if (b == NULL)
        {
            /* nessun B: non elimino nulla */
            pp = &a->next;
            continue;
        }

        /* elimino i nodi tra A e B (esclusi) */
        Lista cur = a->next;
        while (cur != b)
        {
            Lista next = cur->next;
            free(cur->word);
            free(cur);
            cur = next;
        }

        a->next = b;      /* salto il blocco eliminato */
        pp = &a->next;    /* continuo da B */
    }

    return head;
}

/* ========= TEST ========= */

int main(void)
{
    const char *words[] = {
        "uno", "PRE", "x", "y", "okFINE", "due",
        "PRE123", "k", "zzzFINE", "tre",
        "PRE_senzaB", "solo", "quattro",
        "FINE", "fine"
    };

    int n = sizeof(words) / sizeof(words[0]);

    Lista head = build_from_array(words, n);

    print_list("PRIMA: ", head);
    head = elimina_intervalli(head);
    print_list("DOPO:  ", head);

    free_list(head);
    return 0;
}
