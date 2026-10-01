//  Created by Francesco Roscio Ricon on 13/02/26.

#include <stdio.h>
#include <stdlib.h>

typedef struct N {
    int valore;
    struct N *next;
} Nodo;

typedef Nodo* Lista;

/* =========================
   PROTOTIPO RICHIESTO
   ========================= */
Lista f(Lista A, Lista B);   // TODO: ricorsiva (da implementare tu)

/* =========================
   UTILITY PER I TEST
   ========================= */
static Nodo* newNode(int x) {
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    if(!n) { perror("malloc"); exit(1); }
    n->valore = x;
    n->next = NULL;
    return n;
}

static Lista pushBack(Lista L, int x) {
    Nodo* nn = newNode(x);
    if(L == NULL) return nn;
    Nodo* t = L;
    while(t->next != NULL) t = t->next;
    t->next = nn;
    return L;
}

static Lista buildFromArray(const int a[], int n) {
    Lista L = NULL;
    for(int i = 0; i < n; i++) L = pushBack(L, a[i]);
    return L;
}

static void printList(const char* label, Lista L) {
    printf("%s", label);
    if(L == NULL) { printf("NULL\n"); return; }
    while(L != NULL) {
        printf("%d", L->valore);
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
int trova(Lista head, int x);
Lista inserisciincoda(Lista head, int x);
int main(void) {
    /* Test 1: esempio del testo */
    int a1[] = {1,3,2,5,3,4,5};
    int b1[] = {4,2,6,6,4};
    Lista A = buildFromArray(a1, 7);
    Lista B = buildFromArray(b1, 5);

    printf("=== TEST 1 (esempio testo) ===\n");
    printList("A: ", A);
    printList("B: ", B);

    Lista R = f(A, B);
    printList("R: ", R);

    freeList(A);
    freeList(B);
    freeList(R);

    /* Test 2: duplicati pesanti + intersezioni */
    int a2[] = {2,2,2,7,8};
    int b2[] = {2,9,9,8,8};
    A = buildFromArray(a2, 5);
    B = buildFromArray(b2, 5);

    printf("\n=== TEST 2 (duplicati) ===\n");
    printList("A: ", A);
    printList("B: ", B);

    R = f(A, B);
    printList("R: ", R);

    freeList(A);
    freeList(B);
    freeList(R);

    /* Test 3: casi limite */
    printf("\n=== TEST 3 (limiti) ===\n");
    A = NULL;
    int b3[] = {1,1,2};
    B = buildFromArray(b3, 3);

    printList("A: ", A);
    printList("B: ", B);

    R = f(A, B);
    printList("R: ", R);

    freeList(B);
    freeList(R);

    return 0;
}


Lista f(Lista A, Lista B) {
    Lista new=NULL;
    Lista scorriA=A;
    Lista scorriB=B;
    while (scorriA!=NULL) {
        if(trova(B, scorriA->valore)==0)
            {
                new=inserisciincoda(new, scorriA->valore);
            }
        scorriA=scorriA->next;
    }
    while(scorriB!=NULL)
        {
            if(trova(A, scorriB->valore)==0)
                {
                    new=inserisciincoda(new, scorriB->valore);
                }
            scorriB=scorriB->next;
        }
    return new;
}
int trova(Lista head, int x)
    {
        if(head==NULL)
            return 0;
    while (head!=NULL) {
        if(head->valore==x)
            return 1;
        head=head->next;
    }
    return 0;
    }
Lista inserisciincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=head;
                new->valore=x;
                return new;
            }
    head->next=inserisciincoda(head->next, x);
    return head;
    }
