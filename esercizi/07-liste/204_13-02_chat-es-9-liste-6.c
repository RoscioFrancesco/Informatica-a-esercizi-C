//
//  main.c
//  chat es 9 liste -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA LISTA
   ========================= */
typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;



Lista eliminaK(Lista L, int k);

/* =========================
   UTILITY LISTA
   ========================= */
Lista newNode(int v) {
    Lista n = (Lista)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->next = NULL;
    return n;
}

void pushBack(Lista *L, int v) {
    Lista n = newNode(v);
    if (*L == NULL) { *L = n; return; }
    Lista cur = *L;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = n;
}

Lista buildFromArray(const int a[], int n) {
    Lista L = NULL;
    for (int i = 0; i < n; i++)
        pushBack(&L, a[i]);
    return L;
}

void printList(const char *label, Lista L) {
    printf("%s[", label);
    for (Lista cur = L; cur != NULL; cur = cur->next) {
        printf("%d", cur->val);
        if (cur->next) printf(" -> ");
    }
    printf("]\n");
}

int length(Lista L) {
    int c = 0;
    while (L) {
        c++;
        L = L->next;
    }
    return c;
}

void freeList(Lista L) {
    while (L) {
        Lista tmp = L;
        L = L->next;
        free(tmp);
    }
}


/* =========================
   MAIN DI TEST
   ========================= */
void f(Lista *l, int k);
int main(void) {

    int t1[] = {10, 20, 30, 40, 50, 60};
    int t2[] = {1, 2, 3, 4, 5};
    int t3[] = {7, 8, 9};
    int t4[] = {5, 6, 7, 8, 9, 10, 11};
    int t5[] = {42};

    struct {
        const char *name;
        int *arr;
        int n;
        int k;
    } tests[] = {
        {"T1", t1, 6, 3},
        {"T2", t2, 5, 2},
        {"T3", t3, 3, 1},
        {"T4", t4, 7, 4},
        {"T5", t5, 1, 2},
    };

    int nt = sizeof(tests)/sizeof(tests[0]);

    for (int i = 0; i < nt; i++) {
        Lista L = buildFromArray(tests[i].arr, tests[i].n);

        printf("\n==================== %s (k=%d) ====================\n",
               tests[i].name, tests[i].k);

        printList("Prima: ", L);
        printf("Lunghezza prima: %d\n", length(L));

        L = eliminaK(L, tests[i].k);

        printList("Dopo:  ", L);
        printf("Lunghezza dopo:  %d\n", length(L));

        freeList(L);
    }

    return 0;
}
Lista eliminaK(Lista L, int k) {
    f(&L, k);
    return L;
}
void f(Lista *l, int k)
    {
        if(*l==NULL)
            return;
        int count=1;
    Lista *p=l;
        while(*p!=NULL)
            {
                if(count%k==0)
                    {
                        Lista temp=*p;
                        (*p)=(*p)->next;
                        free(temp);
                    }
                else
                    {
                        p=&((*p)->next);
                    }
                count++;
            }
    }
