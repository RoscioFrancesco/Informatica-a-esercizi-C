//
//  main.c
//  es 4 chat -1
//
//  Created by Francesco Roscio Ricon on 18/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int val;
    struct nodo* next;
} nodo;

typedef nodo* lista;


void eliminaDominanti(lista *L);

/* =========================
   SUPPORTO PER I TEST
   ========================= */
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
    for(int i = 0; i < n; i++) L = pushBack(L, a[i]);
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
int main(void) {

    /* --- TEST 1 (esempio del testo) --- */
    {
        int a[] = {1, 40, 3, 15, 5, 6};
        lista L = buildFromArray(a, (int)(sizeof(a)/sizeof(a[0])));

        printf("=== TEST 1 ===\n");
        printList("Input : ", L);

        eliminaDominanti(&L);

        printList("Output: ", L);
        printf("\n");

        freeList(L);
    }

    /* --- TEST 2 (testa dominante, da gestire!) --- */
    {
        int a[] = {10, 1, 2, 3};
        lista L = buildFromArray(a, (int)(sizeof(a)/sizeof(a[0])));

        printf("=== TEST 2 ===\n");
        printList("Input : ", L);

        eliminaDominanti(&L);

        printList("Output: ", L);
        printf("\n");

        freeList(L);
    }

    /* --- TEST 3 (tutti non dominanti) --- */
    {
        int a[] = {1, 1, 1, 1};
        lista L = buildFromArray(a, (int)(sizeof(a)/sizeof(a[0])));

        printf("=== TEST 3 ===\n");
        printList("Input : ", L);

        eliminaDominanti(&L);

        printList("Output: ", L);
        printf("\n");

        freeList(L);
    }

    /* --- TEST 4 (lista vuota) --- */
    {
        lista L = NULL;

        printf("=== TEST 4 ===\n");
        printList("Input : ", L);

        eliminaDominanti(&L);

        printList("Output: ", L);
        printf("\n");

        freeList(L);
    }

    /* --- TEST 5 (un solo nodo) --- */
    {
        int a[] = {7};
        lista L = buildFromArray(a, 1);

        printf("=== TEST 5 ===\n");
        printList("Input : ", L);

        eliminaDominanti(&L);

        printList("Output: ", L);
        printf("\n");

        freeList(L);
    }

    return 0;
}
int sommasucc(lista head)
    {
        if(head==NULL && head->next==NULL)
            return 0;
        int somma=0;
        while(head!=NULL)
            {
                somma=somma+head->val;
                head=head->next;
            }
    return somma;
    }

lista f(lista head)
    {
        if(head==NULL || head->next==NULL)
            return head;
        if(head->val>sommasucc(head->next))
            {
                lista temp=head->next;
                free(head);
                head=temp;
                return f(head);
            }
    head->next=f(head->next);
    return head;
    }
void eliminaDominanti(lista *L)
    {
    *L=f(*L);
    }
