//
//  main.c
//  es 2 chat -3
//
//  Created by Francesco Roscio Ricon on 16/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

void espandiNegativi(Lista *L);

static Nodo* newNode(int x) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->val = x;
    n->next = NULL;
    return n;
}

static void pushBack(Lista *L, int x) {
    Nodo *n = newNode(x);
    if (*L == NULL) { *L = n; return; }
    Nodo *cur = *L;
    while (cur->next) cur = cur->next;
    cur->next = n;
}

static Lista buildFromArray(const int a[], int n) {
    Lista L = NULL;
    for (int i = 0; i < n; i++) pushBack(&L, a[i]);
    return L;
}

static void printList(const char *label, Lista L) {
    printf("%s", label);
    if (!L) { printf("NULL\n"); return; }
    while (L) {
        printf("%d", L->val);
        if (L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

static void freeList(Lista *L) {
    Nodo *cur = *L;
    while (cur) {
        Nodo *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    *L = NULL;
}

/* ====== MAIN DI TEST ====== */
Lista inseriscincoda(Lista head, int val);
int main(void) {
    /* TEST 1: esempio del testo */
    {
        int v[] = {3, -2, 4, -3};
        Lista L = buildFromArray(v, 4);

        printf("=== TEST 1 ===\n");
        printList("Prima : ", L);
        espandiNegativi(&L);
        printList("Dopo  : ", L);
        printf("\n");

        freeList(&L);
    }
//
    /* TEST 2: testa negativa */
    {
        int v[] = {-3, 2, -1, 5};
        Lista L = buildFromArray(v, 4);

        printf("=== TEST 2 ===\n");
        printList("Prima : ", L);
        espandiNegativi(&L);
        printList("Dopo  : ", L);
        printf("\n");

        freeList(&L);
    }

    /* TEST 3: nessun negativo */
    {
        int v[] = {1, 2, 3, 4};
        Lista L = buildFromArray(v, 4);

        printf("=== TEST 3 ===\n");
        printList("Prima : ", L);
        espandiNegativi(&L);
        printList("Dopo  : ", L);
        printf("\n");

        freeList(&L);
    }

    /* TEST 4: tutti negativi */
    {
        int v[] = {-1, -2, -4};
        Lista L = buildFromArray(v, 3);

        printf("=== TEST 4 ===\n");
        printList("Prima : ", L);
        espandiNegativi(&L);
        printList("Dopo  : ", L);
        printf("\n");

        freeList(&L);
    }

    return 0;
}

Lista creasottolista(int k, Lista head)
    {
        if(k==0)
            return head;
    for(int i=0; i<k; i++)
        {
            head=inseriscincoda(head, 1);
        }
    return head;
    }
Lista inseriscincoda(Lista head, int val)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=NULL;
                new->val=val;
                return new;
            }
    head->next=inseriscincoda(head->next, val);
    return head;
    }
Lista f(Lista l)
    {
        if(l==NULL)
            return l;
    Lista scorri=l;
    Lista prec=NULL;
        while(scorri!=NULL)
            {
                Lista succ=scorri->next;
                if(scorri->val<0)
                    {
                        if(prec==NULL)
                            {
                                Lista new=NULL;
                                new=creasottolista(-(scorri->val), new);
                                Lista temp=new;
                                while (temp!=NULL && temp->next!=NULL) {
                                    temp=temp->next;
                                }
                                Lista el=l->next;
                                free(l);
                                l=el;
                                temp->next=l;
                                l=new;
                                scorri=l;
                                prec=NULL;
                            }
                        else
                            {
                                int val=scorri->val;
                                free(scorri);
                                Lista new=NULL;
                                new=creasottolista(-val, new);
                                Lista temp=new;
                                while (temp!=NULL && temp->next!=NULL) {
                                    temp=temp->next;
                                }
                                temp->next=succ;
                                prec->next=new;
                                scorri=succ;
                            }
                    }
                else
                    {
                        prec=scorri;
                        scorri=succ;
                    }
            }
    return l;
    }
void espandiNegativi(Lista *L)
    {
    *L=f(*L);
    }
