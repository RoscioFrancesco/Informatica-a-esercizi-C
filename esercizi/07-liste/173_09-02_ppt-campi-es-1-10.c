//
//  main.c
//  ppt campi es 1-10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct Elem {
    int dato;
    struct Elem *next;
} Nodo;

typedef Nodo *Lista;

void incrocia(Lista *lis, int *vett, int len);

/* =========================
   FUNZIONI DI SERVIZIO (per test)
   ========================= */
static Nodo* nuovoNodo(int x) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = x;
    n->next = NULL;
    return n;
}

static void append(Lista *lis, int x) {
    Nodo *n = nuovoNodo(x);
    if (*lis == NULL) {
        *lis = n;
        return;
    }
    Nodo *cur = *lis;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
}

static void stampaLista(Lista lis) {
    printf("[ ");
    for (Nodo *cur = lis; cur != NULL; cur = cur->next) {
        printf("%d ", cur->dato);
    }
    printf("]\n");
}

static void freeLista(Lista lis) {
    while (lis != NULL) {
        Nodo *tmp = lis->next;
        free(lis);
        lis = tmp;
    }
}

/* =========================
   STUB: NON RISOLVO L'ESERCIZIO
   ========================= */
void incrocia(Lista *lis, int *vett, int len) {
    (void)lis; (void)vett; (void)len;
    
}

/* =========================
   MAIN DI TEST + PRINTF
   ========================= */
void f(Lista *head, int vett[], int len);
int trovato(Lista head, int val);
Lista aggiungincoda(Lista head, int val);
Lista eliminaval(Lista head, int x);
int main(void) {
    /* Lista iniziale (insieme) senza duplicati */
    Lista L = NULL;
    append(&L, 10);
    append(&L, 3);
    append(&L, 7);
    append(&L, 20);

    /* Vettore dinamico (insieme) senza duplicati */
    int len = 5;
    int *V = (int*)malloc(sizeof(int) * len);
    if (!V) { perror("malloc"); exit(1); }
    V[0] = 3;   /* presente in lista -> da rimuovere */
    V[1] = 5;   /* non presente -> da aggiungere in coda */
    V[2] = 20;  /* presente -> da rimuovere */
    V[3] = 11;  /* non presente -> da aggiungere */
    V[4] = 7;   /* presente -> da rimuovere */

    printf("Lista prima di incrocia: ");
    stampaLista(L);

    printf("Vettore passato a incrocia: [ ");
    for (int i = 0; i < len; i++) printf("%d ", V[i]);
    printf("]\n");

    
    f(&L, V, len);

    printf("Lista dopo incrocia: ");
    stampaLista(L);

    free(V);
    freeLista(L);
    return 0;
}
void f(Lista *head, int vett[], int len)
    {
        if(head==NULL || *head==NULL)
            return;
        int *vett_ver=malloc(sizeof(int)*len);
        for(int i=0; i<len; i++)
        {
            vett_ver[i]=trovato(*head, vett[i]);
        }
    for(int i=0; i<len; i++)
        {
            if(vett_ver[i]==1)
                {
                    *head=eliminaval(*head, vett[i]);
                }
            else
                {
                    *head=aggiungincoda(*head, vett[i]);
                }
        }
    return;
    }
Lista aggiungincoda(Lista head, int val)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=head;
                new->dato=val;
                return new;
            }
        head->next=aggiungincoda(head->next, val);
        return head;
    }
int trovato(Lista head, int val)
    {
        if(head==NULL)
            return 0;
        while(head!=NULL)
            {
                if(head->dato==val)
                    return 1;
                head=head->next;
            }
    return 0;
    }
Lista eliminaval(Lista head, int x)
    {
        if(head==NULL)
            return head;
        if(head->dato==x)
            {
                Lista temp=head->next;
                free(head);
                return eliminaval(temp, x);
            }
        head->next=eliminaval(head->next, x);
        return head;
    }
