//
//  main.c
//  es 3 chat int -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int valore;
    struct nodo *next;
} Nodo;

typedef Nodo* lista;
lista eliminaCrescentiInterni(lista L);

/* ===== helper ===== */
static Nodo* newNode(int v) {
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    n->valore = v;
    n->next = NULL;
    return n;
}

static lista buildList(const int v[], int n) {
    if (n <= 0) return NULL;
    Nodo *head = newNode(v[0]), *tail = head;
    for (int i = 1; i < n; i++) {
        tail->next = newNode(v[i]);
        tail = tail->next;
    }
    return head;
}

static void printList(const char *msg, lista L) {
    printf("%s", msg);
    if (!L) { printf("NULL\n"); return; }
    while (L) {
        printf("%d", L->valore);
        if (L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

static void freeList(lista L) {
    while (L) {
        Nodo *tmp = L->next;
        free(L);
        L = tmp;
    }
}

int main(void) {
    /* T1: blocco interno classico */
    int v1[] = {20, 3, 5, 8, 4, 2};
    lista L1 = buildList(v1, 6);
    printList("T1 prima : ", L1);
    L1 = eliminaCrescentiInterni(L1);
    printList("T1 dopo  : ", L1);
    printf("\n");

    /* T2: blocco crescente corto */
    int v2[] = {5, 2, 4, 1};
    lista L2 = buildList(v2, 4);
    printList("T2 prima : ", L2);
    L2 = eliminaCrescentiInterni(L2);
    printList("T2 dopo  : ", L2);
    printf("\n");

    /* T3: blocco crescente in testa */
    int v3[] = {2, 3, 6, 9, 4};
    lista L3 = buildList(v3, 5);
    printList("T3 prima : ", L3);
    L3 = eliminaCrescentiInterni(L3);
    printList("T3 dopo  : ", L3);
    printf("\n");

    /* T4: blocco crescente fino a fine */
    int v4[] = {10, 1, 2, 3, 4};
    lista L4 = buildList(v4, 5);
    printList("T4 prima : ", L4);
    L4 = eliminaCrescentiInterni(L4);
    printList("T4 dopo  : ", L4);
    printf("\n");

    /* T5: più blocchi crescenti */
    int v5[] = {15, 4, 6, 9, 3, 7, 8, 2};
    lista L5 = buildList(v5, 8);
    printList("T5 prima : ", L5);
    L5 = eliminaCrescentiInterni(L5);
    printList("T5 dopo  : ", L5);
    printf("\n");

    /* T6: nessun blocco crescente (tutti decrescenti o uguali) */
    int v6[] = {9, 7, 7, 3, 1};
    lista L6 = buildList(v6, 5);
    printList("T6 prima : ", L6);
    L6 = eliminaCrescentiInterni(L6);
    printList("T6 dopo  : ", L6);
    printf("\n");

    freeList(L1);
    freeList(L2);
    freeList(L3);
    freeList(L4);
    freeList(L5);
    freeList(L6);
    return 0;
}

int blocco(lista head)
    {
        if(head==NULL)
            return 0;
        int count=0;
    while (head!=NULL && head->next!=NULL) {
        if(head->valore>=head->next->valore)
            {
                break;
            }
        count++;
        head=head->next;
    }
    if(head==NULL)
        return 0;
    return count;
    }
lista distruggiK(lista head, int k)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<=k; i++)
        {
            lista succ=head->next;
            free(head);
            head=succ;
        }
    return head;
    }
void f(lista *l) // passop er riferimento la lista in modo tale da riuscire a modificare la testa
    {
        if(*l==NULL) // l è l'indirizzo del puntatore che punta alla testa, *l è la testa della lista,
            return;
        lista *pp=l;
        while(*pp!=NULL)
            {
                int num=blocco(*pp);
                if(num>0)
                    {
                        (*pp)=distruggiK(*pp, num); // *pp è il nodo corrente e sto riassegnando il puntatore che porta al nodo corrente, poir riparto ad eliminare da qua
                    }
                else
                    {
                        pp=&(*pp)->next; // pp è l'indirizzo del puntatore che punta al nodo corrente
                    }
            }
    }
lista eliminaCrescentiInterni(lista L)
    {
    f(&L);
    return L;
    }
