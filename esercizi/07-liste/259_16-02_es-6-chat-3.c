//
//  main.c
//  es 6 chat -3
//
//  Created by Francesco Roscio Ricon on 16/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* ====== TIPI ====== */
typedef struct nodo {
    int val;
    struct nodo *next;
} Nodo;

typedef Nodo* Lista;

/* ====== Utility: crea nodo / append / stampa / free ====== */
static Nodo* newNode(int x) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->val = x;
    n->next = NULL;
    return n;
}

static void pushBack(Lista *L, int x) {
    Nodo *n = newNode(x);
    if (*L == NULL) { *L = n; return; }
    Nodo *cur = *L;
    while (cur->next) cur = cur->next;
    cur->next = n;
}

static void printList(Lista L) {
    if (!L) { printf("NULL\n"); return; }
    while (L) {
        printf("%d", L->val);
        if (L->next) printf(" -> ");
        L = L->next;
    }
    printf(" -> NULL\n");
}

static void freeList(Lista *L) {
    Nodo *cur = *L;
    while (cur) {
        Nodo *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    *L = NULL;
}

/* =========================================================
   FUNZIONE DEBUG: elimina i nodi con valore DISPARI
   Ritorna quanti nodi elimina.
   ========================================================= */
int eliminaDispari_debug(Lista *L)
{
    int removed = 0;
    Lista *pp = L;   // pp punta al "link" (inizialmente la testa)

    printf("\n[START] L (indirizzo della variabile testa) = %p\n", (void*)L);
    printf("[START] *L (testa) = %p\n", (void*)(*L));

    while (*pp != NULL) {
        Nodo *cur = *pp;            // nodo corrente (quello puntato dal link pp)
        Nodo *next = cur->next;     // il suo next

        printf("\n--- ITERAZIONE ---\n");
        printf("pp               = %p  (indirizzo del link che sto guardando)\n", (void*)pp);
        printf("*pp (cur)        = %p  (nodo puntato da quel link)\n", (void*)cur);
        printf("cur->val         = %d\n", cur->val);
        printf("cur->next        = %p\n", (void*)next);

        if (cur->val % 2 != 0) {
            printf("CONDIZIONE VERA: %d e' dispari -> ELIMINO questo nodo\n", cur->val);

            // passo chiave: modifico il LINK puntato da pp per saltare cur
            printf("Prima: *pp = %p (cur)\n", (void*)(*pp));
            *pp = (*pp)->next;
            printf("Dopo : *pp = %p (ora punta a next)\n", (void*)(*pp));

            printf("free(%p)\n", (void*)cur);
            free(cur);
            removed++;

            // NOTA: pp NON CAMBIA.
            // Rimane lo stesso "link", ma adesso quel link punta al nodo successivo.
            printf("pp rimane = %p (stesso link). Ricontrollo da qui.\n", (void*)pp);
        } else {
            printf("CONDIZIONE FALSA: %d e' pari -> NON elimino, AVANZO\n", cur->val);

            // passo chiave che vuoi capire:
            // pp diventa l'indirizzo del campo next del nodo corrente
            printf("Sto facendo: pp = &(*pp)->next\n");

            printf("&cur->next       = %p  (indirizzo del campo next dentro cur)\n", (void*)&cur->next);
            printf("Prima: pp        = %p\n", (void*)pp);

            pp = &(*pp)->next;

            printf("Dopo : pp        = %p  (ora pp punta al next del nodo precedente)\n", (void*)pp);
            printf("Quindi ora *pp   = %p  (cioe' il prossimo nodo)\n", (void*)(*pp));
        }

        printf("Lista attuale: ");
        printList(*L);
    }

    printf("\n[END] removed = %d\n", removed);
    printf("[END] testa finale *L = %p\n", (void*)(*L));
    return removed;
}

/* ====== MAIN ====== */
int main(void)
{
    Lista L = NULL;

    // Lista di test: contiene pari e dispari, anche in testa
    // 5 -> 2 -> 7 -> 8 -> 9 -> 4 -> 1
    int a[] = {5, 2, 7, 8, 9, 4, 1};
    int n = (int)(sizeof(a)/sizeof(a[0]));
    for (int i = 0; i < n; i++) pushBack(&L, a[i]);

    printf("Lista iniziale: ");
    printList(L);
    printf("\n%p\n", L);
    printf("\n%p\n", &L);

    int rem = eliminaDispari_debug(&L);
    

    printf("\nRISULTATO FINALE:\n");
    printf("Eliminati: %d\n", rem);
    printf("Lista finale: ");
    printList(L);

    freeList(&L);
    return 0;
}
