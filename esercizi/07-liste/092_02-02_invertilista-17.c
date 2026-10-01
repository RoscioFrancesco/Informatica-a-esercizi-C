//
//  main.c
//  invertilista -17
//
//  Created by Francesco Roscio Ricon on 02/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =======================
   STRUTTURE DATI
   ======================= */

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef Node* Lista;

/* =======================
   UTILITY: creazione / stampa / free
   ======================= */

static Node* newNode(int v, Node* next) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->next = next;
    return n;
}

static Lista pushFront(Lista l, int v) {
    return newNode(v, l);
}

/* crea lista da array (mantiene l'ordine dell'array) */
static Lista fromArray(const int a[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; i--) {
        l = pushFront(l, a[i]);
    }
    return l;
}

static void printLista(Lista l) {
    printf("[");
    while (l) {
        printf("%d", l->val);
        if (l->next) printf(" -> ");
        l = l->next;
    }
    printf("]\n");
}

static void freeLista(Lista l) {
    while (l) {
        Node* tmp = l;
        l = l->next;
        free(tmp);
    }
}

Lista invertiLista(Lista head) {
    if(head==NULL || head->next==NULL) // se la lista è vuota nulla da invertire, se è un solo nodo è già invertita
        return head;
    Lista temp=invertiLista(head->next);
    head->next->next=head;
    head->next=NULL;
    return temp;
}

/* =======================
   MAIN DI TEST
   ======================= */

int main(void) {
    int a1[] = {1, 2, 3, 4, 5};
    int a2[] = {42};
    int a3[] = {}; /* lista vuota */

    Lista l1 = fromArray(a1, 5);
    Lista l2 = fromArray(a2, 1);
    Lista l3 = NULL;

    printf("=== Test 1 ===\n");
    printf("Originale: ");
    printLista(l1);
    l1 = invertiLista(l1);
    printf("Invertita: ");
    printLista(l1);

    printf("\n=== Test 2 ===\n");
    printf("Originale: ");
    printLista(l2);
    l2 = invertiLista(l2);
    printf("Invertita: ");
    printLista(l2);

    printf("\n=== Test 3 (vuota) ===\n");
    printf("Originale: ");
    printLista(l3);
    l3 = invertiLista(l3);
    printf("Invertita: ");
    printLista(l3);

    freeLista(l1);
    freeLista(l2);
    freeLista(l3);

    return 0;
}
