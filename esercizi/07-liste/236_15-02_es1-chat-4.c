//
//  main.c
//  es1 chat -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct Nodo {
    int val;
    struct Nodo* next;
} Nodo;
Nodo* eliminaBlocchiDominanti(Nodo* head);

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




/* =========================
   MAIN DI TEST
   ========================= */
void f(Nodo **l);
static void runTest(const char* name, const int a[], int n, const char* expected) {
    printf("=== %s ===\n", name);
    Nodo* L = buildListFromArray(a, n);

    printf("Input:   ");
    printList(L);

    f(&L);

    printf("Output:  ");
    printList(L);

    printf("Atteso:  %s\n", expected);
    printf("\n");

    freeList(L);
}

int main(void) {
    /* TEST 1 (quello del testo)
       Input:  10 -> 3 -> 4 -> 2 -> 8 -> 1 -> 5
       Output: 10 -> 8 -> 5
    */
    int t1[] = {10, 3, 4, 2, 8, 1, 5};
    runTest("Test 1 (esempio)", t1, (int)(sizeof(t1)/sizeof(t1[0])), "10 -> 8 -> 5");

    /* TEST 2 (blocco che mangia tutto fino a fine)
       Input:  5 -> 4 -> 3 -> 2 -> 1
       Output: 5
    */
    int t2[] = {5, 4, 3, 2, 1};
    runTest("Test 2 (tutto < primo)", t2, (int)(sizeof(t2)/sizeof(t2[0])), "5");

    /* TEST 3 (blocco interno enorme)
       Input:  7 -> 1 -> 9 -> 2 -> 3 -> 8 -> 0 -> 6
       - Da 7 elimina 1 (perché 1<7)
       - Poi da 9 elimina 2,3,8,0,6 (tutti <9 fino a fine)
       Output: 7 -> 9
    */
    int t3[] = {7, 1, 9, 2, 3, 8, 0, 6};
    runTest("Test 3 (blocchi multipli)", t3, (int)(sizeof(t3)/sizeof(t3[0])), "7 -> 9");

    /* TEST 4 (nessun blocco su alcuni nodi, ma blocchi su altri)
       Input:  4 -> 5 -> 1 -> 0 -> 6 -> 2
       - 4: next=5 non <4 => nessun blocco
       - 5: elimina 1 e 0 (entrambi <5), si ferma su 6
       - 6: elimina 2 (2<6) fino a fine
       Output: 4 -> 5 -> 6
    */
    int t4[] = {4, 5, 1, 0, 6, 2};
    runTest("Test 4 (blocchi sparsi)", t4, (int)(sizeof(t4)/sizeof(t4[0])), "4 -> 5 -> 6");

    return 0;
}
int contablocco(Nodo *head)
    {
        if(head==NULL)
            return 0;
        int count=0;
        int A=head->val;
        (head)=head->next;
        while(head!=NULL)
            {
                if(head->val>=A)
                    break;
                count++;
                head=head->next;
            }
        return count;
    }
Nodo * distruggiK(Nodo *head, int k)
    {
        if(head==NULL)
            return NULL;
        for(int i=0; i<k; i++)
            {
                Nodo *temp=head->next;
                free(head);
                head=temp;
            }
        return head;
    }
void f(Nodo **l) // rivedi a casa
    {
        if(*l==NULL)
            return;
        Nodo **pp=l;
    while(*pp!=NULL)
        {
            int len=contablocco(*pp);
            if(len>0)
                {
                    (*pp)->next=distruggiK((*pp)->next, len);
                    pp=&(*pp)->next;
                }
            else
                {
                    pp=&(*pp)->next;
                }
        }
    }

