//
//  main.c
//  chat es 11 liste -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =======================
   Strutture dati
   ======================= */
typedef struct EL {
    int dato;
    struct EL *next;
} Nodo;

typedef Nodo *Lista;

Lista eliminaKGrandi(Lista L, int k);
/* =======================
   Utility per test
   ======================= */
static Nodo *newNode(int x) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    if(!n) { perror("malloc"); exit(1); }
    n->dato = x;
    n->next = NULL;
    return n;
}

static Lista buildFromArray(const int a[], int n) {
    Lista head = NULL, tail = NULL;
    for(int i = 0; i < n; i++) {
        Nodo *nn = newNode(a[i]);
        if(!head) head = tail = nn;
        else { tail->next = nn; tail = nn; }
    }
    return head;
}

static void printList(const char *label, Lista L) {
    printf("%s", label);
    if(!L) { printf("NULL\n"); return; }
    while(L) {
        printf("%d", L->dato);
        if(L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

static void freeList(Lista L) {
    while(L) {
        Nodo *tmp = L->next;
        free(L);
        L = tmp;
    }
}

static Lista cloneList(Lista L) {
    Lista head = NULL, tail = NULL;
    while(L) {
        Nodo *nn = newNode(L->dato);
        if(!head) head = tail = nn;
        else { tail->next = nn; tail = nn; }
        L = L->next;
    }
    return head;
}

/* =======================
   MAIN di test
   ======================= */
void f(Lista *l, int k);
int main(void) {
    /* Test 1: esempio del testo */
    int t1[] = {10, 3, 2, 1};
    Lista L1 = buildFromArray(t1, 4);

    printf("=== TEST 1 ===\n");
    printList("Input:  ", L1);

    Lista A = cloneList(L1);
    A = eliminaKGrandi(A, 1);
    printList("k=1 ->  ", A);
    freeList(A);

    A = cloneList(L1);
    A = eliminaKGrandi(A, 2);
    printList("k=2 ->  ", A);
    freeList(A);

    freeList(L1);

    /* Test 2: lista più varia */
    int t2[] = {1, 40, 3, 15, 5, 6};
    Lista L2 = buildFromArray(t2, 6);

    printf("\n=== TEST 2 ===\n");
    printList("Input:  ", L2);

    Lista B = cloneList(L2);
    B = eliminaKGrandi(B, 2);
    printList("k=2 ->  ", B);
    freeList(B);

    B = cloneList(L2);
    B = eliminaKGrandi(B, 10);
    printList("k=10 -> ", B);
    freeList(B);

    freeList(L2);

    /* Test 3: casi limite */
    printf("\n=== TEST 3 (limiti) ===\n");
    Lista E = NULL;
    printList("Input:  ", E);
    E = eliminaKGrandi(E, 3);
    printList("k=3 ->  ", E);
    /* E è NULL */

    int t3[] = {7};
    Lista L3 = buildFromArray(t3, 1);
    printList("Input:  ", L3);
    Lista C = eliminaKGrandi(L3, 1);
    printList("k=1 ->  ", C);
    freeList(C);

    return 0;
}

/* =======================
   TODO: NON RISOLVO QUI
   ======================= */
Lista eliminaKGrandi(Lista L, int k) {
    f(&L, k);
    return L;
}
int sommaalladx(Lista head)
    {
        if(head==NULL || head->next==NULL)
            return 0;
    int somma=0;
    head=head->next;
    while (head!=NULL) {
        somma=somma+head->dato;
        head=head->next;
    }
    return somma;
    }
int ver(Lista head)
    {
    if(head==NULL || head->next==NULL)
        return 0;
    int val_now=head->dato;
    if(val_now>sommaalladx(head))
        return 1;
    return 0;
    }
void f(Lista *l, int k) // *pp modifica la lista, pp si sposta lungo la lista
    {
        if(*l==NULL)
            return;
    Lista *pp=l;
    while(*pp!=NULL)
        {
            if(ver(*pp) && k>0)
                {
                    Lista temp=*pp;
                    (*pp)=(*pp)->next;
                    free(temp);
                    k--;
                    pp=l;
                }
            else
                {
                    pp=&(*pp)->next;
                }
        }
    }
