//
//  main.c
//  es 1 chat -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* ============================
   STRUTTURE DATI
   ============================ */
typedef struct Nodo {
    int dato;
    struct Nodo *next;
} Nodo;

typedef Nodo* lista;

/* ============================
   HELPERS (costruzione / stampa / free)
   ============================ */
static lista pushBack(lista L, int x) {
    if (L == NULL) {
        lista n = (lista)malloc(sizeof(Nodo));
        n->dato = x;
        n->next = NULL;
        return n;
    }
    L->next = pushBack(L->next, x);
    return L;
}

static lista buildFromArray(const int a[], int n) {
    lista L = NULL;
    for (int i = 0; i < n; i++) L = pushBack(L, a[i]);
    return L;
}

static void stampaLista(lista L) {
    while (L != NULL) {
        printf("%d", L->dato);
        if (L->next) printf(" -> ");
        L = L->next;
    }
    printf("\n");
}

static void liberaLista(lista L) {
    while (L) {
        lista t = L;
        L = L->next;
        free(t);
    }
}

/* ============================
   ESERCIZIO (DA SVOLGERE)
   ============================ */


/* ============================
   MAIN DI TEST
   ============================ */
lista eliminaBlocchiInstabili(lista L);
int main(void) {
    /* TEST 1: blocchi consecutivi */
    int t1[] = {10, 1, 2, 20, 5, 4, 30};
    lista L1 = buildFromArray(t1, (int)(sizeof(t1)/sizeof(t1[0])));

    printf("=== TEST 1 ===\n");
    printf("Input:\n");
    stampaLista(L1);
    L1 = eliminaBlocchiInstabili(L1);
    printf("Output (ottenuto):\n");
    stampaLista(L1);
    printf("Output ATTESO (corretto):\n");
    printf("10 -> 20 -> 30\n\n");

    liberaLista(L1);

    /* TEST 2: se arrivi a fine lista senza trovare B, NON è un blocco (quindi niente eliminazioni) */
    int t2[] = {5, 4, 3, 2};
    lista L2 = buildFromArray(t2, (int)(sizeof(t2)/sizeof(t2[0])));

    printf("=== TEST 2 ===\n");
    printf("Input:\n");
    stampaLista(L2);
    L2 = eliminaBlocchiInstabili(L2);
    printf("Output (ottenuto):\n");
    stampaLista(L2);
    printf("Output ATTESO (corretto):\n");
    printf("5 -> 4 -> 3 -> 2\n\n");

    liberaLista(L2);

    /* TEST 3: soglia dipende dal passato e dai nodi non eliminati */
    int t3[] = {8, 1, 9, 2, 3, 20, 1, 30};
    lista L3 = buildFromArray(t3, (int)(sizeof(t3)/sizeof(t3[0])));

    printf("=== TEST 3 ===\n");
    printf("Input:\n");
    stampaLista(L3);
    L3 = eliminaBlocchiInstabili(L3);
    printf("Output (ottenuto):\n");
    stampaLista(L3);
    printf("Output ATTESO (corretto):\n");
    printf("8 -> 9 -> 20 -> 30\n\n");

    liberaLista(L3);

    return 0;
}


int blocco(lista head)
    {
        if(head==NULL)
            return 0;
        int count=1;
        int somma=head->dato;
        int k=1;
        head=head->next;
    while (head!=NULL) {
        somma=somma+head->dato;
        count++;
        if(!(head->dato<somma/count))
            break;
        k++;
        head=head->next;
        }
    if(head==NULL)
        return 0;
    return k;
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
lista copialista(lista head)
    {
        if(head==NULL)
            return NULL;
    lista new=(lista)malloc(sizeof(*new));
    new->dato=head->dato;
    new->next=copialista(head->next);
    return new;
    }
void f(lista *l)
    {
        if(*l==NULL)
            return;
        lista *pp=l;
        while(*pp!=NULL)
            {
                int len=blocco(*pp);
                if(len>1)
                    {
                        (*pp)->next=distruggiK((*pp)->next, len-1);
                        pp=&(*pp)->next;
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
lista eliminaBlocchiInstabili(lista L)
    {
    f(&L);
    return L;
    }
