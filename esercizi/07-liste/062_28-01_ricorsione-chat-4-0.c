//
//  main.c
//  ricorsione chat 4.0
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



Lista rimuovi(Lista l, int x);


/* ===== MAIN DI TEST ===== */

int main(void) {

    Lista t1 = cons(1, cons(2, cons(3, cons(2, cons(4, NULL)))));  // [1,2,3,2,4]
    Lista t2 = cons(2, cons(2, cons(2, NULL)));                    // [2,2,2]
    Lista t3 = cons(1, cons(3, cons(5, NULL)));                    // [1,3,5]
    Lista t4 = cons(2, cons(1, cons(2, cons(2, cons(3, NULL)))));  // [2,1,2,2,3]
    Lista t5 = NULL;                                               // []

    struct {
        Lista l;
        int x;
        const char *nome;
    } tests[] = {
        {t1, 2, "rimuovi 2 da [1,2,3,2,4]"},
        {t2, 2, "rimuovi 2 da [2,2,2]"},
        {t3, 2, "rimuovi 2 da [1,3,5]"},
        {t4, 2, "rimuovi 2 da [2,1,2,2,3]"},
        {t5, 2, "rimuovi 2 da []"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("%s\n", tests[i].nome);
        printf("  prima: "); stampa(tests[i].l);

        tests[i].l = rimuovi(tests[i].l, tests[i].x);

        printf("\n  dopo : "); stampa(tests[i].l);
        printf("\n\n");
    }

    return 0;
}

Lista rimuovi(Lista head, int k)
    {
        if(head==NULL)
            return head;
        if(head->val==k)
            {
                Lista temp=head->next;
                free(head);
                head=temp;
                return rimuovi(head, k);
            }
    head->next=rimuovi(head->next, k);
    return head;
    }
