//
//  main.c
//  E3 iterativo 2 -17
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
    char *p = (char*)malloc(n);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n);
    return p;
}

Lista push_back(Lista head, const char *w) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->word = dupstr(w);
    n->next = NULL;

    if (!head) return n;

    Nodo *cur = head;
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
    for (Nodo *cur = head; cur != NULL; cur = cur->next) {
        printf("%s", cur->word);
        if (cur->next) printf(" -> ");
    }
    printf("\n");
}

void free_list(Lista head) {
    while (head) {
        Nodo *next = head->next;
        free(head->word);
        free(head);
        head = next;
    }
}

/* ========= REGEX SCELTE =========
   REGEX_A: ^PRE.*$   (parole che iniziano con "PRE")
   REGEX_B: ^.*FINE$  (parole che finiscono con "FINE")
*/

static int regex_match(const char *pattern, const char *text) {
    if (!text) return 0;

    regex_t re;
    int rc = regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB);
    if (rc != 0) {
        /* Se la regex è scritta male, qui è un errore del programmatore */
        fprintf(stderr, "Errore: regex non valida: %s\n", pattern);
        exit(1);
    }

    rc = regexec(&re, text, 0, NULL, 0);
    regfree(&re);

    return (rc == 0); /* 0 = match */
}

int match_REGEX_A(const char *w) {
    return regex_match("^PRE.*$", w);
}

int match_REGEX_B(const char *w) {
    return regex_match("^.*FINE$", w);
}

Lista elimina_intervalli(Lista head) {
    (void)head;
    /* TODO: QUI va la soluzione (ricorsiva) */
    return NULL; /* placeholder */
}

/* ========= TEST ========= */
Lista f(Lista head);
Lista eliminafinoaB(Lista head, Lista finish);
void blocco(Lista start, Lista *finish);
Lista ritorno_prev(Lista head);

void test_E3(void) {
    const char *words[] = {
        "PRE", "z", "x", "y", "okFINE", "due",
        "PRE123", "k", "zzzFINE", "tre",
        "PRE_senzaB", "z", "quattro",
        "a", "c"
    };
    int n = (int)(sizeof(words) / sizeof(words[0]));

    Lista head = build_from_array(words, n);

    print_list("PRIMA: ", head);

    head=f(head);

    print_list("DOPO:  ", head);

    free_list(head);
}
void Elimina(Lista a, Lista b);
int main(void) {
    test_E3();
    return 0;
}
/* ========= FUNZIONE DA SVOLGERE (NON RISOLTA) =========
   E3 - Elimina intervalli tra A e successivo B (ESCLUSIVI).
*/
Lista f(Lista head)
{
    if(head==NULL)
        return head;
    Lista scorri=head;
    while(scorri!=NULL)
    {
        if(match_REGEX_A(scorri->word))
        {
            Lista a=scorri;
            Lista b_prev=ritorno_prev(scorri);
            Lista b=b_prev->next;
            if(b!=NULL && b_prev!=a)
            {
                Lista temp=scorri->next;
                a->next=b;
                Elimina(temp, b_prev);
                scorri=b;
            }
        }
        scorri=scorri->next;
    }
    return head;
}
Lista ritorno_prev(Lista head) // head è quello che matcha A
    {
    Lista scorri=head;
    while(scorri!=NULL && scorri->next!=NULL && match_REGEX_B(scorri->next->word)==0)
        {
            scorri=scorri->next;
        }
    return scorri; // scorri mi da al massimo l'ultima casella(se non trova nessun match);
    }
void Elimina(Lista a, Lista b) // gli do il succ a PRE e l'output di scorri
    {
        if(b==NULL)
            return;
        while(a!=NULL && a!=b)
            {
                Lista temp=a->next;
                free(a->word);
                free(a);
                a=temp;
            }
        free(b->word);
        free(b);
    }
