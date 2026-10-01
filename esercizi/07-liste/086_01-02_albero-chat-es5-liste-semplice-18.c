//
//  main.c
//  albero chat es5 liste semplice -18
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
   STATS (output richiesto)
   ========================= */

typedef struct {
    int blocchi_eliminati;
    int max_len_eliminata;
} Stats;

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
    int i;

    for (i = 0; i < n; i++) {
        head = push_back(head, a[i]);
    }
    return head;
}

static void print_list(Lista l) {
    Node *cur;

    printf("[");
    cur = l;
    while (cur != NULL) {
        printf("\"%s\"", cur->word);
        if (cur->next != NULL) printf(" -> ");
        cur = cur->next;
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

/* =========================
   dist(a,b): 0 se uguali,
              1 se differiscono per UNA sola sostituzione,
              2 altrimenti
   (NB: solo sostituzioni => quindi lunghezze diverse => 2)
   ========================= */

int Leve(char parola1[], char parola2[]) {
    int len1, len2;
    int count;
    int i;

    if (parola1 == NULL || parola2 == NULL) return 2;

    len1 = (int)strlen(parola1);
    len2 = (int)strlen(parola2);

    if (len1 != len2) return 2;

    count = 0;
    for (i = 0; i < len1; i++) {
        if (parola1[i] != parola2[i]) {
            count++;
            if (count > 1) return 2;
        }
    }

    if (count == 0) return 0;
    return 1;
}

/* =========================
   FUNZIONI RICORSIVE (NO CICLI PER I BLOCCHI)
   ========================= */

/* Estende il blocco massimo che parte da start.
   - scrive in *len la lunghezza del blocco (numero di nodi)
   - ritorna il primo nodo DOPO il blocco (può essere NULL) */
Lista estendi_blocco(Lista start, int *len)
{
    if (start == NULL) {
        *len = 0;
        return NULL;
    }

    if (start->next == NULL) {
        *len = 1;
        return NULL;
    }

    if (Leve(start->word, start->next->word) > 1) {
        *len = 1;
        return start->next;
    }

    int sublen = 0;
    Lista after = estendi_blocco(start->next, &sublen);
    *len = 1 + sublen;
    return after;
}

/* Elimina esattamente n nodi dalla testa e ritorna la nuova testa */
Lista elimina_n(Lista head, int n)
{
    if (head == NULL) return NULL;
    if (n == 0) return head;

    Lista next = head->next;
    free(head->word);
    free(head);
    return elimina_n(next, n - 1);
}

/* Funzione principale: elimina tutti i blocchi massimi con len >= T */
Lista elimina_blocchi_lev(Lista head, int T, Stats *st)
{
    if (head == NULL) return NULL;

    int len = 0;
    Lista after = estendi_blocco(head, &len);

    (void)after; /* after non serve direttamente: ci serve len, e l'eliminazione è basata su len */

    if (len >= T) {
        if (st != NULL) {
            st->blocchi_eliminati++;
            if (len > st->max_len_eliminata) st->max_len_eliminata = len;
        }
        return elimina_blocchi_lev(elimina_n(head, len), T, st);
    }

    head->next = elimina_blocchi_lev(head->next, T, st);
    return head;
}

/* =========================
   MAIN DI TEST
   ========================= */

int main(void) {
    const char *w1[] = {
        "casa", "cava", "cava", "casa",  // blocco len 4 (dist<=1 adiacenti)
        "mare",
        "pane", "pane", "pane",          // blocco len 3
        "x", "y",                        // blocco len 2
        "zz"                             // isolata
    };
    int n1 = (int)(sizeof(w1) / sizeof(w1[0]));

    Lista L = build_list_from_array(w1, n1);

    printf("Lista iniziale:\n");
    print_list(L);

    int T = 3;
    Stats st;
    st.blocchi_eliminati = 0;
    st.max_len_eliminata = 0;

    printf("\nChiamo elimina_blocchi_lev(T=%d)...\n", T);
    L = elimina_blocchi_lev(L, T, &st);

    printf("\nLista finale:\n");
    print_list(L);

    printf("\nSTATISTICHE:\n");
    printf("- blocchi eliminati = %d\n", st.blocchi_eliminati);
    printf("- max len eliminata = %d\n", st.max_len_eliminata);

    free_list(L);
    return 0;
}
