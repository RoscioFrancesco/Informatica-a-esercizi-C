//
//  main.c
//  es 3 chat -1
//
//  Created by Francesco Roscio Ricon on 18/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct nodo{
    int val;
    struct nodo* next;
} nodo;

typedef nodo* lista;


void comprimiBlocchiCrescenti(lista *L);

/* =========================
   FUNZIONI DI SUPPORTO (test)
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
lista f(lista head);
int main(void) {

    /* ---- TEST 1 (esempio del testo) ---- */
    {
        int a[] = {1, 3, 5, 2, 4, 7, 6, 8};
        lista L = buildFromArray(a, (int)(sizeof(a)/sizeof(a[0])));

        printf("=== TEST 1 ===\n");
        printList("Input : ", L);

        comprimiBlocchiCrescenti(&L);

        printList("Output: ", L);
        printf("\n");

        freeList(L);
    }

    /* ---- TEST 2 (nessun blocco crescente) ---- */
    {
        int a[] = {5, 4, 3};
        lista L = buildFromArray(a, (int)(sizeof(a)/sizeof(a[0])));

        printf("=== TEST 2 ===\n");
        printList("Input : ", L);

        comprimiBlocchiCrescenti(&L);

        printList("Output: ", L);
        printf("\n");

        freeList(L);
    }

    /* ---- TEST 3 (tutta la lista è un unico blocco crescente) ---- */
    {
        int a[] = {1, 2, 3, 4};
        lista L = buildFromArray(a, (int)(sizeof(a)/sizeof(a[0])));

        printf("=== TEST 3 ===\n");
        printList("Input : ", L);

        comprimiBlocchiCrescenti(&L);

        printList("Output: ", L);
        printf("\n");

        freeList(L);
    }

    /* ---- TEST 4 (blocchi interni + duplicati che spezzano) ---- */
    {
        int a[] = {2, 2, 3, 1, 2};
        lista L = buildFromArray(a, (int)(sizeof(a)/sizeof(a[0])));

        printf("=== TEST 4 ===\n");
        printList("Input : ", L);

        comprimiBlocchiCrescenti(&L);

        printList("Output: ", L);
        printf("\n");

        freeList(L);
    }

    return 0;
}
int blocco(lista head)
{
    if(head==NULL)
        return 0;
    int count=0;
    lista prec=NULL;
    while(head!=NULL)
    {
        if(prec!=NULL)
            {
                if(prec->val>=head->val)
                    break;
            }
            count++;
            prec=head;
            head=head->next;
        }
    return count;
}
int somma(lista head, int count)
    {
    int somma=0;
    for(int i=0; i<count && head!=NULL; i++)
        {
            somma=somma+head->val;
            head=head->next;
        }
    return somma;
    }
lista eliminaK(lista head, int K)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<K && head!=NULL; i++)
        {
            lista temp=head->next;
            free(head);
            head=temp;
        }
    return head;
    }

void comprimiBlocchiCrescenti(lista *L)
    {
        if(*L==NULL)
            return;
    lista *pp=L;
    while(*pp!=NULL)
        {
            int len=blocco(*pp);
            if(len>0)
                {
                    int sum=somma(*pp, len);
                    (*pp)->val=sum;
                    (*pp)->next=eliminaK((*pp)->next, len-1);
                    pp=&(*pp)->next;
                }
            else
                {
                    pp=&(*pp)->next;
                }
        }
    }
