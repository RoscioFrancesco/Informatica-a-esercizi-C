//
//  main.c
//  es2 chat -3
//
//  Created by Francesco Roscio Ricon on 16/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int val;
    struct Nodo* next;
} Nodo;

Nodo* eliminaBlocchiPari(Nodo* head);

static Nodo* newNode(int x) {
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->val = x;
    n->next = NULL;
    return n;
}

static Nodo* pushBack(Nodo* head, int x) {
    Nodo* n = newNode(x);
    if (!head) return n;
    Nodo* cur = head;
    while (cur->next) cur = cur->next;
    cur->next = n;
    return head;
}

static Nodo* buildListFromArray(const int a[], int n) {
    Nodo* head = NULL;
    for (int i = 0; i < n; i++) head = pushBack(head, a[i]);
    return head;
}

static void printList(const Nodo* head) {
    const Nodo* cur = head;
    if (!cur) { printf("(vuota)\n"); return; }
    while (cur) {
        printf("%d", cur->val);
        if (cur->next) printf(" -> ");
        cur = cur->next;
    }
    printf("\n");
}

static void freeList(Nodo* head) {
    while (head) {
        Nodo* tmp = head;
        head = head->next;
        free(tmp);
    }
}


void f(Nodo **l);
Nodo* eliminaBlocchiPari(Nodo* head) {
    f(&head);
    return head;
}

/* =========================
   TEST
   ========================= */
static void runTest(const char* name, const int a[], int n, const char* expected) {
    printf("=== %s ===\n", name);
    Nodo* L = buildListFromArray(a, n);

    printf("Input:   ");
    printList(L);

    L = eliminaBlocchiPari(L);

    printf("Output:  ");
    printList(L);

    printf("Atteso:  %s\n\n", expected);

    freeList(L);
}

int main(void) {
    /* TEST 1 (esempio del testo) */
    int t1[] = {4, 6, 3, 8, 10, 12, 5, 2};
    runTest("Test 1 (esempio)", t1, (int)(sizeof(t1)/sizeof(t1[0])), "3 -> 5 -> 2");

    /* TEST 2 (blocco in testa) */
    int t2[] = {2, 4, 6, 7, 9};
    runTest("Test 2 (blocco in testa)", t2, (int)(sizeof(t2)/sizeof(t2[0])), "7 -> 9");

    /* TEST 3 (blocco in coda) */
    int t3[] = {1, 3, 5, 8, 10};
    runTest("Test 3 (blocco in coda)", t3, (int)(sizeof(t3)/sizeof(t3[0])), "1 -> 3 -> 5");

    /* TEST 4 (lista tutta pari, lunghezza >= 2) */
    int t4[] = {2, 4, 6, 8};
    runTest("Test 4 (tutta pari)", t4, (int)(sizeof(t4)/sizeof(t4[0])), "(vuota)");

    /* TEST 5 (pari singolo che resta + blocco interno) */
    int t5[] = {1, 2, 3, 4, 6, 5, 8, 7};
    /* 2 resta (lunghezza 1), 4-6 eliminati, 8 resta (lunghezza 1) */
    runTest("Test 5 (singoli pari + blocco interno)", t5, (int)(sizeof(t5)/sizeof(t5[0])), "1 -> 2 -> 3 -> 5 -> 8 -> 7");

    return 0;
}

int contablocchi(Nodo *head)
    {
    if (head==NULL) {
        return 0;
        }
    int count=0;
    while(head!=NULL)
        {
            if(head->val%2==1)
                break;
            count++;
            head=head->next;
        }
    return count;
    }
Nodo * eliminaK(Nodo *head, int K)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<K && head!=NULL; i++)
        {
            Nodo * temp=head->next;
            free(head);
            head=temp;
        }
    return head;
    }

void f(Nodo **l)
    {
        if(l==NULL || *l==NULL)
            return;
        Nodo **pp=l; // pp contien l'indirizzo dela head(ovvero l'indirizzo del puntatore al primo nodo della lista), dereferenziando pp(ovvero  facedno *pp si ottiene l'indirizzo della nodo testa ), mentre *pp è il nodo vero e proprio.
        while (*pp!=NULL) {
                int num=contablocchi(*pp);
                if(num>=2)
                {
                    (*pp)=eliminaK((*pp), num);
                    pp=l;
                }
                else
                    {
                        pp=&(*pp)->next;
                    }
        }
    }
