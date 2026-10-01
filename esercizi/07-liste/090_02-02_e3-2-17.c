//
//  main.c
//  E3.2 -17
//
//  Created by Francesco Roscio Ricon on 02/02/26.
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

void test_E3(void) {
    const char *words[] = {
        "uno", "PRE", "x", "y", "okFINE", "due",
        "PRE123", "k", "zzzFINE", "tre",
        "PRE_senzaB", "solo", "quattro",
        "FINE", "fine"
    };
    int n = (int)(sizeof(words) / sizeof(words[0]));

    Lista head = build_from_array(words, n);

    print_list("PRIMA: ", head);

    head=f(head);

    print_list("DOPO:  ", head);

    free_list(head);
}

int main(void) {
    test_E3();
    return 0;
}
/* ========= FUNZIONE DA SVOLGERE (NON RISOLTA) =========
   E3 - Elimina intervalli tra A e successivo B (ESCLUSIVI).
*/
void blocco(Lista start, Lista *finish)
    {
        if(start==NULL)
            return;
        if(*finish==NULL)
            return;
        if(match_REGEX_B((*finish)->word)==1)
            return;
        *finish=(*finish)->next;
        blocco(start, finish);
    }
Lista eliminafinoaB(Lista head, Lista finish)
    {
        if(head==NULL)
            return head;
        int flag=0;
        Lista temp=head->next;
        if(head==finish)
            flag=1;
        free(head->word);
        free(head);
        if(flag==1)
            return temp;
    return eliminafinoaB(temp, finish);
    }
Lista f(Lista head)
    {
        if(head==NULL || head->next==NULL)
            return head;
        if (match_REGEX_A(head->next->word))
        {
            Lista A = head->next;
            Lista B = A->next;                 // <-- parte interna dopo A
            blocco(A, &B);                     // <-- ora B diventa il nodo che matcha REGEX_B (oppure NULL)

            if (B == NULL)
                return head;                   // <-- A senza B successivo: non eliminare nulla

            if (A->next != B)                  // <-- se c'è qualcosa tra A e B
            {
                Lista prevB = A;
                while (prevB->next != B)       // <-- trova il nodo prima di B
                    prevB = prevB->next;

                A->next = eliminafinoaB(A->next, prevB);  // <-- elimina solo l'intervallo interno
                // dopo questa, A->next punta a B
            }

            head->next = f(head->next);        // continua dopo A (che è rimasto)
            return head;
        }
        head->next=f(head->next);
        return head;
    }
