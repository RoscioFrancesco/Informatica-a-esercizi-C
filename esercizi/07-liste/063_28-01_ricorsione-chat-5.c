//
//  main.c
//  ricorsione chat 5
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

/* ===== ESERCIZIO 5: LISTA QUASI ORDINATA =====
   Una lista è "quasi ordinata" se è non decrescente,
   ma è permesso VIOLARE l'ordine al massimo UNA volta.

   Formalmente: contando i punti in cui l->val > l->next->val,
   questo numero deve essere <= 1.

   Esempi:
     [1,2,3,4]       -> 1
     [1,2,4,3,5]     -> 1  (una violazione: 4>3)
     [1,3,2,5,4]     -> 0  (due violazioni: 3>2 e 5>4)
     [3,2,1]         -> 0  (due violazioni: 3>2 e 2>1)
     [2,2,2]         -> 1
     [] / [x]        -> 1
*/

int quasiOrdinata(Lista l);


/* ===== MAIN DI TEST ===== */
int f(Lista l, int *count);
int main(void) {

    Lista t1  = cons(1, cons(2, cons(3, cons(4, NULL))));               // 1
    Lista t2  = cons(1, cons(2, cons(4, cons(3, cons(5, NULL)))));      // 1
    Lista t3  = cons(1, cons(3, cons(2, cons(5, cons(4, NULL)))));      // 0
    Lista t4  = cons(3, cons(2, cons(1, NULL)));                        // 0
    Lista t5  = cons(2, cons(2, cons(2, NULL)));                        // 1
    Lista t6  = cons(1, NULL);                                          // 1
    Lista t7  = NULL;                                                   // 1
    Lista t8  = cons(1, cons(5, cons(2, cons(3, cons(4, NULL)))));      // 1 (una violazione: 5>2)
    Lista t9  = cons(1, cons(5, cons(2, cons(0, cons(4, NULL)))));      // 0 (violazioni: 5>2 e 2>0)
    Lista t10 = cons(1, cons(1, cons(0, cons(1, NULL))));               // 1 (una violazione: 1>0)

    Lista tests[] = {t1,t2,t3,t4,t5,t6,t7,t8,t9,t10};
    int attesi[]  = { 1, 1, 0, 0, 1, 1, 1, 1, 0,  1};

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        stampa(tests[i]);
        int res = quasiOrdinata(tests[i]);
        printf(" -> %d (atteso %d)\n", res, attesi[i]);
    }

    return 0;
}
/* ===== ESERCIZIO 5: LISTA QUASI ORDINATA =====
   Una lista è "quasi ordinata" se è non decrescente,
   ma è permesso VIOLARE l'ordine al massimo UNA volta.

   Formalmente: contando i punti in cui l->val > l->next->val,
   questo numero deve essere <= 1.

   Esempi:
     [1,2,3,4]       -> 1
     [1,2,4,3,5]     -> 1  (una violazione: 4>3)
     [1,3,2,5,4]     -> 0  (due violazioni: 3>2 e 5>4)
     [3,2,1]         -> 0  (due violazioni: 3>2 e 2>1)
     [2,2,2]         -> 1
     [] / [x]        -> 1
*/

int f(Lista l, int *count)
    {
        if(l==NULL)
            return 1;
        if(l->next==NULL)
            {
                return 1;
            }
        if(l->next->val<l->val)
            {
                (*count)++;
            }
    if(*count>1)
        return 0;
    return f(l->next, count);
    }
int quasiOrdinata(Lista l)
    {
    int count=0;
    return f(l, &count);
    }
