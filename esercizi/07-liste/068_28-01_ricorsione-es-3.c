//
//  main.c
//  ricorsione es 3
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



Lista eliminaDopoX(Lista l, int x);


/* ===== MAIN DI TEST ===== */

int main(void) {

    Lista t1 = cons(1, cons(7, cons(2, cons(7, cons(3, NULL)))));     // [1,7,2,7,3]
    Lista t2 = cons(7, cons(8, NULL));                                 // [7,8]
    Lista t3 = cons(7, NULL);                                          // [7]
    Lista t4 = NULL;                                                   // []
    Lista t5 = cons(1, cons(2, cons(3, NULL)));                        // [1,2,3]
    Lista t6 = cons(7, cons(1, cons(2, cons(7, cons(9, NULL)))));      // [7,1,2,7,9]
    Lista t7 = cons(1, cons(7, cons(7, cons(7, cons(2, NULL)))));      // [1,7,7,7,2]

    struct {
        Lista l;
        int x;
        const char *nome;
    } tests[] = {
        {t1, 7, "[1,7,2,7,3], x=7  -> atteso [1,7,7]"},
        {t2, 7, "[7,8], x=7        -> atteso [7]"},
        {t3, 7, "[7], x=7          -> atteso [7]"},
        {t4, 7, "[], x=7           -> atteso []"},
        {t5, 7, "[1,2,3], x=7      -> atteso [1,2,3]"},
        {t6, 7, "[7,1,2,7,9], x=7  -> atteso [7,2,7]"},
        {t7, 7, "[1,7,7,7,2], x=7  -> atteso [1,7,7]"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("%s\n", tests[i].nome);
        printf("  prima: "); stampa(tests[i].l);

        tests[i].l = eliminaDopoX(tests[i].l, tests[i].x);

        printf("\n  dopo : "); stampa(tests[i].l);
        printf("\n\n");
    }

    return 0;
}

Lista eliminaDopoX(Lista l, int x)
    {
        if(l==NULL || l->next==NULL)
            return l;
        if(l->val==x)
            {
                Lista temp=l->next;
                l->next=temp->next;
                free(temp);
            }
        l->next=eliminaDopoX(l->next, x);
        return l;
    }
