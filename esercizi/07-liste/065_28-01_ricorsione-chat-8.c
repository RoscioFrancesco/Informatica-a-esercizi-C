//
//  main.c
//  ricorsione chat 8
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



Lista eliminaK(Lista l, int k);


/* ===== MAIN DI TEST ===== */

int main(void) {

    Lista l1 = cons(1, cons(2, cons(3, cons(4, cons(5, cons(6, NULL)))))); // [1..6]
    Lista l2 = cons(1, cons(2, cons(3, cons(4, cons(5, cons(6, NULL)))))); // [1..6]
    Lista l3 = cons(1, cons(2, cons(3, NULL)));                             // [1,2,3]
    Lista l4 = cons(1, cons(2, cons(3, NULL)));                             // [1,2,3]
    Lista l5 = NULL;                                                        // []
    Lista l6 = cons(7, NULL);                                                // [7]

    struct {
        Lista l;
        int k;
        const char *nome;
    } tests[] = {
        {l1, 2,  "k=2 su [1,2,3,4,5,6]  -> atteso [1,3,5]"},
        {l2, 3,  "k=3 su [1,2,3,4,5,6]  -> atteso [1,2,4,5]"},
        {l3, 1,  "k=1 su [1,2,3]        -> atteso []"},
        {l4, 10, "k=10 su [1,2,3]       -> atteso [1,2,3]"},
        {l5, 2,  "k=2 su []             -> atteso []"},
        {l6, 1,  "k=1 su [7]            -> atteso []"},
    };

    int n = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < n; i++) {
        printf("%s\n", tests[i].nome);
        printf("  prima: "); stampa(tests[i].l);

        tests[i].l = eliminaK(tests[i].l, tests[i].k);

        printf("\n  dopo : "); stampa(tests[i].l);
        printf("\n\n");
    }

    return 0;
}
//  elimino il k esimo valore

Lista f(Lista head, int k, int count)
{
    if(head==NULL)
        return head;
    if(count%k==0)
        {
            Lista temp=head->next;
            free(head);
            return f(temp, k, count+1);
        }
    head->next=f(head->next, k, count+1);
    return head;
}
Lista eliminaK(Lista l, int k)
    {
    return f(l, k, 1);
    }
