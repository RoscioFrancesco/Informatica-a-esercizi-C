//
//  main.c
//  chat lista es 6 -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE DATI
   ========================= */

typedef struct Nodo {
    int numero;
    struct Nodo *next;
} Nodo;

typedef Nodo* Lista;

typedef struct NodoCompresso {
    int numero;
    int quanti;
    struct NodoCompresso *next;
} NodoCompresso;

typedef NodoCompresso* ListaCompressa;



/* Costruisce una nuova lista compressa:
   per ogni run di valori uguali consecutivi in A, inserisce (valore, conteggio) in B.
   Vincoli: ricorsiva, senza cicli (nella soluzione).
*/
ListaCompressa comprimi(Lista A);   /* TODO */

/* =========================
   UTILITY (PER TEST - OK USARE CICLI QUI)
   ========================= */

static Lista newNodeInt(int x, Lista next) {
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->numero = x;
    n->next = next;
    return n;
}

static Lista fromArrayInt(const int a[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; i--) {
        l = newNodeInt(a[i], l);
    }
    return l;
}

static void printListaInt(Lista l) {
    printf("[");
    while (l) {
        printf("%d", l->numero);
        if (l->next) printf(", ");
        l = l->next;
    }
    printf("]\n");
}

static void printListaCompressa(ListaCompressa l) {
    printf("[");
    while (l) {
        printf("(%d,%d)", l->numero, l->quanti);
        if (l->next) printf(", ");
        l = l->next;
    }
    printf("]\n");
}

static void freeListaInt(Lista l) {
    while (l) {
        Lista tmp = l->next;
        free(l);
        l = tmp;
    }
}

static void freeListaCompressa(ListaCompressa l) {
    while (l) {
        ListaCompressa tmp = l->next;
        free(l);
        l = tmp;
    }
}



ListaCompressa comprimi(Lista A) {
    
    return NULL;
}

/* =========================
   MAIN DI TEST
   ========================= */
ListaCompressa f(Lista head);
ListaCompressa inserisciincoda(ListaCompressa head, int valore, int occ);
int main(void) {
    int a[] = {3, 3, 3, 3, 2, 2, 3, 5, 5, 5};
    int n = (int)(sizeof(a) / sizeof(a[0]));

    Lista L = fromArrayInt(a, n);

    printf("=== LISTA ORIGINALE ===\n");
    printListaInt(L);

    ListaCompressa C = f(L);

    printf("\n=== LISTA COMPRESSA (valore,conteggio) ===\n");
    printListaCompressa(C);

    

    freeListaInt(L);
    freeListaCompressa(C);
    return 0;
}
ListaCompressa inserisciincoda(ListaCompressa head, int valore, int occ)
    {
        if(head==NULL)
            {
                ListaCompressa new=(ListaCompressa)malloc(sizeof(*new));
                new->numero=valore;
                new->quanti=occ;
                new->next=NULL;
                return new;
            }
        head->next=inserisciincoda(head->next, valore, occ);
        return head;
    }
ListaCompressa f(Lista head)
    {
        if(head==NULL)
            return NULL;
    Lista scorri=head;
    ListaCompressa testa=NULL;
    while (scorri!=NULL) {
        Lista succ=scorri;
        int count=0;
        while(succ!=NULL && succ->numero==scorri->numero)
            {
                count++;
                succ=succ->next;
            }
        testa=inserisciincoda(testa, scorri->numero, count);
        scorri=succ;
    }
    return testa;
    }
