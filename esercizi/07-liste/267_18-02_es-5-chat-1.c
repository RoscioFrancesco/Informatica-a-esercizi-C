//
//  main.c
//  es 5 chat -1
//
//  Created by Francesco Roscio Ricon on 18/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int val;
    struct nodo* next;
} nodo;

typedef nodo* lista;

int palindromaCentrale(lista L);
lista copialista(lista L);

static nodo* newNode(int x) {
    nodo* n = (nodo*)malloc(sizeof(nodo));
    if(!n) { perror("malloc"); exit(1); }
    n->val = x;
    n->next = NULL;
    return n;
}

static lista pushBack(lista L, int x) {
    nodo* n = newNode(x);
    if(L == NULL) return n;
    nodo* cur = L;
    while(cur->next != NULL) cur = cur->next;
    cur->next = n;
    return L;
}

static lista buildFromArray(const int a[], int n) {
    lista L = NULL;
    for(int i = 0; i < n; i++) L = pushBack(L, a[i]);
    return L;
}

static void printList(const char* label, lista L) {
    printf("%s", label);
    if(L == NULL) {
        printf("NULL\n");
        return;
    }
    while(L != NULL) {
        printf("%d", L->val);
        if(L->next != NULL) printf(" -> ");
        L = L->next;
    }
    printf("\n");
}

static void freeList(lista L) {
    while(L != NULL) {
        nodo* tmp = L;
        L = L->next;
        free(tmp);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
lista invertilista(lista l);
int main(void) {

    /* --- TEST 1 (palindroma: esempio) --- */
    {
        int a[] = {1, 4, 7, 4, 1};
        lista L = buildFromArray(a, (int)(sizeof(a)/sizeof(a[0])));

        printf("=== TEST 1 ===\n");
        printList("Lista: ", L);

        int ok = palindromaCentrale(L);
        printf("palindromaCentrale = %d\n\n", ok);

        /* verifica che la lista sia stata ripristinata */
        printList("Dopo funzione (deve essere uguale): ", L);
        printf("\n");

        freeList(L);
    }

    /* --- TEST 2 (NON palindroma: esempio) --- */
    {
        int a[] = {1, 2, 3, 2, 4};
        lista L = buildFromArray(a, (int)(sizeof(a)/sizeof(a[0])));

        printf("=== TEST 2 ===\n");
        printList("Lista: ", L);

        int ok = palindromaCentrale(L);
        printf("palindromaCentrale = %d\n\n", ok);

        /* verifica ripristino */
        printList("Dopo funzione (deve essere uguale): ", L);
        printf("\n");

        freeList(L);
    }

    /* --- TEST 3 (minimo caso dispari) --- */
    {
        int a[] = {9};
        lista L = buildFromArray(a, 1);

        printf("=== TEST 3 ===\n");
        printList("Lista: ", L);

        int ok = palindromaCentrale(L);
        printf("palindromaCentrale = %d\n\n", ok);

        printList("Dopo funzione (deve essere uguale): ", L);
        printf("\n");

        freeList(L);
    }

    /* --- TEST 4 (dispari, palindroma con negativi) --- */
    {
        int a[] = {-1, 0, -1};
        lista L = buildFromArray(a, (int)(sizeof(a)/sizeof(a[0])));

        printf("=== TEST 4 ===\n");
        printList("Lista: ", L);

        int ok = palindromaCentrale(L);
        printf("palindromaCentrale = %d\n\n", ok);

        printList("Dopo funzione (deve essere uguale): ", L);
        printf("\n");

        freeList(L);
    }

    return 0;
}
lista invertilista(lista l)
    {
        if(l==NULL || l->next==NULL)
            return l;
    lista temp=invertilista(l->next);
    l->next->next=l;
    l->next=NULL;
    return temp;
    }
int palindromaCentrale(lista L)
    {
    lista new=copialista(L);
    new=invertilista(new);
    lista scorri=new;
    lista scorri2=L;
    while(scorri!=NULL)
        {
            if(scorri->val!=scorri2->val)
                return 0;
            scorri2=scorri2->next;
            scorri=scorri->next;
        }
    return 1;
    }
lista copialista(lista L)
    {
        if(L==NULL)
            return L;
    lista new=(lista)malloc(sizeof(*new));
    new->val=L->val;
    new->next=copialista(L->next);
    return new;
    }
