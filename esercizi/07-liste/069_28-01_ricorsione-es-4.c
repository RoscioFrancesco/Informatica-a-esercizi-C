//
//  main.c
//  ricorsione es 4
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

/* ===== ESERCIZIO =====
   Verificare RICORSIVAMENTE se la lista alterna PARI/DISPARI
   ad ogni passo. Può iniziare con pari o con dispari.

   Esempi:
     [2,5,8,1] -> 1
     [3,2,1]   -> 1
     [2,4,1]   -> 0  (2 e 4 sono entrambi pari consecutivi)
     [] / [x]  -> 1
*/

int alternaPariDispari(Lista l);


/* ===== MAIN DI TEST ===== */

int main(void) {

    Lista t1 = cons(2, cons(5, cons(8, cons(1, NULL))));          // 1
    Lista t2 = cons(3, cons(2, cons(1, NULL)));                   // 1
    Lista t3 = cons(2, cons(4, cons(1, NULL)));                   // 0
    Lista t4 = cons(1, cons(3, cons(5, NULL)));                   // 0 (tutti dispari)
    Lista t5 = cons(2, cons(4, cons(6, NULL)));                   // 0 (tutti pari)
    Lista t6 = cons(7, NULL);                                     // 1
    Lista t7 = NULL;                                              // 1
    Lista t8 = cons(1, cons(2, cons(3, cons(4, cons(5, NULL))))); // 1
    Lista t9 = cons(1, cons(2, cons(4, NULL)));                   // 0 (2 e 4 pari)
    Lista t10 = cons(0, cons(-1, cons(2, cons(-3, NULL))));       // 1 (pari, dispari, pari, dispari)

    Lista tests[] = {t1,t2,t3,t4,t5,t6,t7,t8,t9,t10};
    int attesi[]  = { 1, 1, 0, 0, 0, 1, 1, 1, 0,  1};

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        stampa(tests[i]);
        int res = alternaPariDispari(tests[i]);
        printf(" -> %d (atteso %d)\n", res, attesi[i]);
    }

    return 0;
}

int alternaPariDispari(Lista l)
    {
        if(l==NULL)
            return 1;
        if(l->next==NULL)
            return 1;
        if(l->val%2==0 && l->next->val%2==0)
            return 0;
        if(l->val%2==1 && l->next->val%2==1)
            return 0;
    return alternaPariDispari(l->next);
    }
