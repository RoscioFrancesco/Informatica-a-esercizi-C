//
//  main.c
//  es 6 chat -1
//
//  Created by Francesco Roscio Ricon on 18/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int val;
    struct nodo* next;
} nodo;

typedef nodo* lista;

lista fondeSeMaggiore(lista L1, lista L2);

static nodo* newNode(int x) {
    nodo* n = (nodo*)malloc(sizeof(nodo));
    if(!n) { perror("malloc"); exit(1); }
    n->val = x;
    n->next = NULL;
    return n;
}

static lista pushBack(lista L, int x) {
    nodo* n = newNode(x);
    if(L == NULL) return n;
    nodo* cur = L;
    while(cur->next != NULL) cur = cur->next;
    cur->next = n;
    return L;
}

static lista buildFromArray(const int a[], int n) {
    lista L = NULL;
    for(int i = 0; i < n; i++)
        L = pushBack(L, a[i]);
    return L;
}

static void printList(const char* label, lista L) {
    printf("%s", label);
    if(L == NULL) {
        printf("NULL\n");
        return;
    }
    while(L != NULL) {
        printf("%d", L->val);
        if(L->next != NULL) printf(" -> ");
        L = L->next;
    }
    printf("\n");
}

static void freeList(lista L) {
    while(L != NULL) {
        nodo* tmp = L;
        L = L->next;
        free(tmp);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
lista f(lista l1, lista l2);
int main(void) {

    /* --- TEST 1 (esempio del testo) --- */
    {
        int a1[] = {3, 8, 5};
        int a2[] = {4, 2, 7};

        lista L1 = buildFromArray(a1, 3);
        lista L2 = buildFromArray(a2, 3);

        printf("=== TEST 1 ===\n");
        printList("L1: ", L1);
        printList("L2: ", L2);

        lista R = fondeSeMaggiore(L1, L2);

        printList("Risultato: ", R);
        printf("\n");

        /* verifico che le originali siano intatte */
        printList("L1 dopo: ", L1);
        printList("L2 dopo: ", L2);
        printf("\n");

        freeList(L1);
        freeList(L2);
        freeList(R);
    }

    /* --- TEST 2 (mai inserire L2) --- */
    {
        int a1[] = {5, 6, 7};
        int a2[] = {1, 2, 3};

        lista L1 = buildFromArray(a1, 3);
        lista L2 = buildFromArray(a2, 3);

        printf("=== TEST 2 ===\n");
        printList("L1: ", L1);
        printList("L2: ", L2);

        lista R = fondeSeMaggiore(L1, L2);

        printList("Risultato: ", R);
        printf("\n");

        freeList(L1);
        freeList(L2);
        freeList(R);
    }

    /* --- TEST 3 (sempre inserire L2) --- */
    {
        int a1[] = {1, 2, 3};
        int a2[] = {4, 5, 6};

        lista L1 = buildFromArray(a1, 3);
        lista L2 = buildFromArray(a2, 3);

        printf("=== TEST 3 ===\n");
        printList("L1: ", L1);
        printList("L2: ", L2);

        lista R = fondeSeMaggiore(L1, L2);

        printList("Risultato: ", R);
        printf("\n");

        freeList(L1);
        freeList(L2);
        freeList(R);
    }

    /* --- TEST 4 (valori uguali) --- */
    {
        int a1[] = {2, 4, 6};
        int a2[] = {2, 5, 6};

        lista L1 = buildFromArray(a1, 3);
        lista L2 = buildFromArray(a2, 3);

        printf("=== TEST 4 ===\n");
        printList("L1: ", L1);
        printList("L2: ", L2);

        lista R = fondeSeMaggiore(L1, L2);

        printList("Risultato: ", R);
        printf("\n");

        freeList(L1);
        freeList(L2);
        freeList(R);
    }

    return 0;
}
lista inserisciincoda(lista head, int x)
    {
        if(head==NULL)
            {
                lista new=(lista)malloc(sizeof(nodo));
                new->next=NULL;
                new->val=x;
                return new;
            }
        head->next=inserisciincoda(head->next, x);
        return head;
    }
lista fondeSeMaggiore(lista l1, lista l2)
    {
        if(l1==NULL || l2==NULL)
            return NULL;
        lista new=NULL;
    lista scorri1=l1;
    lista scorri2=l2;
    while(scorri1!=NULL && scorri2!=NULL)
        {
            new=inserisciincoda(new, scorri1->val);
            int val=scorri1->val;
            scorri1=scorri1->next;
            if(scorri2->val>val)
                {
                    new=inserisciincoda(new, scorri2->val);
                }
            scorri2=scorri2->next;
        }
    return new;
    }

