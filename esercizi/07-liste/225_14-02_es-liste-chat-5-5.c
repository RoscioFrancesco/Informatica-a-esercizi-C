//
//  main.c
//  es  liste chat 5 -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct N {
    int v;
    struct N *next;
} Nodo;

typedef Nodo* Lista;

/* =========================
   PROTOTIPO RICHIESTO
   ========================= */
/* Elimina ogni blocco massimale di nodi consecutivi tutti < valore del nodo precedente al blocco */
Lista eliminaBlocchiDominati(Lista L);  // TODO: da implementare

/* =========================
   UTILITY
   ========================= */
static Nodo* newNode(int x) {
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    if(!n) { perror("malloc"); exit(1); }
    n->v = x;
    n->next = NULL;
    return n;
}

static Lista pushBack(Lista L, int x) {
    Nodo* nn = newNode(x);
    if(L == NULL) return nn;
    Nodo* t = L;
    while(t->next) t = t->next;
    t->next = nn;
    return L;
}

static Lista buildFromArray(const int a[], int n) {
    Lista L = NULL;
    for(int i = 0; i < n; i++) L = pushBack(L, a[i]);
    return L;
}

static void printList(const char* msg, Lista L) {
    printf("%s", msg);
    if(L == NULL) { printf("NULL\n"); return; }
    while(L) {
        printf("%d", L->v);
        if(L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

static void freeList(Lista L) {
    while(L) {
        Nodo* tmp = L;
        L = L->next;
        free(tmp);
    }
}
void f(Lista *l);
int lunghezzaBloccoDominato(Lista prev);
int trovaBloccoDominato(Lista prev, Lista *start, Lista *after);
/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    /* Test 1: esempio del testo */
    int t1[] = {10,3,4,2,8,1,1,9};
    Lista L1 = buildFromArray(t1, 8);

    printf("=== TEST 1 (esempio) ===\n");
    printList("Input:  ", L1);
    Lista R1 = eliminaBlocchiDominati(L1);
    printList("Output: ", R1);
    freeList(R1);

    /* Test 2: nessun blocco eliminabile */
    int t2[] = {5,6,7,8};
    Lista L2 = buildFromArray(t2, 4);

    printf("\n=== TEST 2 (nessuna eliminazione) ===\n");
    printList("Input:  ", L2);
    Lista R2 = eliminaBlocchiDominati(L2);
    printList("Output: ", R2);
    freeList(R2);

    /* Test 3: un blocco domina fino alla fine */
    int t3[] = {9,1,2,3};
    Lista L3 = buildFromArray(t3, 4);

    printf("\n=== TEST 3 (blocco fino in fondo) ===\n");
    printList("Input:  ", L3);
    Lista R3 = eliminaBlocchiDominati(L3);
    printList("Output: ", R3);
    freeList(R3);

    /* Test 4: blocchi attaccati con diversi riferimenti */
    int t4[] = {7,1,2,8,0,0,6};
    Lista L4 = buildFromArray(t4, 7);

    printf("\n=== TEST 4 (piu blocchi) ===\n");
    printList("Input:  ", L4);
    Lista R4 = eliminaBlocchiDominati(L4);
    printList("Output: ", R4);
    freeList(R4);

    return 0;
}


Lista eliminaBlocchiDominati(Lista L) {
    f(&L);
    return L;
}
//Per ogni blocco massimale di elementi consecutivi tutti strettamente minori del nodo precedente al blocco, elimina il blocco.
/*
 * Dato prev (nodo prima del blocco), identifica il blocco massimale
 * formato da nodi consecutivi tutti con valore < prev->v.
 *
 * Output:
 *  - *start = primo nodo del blocco (oppure NULL se blocco assente)
 *  - *after = primo nodo dopo il blocco (può essere NULL)
 *  - return = lunghezza del blocco (in nodi)
 */
int lunghezzaBloccoDominato(Lista prev)
{
    if(prev == NULL || prev->next == NULL)
        return 0;

    int ref = prev->v;
    int len = 0;

    Lista curr = prev->next;

    while(curr != NULL && curr->v < ref)
    {
        len++;
        curr = curr->next;
    }

    return len;
}
Lista distruggiK(Lista head, int K)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<K && head!=NULL; i++)
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
                int len=lunghezzaBloccoDominato(*pp);
                if(len>0)
                    {
                        (*pp)->next=distruggiK((*pp)->next, len);
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
