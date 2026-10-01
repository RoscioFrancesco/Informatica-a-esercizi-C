//
//  main.c
//  ricorsione chat 2
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

/* ===== ESERCIZIO 2: LISTA A MONTAGNA =====
   Una lista è "a montagna" se:
   - cresce strettamente per almeno un passo,
   - poi decresce strettamente per almeno un passo,
   - senza uguaglianze (niente valori consecutivi uguali).

   Esempi:
     [1,3,5,4,2] -> 1
     [1,2,3]     -> 0
     [3,2,1]     -> 0
     [1,2,2,1]   -> 0
     [1]         -> 0
     []          -> 0
*/


/* ===== MAIN DI TEST ===== */
int montagna(Lista l);
int main(void) {

    Lista t1 = cons(1, cons(3, cons(5, cons(4, cons(2, NULL))))); // 1
    Lista t2 = cons(1, cons(2, cons(3, NULL)));                   // 0 (solo salita)
    Lista t3 = cons(3, cons(2, cons(1, NULL)));                   // 0 (solo discesa)
    Lista t4 = cons(1, cons(2, cons(2, cons(1, NULL))));          // 0 (uguaglianza)
    Lista t5 = cons(1, cons(3, cons(2, NULL)));                   // 1 (salita+discesa minime)
    Lista t6 = cons(1, cons(1, cons(0, NULL)));                   // 0 (uguaglianza)
    Lista t7 = cons(1, NULL);                                     // 0 (troppo corta)
    Lista t8 = NULL;                                              // 0 (vuota)
    Lista t9 = cons(1, cons(2, cons(1, cons(0, NULL))));          // 1
    Lista t10 = cons(1, cons(4, cons(3, cons(2, cons(2, NULL)))));// 0 (finisce con uguaglianza)

    Lista tests[] = {t1,t2,t3,t4,t5,t6,t7,t8,t9,t10};
    int attesi[]  = { 1, 0, 0, 0, 1, 0, 0, 0, 1,  0};

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        stampa(tests[i]);
        int res = montagna(tests[i]);
        printf(" -> %d (atteso %d)\n", res, attesi[i]);
    }

    return 0;
}

/* ===== ESERCIZIO 2: LISTA A MONTAGNA =====
   Una lista è "a montagna" se:
   - cresce strettamente per almeno un passo,
   - poi decresce strettamente per almeno un passo,
   - senza uguaglianze (niente valori consecutivi uguali).

   Esempi:
     [1,3,5,4,2] -> 1
     [1,2,3]     -> 0
     [3,2,1]     -> 0
     [1,2,2,1]   -> 0
     [1]         -> 0
     []          -> 0
*/

int f(Lista l ,int *s, int *d)
    {
        if(l==NULL)
            return 0;
        if(l->next==NULL)
            return 1;
        if(l->val==l->next->val)
            return 0;
        if(l->next->val>l->val)
            (*s)++;
        else
            (*d)++;
        if(*d>0)
            {
                if(l->next->val>l->val)
                    return 0;
            }
    return f(l->next, s, d);
    }
int montagna(Lista l)
    {
    if(l==NULL)
        return 0;
    int s=0;
    int d=0;
    int ris=f(l, &s, &d);
    if(s==0 || d==0)
        return 0;
    return ris;
    }
