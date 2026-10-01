//
//  main.c
//  tde 5 es liste -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int numero;
    struct Node *next;
} Nodo;

typedef Nodo *Lista;
int f(Lista head, int *hasprec1, int *hasprec2, Lista *prec1, Lista *prec2);

Lista pushBack(Lista l, int x) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    n->numero = x;
    n->next = NULL;

    if (l == NULL) return n;

    Nodo *cur = l;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return l;
}

Lista buildFromArray(const int v[], int n) {
    Lista l = NULL;
    for (int i = 0; i < n; i++) l = pushBack(l, v[i]);
    return l;
}

void stampaLista(Lista l) {
    for (Nodo *cur = l; cur != NULL; cur = cur->next) {
        printf("%d", cur->numero);
        if (cur->next) printf(" -> ");
    }
    printf(" -> NULL\n");
}

void liberaLista(Lista l) {
    while (l) {
        Nodo *tmp = l;
        l = l->next;
        free(tmp);
    }
}
int crescitaLenta(Lista l);
int main(void) {
    int a1[] = {7, 45, 67, 78};
    int a2[] = {7,  9, 11, 13};
    int a3[] = {7, 45, 38, 47};
    int a4[] = {7, 45, 234, 247};

    Lista L1 = buildFromArray(a1, 4);
    Lista L2 = buildFromArray(a2, 4);
    Lista L3 = buildFromArray(a3, 4);
    Lista L4 = buildFromArray(a4, 4);

    printf("Test 1: ");
    stampaLista(L1);
    printf("Risultato crescitaLenta = %d\n\n", crescitaLenta(L1));

    printf("Test 2: ");
    stampaLista(L2);
    printf("Risultato crescitaLenta = %d\n\n", crescitaLenta(L2));

    printf("Test 3: ");
    stampaLista(L3);
    printf("Risultato crescitaLenta = %d\n\n", crescitaLenta(L3));

    printf("Test 4: ");
    stampaLista(L4);
    printf("Risultato crescitaLenta = %d\n\n", crescitaLenta(L4));

    liberaLista(L1);
    liberaLista(L2);
    liberaLista(L3);
    liberaLista(L4);

    return 0;
}
int f(Lista head, int *hasprec1, int *hasprec2, Lista *prec1, Lista *prec2)
    {
        if(head==NULL)
            return 1;
        if(*hasprec1!=0 && *hasprec2!=0 && head->numero-(*prec1)->numero>(*prec1)->numero-(*prec2)->numero)
            return 0;
        if(head->next!=NULL && head->numero>head->next->numero)
            return 0;
    if(*hasprec2==0 && *hasprec1!=0)
        {
            *hasprec2=1;
            (*prec2)=*prec1;
        }
    else
        {
            *prec2=*prec1;
        }
        if(*hasprec1==0)
            {
                *hasprec1=1;
                *prec1=head;
            }
        else
            {
                *prec1=head;
            }
    return f(head->next, hasprec1, hasprec2, prec1, prec2);
    }
int crescitaLenta(Lista l)
    {
    int hasprec1=0;
    int hasprec2=0;
    Lista prec1=NULL;
    Lista prec2=NULL;
    return f(l, &hasprec1, &hasprec2, &prec1, &prec2);
}
