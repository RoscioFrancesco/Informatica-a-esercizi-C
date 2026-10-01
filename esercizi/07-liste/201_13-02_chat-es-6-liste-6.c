//
//  main.c
//  chat es 6 liste -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//
//Elimina ogni blocco massimale di lunghezza ≥ 3 dove i valori:
//sono alternati pari/dispari
//iniziano e finiscono con numero pari
//Esempio:
//2 → 5 → 4 → 7 → 6 → 9 → 8
//⚠ Devi riconoscere pattern dinamico.

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

/*
  Elimina ogni blocco massimale di lunghezza >= 3
  con parità alternata, che inizia e finisce con pari.

  Ritorna il numero di nodi eliminati (utile per debug).
*/
int eliminaBlocchiParitaAlternata(Lista *L);

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

Lista distruggiK(Lista head, int K);
int trovablocco(Lista head);
int èpari(int x);
int main(void) {
    /* Test 1: esempio (tutto alternato, inizia pari, finisce pari) -> elimina tutto */
    int t1[] = {2, 5, 4, 7, 6, 9, 8};

    /* Test 2: alterna ma finisce dispari -> non elimina */
    int t2[] = {2, 5, 4, 7, 6};

    /* Test 3: due blocchi separati */
    int t3[] = {1, 2, 5, 4, 7, 6, 3, 8, 1, 4, 9, 2};

    /* Test 4: blocco alternato lungo ma “spezzato” da due pari consecutivi */
    int t4[] = {2, 5, 4, 7, 6, 6, 9, 8};

    /* Test 5: blocco minimo valido (len=3) */
    int t5[] = {10, 3, 8, 1};

    struct {
        const char *name;
        int *arr;
        int n;
    } tests[] = {
        {"T1", t1, 7},
        {"T2", t2, 5},
        {"T3", t3, 12},
        {"T4", t4, 8},
        {"T5", t5, 4},
    };

    int nt = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < nt; i++) {
        Lista L = buildFromArray(tests[i].arr, tests[i].n);

        printf("\n==================== %s ====================\n", tests[i].name);
        printList("Prima: ", L);
        printf("Lunghezza prima: %d\n", length(L));

        int removed = eliminaBlocchiParitaAlternata(&L);

        printList("Dopo:  ", L);
        printf("Lunghezza dopo:  %d\n", length(L));
        printf("Nodi rimossi: %d\n", removed);

        freeList(L);
    }

    return 0;
}
int trovablocco(Lista head)
    {
        if(head==NULL || head->val%2!=0)
            return 0;
    int count=1;
    while (head!=NULL && head->next!=NULL) {
        if(èpari(head->val)==èpari(head->next->val))
            break;
        count++;
        head=head->next;
    }
    if(count%2==0)
        return 0;
    return count;
    }
int èpari(int x)
    {
        if(x%2==0)
            return 1;
    return 0;
    }
Lista distruggiK(Lista head, int K)
    {
        if(head==NULL)
            return head;
        for(int i=0; head!=NULL && i<K; i++)
            {
                Lista succ=head->next;
                free(head);
                head=succ;
            }
        return head;
    }

int eliminaBlocchiParitaAlternata(Lista *L)
    {
        if(*L==NULL)
            return 0;
        Lista *pp=L;
    int somma=0;
    while (*pp!=NULL) {
        int count=trovablocco(*pp);
        if(count>=3)
            {
                somma=somma+count;
                *pp=distruggiK(*pp, count);
            }
        else
            {
                pp=&(*pp)->next;
            }
    }
    return somma;
    }
