//
//  main.c
//  liste 1 -16
//
//  Created by Francesco Roscio Ricon on 03/02/26.
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
Lista eliminaNonLocale(Lista head);  // TODO: implementa tu

/* =========================
   UTILITY (QUI OK CICLI PER TEST)
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
    while (cur->next) cur = cur->next;
    cur->next = n;
    return l;
}

static void printLista(Lista l, const char *label) {
    printf("%s: ", label);
    for (Node *cur = l; cur; cur = cur->next) {
        printf("\"%s\"(%zu)", cur->word, strlen(cur->word));
        if (cur->next) printf(" -> ");
    }
    printf(" -> NULL\n");
}

static void freeLista(Lista l) {
    while (l) {
        Node *tmp = l->next;
        free(l->word);
        free(l);
        l = tmp;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
Lista f(Lista head);
int proprità(char curr[], char succ[]);
int main(void) {
    Lista l = NULL;

    /*
      Esempio pensato per far scattare la proprietà non locale:
      - "ciao"(4) > "a"(1)    => "ciao" va eliminata
      - "programmazione"(14) > "C"(1) => "programmazione" va eliminata
      - "bb"(2) > "bbb"(3)    => NO (rimane)
      Nota: l'ultimo nodo non ha successivo, quindi NON viene eliminato per questa proprietà.
    */
    const char *parole[] = {"ciao", "a", "bb", "bbb", "programmazione", "C", "fine"};
    int n = (int)(sizeof(parole) / sizeof(parole[0]));
    for (int i = 0; i < n; i++) l = push_back(l, parole[i]);

    printLista(l, "Prima");

    
    l = f(l);

    printLista(l, "Dopo");

    freeLista(l);
    return 0;
}

/* =========================
   STUB (NON RISOLVO L’ESERCIZIO)
   ========================= */

Lista eliminaNonLocale(Lista head) {
    
    (void)head;
    return head; // placeholder
}

/*
  Rimuovi ricorsivamente (senza cicli) i nodi che soddisfano la proprietà non locale:
  "len(curr->word) > len(curr->next->word)".
  - Stable: l’ordine degli altri nodi deve rimanere invariato.
  - Libera correttamente word e nodo per ogni eliminazione.
*/
int proprità(char curr[], char succ[])
    {
        if(strlen(curr)>strlen(succ))
            return 1;
        return 0;
    }
Lista f(Lista head)
    {
        if(head==NULL || head->next==NULL)
            return head;
        if(proprità(head->word, head->next->word))
            {
                Lista l=head->next;
                free(head->word);
                free(head);
                return f(l);
            }
        head->next=f(head->next);
        return head;
    }
