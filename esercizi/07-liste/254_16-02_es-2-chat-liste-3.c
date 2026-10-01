//
//  main.c
//  es 2 chat liste  -3
//
//  Created by Francesco Roscio Ricon on 16/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE
   ========================= */
typedef struct Nodo {
    int val;
    struct Nodo *next;
} Nodo;

typedef Nodo* lista;

/* =========================
   PROTOTIPI
   ========================= */
void eliminaBlocchiMedia(lista *L);   // <-- DA IMPLEMENTARE (non risolto qui)

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

/* =========================
   FUNZIONE DA SVOLGERE
   (STUB: NON risolve l'esercizio)
   ========================= */
void f(lista *l);
void eliminaBlocchiMedia(lista *L) {
    f(L);
}

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    /* ---------- TEST 1 (quello classico) ----------
       Input:  10 -> 2 -> 3 -> 20 -> 5 -> 4 -> 15
       Atteso: 10 -> 20 -> 15
    */
    lista L1 = NULL;
    int a1[] = {10, 2, 3, 20, 5, 4, 15};
    int n1 = (int)(sizeof(a1)/sizeof(a1[0]));
    for(int i = 0; i < n1; i++) L1 = pushBack(L1, a1[i]);

    printLista("TEST1 - iniziale: ", L1);
    eliminaBlocchiMedia(&L1);
    printLista("TEST1 - dopo    : ", L1);
    freeLista(L1);

    printf("\n");

    /* ---------- TEST 2 (cascata) ----------
       Input:  8 -> 1 -> 2 -> 9 -> 3 -> 4 -> 10
       Spiegazione attesa:
         - Primo blocco: 8 ... 9 (1 e 2 < media(8,9)=8.5) => elimini 1,2
           lista diventa: 8 -> 9 -> 3 -> 4 -> 10
         - Nuovo blocco: 9 ... 10 (3 e 4 < media(9,10)=9.5) => elimini 3,4
           finale: 8 -> 9 -> 10
    */
    lista L2 = NULL;
    int a2[] = {8, 1, 2, 9, 3, 4, 10};
    int n2 = (int)(sizeof(a2)/sizeof(a2[0]));
    for(int i = 0; i < n2; i++) L2 = pushBack(L2, a2[i]);

    printLista("TEST2 - iniziale: ", L2);
    eliminaBlocchiMedia(&L2);
    printLista("TEST2 - dopo    : ", L2);
    freeLista(L2);

    return 0;
}
int blocco(lista head)
    {
        if(head==NULL || head->next==NULL)
            return 0;
    lista A=head;
    lista scorri=head->next;
    int count=0;
    while(scorri!=NULL && scorri->next!=NULL)
        {
            lista B=scorri->next;
            float media=(A->val+B->val)/2;
            if(scorri->val>=media)
                break;
            count++;
            scorri=scorri->next;
        }
    return count;
    }
lista eliminaK(lista head, int k)
    {
        if(head==NULL)
            return 0;
    for(int i=0; i<k && head!=NULL; i++)
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
                if(len>0)
                    {
                        (*pp)->next=eliminaK((*pp)->next, len);
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
