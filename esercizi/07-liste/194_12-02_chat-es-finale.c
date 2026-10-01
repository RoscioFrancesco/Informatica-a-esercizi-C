//  Created by Francesco Roscio Ricon on 12/02/26.

#include <stdio.h>
#include <stdlib.h>
typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

/*
  Elimina dalla lista ogni blocco massimale consecutivo di nodi tali che:
  ogni elemento del blocco è strettamente maggiore della media aritmetica
  di TUTTI gli elementi che lo seguono nella lista.

  Suggerimento di interfaccia per test:
  - prende puntatore alla testa così puoi modificare anche l'inizio
  - ritorna numero di nodi eliminati (utile per debug)
*/
float media(Lista head);
int cancellaBlocchiMediaFutura(Lista *L);

Lista newNode(int v) {
    Lista n = (Lista)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->val = v;
    n->next = NULL;
    return n;
}

void pushBack(Lista *L, int v) {
    Lista n = newNode(v);
    if (*L == NULL) {
        *L = n;
        return;
    }
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
    printf("%s", label);
    printf("[");
    for (Lista cur = L; cur != NULL; cur = cur->next) {
        printf("%d", cur->val);
        if (cur->next) printf(" -> ");
    }
    printf("]\n");
}

int length(Lista L) {
    int k = 0;
    for (; L != NULL; L = L->next) k++;
    return k;
}

void freeList(Lista L) {
    while (L != NULL) {
        Lista tmp = L;
        L = L->next;
        free(tmp);
    }
}

/* =======================
   STUB: NON RISOLVO L'ESERCIZIO
   ======================= */
int cancellaBlocchiMediaFutura(Lista *L) {
    if(*L==NULL)
        return 0;
    if((*L)->val>media(*L))
        {
            Lista temp=*L;
            (*L)=(*L)->next;
            free(temp);
            return 1+cancellaBlocchiMediaFutura(L);
        }
    return cancellaBlocchiMediaFutura(&(*L)->next);
}

/* =======================
   MAIN DI TEST
   ======================= */
int main(void) {
    /* Alcune liste di test:
       - valori decrescenti (spesso scatta la condizione sui primi)
       - valori misti con picchi
       - casi piccoli e casi con ripetizioni
    */

    int a1[] = {10, 2, 3, 13, 101};
    int a2[] = {9, 8, 7, 6, 5, 4};
    int a3[] = {1, 100, 2, 90, 3, 80, 4};
    int a4[] = {5, 5, 5, 5};
    int a5[] = {20, 1, 1, 1, 1, 1};

    Lista T1 = buildFromArray(a1, (int)(sizeof(a1)/sizeof(a1[0])));
    Lista T2 = buildFromArray(a2, (int)(sizeof(a2)/sizeof(a2[0])));
    Lista T3 = buildFromArray(a3, (int)(sizeof(a3)/sizeof(a3[0])));
    Lista T4 = buildFromArray(a4, (int)(sizeof(a4)/sizeof(a4[0])));
    Lista T5 = buildFromArray(a5, (int)(sizeof(a5)/sizeof(a5[0])));

    Lista tests[] = {T1, T2, T3, T4, T5};
    const char *names[] = {"T1", "T2", "T3", "T4", "T5"};
    int nt = (int)(sizeof(tests)/sizeof(tests[0]));

    for (int i = 0; i < nt; i++) {
        printf("\n==================== %s ====================\n", names[i]);
        printList("Prima: ", tests[i]);
        printf("Lunghezza prima: %d\n", length(tests[i]));

        int removed = cancellaBlocchiMediaFutura(&tests[i]);

        printList("Dopo:  ", tests[i]);
        printf("Lunghezza dopo:  %d\n", length(tests[i]));
        printf("Nodi rimossi (ritorno funzione): %d\n", removed);
    }

    /* Free: attenzione che tests[] contiene le teste (potenzialmente modificate) */
    for (int i = 0; i < nt; i++) freeList(tests[i]);

    return 0;
}
float media(Lista head)
    {
    float somma=0;
    float count=0;
    while (head!=NULL) {
        somma=somma+head->val;
        count++;
        head=head->next;
    }
    return somma/count;
    }
