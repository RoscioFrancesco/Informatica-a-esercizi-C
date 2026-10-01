//
//  main.c
//  es 4 chat -3
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

/* ======================
   PROTOTIPO (DA FARE TU)
   ====================== */
void comprimiSomma(Lista *L);

/* ======================
   SUPPORTO: build/print/free
   ====================== */
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
void f(Lista *l);
int main(void) {
    /* TEST 1: esempio del testo */
    {
        int v[] = {2, 2, 2, 5, 5, 7};
        Lista L = buildFromArray(v, 6);

        printf("=== TEST 1 ===\n");
        printList("Prima : ", L);
        comprimiSomma(&L);
        printList("Dopo  : ", L);
        printf("\n");

        freeList(&L);
    }

    /* TEST 2: tutta la lista uguale */
    {
        int v[] = {4, 4, 4, 4};
        Lista L = buildFromArray(v, 4);

        printf("=== TEST 2 ===\n");
        printList("Prima : ", L);
        comprimiSomma(&L);
        printList("Dopo  : ", L);
        printf("\n");

        freeList(&L);
    }

    /* TEST 3: nessun duplicato */
    {
        int v[] = {1, 3, 6, 10};
        Lista L = buildFromArray(v, 4);

        printf("=== TEST 3 ===\n");
        printList("Prima : ", L);
        comprimiSomma(&L);
        printList("Dopo  : ", L);
        printf("\n");

        freeList(&L);
    }

    /* TEST 4: duplicati anche in testa e in coda */
    {
        int v[] = {0, 0, 1, 1, 1, 2, 5, 5, 5};
        Lista L = buildFromArray(v, 9);

        printf("=== TEST 4 ===\n");
        printList("Prima : ", L);
        comprimiSomma(&L);
        printList("Dopo  : ", L);
        printf("\n");

        freeList(&L);
    }

    return 0;
}

int blocco(Lista head)
    {
        if(head==NULL)
            return 0;
        int count=0;
        int val=head->val;
        while(head!=NULL)
            {
                if(head->val!=val)
                    break;
                count++;
                head=head->next;
            }
        return count;
    }
Lista distruggiK(Lista head, int k)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<k && head!=NULL; i++)
        {
            Lista temp=head->next;
            free(head);
            head=temp;
        }
    return head;
    }
void f(Lista *l)
    {
        if(*l==NULL)
            return;
        Lista *pp=l;
        while(*pp!=NULL)
            {
                int len=blocco(*pp);
                if(len>1)
                    {
                        (*pp)->val=(*pp)->val*len;
                        (*pp)->next=distruggiK((*pp)->next, len-1);
                        pp=&(*pp)->next;
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
void comprimiSomma(Lista *L)
    {
    f(L);
    }
