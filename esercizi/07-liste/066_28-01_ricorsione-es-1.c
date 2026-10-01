//
//  main.c
//  ricorsione es 1
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



Lista comprimiX(Lista l, int x);


/* ===== MAIN DI TEST ===== */

int main(void) {

    Lista t1 = cons(1, cons(2, cons(2, cons(2, cons(3, NULL)))));   // [1,2,2,2,3]
    Lista t2 = cons(2, cons(2, cons(2, NULL)));                     // [2,2,2]
    Lista t3 = cons(1, cons(3, NULL));                               // [1,3]
    Lista t4 = cons(2, cons(1, cons(2, cons(2, cons(3, NULL)))));   // [2,1,2,2,3]
    Lista t5 = cons(2, cons(2, cons(3, cons(2, cons(2, NULL)))));   // [2,2,3,2,2]
    Lista t6 = NULL;                                                 // []

    struct {
        Lista l;
        int x;
        int atteso;
        const char *nome;
    } tests[] = {
        {t1, 2, 1, "[1,2,2,2,3]  x=2  -> [1,2,3]"},
        {t2, 2, 1, "[2,2,2]      x=2  -> [2]"},
        {t3, 2, 1, "[1,3]        x=2  -> [1,3]"},
        {t4, 2, 1, "[2,1,2,2,3]  x=2  -> [2,1,2,3]"},
        {t5, 2, 1, "[2,2,3,2,2]  x=2  -> [2,3,2]"},
        {t6, 2, 1, "[]           x=2  -> []"},
    };

    int n = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < n; i++) {
        printf("%s\n", tests[i].nome);
        printf("  prima: "); stampa(tests[i].l);

        tests[i].l = comprimiX(tests[i].l, tests[i].x);

        printf("\n  dopo : "); stampa(tests[i].l);
        printf("\n\n");
    }

    return 0;
}


Lista f(Lista l, int x, int *flag)
    {
        if(l==NULL)
            return l;
        if(*flag==1 && l->val==x)
            {
                Lista temp=l;
                l=l->next;
                free(temp);
                return f(l,x,flag);
            }
        else
            {
                *flag=0;
            }
        if(l->val==x)
            {
                *flag=1;
            }
    l->next=f(l->next, x, flag);
    return l;
    }
Lista comprimiX(Lista l, int x)
    {
    int flag=0;
    return f(l,x,&flag);
    }

