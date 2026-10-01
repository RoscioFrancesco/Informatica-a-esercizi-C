//
//  main.c
//  ricorsione chat
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
    if (!n) {
        perror("malloc");
        exit(1);
    }
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



int pariPrimaDispari(Lista l, int flag);
int wrapper(Lista l);

int main(void) {

    Lista t1 = cons(2, cons(4, cons(6, cons(1, cons(3, NULL)))));
    Lista t2 = cons(2, cons(1, cons(4, NULL)));
    Lista t3 = cons(1, cons(3, cons(5, NULL)));
    Lista t4 = cons(2, cons(4, cons(6, NULL)));
    Lista t5 = NULL;   // lista vuota

    Lista tests[] = {t1, t2, t3, t4, t5};
    int n = 5;

    for (int i = 0; i < n; i++) {
        stampa(tests[i]);
        printf(" -> %d\n", wrapper(tests[i]));
    }

    return 0;
}
int pariPrimaDispari(Lista l, int flag)
    {
        if(l==NULL)
            return 1;
        if(flag==1)
            {
                if(l->val%2==0)
                    return 0;
                return pariPrimaDispari(l->next, flag);
            }
        if(l->val%2==1)
            {
                flag=1;
            }
    return pariPrimaDispari(l->next, flag);
    }
int wrapper(Lista l)
    {
    int flag=0;
    return pariPrimaDispari(l, flag);
    }
