//
//  main.c
//  es 1 chat -3
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
void f(Lista *l, int *count);

int eliminaBlocchiDominati(Lista *L);

static Nodo* newNode(int x) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->val = x;
    n->next = NULL;
    return n;
}

static void pushBack(Lista *L, int x) {
    Nodo *n = newNode(x);
    if (*L == NULL) {
        *L = n;
        return;
    }
    Nodo *cur = *L;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
}

static Lista buildFromArray(const int a[], int n) {
    Lista L = NULL;
    for (int i = 0; i < n; i++) pushBack(&L, a[i]);
    return L;
}

static void printList(const char *label, Lista L) {
    printf("%s", label);
    if (L == NULL) {
        printf("NULL\n");
        return;
    }
    while (L != NULL) {
        printf("%d", L->val);
        if (L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

static void freeList(Lista *L) {
    Nodo *cur = *L;
    while (cur != NULL) {
        Nodo *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    *L = NULL;
}

/* =========================================================
   MAIN DI TEST (stampa input, chiama funzione, stampa output)
   ========================================================= */
int main(void) {
    /* TEST 1: blocchi interni + cascata */
    {
        int v[] = {10, 2, 3, 20, 5, 4, 15};
        Lista L = buildFromArray(v, (int)(sizeof(v)/sizeof(v[0])));
        printf("=== TEST 1 ===\n");
        printList("Input : ", L);
        int rimossi = eliminaBlocchiDominati(&L);
        printf("Rimossi: %d\n", rimossi);
        printList("Output: ", L);
        freeList(&L);
        printf("\n");
    }

    /* TEST 2: blocco dominato che parte dalla testa (cambio testa) */
    {
        int v[] = {1, 2, 3, 0, 4};
        Lista L = buildFromArray(v, (int)(sizeof(v)/sizeof(v[0])));
        printf("=== TEST 2 ===\n");
        printList("Input : ", L);
        int rimossi = eliminaBlocchiDominati(&L);
        printf("Rimossi: %d\n", rimossi);
        printList("Output: ", L);
        freeList(&L);
        printf("\n");
    }

    /* TEST 3: cascata forte dalla testa */
    {
        int v[] = {5, 1, 2, 3, 4, 6};
        Lista L = buildFromArray(v, (int)(sizeof(v)/sizeof(v[0])));
        printf("=== TEST 3 ===\n");
        printList("Input : ", L);
        int rimossi = eliminaBlocchiDominati(&L);
        printf("Rimossi: %d\n", rimossi);
        printList("Output: ", L);
        freeList(&L);
        printf("\n");
    }

    /* TEST 4: eliminazioni a blocchi + nuove dominanze create */
    {
        int v[] = {8, 7, 6, 9, 1, 2, 10};
        Lista L = buildFromArray(v, (int)(sizeof(v)/sizeof(v[0])));
        printf("=== TEST 4 ===\n");
        printList("Input : ", L);
        int rimossi = eliminaBlocchiDominati(&L);
        printf("Rimossi: %d\n", rimossi);
        printList("Output: ", L);
        freeList(&L);
        printf("\n");
    }

    return 0;
}
int blocco(Lista head)
    {
        if(head==NULL)
            return 0;
        int count=0;
        int val=head->val;
        head=head->next;
        while(head!=NULL)
            {
                if(head->val>val)
                    break;
                count++;
                head=head->next;
            }
    return count;
    }

Lista eliminaK(Lista head, int K)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<K; i++)
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
                    (*pp)->next=eliminaK((*pp)->next, len);
                    (*count)=(*count)+len;
                    pp=l;
                }
            else
                {
                    pp=&(*pp)->next;
                }
        }
    }
int eliminaBlocchiDominati(Lista *L)
    {
    int count=0;
    f(L, &count);
    return count;
    }
