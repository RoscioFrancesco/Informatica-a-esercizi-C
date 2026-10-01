//
//  main.c
//  es 8 chat -1
//
//  Created by Francesco Roscio Ricon on 18/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE
   ========================= */
typedef struct nodo{
    int val;
    struct nodo* next;
} nodo;

typedef nodo* lista;


int eliminaIntervalliTraZeri(lista *L);

/* =========================
   SUPPORTO TEST
   ========================= */
static nodo* newNode(int x){
    nodo* n = (nodo*)malloc(sizeof(nodo));
    if(!n){ perror("malloc"); exit(1); }
    n->val = x;
    n->next = NULL;
    return n;
}

static lista pushBack(lista L, int x){
    nodo* n = newNode(x);
    if(L == NULL) return n;
    nodo* cur = L;
    while(cur->next) cur = cur->next;
    cur->next = n;
    return L;
}

static lista buildFromArray(const int a[], int n){
    lista L = NULL;
    for(int i=0;i<n;i++) L = pushBack(L, a[i]);
    return L;
}

static void printList(const char* label, lista L){
    printf("%s", label);
    if(L == NULL){ printf("NULL\n"); return; }
    while(L){
        printf("%d", L->val);
        if(L->next) printf(" -> ");
        L = L->next;
    }
    printf("\n");
}

static void freeList(lista L){
    while(L){
        nodo* t = L;
        L = L->next;
        free(t);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void){

    /* --- TEST 1: caso base con due zeri e numeri in mezzo --- */
    {
        int a[] = {5, 0, 7, 8, 0, 9};
        lista L = buildFromArray(a, 6);

        printf("=== TEST 1 ===\n");
        printList("Input : ", L);

        int eliminati = eliminaIntervalliTraZeri(&L);

        printList("Output: ", L);
        printf("Eliminati = %d\n\n", eliminati);

        freeList(L);
    }

    /* --- TEST 2: più intervalli, anche con zeri adiacenti --- */
    {
        int a[] = {0, 1, 2, 0, 3, 0, 0, 4};
        lista L = buildFromArray(a, 8);

        printf("=== TEST 2 ===\n");
        printList("Input : ", L);

        int eliminati = eliminaIntervalliTraZeri(&L);

        printList("Output: ", L);
        printf("Eliminati = %d\n\n", eliminati);

        freeList(L);
    }

    /* --- TEST 3: nessuna coppia di zeri che chiude un intervallo --- */
    {
        int a[] = {1, 0, 2, 3, 4};
        lista L = buildFromArray(a, 5);

        printf("=== TEST 3 ===\n");
        printList("Input : ", L);

        int eliminati = eliminaIntervalliTraZeri(&L);

        printList("Output: ", L);
        printf("Eliminati = %d\n\n", eliminati);

        freeList(L);
    }

    /* --- TEST 4: solo zeri --- */
    {
        int a[] = {0, 0, 0};
        lista L = buildFromArray(a, 3);

        printf("=== TEST 4 ===\n");
        printList("Input : ", L);

        int eliminati = eliminaIntervalliTraZeri(&L);

        printList("Output: ", L);
        printf("Eliminati = %d\n\n", eliminati);

        freeList(L);
    }

    /* --- TEST 5: lista vuota --- */
    {
        lista L = NULL;

        printf("=== TEST 5 ===\n");
        printList("Input : ", L);

        int eliminati = eliminaIntervalliTraZeri(&L);

        printList("Output: ", L);
        printf("Eliminati = %d\n\n", eliminati);

        freeList(L);
    }

    return 0;
}
int blocco(lista head)
    {
        if(head==NULL)
            return 0;
    head=head->next;
    int count=0;
    while(head!=NULL)
        {
            count++;
            if(head->val==0)
                break;
            head=head->next;
        }
    if(head==NULL)
        return 0;
//    printf("\ncount: %d", count);
    return count;
    }
lista distruggiK(lista head, int k)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<k && head!=NULL; i++)
        {
            lista temp=head->next;
            free(head);
            head=temp;
        }
    return head;
    }
int eliminaIntervalliTraZeri(lista *L)
    {
        if(*L==NULL)
            return 0;
        int len=0;
        if((*L)->val==0)
            len=blocco(*L);
        if(len>0)
            {
                (*L)->next=distruggiK((*L)->next, len);
                return len+eliminaIntervalliTraZeri(L);
            }
    return eliminaIntervalliTraZeri(&(*L)->next);
    }
