//  Created by Francesco Roscio Ricon on 04/02/26.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;            /* stringa dinamica */
    struct Node *next;
} Node;

typedef Node* Lista;



/* Elimina le parole duplicate mantenendo SOLO l’ultima occorrenza
   Vincoli: ricorsivo, niente strutture ausiliarie */
Lista eliminaDuplicatiUltimaOccorrenza(Lista head); /* TODO */

/* =========================
   UTILITY (PER TEST - OK USARE CICLI QUI)
   ========================= */

static char* dupstr(const char *s) {
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static Node* newNodeDup(const char *w, Node *next) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->word = dupstr(w);
    n->next = next;
    return n;
}

/* crea lista da array di stringhe mantenendo l'ordine */
static Lista fromArray(const char *a[], int n) {
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
        if (l->next) printf(", ");
        l = l->next;
    }
    printf("]\n");
}

static void freeLista(Lista l) {
    while (l) {
        Lista tmp = l->next;
        free(l->word);
        free(l);
        l = tmp;
    }
}




/* =========================
   MAIN
   ========================= */
Lista eliminaDuplicatiUltimaOccorrenza(Lista head);
int trovaparola(Lista head, char parola[]);
int main(void) {
    /* esempio con duplicati: mantieni SOLO l'ultima occorrenza */
    const char *parole[] = {
        "casa", "mare", "cane", "mare", "sole", "casa", "mare"
        /* ultime occorrenze: "cane", "sole", "casa", "mare" (ordine relativo preservato) */
    };
    int n = (int)(sizeof(parole) / sizeof(parole[0]));

    Lista l = fromArray(parole, n);

    printf("=== LISTA ORIGINALE ===\n");
    printLista(l);

    l = eliminaDuplicatiUltimaOccorrenza(l);

    printf("\n=== LISTA DOPO ELIMINAZIONE DUPLICATI (ultima occorrenza) ===\n");
    printLista(l);

    freeLista(l);
    return 0;
}
/* Elimina le parole duplicate mantenendo SOLO l’ultima occorrenza
   Vincoli: ricorsivo, niente strutture ausiliarie */

int trovaparola(Lista head, char parola[])
    {
        if(head==NULL)
            return 0;
        if(strcmp(head->word, parola)==0)
            {
                return 1;
            }
        return trovaparola(head->next, parola);
    }
Lista eliminaDuplicatiUltimaOccorrenza(Lista head)
    {
        if(head==NULL || head->next==NULL)
            return head;
        if(trovaparola(head->next, head->word))
            {
                Lista temp=head->next;
                free(head);
                return eliminaDuplicatiUltimaOccorrenza(temp);
            }
        head->next=eliminaDuplicatiUltimaOccorrenza(head->next);
        return head;
    }
