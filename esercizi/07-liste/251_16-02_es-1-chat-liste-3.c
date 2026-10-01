//
//  main.c
//  es 1 chat liste  -3
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
void eliminaInstabili(lista *L);   // <-- DA IMPLEMENTARE (non risolto qui)

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
void eliminaInstabili(lista *L);

/* =========================
   MAIN DI TEST
   ========================= */
int main(void) {
    lista L = NULL;

    /* ESEMPIO DEL TESTO:
       Input:  1 -> 40 -> 3 -> 15 -> 5 -> 6
       Output: 1 -> 3 -> 5 -> 6
    */
    int a[] = {1, 40, 3, 15, 5, 6};
    int n = (int)(sizeof(a)/sizeof(a[0]));
    for(int i = 0; i < n; i++) {
        L = pushBack(L, a[i]);
    }

    printLista("Lista iniziale: ", L);

    eliminaInstabili(&L);

    printLista("Lista dopo    : ", L);

    freeLista(L);
    return 0;
}
int sommasucc(lista head) // 1 se va eliminato
    {
        if(head==NULL || head->next==NULL)
            return 0;
    int somma=0;
    int val=head->val;
    head=head->next;
    while(head!=NULL)
        {
            somma=somma+head->val;
            head=head->next;
        }
    if(val>somma)
        return 1;
    return 0;
    }
void eliminaInstabili(lista *L) {
    if(*L==NULL)
        return;
    lista *pp=L;
    while(*pp!=NULL)
        {
            if(sommasucc(*pp)==1)
                {
                    lista temp=(*pp);
                    (*pp)=(*pp)->next;
                    free(temp);
                    pp=L;
                }
            else
                {
                    pp=&(*pp)->next;
                }
        }
}
