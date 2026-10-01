//
//  main.c
//  ricorsione chat 6
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

/* ===== ESERCIZIO 6: ZIG-ZAG =====
   Una lista è zig-zag se confrontando ogni coppia consecutiva
   alterna strettamente "<" e ">" (nessuna uguaglianza).

   Esempi:
     [1,3,2,4,3] -> 1   (1<3>2<4>3)
     [3,1,2,1]   -> 1   (3>1<2>1)
     [1,2,3]     -> 0   (1<2<3 non alterna)
     [1,1,2]     -> 0   (uguaglianza)
     [] / [x]    -> 1
     [2,1]       -> 1
*/
int zigag(Lista l);
int f(Lista l, int b);

int main(void) {

    Lista t1  = cons(1, cons(3, cons(2, cons(4, cons(3, NULL))))); // 1
    Lista t2  = cons(3, cons(1, cons(2, cons(1, NULL))));          // 1
    Lista t3  = cons(1, cons(2, cons(3, NULL)));                   // 0
    Lista t4  = cons(1, cons(1, cons(2, NULL)));                   // 0
    Lista t5  = NULL;                                              // 1
    Lista t6  = cons(7, NULL);                                     // 1
    Lista t7  = cons(2, cons(1, NULL));                            // 1
    Lista t8  = cons(1, cons(2, cons(1, cons(2, cons(1, NULL))))); // 1
    Lista t9  = cons(1, cons(2, cons(1, cons(1, NULL))));          // 0 (uguaglianza finale)
    Lista t10 = cons(5, cons(4, cons(3, cons(2, cons(1, NULL))))); // 0 (sempre decrescente)

    Lista tests[] = {t1,t2,t3,t4,t5,t6,t7,t8,t9,t10};
    int attesi[]  = { 1, 1, 0, 0, 1, 1, 1, 1, 0,  0};

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        stampa(tests[i]);
        int res = zigag(tests[i]);
        printf(" -> %d (atteso %d)\n", res, attesi[i]);
    }

    return 0;
}

int f(Lista l, int b) // se b=0 allora il prossimo deve essere più grande, se b=1 allora il prossimo deve essere più picolo
    {
        if(l==NULL)
            return 1;
        if(l->next==NULL)
            return 1;
        if(l->val==l->next->val)
            return 0;
        if(b==0)
            {
                if(l->val>l->next->val)
                    return 0;
                else
                    return f(l->next, 1);
            }
        if(b==1)
            {
                if(l->val<l->next->val)
                    return 0;
                else
                    return f(l->next, 0);
            }
        return 0;
    }
int zigag(Lista l)
    {
    return f(l,0) || f(l, 1);
    }
