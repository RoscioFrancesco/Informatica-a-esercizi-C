//
//  main.c
//  es 3 chat -3
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

int eliminaSegmentiPari(Lista *L);

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
    /* TEST 1: esempio del testo (tutti segmenti pari => NULL) */
    {
        int v[] = {2, 4, -3, -1, 5, 7};
        Lista L = buildFromArray(v, 6);

        printf("=== TEST 1 ===\n");
        printList("Input : ", L);
        int seg = eliminaSegmentiPari(&L);
        printf("Segmenti eliminati: %d\n", seg);
        printList("Output: ", L);
        printf("\n");

        freeList(&L);
    }

    /* TEST 2: mix (restano segmenti dispari) */
    {
        int v[] = {1, 3, 2, -1, -2, -3, 4, 5, 6, -7, 8};
        Lista L = buildFromArray(v, 11);

        printf("=== TEST 2 ===\n");
        printList("Input : ", L);
        int seg = eliminaSegmentiPari(&L);
        printf("Segmenti eliminati: %d\n", seg);
        printList("Output: ", L);
        printf("\n");

        freeList(&L);
    }

    /* TEST 3: testa eliminata + zeri (>=0) */
    {
        int v[] = {-2, -4, 1, 1, 1, -5, -1, 0, 2};
        Lista L = buildFromArray(v, 9);

        printf("=== TEST 3 ===\n");
        printList("Input : ", L);
        int seg = eliminaSegmentiPari(&L);
        printf("Segmenti eliminati: %d\n", seg);
        printList("Output: ", L);
        printf("\n");

        freeList(&L);
    }

    /* TEST 4: nessun segmento eliminato */
    {
        int v[] = {2, 1, -1, 3, -3, 5};
        Lista L = buildFromArray(v, 6);

        printf("=== TEST 4 ===\n");
        printList("Input : ", L);
        int seg = eliminaSegmentiPari(&L);
        printf("Segmenti eliminati: %d\n", seg);
        printList("Output: ", L);
        printf("\n");

        freeList(&L);
    }

    return 0;
}


int pos(int x)
    {
        if(x>=0)
            return 1;
    return -1;
    }

int blocco(Lista head)
    {
        if(head==NULL)
            return 0;
        int count=0;
        int somma=0;
    int val=pos(head->val);
    while(head!=NULL)
        {
            if(pos(head->val)!=val)
                break;
            count++;
            somma=somma+head->val;
            head=head->next;
        }
    if(somma%2==0)
        return count;
    return 0;
    }

Lista eliminaK(Lista head, int k)
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
void f(Lista *l, int *count)
    {
        if(*l==NULL)
            return;
    Lista *pp=l;
    while(*pp!=NULL)
        {
            int len=blocco(*pp);
            if(len>0)
                {
                    *pp=eliminaK(*pp, len);
                    (*count)++;
                }
            else
                {
                    pp=&(*pp)->next;
                }
        }
    }
int eliminaSegmentiPari(Lista *L)
    {
    int count=0;
    f(L, &count);
    return count;
    }
