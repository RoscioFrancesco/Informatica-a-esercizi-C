//
//  main.c
//  tde 2 es 1 -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int valore;
    struct nodo* next;
} nodo;

typedef nodo* lista;

lista listapicchi(lista L);

lista pushBack(lista L, int x) {
    nodo* n = (nodo*)malloc(sizeof(nodo));
    n->valore = x;
    n->next = NULL;

    if (L == NULL)
        return n;

    nodo* temp = L;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = n;
    return L;
}

void stampaLista(const char* msg, lista L) {
    printf("%s", msg);
    while (L != NULL) {
        printf("%d", L->valore);
        if (L->next != NULL)
            printf(" -> ");
        L = L->next;
    }
    printf("\n");
}

void liberaLista(lista L) {
    while (L != NULL) {
        nodo* tmp = L;
        L = L->next;
        free(tmp);
    }
}

int verifica(lista head, lista nodo);
int main() {

    /* ===== TEST 1 (esempio del testo) ===== */

    lista L1 = NULL;

    int valori1[] = {1,5,16,11,12,4,5,5,3,1,5};
    int n1 = sizeof(valori1)/sizeof(int);

    for (int i = 0; i < n1; i++)
        L1 = pushBack(L1, valori1[i]);

    printf("=== TEST 1 ===\n");
    stampaLista("Input : ", L1);

    lista R1 = listapicchi(L1);

    stampaLista("Output: ", R1);
    printf("\n");


    /* ===== TEST 2 ===== */
    lista L2 = NULL;
    int valori2[] = {2,4,2};
    int n2 = sizeof(valori2)/sizeof(int);

    for (int i = 0; i < n2; i++)
        L2 = pushBack(L2, valori2[i]);

    printf("=== TEST 2 ===\n");
    stampaLista("Input : ", L2);

    lista R2 = listapicchi(L2);

    stampaLista("Output: ", R2);
    printf("\n");


    /* ===== TEST 3 ===== */
    lista L3 = NULL;
    int valori3[] = {10,20,30,40};
    int n3 = sizeof(valori3)/sizeof(int);

    for (int i = 0; i < n3; i++)
        L3 = pushBack(L3, valori3[i]);

    printf("=== TEST 3 ===\n");
    stampaLista("Input : ", L3);

    lista R3 = listapicchi(L3);

    stampaLista("Output: ", R3);
    printf("\n");


    /* ===== TEST 4 ===== */
    lista L4 = NULL;
    int valori4[] = {5,3,5,3,5};
    int n4 = sizeof(valori4)/sizeof(int);

    for (int i = 0; i < n4; i++)
        L4 = pushBack(L4, valori4[i]);

    printf("=== TEST 4 ===\n");
    stampaLista("Input : ", L4);

    lista R4 = listapicchi(L4);

    stampaLista("Output: ", R4);
    printf("\n");

    return 0;
}

lista inseriscincoda(lista head, int x)
    {
        if(head==NULL)
            {
                lista new=(lista)malloc(sizeof(*new));
                new->valore=x;
                new->next=NULL;
                return new;
            }
    head->next=inseriscincoda(head->next, x);
    return head;
    }
int èpicco(lista nodo, lista head)
    {
        if(nodo==NULL)
            return 0;
    lista temp=nodo;
    while(temp!=NULL)
        {
            if(temp->valore>nodo->valore)
                return 0;
            temp=temp->next;
        }
    return verifica(head, nodo);
    }
int verifica(lista head, lista nodo)
    {
        if(head==NULL)
            return 0;
        while(head!=nodo)
            {
                if(head->valore>nodo->valore)
                    return 0;
                head=head->next;
            }
    return 1;
    }

lista listapicchi(lista L)
    {
        if(L==NULL)
            return L;
    lista scorri=L;
    lista new=NULL;
    while (scorri!=NULL) {
        if(verifica(L, scorri) && L!=scorri && scorri->next!=NULL)
            {
                new=inseriscincoda(new, scorri->valore);
            }
        scorri=scorri->next;
        }
    return new;
    }
