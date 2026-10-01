//
//  main.c
//  es 2 chat int -5
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


lista eliminaBlocchiChiusi(lista L);

/* ===== Helper ===== */

Nodo* newNode(int v) {
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    n->valore = v;
    n->next = NULL;
    return n;
}

lista buildList(int v[], int n) {
    if (n == 0) return NULL;

    Nodo* head = newNode(v[0]);
    Nodo* tail = head;

    for (int i = 1; i < n; i++) {
        tail->next = newNode(v[i]);
        tail = tail->next;
    }
    return head;
}

void printList(const char* msg, lista L) {
    printf("%s", msg);
    if (!L) {
        printf("NULL\n");
        return;
    }
    while (L) {
        printf("%d", L->valore);
        if (L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

void freeList(lista L) {
    while (L) {
        Nodo* tmp = L->next;
        free(L);
        L = tmp;
    }
}

int main() {

    /* T1: esempio del testo */
    int v1[] = {5,2,3,5,7,8,7,1};
    lista L1 = buildList(v1, 8);

    printList("T1 prima : ", L1);
    L1 = eliminaBlocchiChiusi(L1);
    printList("T1 dopo  : ", L1);
    printf("\n");

    /* T2: nessun blocco */
    int v2[] = {1,2,3,4};
    lista L2 = buildList(v2, 4);

    printList("T2 prima : ", L2);
    L2 = eliminaBlocchiChiusi(L2);
    printList("T2 dopo  : ", L2);
    printf("\n");

    /* T3: blocco fino a fine lista */
    int v3[] = {9,4,5,6,9};
    lista L3 = buildList(v3, 5);

    printList("T3 prima : ", L3);
    L3 = eliminaBlocchiChiusi(L3);
    printList("T3 dopo  : ", L3);
    printf("\n");

    /* T4: blocchi annidati */
    int v4[] = {1,2,3,2,1};
    lista L4 = buildList(v4, 5);

    printList("T4 prima : ", L4);
    L4 = eliminaBlocchiChiusi(L4);
    printList("T4 dopo  : ", L4);
    printf("\n");

    /* T5: valori uguali consecutivi */
    int v5[] = {7,7,8,9};
    lista L5 = buildList(v5, 4);

    printList("T5 prima : ", L5);
    L5 = eliminaBlocchiChiusi(L5);
    printList("T5 dopo  : ", L5);
    printf("\n");

    freeList(L1);
    freeList(L2);
    freeList(L3);
    freeList(L4);
    freeList(L5);

    return 0;
}
/*
Blocco chiuso tra due valori uguali V:

V -> (nodi diversi da V) -> V

- il primo V resta
- si eliminano tutti i nodi intermedi
- si elimina anche il secondo V
- si eliminano tutti i blocchi presenti nella lista
*/
int blocco(lista head)
    {
        if(head==NULL)
            return 0;
        int val=head->valore;
    int count=1;
        head=head->next;
        while (head!=NULL) {
        if(head->valore==val)
            break;
        count++;
        head=head->next;
        }
    if(head==NULL)
        return 0;
    return count;
    }
lista eliminaK(lista head, int k)
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

void f(lista *l)
    {
        if(*l==NULL)
            return;
        lista *pp=l;
        while (*pp!=NULL) {
            int num=blocco(*pp);
            if(num>0)
                {
                    (*pp)->next=eliminaK((*pp)->next, num);
                    pp=&(*pp)->next;
                }
            else
                {
                    pp=&(*pp)->next;
                }
        }
    }
lista eliminaBlocchiChiusi(lista L)
    {
        if(L==NULL)
            return L;
        f(&L);
    return L;
    }
