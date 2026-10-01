//
//  main.c
//  es 3 chat liste  -3
//
//  Created by Francesco Roscio Ricon on 16/02/26.
//

#include <stdio.h>
#include <stdlib.h>
typedef struct Nodo {
    int val;
    struct Nodo *next;
} Nodo;

typedef Nodo* lista;

void comprimiCrescenti(lista *L);  // <-- DA IMPLEMENTARE (non risolto qui)

lista pushBack(lista L, int x);
void printLista(const char *msg, lista L);
void freeLista(lista L);

/* =========================
   HELPERS
   ========================= */
lista pushBack(lista L, int x) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    if(!n) { perror("malloc"); exit(1); }
    n->val = x;
    n->next = NULL;

    if(L == NULL) return n;

    Nodo *cur = L;
    while(cur->next != NULL) cur = cur->next;
    cur->next = n;
    return L;
}

void printLista(const char *msg, lista L) {
    printf("%s", msg);
    if(L == NULL) { printf("NULL\n"); return; }
    while(L != NULL) {
        printf("%d", L->val);
        if(L->next != NULL) printf(" -> ");
        L = L->next;
    }
    printf("\n");
}

void freeLista(lista L) {
    while(L != NULL) {
        Nodo *tmp = L;
        L = L->next;
        free(tmp);
    }
}
void f(lista *l);;

void comprimiCrescenti(lista *L) {
    f(L);
}

/* =========================
   MAIN DI TEST
   ========================= */
void f(lista *l);
int main(void) {
    /* ---------- TEST 1 (esempio testo) ----------
       Input : 2 -> 4 -> 7 -> 10 -> 3 -> 5 -> 6 -> 1
       Atteso: 4 -> 3 -> 1
    */
    lista L1 = NULL;
    int a1[] = {2, 4, 7, 10, 3, 5, 6, 1};
    int n1 = (int)(sizeof(a1)/sizeof(a1[0]));
    for(int i = 0; i < n1; i++) L1 = pushBack(L1, a1[i]);

    printLista("TEST1 - iniziale: ", L1);
    comprimiCrescenti(&L1);
    printLista("TEST1 - dopo    : ", L1);
    freeLista(L1);

    printf("\n");

    /* ---------- TEST 2 (compressioni multiple) ----------
       Input : 1 -> 2 -> 3 -> 9 -> 8 -> 10 -> 11 -> 12 -> 7
       Sequenze:
         1,2,3,9  (len 4)  => diventa "4 -> 9"
         8,10,11,12 (len 4) => diventa "4 -> 12"
       Atteso finale: 4 -> 9 -> 4 -> 12 -> 7
    */
    lista L2 = NULL;
    int a2[] = {1, 2, 3, 9, 8, 10, 11, 12, 7};
    int n2 = (int)(sizeof(a2)/sizeof(a2[0]));
    for(int i = 0; i < n2; i++) L2 = pushBack(L2, a2[i]);

    printLista("TEST2 - iniziale: ", L2);
    comprimiCrescenti(&L2);
    printLista("TEST2 - dopo    : ", L2);
    freeLista(L2);

    return 0;
}
int blocco(lista head)
    {
        if(head==NULL)
            return 0;
        int count=1;
    while (head!=NULL && head->next!=NULL) {
        if(head->next->val<=head->val)
            {break;}
        count++;
        head=head->next;
    }
    return count;
    }
lista eliminaK(lista head, int k)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<k; i++)
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
        while(*pp!=NULL)
            {
                int len=blocco(*pp);
                if(len>=3)
                    {
                        (*pp)->val=len;
                        (*pp)->next=eliminaK((*pp)->next, len);
                        pp=&(*pp)->next;
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
