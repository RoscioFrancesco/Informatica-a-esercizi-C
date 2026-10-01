//
//  main.c
//  chat es 12 liste -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//

#include <stdio.h>
#include <stdlib.h>
typedef struct EL {
    int dato;
    struct EL *next;
} Nodo;

typedef Nodo* Lista;

Lista tagliaDaMinimo(Lista L, int k);  // TODO: da implementare
Nodo* newNode(int x) {
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    n->dato = x;
    n->next = NULL;
    return n;
}

Lista buildFromArray(int a[], int n) {
    Lista head = NULL, tail = NULL;
    for(int i = 0; i < n; i++) {
        Nodo* nn = newNode(a[i]);
        if(head == NULL) {
            head = tail = nn;
        } else {
            tail->next = nn;
            tail = nn;
        }
    }
    return head;
}

void printList(const char *msg, Lista L) {
    printf("%s", msg);
    if(L == NULL) {
        printf("NULL\n");
        return;
    }
    while(L != NULL) {
        printf("%d", L->dato);
        if(L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

void freeList(Lista L) {
    while(L) {
        Nodo* tmp = L;
        L = L->next;
        free(tmp);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
void f(Lista *l, int K);
Lista eliminaK(Lista head, int K);
Lista trovaminio(Lista head);
int main() {

    printf("=== TEST 1 ===\n");
    int t1[] = {7,5,9,5,1,8,2};
    Lista L1 = buildFromArray(t1, 7);
    printList("Input:  ", L1);

    Lista R1 = tagliaDaMinimo(L1, 3);
    printList("k=3 ->  ", R1);

    freeList(R1);


    printf("\n=== TEST 2 (minimo in testa) ===\n");
    int t2[] = {1,4,6,2,3};
    Lista L2 = buildFromArray(t2, 5);
    printList("Input:  ", L2);

    Lista R2 = tagliaDaMinimo(L2, 2);
    printList("k=2 ->  ", R2);

    freeList(R2);


    printf("\n=== TEST 3 (minimo in coda) ===\n");
    int t3[] = {4,7,9,2};
    Lista L3 = buildFromArray(t3, 4);
    printList("Input:  ", L3);

    Lista R3 = tagliaDaMinimo(L3, 3);
    printList("k=3 ->  ", R3);

    freeList(R3);


    printf("\n=== TEST 4 (k maggiore del disponibile) ===\n");
    int t4[] = {5,3,6};
    Lista L4 = buildFromArray(t4, 3);
    printList("Input:  ", L4);

    Lista R4 = tagliaDaMinimo(L4, 10);
    printList("k=10 -> ", R4);

    freeList(R4);


    printf("\n=== TEST 5 (lista singola) ===\n");
    int t5[] = {8};
    Lista L5 = buildFromArray(t5, 1);
    printList("Input:  ", L5);

    Lista R5 = tagliaDaMinimo(L5, 3);
    printList("k=3 ->  ", R5);

    freeList(R5);

    return 0;
}



Lista tagliaDaMinimo(Lista L, int k) {
    f(&L, k);
    return L;
}
Lista trovaminio(Lista head)
    {
        if(head==NULL)
            return 0;
        Lista min=head;
        while(head!=NULL)
            {
                if(head->dato<min->dato)
                    min=head;
                head=head->next;
            }
        return min;
    }
Lista eliminaK(Lista head, int K)
    {
            if(head==NULL)
                return head;
    for(int i=0; i<K && head!=NULL ;i++)
        {
            Lista succ=head->next;
            free(head);
            head=succ;
        }
    return head;
    }
void f(Lista *l, int K)
    {
        if(*l==NULL)
            return;
    Lista *pp=l;
    Lista min=trovaminio(*l);
        while(*pp!=NULL)
            {
                if((*pp)==min)
                    {
                        (*pp)=eliminaK(*pp, K);
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
