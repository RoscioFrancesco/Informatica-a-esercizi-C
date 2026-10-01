//
//  main.c
//  E4.2 -17
//
//  Created by Francesco Roscio Ricon on 02/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
    char *word;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

/* =======================
   UTILITY (build/print/free)
   ======================= */
Lista f(Lista head, int k);
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

/* =======================
   PROPRIETA' ANCHOR (da definire)
   ======================= */

/* Esempio: ANCHOR se la parola inizia con '#'
   Cambiala come vuoi (o rendila più complessa). */
int ANCHOR(const char *w) {
    return (w != NULL && w[0] == '#');
}

/* =======================
   ESERCIZIO E4 (STUB - NON RISOLTO)
   ======================= */


Lista elimina_k_dopo_ancora(Lista head, int k, int *deleted) {
    (void)head; (void)k;
    if (deleted) *deleted = 0;

    
    return NULL; /* placeholder */
}

/* =======================
   MAIN / TEST
   ======================= */

int main(void) {
    /* Lista di test: alcune parole sono "ancore" (iniziano con '#') */
    const char *words[] = {
        "uno", "#A", "x1", "x2", "x3", "due",
        "#B", "y1", "#C", "z1", "z2", "tre",
        "#D", "fine"
    };
    int n = (int)(sizeof(words) / sizeof(words[0]));

    Lista head = NULL;
    for (int i = 0; i < n; i++)
        head = push_back(head, words[i]);

    int k = 2;              /* puoi cambiare k */
    int deleted = 0;

    print_list("PRIMA: ", head);

    
    head = f(head, k);

    print_list("DOPO:  ", head);
    free_list(head);
    return 0;
}
/*
E4 - Elimina k parole dopo una parola-ancora
- Per ogni nodo che soddisfa ANCHOR, elimina le successive k parole (se esistono).
- Il nodo ancora resta.
- Se due ancore sono vicine, l’eliminazione ha priorità: un nodo eliminato non può diventare ancora.
- Niente cicli, O(n).
- Restituisci anche quante eliminazioni effettive sono state fatte.

Firma suggerita:
- ritorna la nuova testa
- aggiorna *deleted con il totale dei nodi realmente eliminati
*/

Lista f(Lista head, int k)
    {
        if(head==NULL)
            return head;
    Lista scorri=head;
    while (scorri!=NULL)
        {
            if(ANCHOR(scorri->word))
                {
                    if(scorri->next==NULL)
                        continue;
                    Lista succ=scorri->next;
                    Lista arpione=succ;
                    for(int i=0; arpione!=NULL &&i<k; i++)
                        {
                            arpione=arpione->next;
                        }
                    scorri->next=arpione;
                    for(int i=0;succ!=NULL && i<k ; i++)
                        {
                            Lista temp=succ->next;
                            free(succ->word);
                            free(succ);
                            succ=temp;
                        }
                }
            scorri=scorri->next;
        }
    return head;
    }
