//
//  main.c
//  es 14 esercitazione alessandrini
//
//  Created by Francesco Roscio Ricon on 24/01/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

/* Crea un nuovo nodo */
Lista newNode(int x) {
    Lista n = (Lista)malloc(sizeof(Nodo));
    if (n == NULL) {
        printf("Errore malloc\n");
        exit(1);
    }
    n->val = x;
    n->next = NULL;
    return n;
}

/* Inserisce in fondo */
Lista insInFondo(Lista L, int x) {
    if (L == NULL) return newNode(x);
    L->next = insInFondo(L->next, x);
    return L;
}

/* Stampa lista */
void stampaLista(Lista L) {
    while (L != NULL) {
        printf("%d -> ", L->val);
        L = L->next;
    }
    printf("NULL\n");
}

/* Libera lista */
void freeLista(Lista L) {
    while (L != NULL) {
        Lista tmp = L;
        L = L->next;
        free(tmp);
    }
}


Lista eliminaMinoriIter(Lista head, int k) {
    Lista curr = head;
    Lista prev = NULL;

    while (curr != NULL) {
        if (curr->val < k) {
            Lista daEliminare = curr;

            if (prev == NULL) {
                head = curr->next;       // eliminazione in testa
                curr = head;
            } else {
                prev->next = curr->next; // salta curr
                curr = curr->next;
            }

            free(daEliminare);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    return head;
}


Lista eliminaMinoriRic(Lista head, int k)
    {
        if(head==NULL)
            return NULL;
        if(head->val<k)
            {
                Lista temp=head;
                head=head->next;
                free(temp);
                return eliminaMinoriRic(head, k);
            }
        else
            {
                head->next=eliminaMinoriRic(head->next, k);
                return head;
            }
    }

int main() {
    Lista L1 = NULL;
    Lista L2 = NULL;

    /* Creo una lista di esempio */
    int valori[] = {7, 2, 10, 3, 5, 1, 8, 4};
    int n = sizeof(valori) / sizeof(valori[0]);

    for (int i = 0; i < n; i++) {
        L1 = insInFondo(L1, valori[i]);
        L2 = insInFondo(L2, valori[i]);  // seconda copia per test ricorsivo
    }

    int k = 5;

    printf("Lista iniziale:\n");
    stampaLista(L1);

    printf("\n--- Eliminazione ITERATIVA (minori di %d) ---\n", k);
    L1 = eliminaMinoriIter(L1, k);
    stampaLista(L1);

    printf("\n--- Eliminazione RICORSIVA (minori di %d) ---\n", k);
    L2 = eliminaMinoriRic(L2, k);
    stampaLista(L2);

    freeLista(L1);
    freeLista(L2);

    return 0;
}
