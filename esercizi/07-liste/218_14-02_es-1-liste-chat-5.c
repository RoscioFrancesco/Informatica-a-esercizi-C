//
//  main.c
//  es 1 liste chat  -5
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

/* Elimina blocchi sotto soglia mobile: soglia = media reale dei 2 precedenti (nella lista originale) */
Lista eliminaSottoSogliaMobile(Lista L);  // TODO: da implementare

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
void f(Lista *l);
int main(void) {
    /* Test 1: esempio */
    int t1[] = {7,5,3,2,9,1,4,10};
    Lista L1 = buildFromArray(t1, 8);

    printf("=== TEST 1 (esempio) ===\n");
    printList("Input:  ", L1);
    Lista R1 = eliminaSottoSogliaMobile(L1);
    printList("Output: ", R1);
    freeList(R1);

    /* Test 2: blocco che parte dal 3° nodo e si estende */
    int t2[] = {10, 0, 4, 3, 2, 9};
    Lista L2 = buildFromArray(t2, 6);

    printf("\n=== TEST 2 ===\n");
    printList("Input:  ", L2);
    Lista R2 = eliminaSottoSogliaMobile(L2);
    printList("Output: ", R2);
    freeList(R2);

    /* Test 3: nessun blocco eliminabile */
    int t3[] = {1, 2, 3, 4, 5};
    Lista L3 = buildFromArray(t3, 5);

    printf("\n=== TEST 3 (nessuna eliminazione) ===\n");
    printList("Input:  ", L3);
    Lista R3 = eliminaSottoSogliaMobile(L3);
    printList("Output: ", R3);
    freeList(R3);

    return 0;
}


Lista eliminaSottoSogliaMobile(Lista L) {
    f(&L);
    return L;
}
float media(int a, int b)
    {
    return (a+b)/2.0f;
    }

int vaiavanti(Lista prev1, Lista prev2, Lista now)
    {
        if(prev1==NULL || prev2==NULL)
            return 0;
    float m=media(prev1->v, prev2->v);
    if(now->v<m)
        return 1;
    return 0;
    }
int blocco(Lista now, Lista prev1, Lista prev2)
    {
        if(now==NULL)
            return 0;
        int count=0;
        while(now!=NULL)
            {
                if(vaiavanti(prev1, prev2, now)==0)
                    break;
                count++;
                prev1=prev1->next;
                prev2=prev2->next;
                now=now->next;
            }
        return count;
    }

Lista distruggiK(Lista head, int k)
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
        if(*l==NULL || (*l)->next==NULL || (*l)->next->next==NULL)
            return;
        Lista *pp=l;
        pp=&((*l)->next->next);
        Lista *prev1=l;
        Lista *prev2=&(*l)->next;
        while(*pp!=NULL)
            {
                int num=blocco(*pp, *prev1, *prev2);
                if(num>0)
                    {
                        *pp=distruggiK(*pp, num);
                    }
                else
                    {
                        pp=&(*pp)->next;
                        prev1=&(*prev1)->next;
                        prev2=&(*prev2)->next;
                    }
            }
    }
