//
//  main.c
//  es 3 liste chat -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA LISTA
   ========================= */
typedef struct N {
    int v;
    struct N *next;
} Nodo;

typedef Nodo* Lista;

Lista eliminaBlocchiEstremiUguali(Lista L);

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

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    /* Test 1: esempio del testo */
    int t1[] = {2,5,3,5,2,7,7,8};
    Lista L1 = buildFromArray(t1, 8);

    printf("=== TEST 1 (esempio) ===\n");
    printList("Input:  ", L1);
    Lista R1 = eliminaBlocchiEstremiUguali(L1);
    printList("Output: ", R1);
    freeList(R1);

    /* Test 2: nessun blocco eliminabile */
    int t2[] = {1,2,3,4};
    Lista L2 = buildFromArray(t2, 4);

    printf("\n=== TEST 2 (nessuna eliminazione) ===\n");
    printList("Input:  ", L2);
    Lista R2 = eliminaBlocchiEstremiUguali(L2);
    printList("Output: ", R2);
    freeList(R2);

    /* Test 3: blocco che include tutta la lista */
    int t3[] = {9,1,2,1,9};
    Lista L3 = buildFromArray(t3, 5);

    printf("\n=== TEST 3 (tutta la lista) ===\n");
    printList("Input:  ", L3);
    Lista R3 = eliminaBlocchiEstremiUguali(L3);
    printList("Output: ", R3);
    freeList(R3);

    /* Test 4: più blocchi successivi eliminabili */
    int t4[] = {4,4, 6,7,6, 3,3, 9};
    Lista L4 = buildFromArray(t4, 8);

    printf("\n=== TEST 4 (piu blocchi) ===\n");
    printList("Input:  ", L4);
    Lista R4 = eliminaBlocchiEstremiUguali(L4);
    printList("Output: ", R4);
    freeList(R4);

    return 0;
}


int blocco(Lista head)
    {
        if(head==NULL)
            return 0;
        int value=head->v;
        head=head->next;
        int count=1;
        int max=1;
        while(head!=NULL)
            {
                count++;
                if(head->v==value)
                    max=count;
                head=head->next;
            }
        if(head==NULL && max==1)
            return 0;
        return max;
    }
Lista eliminak(Lista head, int k)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<k && head!=NULL; i++)
        {
            Lista succ=head->next;
            free(head);
            head=succ;
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
                int num=blocco(*pp);
                if(num>0)
                    {
                        *pp=eliminak(*pp, num);
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
Lista eliminaBlocchiEstremiUguali(Lista L) {
    f(&L);
    return L;
}
