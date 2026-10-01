//
//  main.c
//  ricorsione chat 4
//
//  Created by Francesco Roscio Ricon on 28/01/26.
//

#include <stdio.h>
#include <stdlib.h>

/* ===== STRUTTURE ===== */

typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

/* ===== UTILS ===== */

Lista cons(int v, Lista tail) {
    Nodo *n = malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->next = tail;
    return n;
}

void stampa(Lista l) {
    printf("[");
    while (l) {
        printf("%d", l->val);
        if (l->next) printf(", ");
        l = l->next;
    }
    printf("]");
}



int sottolista(Lista l1, Lista l2);


/* ===== MAIN DI TEST ===== */

int main(void) {

    Lista l1 = cons(1, cons(2, cons(3, cons(4, cons(5, NULL)))));
    Lista a  = cons(3, cons(4, NULL));                   // presente (3,4)
    Lista b  = cons(2, cons(4, NULL));                   // non contigua
    Lista c  = cons(1, cons(2, cons(3, NULL)));          // prefisso
    Lista d  = cons(4, cons(5, NULL));                   // suffisso
    Lista e  = cons(5, NULL);                            // singolo presente
    Lista f  = cons(6, NULL);                            // singolo assente
    Lista g  = NULL;                                     // lista vuota

    // casi con ripetizioni
    Lista lrep = cons(1, cons(2, cons(1, cons(2, cons(1, NULL)))));
    Lista h = cons(1, cons(2, cons(1, NULL)));           // presente (1,2,1)
    Lista i = cons(2, cons(1, cons(2, NULL)));           // presente (2,1,2)
    Lista j = cons(1, cons(1, NULL));                    // assente come contigua

    struct {
        Lista x;
        Lista y;
        int atteso;
        const char *nome;
    } tests[] = {
        {l1, a, 1, "l1 contiene [3,4]"},
        {l1, b, 0, "l1 contiene [2,4] (no, non contigua)"},
        {l1, c, 1, "l1 contiene [1,2,3] (prefisso)"},
        {l1, d, 1, "l1 contiene [4,5] (suffisso)"},
        {l1, e, 1, "l1 contiene [5]"},
        {l1, f, 0, "l1 contiene [6] (no)"},
        {l1, g, 1, "l1 contiene [] (sempre)"},
        {g,  e, 0, "[] contiene [5] (no)"},
        {g,  g, 1, "[] contiene [] (si)"},
        {lrep, h, 1, "ripetizioni: [1,2,1]"},
        {lrep, i, 1, "ripetizioni: [2,1,2]"},
        {lrep, j, 0, "ripetizioni: [1,1] (no)"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int k = 0; k < n; k++) {
        printf("%s\n", tests[k].nome);
        printf("  l1 = "); stampa(tests[k].x);
        printf("\n  l2 = "); stampa(tests[k].y);
        int res = sottolista(tests[k].x, tests[k].y);
        printf("\n  -> %d (atteso %d)\n\n", res, tests[k].atteso);
    }

    return 0;
}

int matchDaQui(Lista l1, Lista l2)
{
    if (l2 == NULL) return 1;   // finita l2: match completato
    if (l1 == NULL) return 0;   // finita l1 ma l2 no: fallito

    if (l1->val != l2->val) return 0;
    return matchDaQui(l1->next, l2->next);
}
int sottolista(Lista l1, Lista l2)
{
    if (l2 == NULL) return 1;   // la lista vuota è sottolista di tutto
    if (l1 == NULL) return 0;

    if (matchDaQui(l1, l2)) return 1;
    return sottolista(l1->next, l2);  // prova a partire dal nodo successivo
}


