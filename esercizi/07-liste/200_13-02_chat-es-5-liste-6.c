//
//  main.c
//  chat es 5 liste -6
//
//  Created by Francesco Roscio Ricon on 13/02/26.
//

//Elimina nodi che violano vincolo moltiplicativo
//
//Una lista è valida se:
//ogni elemento ha un successore ≥ triplo del valore corrente
//
//
//
#include <stdio.h>
#include <stdlib.h>
typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;
typedef Nodo* Lista;

/*
  Elimina i nodi che causano violazioni del vincolo.
  Attenzione: eliminare un nodo può creare nuove violazioni (effetto domino).
  Ritorna il numero di nodi eliminati.
*/
int eliminaViolazioniTriplo(Lista *L);

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
int main(void) {
    /* Test scelti per coprire: già valida, invalida semplice, e domino */
    int t1[] = {1, 3, 9, 27};              // già valida
    int t2[] = {2, 5, 20};                 // 5 non è >= 6 (violazione tra 2 e 5)
    int t3[] = {2, 7, 20};                 // domino: tra 2 e 7 violazione; dopo rimozione 2->20 ok
    int t4[] = {3, 8, 10, 40};             // domino: 3->8 viol, rimuovi 3; 8->10 viol, rimuovi 8; 10->40 ok
    int t5[] = {5, 14, 15, 16, 100};       // domino a catena
    int t6[] = {10};                       // sempre valida (un solo nodo)

    struct {
        const char *name;
        int *arr;
        int n;
    } tests[] = {
        {"T1", t1, 4},
        {"T2", t2, 3},
        {"T3", t3, 3},
        {"T4", t4, 4},
        {"T5", t5, 5},
        {"T6", t6, 1},
    };

    int nt = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < nt; i++) {
        Lista L = buildFromArray(tests[i].arr, tests[i].n);

        printf("\n==================== %s ====================\n", tests[i].name);
        printList("Prima: ", L);
        printf("Lunghezza prima: %d\n", length(L));


        int removed = eliminaViolazioniTriplo(&L);

        printList("Dopo:  ", L);
        printf("Lunghezza dopo:  %d\n", length(L));
        printf("Nodi rimossi: %d\n", removed);

    }

    return 0;
}
//Una lista è valida se:
//ogni elemento ha un successore ≥ triplo del valore corrente
//
//
int valida(Lista head)
    {
        if(head==NULL)
            return 1;
        if(head->next==NULL)
            return 1;
        int val=head->val;
        if(head->next->val>=3*val)
            return 1;    
        return 0;
    }
int trovalocco(Lista head)
    {
    int count=0;
    while(head!=NULL && !valida(head))
        {
            count++;
            head=head->next;
        }
    return count;
    }
Lista distruggiblocco(Lista head, int k)
    {
        if(head==NULL)
            return head;
    for (int i=0; head!=NULL && i<k; i++) {
        Lista temp=head->next;
        free(head);
        head=temp;
    }
    return head;
    }
int eliminaViolazioniTriplo(Lista *L)
    {
        if(*L==NULL)
            return 0;
        int somma=0;
        Lista *pp=L;
        while (*pp!=NULL) {
            int val=trovalocco(*pp);
            somma=somma+val;
            if(val>0)
                {
                    *pp=distruggiblocco(*pp, val);
                }
            else
                {
                    pp=&(*pp)->next;
                }
        }
    return somma;
    }
