//
//  main.c
//  chat es 10 liste -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;


Lista eliminaBlocchiK(Lista L, int k);

/* =========================
   UTILITY LISTA
   ========================= */
Lista newNode(int v) {
    Lista n = (Lista)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->next = NULL;
    return n;
}

void pushBack(Lista *L, int v) {
    Lista n = newNode(v);
    if (*L == NULL) { *L = n; return; }
    Lista cur = *L;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
}

Lista buildFromArray(const int a[], int n) {
    Lista L = NULL;
    for (int i = 0; i < n; i++) pushBack(&L, a[i]);
    return L;
}

void printList(const char *label, Lista L) {
    printf("%s[", label);
    for (Lista cur = L; cur != NULL; cur = cur->next) {
        printf("%d", cur->val);
        if (cur->next) printf(" -> ");
    }
    printf("]\n");
}

int length(Lista L) {
    int c = 0;
    while (L) { c++; L = L->next; }
    return c;
}

void freeList(Lista L) {
    while (L) {
        Lista tmp = L;
        L = L->next;
        free(tmp);
    }
}

/* =========================
   STUB (NON RISOLVO)
   ========================= */


/* =========================
   MAIN DI TEST
   ========================= */
int trovablocco(Lista head, int k);
int main(void) {

    int a1[] = {1, 2, 3, 4, 5, 6};         // k=2 -> nessuna eliminazione
    int a2[] = {2, 4, 1, 3, 6};            // k=2 -> elimina (2,4) -> 1,3,6
    int a3[] = {1, 1, 1, 1, 1, 1};         // k=3 -> (1,1,1)=3 dispari -> nessuna eliminazione
    int a4[] = {1, 2, 1, 2, 1, 2};         // k=2 -> (1,2)=3 dispari sempre -> nessuna
    int a5[] = {2, 2, 2, 2, 2};            // k=2 -> elimina (2,2), poi elimina (2,2), resta 2
    int a6[] = {3, 1, 2, 4, 5, 1};         // k=3 -> (3,1,2)=6 pari elimina -> resta 4,5,1

    struct {
        const char *name;
        int *arr;
        int n;
        int k;
    } tests[] = {
        {"T1", a1, 6, 2},
        {"T2", a2, 5, 2},
        {"T3", a3, 6, 3},
        {"T4", a4, 6, 2},
        {"T5", a5, 5, 2},
        {"T6", a6, 6, 3},
    };

    int nt = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < nt; i++) {
        Lista L = buildFromArray(tests[i].arr, tests[i].n);

        printf("\n==================== %s (k=%d) ====================\n", tests[i].name, tests[i].k);
        printList("Prima: ", L);
        printf("Lunghezza prima: %d\n", length(L));

        L = eliminaBlocchiK(L, tests[i].k);

        printList("Dopo:  ", L);
        printf("Lunghezza dopo:  %d\n", length(L));

        freeList(L);
    }

    return 0;
}

int trovablocco(Lista head, int k)
    {
        if(head==NULL)
            return 0;
        int somma=0;
    int i=0;
    for (i=0; head!=NULL && i<k; i++) {
        somma=somma+head->val;
        head=head->next;
    }
    if(i<k)
        return 0;
    if(somma%2==0)
        return 1;
    return 0;
    }
Lista distruggiK(Lista head, int K)
    {
        if(head==NULL)
            return head;
        for(int i=0; head!=NULL && i<K; i++)
            {
                Lista temp=head->next;
                free(head);
                head=temp;
            }
    return head;
    }
void f(Lista *l, int K)
    {
        if(*l==NULL)
            return;
        Lista *pp=l;
        while(*pp!=NULL)
            {
                if(trovablocco(*pp,K))
                    {
                        *pp=distruggiK(*pp, K);
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
Lista eliminaBlocchiK(Lista L, int k) {
    f(&L, k);
    return L;
}
