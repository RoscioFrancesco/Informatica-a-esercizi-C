//
//  main.c
//  albero chat es6 liste -18
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
    char *word;            // stringa dinamica
    struct Node *next;
} Node;

typedef Node* Lista;

/* =========================
   UTIL: CREAZIONE / STAMPA / FREE
   ========================= */

static char* str_dup(const char *s) {
    size_t n;
    char *p;
    if (s == NULL) return NULL;
    n = strlen(s);
    p = (char*)malloc(n + 1);
    if (p == NULL) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static Lista push_back(Lista head, const char *w) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (n == NULL) { perror("malloc"); exit(1); }
    n->word = str_dup(w);
    n->next = NULL;

    if (head == NULL) return n;

    Node *cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return head;
}

static Lista build_list_from_array(const char *a[], int n) {
    Lista head = NULL;
    for (int i = 0; i < n; i++) head = push_back(head, a[i]);
    return head;
}

static void print_list(Lista l) {
    printf("[");
    for (Node *cur = l; cur != NULL; cur = cur->next) {
        printf("\"%s\"", cur->word);
        if (cur->next != NULL) printf(" -> ");
    }
    printf("]\n");
}

static void free_list(Lista l) {
    while (l != NULL) {
        Node *tmp = l->next;
        free(l->word);
        free(l);
        l = tmp;
    }
}



Lista elimina_blocchi_begin_end(Lista head);

/* =========================
   MAIN DI TEST (con casi cattivi)
   ========================= */
Lista f(Lista head);
Lista eliminafinoaFinish(Lista head, Lista finish);
void blocco(Lista start, Lista *finish);

int main(void) {
    /* Caso A: annidamento completo + testo fuori */
    const char *a1[] = {
        "uno",
        "BEGIN", "a", "BEGIN", "b", "END", "c", "END",
        "due"
    };

    /* Caso B: END senza BEGIN (non elimina niente per quello) + blocco valido dopo */
    const char *a2[] = {
        "END", "x",
        "BEGIN", "y", "END",
        "z"
    };

    /* Caso C: blocchi consecutivi + blocco che include la testa */
    const char *a3[] = {
        "BEGIN", "x", "END",
        "BEGIN", "BEGIN", "y", "END", "END",
        "fine"
    };

    /* Caso D: BEGIN senza END (da quel BEGIN in poi non eliminare nulla) */
    const char *a4[] = {
        "start",
        "BEGIN", "k", "BEGIN", "m", "END", "n",   /* qui manca l'END esterno */
        "tail", "END",                            /* END “tardivo” ma non corrisponde secondo regola 3? (dipende dalla tua definizione) */
        "ultima"
    };

    /* Nota: il caso D serve proprio per vedere se la tua soluzione rispetta:
       "Se c'è un BEGIN senza END corrispondente, non eliminare nulla a partire da quel BEGIN".
       Quindi spesso l'atteso è: lasci tutto da quel BEGIN in poi INALTERATO. */

    const char **tests[] = { a1, a2, a3, a4 };
    int lens[] = {
        (int)(sizeof(a1) / sizeof(a1[0])),
        (int)(sizeof(a2) / sizeof(a2[0])),
        (int)(sizeof(a3) / sizeof(a3[0])),
        (int)(sizeof(a4) / sizeof(a4[0]))
    };
    const char *names[] = { "A", "B", "C", "D" };

    for (int t = 0; t < 4; t++) {
        printf("=========== TEST %s ===========\n", names[t]);
        Lista L = build_list_from_array(tests[t], lens[t]);

        printf("Lista iniziale:\n");
        print_list(L);

        printf("Chiamo elimina_blocchi_begin_end...\n");
        L = elimina_blocchi_begin_end(L);

        printf("Lista finale:\n");
        print_list(L);

        free_list(L);
        printf("\n");
    }

    return 0;
}


Lista elimina_blocchi_begin_end(Lista head) {
    return f(head);
}
/*
    =========================
   (DA FARE) ESERCIZIO E15
   - Elimina tutti i blocchi validi BEGIN ... END con annidamento
   - Se un BEGIN non ha END corrispondente: da quel BEGIN in poi NON eliminare nulla
   - NO stack espliciti: annidamento via ricorsione
   - Gestire END senza BEGIN, blocchi consecutivi, blocchi che includono la testa
   =========================
 */
void blocco(Lista start, Lista *finish)
    {
        if(start==NULL)
            return;
        if(*finish==NULL)
            return;
        if(strcmp("END", (*finish)->word)==0)
            {
                (*finish)=(*finish)->next;
                return;
            }
        (*finish)=(*finish)->next;
        blocco(start, finish);
    }
Lista eliminafinoaFinish(Lista head, Lista finish)
    {
        if(head==NULL)
            return head;
        if(head==finish)
            {
                return head;
            }
        Lista temp=head->next;
        free(head->word);
        free(head);
        return eliminafinoaFinish(temp, finish);
    }
Lista f(Lista head)
    {
        if(head==NULL)
            return head;
        if(strcmp("BEGIN", head->word)==0)
            {
                Lista finish=head->next;
                blocco(head, &finish);
                Lista new=eliminafinoaFinish(head, finish);
                return f(new);
            }
        head->next=f(head->next);
        return head;
    }
