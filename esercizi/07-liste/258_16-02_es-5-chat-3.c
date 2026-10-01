//
//  main.c
//  es 5 chat -3
//
//  Created by Francesco Roscio Ricon on 16/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

int eliminaFinestre(Lista *L);

static Nodo* newNode(int x) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->val = x;
    n->next = NULL;
    return n;
}

static void pushBack(Lista *L, int x) {
    Nodo *n = newNode(x);
    if (*L == NULL) { *L = n; return; }
    Nodo *cur = *L;
    while (cur->next) cur = cur->next;
    cur->next = n;
}

static Lista buildFromArray(const int a[], int n) {
    Lista L = NULL;
    for (int i = 0; i < n; i++) pushBack(&L, a[i]);
    return L;
}

static void printList(const char *label, Lista L) {
    printf("%s", label);
    if (!L) { printf("NULL\n"); return; }
    while (L) {
        printf("%d", L->val);
        if (L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

static void freeList(Lista *L) {
    Nodo *cur = *L;
    while (cur) {
        Nodo *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    *L = NULL;
}

/* ======================
   MAIN DI TEST
   ====================== */
int main(void) {
    /* TEST 1: esempio del testo */
    {
        int v[] = {1, 3, 2, 5, 3};
        Lista L = buildFromArray(v, 5);

        printf("=== TEST 1 ===\n");
        printList("Prima : ", L);
        int elim = eliminaFinestre(&L);
        printf("Eliminazioni: %d\n", elim);
        printList("Dopo  : ", L);
        printf("\n");

        freeList(&L);
    }

    /* TEST 2: nessuna eliminazione */
    {
        int v[] = {1, 2, 4, 8, 16};
        Lista L = buildFromArray(v, 5);

        printf("=== TEST 2 ===\n");
        printList("Prima : ", L);
        int elim = eliminaFinestre(&L);
        printf("Eliminazioni: %d\n", elim);
        printList("Dopo  : ", L);
        printf("\n");

        freeList(&L);
    }

    /* TEST 3: eliminazioni che creano nuove finestre */
    {
        int v[] = {2, 5, 3, 8, 5, 13, 8};
        Lista L = buildFromArray(v, 7);

        printf("=== TEST 3 ===\n");
        printList("Prima : ", L);
        int elim = eliminaFinestre(&L);
        printf("Eliminazioni: %d\n", elim);
        printList("Dopo  : ", L);
        printf("\n");

        freeList(&L);
    }

    /* TEST 4: lista corta (meno di 3 nodi) */
    {
        int v[] = {7, 7};
        Lista L = buildFromArray(v, 2);

        printf("=== TEST 4 ===\n");
        printList("Prima : ", L);
        int elim = eliminaFinestre(&L);
        printf("Eliminazioni: %d\n", elim);
        printList("Dopo  : ", L);
        printf("\n");

        freeList(&L);
    }

    return 0;
}

int ver(Lista a, Lista b, Lista c) // 1 se va eliminato
    {
        if(a==NULL || c==NULL)
            return 0;
        if(a->val+c->val==b->val)
            return 1;
    return 0;
    }

void f(Lista *l)
    {
        if(*l==NULL)
            return;
        Lista *pp=l;
        Lista prec=NULL;
        while(*pp!=NULL)
            {
                Lista succ=(*pp)->next;
                if(ver(prec, (*pp), succ))
                    {
                        Lista temp=(*pp);
                        (*pp)=(*pp)->next;
                        free(temp);
                        pp=l;
                    }
                else
                    {
                        prec=*pp;
                        pp=&(*pp)->next;
                    }
            }
    }
int eliminaFinestre(Lista *L)
    {
    f(L);
    return 0;
    }
