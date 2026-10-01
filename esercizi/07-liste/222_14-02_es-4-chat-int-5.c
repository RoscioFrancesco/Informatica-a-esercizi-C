//
//  main.c
//  es 4 chat int -5
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

lista eliminaBlocchiPari(lista L);

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
    int v1[] = {3,4,6,8,5,2,10,7};
    lista L1 = buildList(v1, 8);

    printList("T1 prima : ", L1);
    L1 = eliminaBlocchiPari(L1);
    printList("T1 dopo  : ", L1);
    printf("\n");

    /* T2: blocco in testa */
    int v2[] = {1,2,4,6,9,11};
    lista L2 = buildList(v2, 6);

    printList("T2 prima : ", L2);
    L2 = eliminaBlocchiPari(L2);
    printList("T2 dopo  : ", L2);
    printf("\n");

    /* T3: nessun blocco chiuso */
    int v3[] = {3,4,6,8};
    lista L3 = buildList(v3, 4);

    printList("T3 prima : ", L3);
    L3 = eliminaBlocchiPari(L3);
    printList("T3 dopo  : ", L3);
    printf("\n");

    /* T4: blocchi multipli */
    int v4[] = {5,2,4,7,9,8,10,3};
    lista L4 = buildList(v4, 8);

    printList("T4 prima : ", L4);
    L4 = eliminaBlocchiPari(L4);
    printList("T4 dopo  : ", L4);
    printf("\n");

    /* T5: tutti pari tra due dispari */
    int v5[] = {7,2,4,6,8,9};
    lista L5 = buildList(v5, 6);

    printList("T5 prima : ", L5);
    L5 = eliminaBlocchiPari(L5);
    printList("T5 dopo  : ", L5);
    printf("\n");

    freeList(L1);
    freeList(L2);
    freeList(L3);
    freeList(L4);
    freeList(L5);

    return 0;
}


int blocco(lista head)
    {
        if(head==NULL)
            return 0;
        if(head->valore%2==0)
            return 0;
        head=head->next;
        int count=0;
        while(head!=NULL)
            {
                if(head->valore%2==1)
                    break;
                count++;
                head=head->next;
            }
        if(head==NULL || count<2)
            return 0;
    return count;
    }
lista eliminak(lista head, int k)
    {
        if(head==NULL)
            return head;
    head=head->next;
    for(int i=0; i<=k && head!=NULL; i++)
        {
            lista succ=head->next;
            free(head);
            head=succ;
        }
    return head;
    }
void f(lista *l)
    {
        if(*l==NULL)
            return;
    lista *pp=l;
        while(*pp!=NULL)
            {
                if((*pp)->valore%2==1)
                {
                    int num=blocco(*pp);
                    if(num>0)
                    {
                        (*pp)->next=eliminak((*pp), num);
                        pp=l;
                        
                    }
                    else
                        {
                            pp=&(*pp)->next;
                        }
                }
                        else
                            {
                                pp=&(*pp)->next;
                            }
                    
            }
    }
lista eliminaBlocchiPari(lista L)
    {
    f(&L);
    return L;
    }
