//
//  main.c
//  liste 2 pag 83 -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//
//


#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int numero;
    struct Node *next;
} Nodo;
typedef Nodo *Lista;

int linziana(Lista lis);

static Lista nuovoNodo(int x) {
    Lista n = (Lista)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->numero = x;
    n->next = NULL;
    return n;
}

static Lista inserisciInCoda(Lista head, int x) {
    Lista n = nuovoNodo(x);
    if (head == NULL) return n;
    Lista cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return head;
}

static void stampaLista(Lista l) {
    while (l != NULL) {
        printf("%d -> ", l->numero);
        l = l->next;
    }
    printf("NULL\n");
}

static void freeLista(Lista l) {
    while (l != NULL) {
        Lista tmp = l->next;
        free(l);
        l = tmp;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {

    /* Lista linziana (dal testo):
       4 2 1 36 18 9 23 87 34 17 64 32 16 8 4 2 1
    */
    int a1[] = {4,2,1,36,18,9,23,87,34,17,64,32,16,8,4,2,1};
    int n1 = (int)(sizeof(a1) / sizeof(a1[0]));
    Lista l1 = NULL;
    for (int i = 0; i < n1; i++)
        l1 = inserisciInCoda(l1, a1[i]);

    /* Lista NON linziana (dal testo):
       4 2 36 18 9 23 87 34 17 64 32 16 8 4 2 1
    */
    int a2[] = {4,2,36,18,9,23,87,34,17,64,32,16,8,4,2,1};
    int n2 = (int)(sizeof(a2) / sizeof(a2[0]));
    Lista l2 = NULL;
    for (int i = 0; i < n2; i++)
        l2 = inserisciInCoda(l2, a2[i]);

    printf("Lista 1 (attesa: linziana):\n");
    stampaLista(l1);

    printf("Lista 2 (attesa: NON linziana):\n");
    stampaLista(l2);
    printf("Lista 1 linziana? %d\n", linziana(l1));
    printf("Lista 2 linziana? %d\n", linziana(l2));

    freeLista(l1);
    freeLista(l2);

    return 0;
}

int linziana(Lista lis) {
    if(lis==NULL || lis->next==NULL)
        return 1;
    if(lis->numero%2==0 && lis->next->numero!=lis->numero/2)
        return 0;
    return linziana(lis->next);
}

