//
//  main.c
//  es 2 chat -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* ===================== STRUTTURA ===================== */

typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

/* ===================== PROTOTIPO ===================== */

int eliminaBlocchiNonCrescentiNum(Lista *L);  // DA IMPLEMENTARE TU

/* ===================== FUNZIONI DI SUPPORTO ===================== */

Nodo* newNode(int x) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    if(n == NULL) {
        perror("malloc");
        exit(1);
    }
    n->val = x;
    n->next = NULL;
    return n;
}

void pushBack(Lista *L, int x) {
    Nodo *n = newNode(x);

    if(*L == NULL) {
        *L = n;
        return;
    }

    Nodo *curr = *L;
    while(curr->next != NULL)
        curr = curr->next;

    curr->next = n;
}

void printList(const char *msg, Lista L) {
    printf("%s", msg);

    Nodo *curr = L;
    while(curr != NULL) {
        printf("%d", curr->val);
        if(curr->next != NULL)
            printf(" -> ");
        curr = curr->next;
    }
    printf("\n");
}

void freeList(Lista L) {
    Nodo *curr = L;
    while(curr != NULL) {
        Nodo *tmp = curr->next;
        free(curr);
        curr = tmp;
    }
}

/* ===================== FUNZIONE DA FARE ===================== */



/* ===================== MAIN DI TEST ===================== */

int main() {

    /* ================= TEST 1 =================
       1 -> 4 -> 4 -> 2 -> 7
       Atteso: elimina 4 -> 2
       Risultato: 1 -> 4 -> 7
    */
    Lista L1 = NULL;
    pushBack(&L1, 1);
    pushBack(&L1, 4);
    pushBack(&L1, 4);
    pushBack(&L1, 2);
    pushBack(&L1, 7);

    printList("L1 prima : ", L1);
    int r1 = eliminaBlocchiNonCrescentiNum(&L1);
    printf("Eliminati: %d\n", r1);
    printList("L1 dopo  : ", L1);
    printf("\n");


    /* ================= TEST 2 =================
       3 -> 8 -> 8 -> 1
       Blocco arriverebbe fino alla fine.
       NON puoi eliminare l'ultimo nodo (1).
       Atteso: elimina solo il terzo nodo 8
       Risultato: 3 -> 8 -> 1
    */
    Lista L2 = NULL;
    pushBack(&L2, 3);
    pushBack(&L2, 8);
    pushBack(&L2, 8);
    pushBack(&L2, 1);

    printList("L2 prima : ", L2);
    int r2 = eliminaBlocchiNonCrescentiNum(&L2);
    printf("Eliminati: %d\n", r2);
    printList("L2 dopo  : ", L2);
    printf("\n");


    /* ================= TEST 3 =================
       Lista già crescente
       1 -> 2 -> 5 -> 9
       Atteso: nessuna eliminazione
    */
    Lista L3 = NULL;
    pushBack(&L3, 1);
    pushBack(&L3, 2);
    pushBack(&L3, 5);
    pushBack(&L3, 9);

    printList("L3 prima : ", L3);
    int r3 = eliminaBlocchiNonCrescentiNum(&L3);
    printf("Eliminati: %d\n", r3);
    printList("L3 dopo  : ", L3);
    printf("\n");


    /* ================= TEST 4 =================
       Rottura subito all'inizio
       5 -> 3 -> 2 -> 10
       ancora = 5
       blocco = 3 -> 2
       risultato: 5 -> 10
    */
    Lista L4 = NULL;
    pushBack(&L4, 5);
    pushBack(&L4, 3);
    pushBack(&L4, 2);
    pushBack(&L4, 10);

    printList("L4 prima : ", L4);
    int r4 = eliminaBlocchiNonCrescentiNum(&L4);
    printf("Eliminati: %d\n", r4);
    printList("L4 dopo  : ", L4);
    printf("\n");


    freeList(L1);
    freeList(L2);
    freeList(L3);
    freeList(L4);

    return 0;
}

int blocco(Lista prev)
    {
        if(prev==NULL)
            return 0;
        Lista inizio=prev;
        int fisso=prev->val;
        int count=0;
        while(inizio!=NULL && inizio->next!=NULL)
            {
                if(!(inizio->val<=fisso))
                    break;
                count++;
                inizio=inizio->next;
            }
        return count;
    }
Lista elimina(Lista head, int K)
    {
        if(head==NULL)
            return head;
        for(int i=0; i<K && head!=NULL; i++)
            {
                Lista succ=head->next;
                free(head);
                head=succ;
            }
        return head;
    }
void f(Lista *l, int *count)
    {
        if(*l==NULL)
            return;
        Lista *pp=l;
        Lista prec=NULL;
        while (*pp!=NULL) {
                if(prec!=NULL && (*pp)->val<=prec->val)
                    {
                        int ris=blocco(*pp);
                        if(ris>0)
                            {
                                *pp=elimina(*pp, ris);
                                *count=(*count)+ris;
                            }
                        else {
                                prec = *pp;
                                pp = &(*pp)->next;
                            }
                    }
            else
                {
                    prec=*pp;
                    pp=&(*pp)->next;
                }
        }
    }
int eliminaBlocchiNonCrescentiNum(Lista *L) {
    int count=0;
    f(L, &count);
    return count;
}
