//
//  main.c
//  ricorsione es 2
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




/* ===== MAIN DI TEST ===== */

Lista f(Lista l, int count);
Lista eliminaPariPos(Lista l);
int main(void) {

    Lista t1 = cons(10, cons(20, cons(30, cons(40, cons(50, NULL))))); // [10,20,30,40,50]
    Lista t2 = cons(1,  cons(2,  cons(3,  cons(4,  NULL))));          // [1,2,3,4]
    Lista t3 = cons(7, NULL);                                         // [7]
    Lista t4 = NULL;                                                  // []
    Lista t5 = cons(1, cons(2, cons(3, cons(4, cons(5, NULL)))));      // [1,2,3,4,5]
    Lista t6 = cons(2, cons(4, cons(6, cons(8, NULL))));               // [2,4,6,8]

    struct {
        Lista l;
        const char *nome;
    } tests[] = {
        {t1, "[10,20,30,40,50] -> atteso [10,30,50]"},
        {t2, "[1,2,3,4]        -> atteso [1,3]"},
        {t3, "[7]              -> atteso [7]"},
        {t4, "[]               -> atteso []"},
        {t5, "[1,2,3,4,5]      -> atteso [1,3,5]"},
        {t6, "[2,4,6,8]        -> atteso [2,6]"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("%s\n", tests[i].nome);
        printf("  prima: "); stampa(tests[i].l);

        tests[i].l = eliminaPariPos(tests[i].l);

        printf("\n  dopo : "); stampa(tests[i].l);
        printf("\n\n");
    }

    return 0;
}


Lista eliminaPariPos(Lista l)
    {
    return f(l, 1);
    }
Lista f(Lista l, int count)
    {
        if(l==NULL)
            return NULL;
        if(count%2==0)
            {
                Lista temp=l;
                l=l->next;
                free(temp);
                return f(l, count+1);
            }
    l->next=f(l->next, count+1);
    return l;
    }
