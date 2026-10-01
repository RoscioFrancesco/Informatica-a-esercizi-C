//
//  main.c
//  albero chat es5 liste-18
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
    if (!s) return NULL;
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static Lista push_back(Lista head, const char *w) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->word = str_dup(w);
    n->next = NULL;

    if (!head) return n;

    Node *cur = head;
    while (cur->next) cur = cur->next;
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
    for (Node *cur = l; cur; cur = cur->next) {
        printf("\"%s\"", cur->word);
        if (cur->next) printf(" -> ");
    }
    printf("]\n");
}

static void free_list(Lista l) {
    while (l) {
        Node *tmp = l->next;
        free(l->word);
        free(l);
        l = tmp;
    }
}
static int dist_approx(const char *a, const char *b) {
    if (!a || !b) return 2;

    size_t la = strlen(a), lb = strlen(b);
    if (la != lb) return 2;

    int diff = 0;
    for (size_t i = 0; i < la; i++) {
        if (a[i] != b[i]) {
            diff++;
            if (diff > 1) return 2;
        }
    }
    return (diff == 0) ? 0 : 1;
}

/* =========================
   (DA FARE) FUNZIONE RICORSIVA PRINCIPALE
   - elimina ogni blocco massimo di parole consecutive
     dove per ogni coppia adiacente dist<=1
   - elimina SOLO se lunghezza blocco >= T
   - NO CICLI per la logica del blocco (scan e decisione blocco ricorsivi)
   - aggiorna stats: quanti blocchi eliminati, max len eliminata
   ========================= */

/*
  Suggerimento firma comoda:
  - ritorna la nuova testa
  - stats aggiornate per side-effect
*/
Lista f(Lista head, Stats *st, int T);
Lista elimina_blocchi_lev(Lista head, int T, Stats *st);

/* =========================
   MAIN DI TEST
   ========================= */

int main(void) {
    // Esempio 1: blocco lungo con dist<=1 (solo sostituzioni)
    const char *w1[] = {
        "casa", "cava", "cava", "casa",  // dist(casa,cava)=1, dist(cava,cava)=0, dist(cava,casa)=1  => blocco len 4
        "mare",
        "pane", "pane", "pane",          // blocco len 3
        "x", "y",                        // dist=1 (len1=1) => blocco len 2
        "zz"                             // isolata
    };
    int n1 = (int)(sizeof(w1)/sizeof(w1[0]));

    Lista L = build_list_from_array(w1, n1);

    printf("Lista iniziale:\n");
    print_list(L);

    int T = 3;
    Stats st = {0, 0};

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


Lista elimina_blocchi_lev(Lista head, int T, Stats *st) {
    (void)T;
    return f(head, st, T);
}
/* =========================
   dist(a,b): 0 se uguali,
              1 se differiscono per UNA sola sostituzione,
              2 altrimenti
   (NB: solo sostituzioni => quindi lunghezze diverse => 2)
   ========================= */
int Leve(char parola1[], char parola2[])
{
    int len1 = strlen(parola1);
    int len2 = strlen(parola2);
    if (len1 != len2) return 2;

    int count = 0;
    for (int i = 0; i < len1; i++) {
        if (parola1[i] != parola2[i]) count++;
        if (count > 1) return 2;
    }
    return count; // 0 o 1
}
void blocco(Lista start, Lista prec_finish, Lista *finish, int *count)
    {
        if(start==NULL)
            return;
        if (*finish == NULL) return;
        if(Leve(prec_finish->word, (*finish)->word)>1)
            {
                return;
            }
        (*count)++;
        (*finish)=(*finish)->next;
        blocco(start, prec_finish->next, finish, count);
    }

Lista eliminafinoafinish(Lista start, Lista finish)
    {
        if (start == NULL) return NULL;
        if(start==finish)
            return finish;
        Lista temp=start->next;
        free(start->word);
        free(start);
        return eliminafinoafinish(temp, finish);
    }
Lista f(Lista head, Stats *st, int T)
    {
        if(head==NULL)
            return head;
        Lista finish=head->next;
        int count=1;
        blocco(head, head, &finish, &count);
        if(count>=T)
        {
            Lista new=eliminafinoafinish(head, finish);
            st->max_len_eliminata=count;
            st->blocchi_eliminati++;
            return f(new, st, T);
        }
        head->next=f(head->next, st, T);
        return head;
    }
