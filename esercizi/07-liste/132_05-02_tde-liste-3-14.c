//
//  main.c
//  tde liste 3 -14
//
//  Created by Francesco Roscio Ricon on 05/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   STRUTTURE DATI
   ========================================================= */
typedef struct nodo {
    int valore;
    struct nodo* next;
} nodo;

typedef nodo* Lista;

/* =========================================================
   PROTOTIPO (DA SVOLGERE)
   ========================================================= */
void prodottoPrecedente(Lista l);   

/* =========================================================
   UTILITY PER TEST (qui i cicli sono OK)
   ========================================================= */
static Lista nuovoNodo(int val, Lista next) {
    Lista n = (Lista)malloc(sizeof(nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->valore = val;
    n->next = next;
    return n;
}

static Lista creaListaDaArray(const int a[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; i--) {
        l = nuovoNodo(a[i], l);
    }
    return l;
}

static void stampaLista(Lista l) {
    printf("[ ");
    while (l != NULL) {
        printf("%d ", l->valore);
        l = l->next;
    }
    printf("]\n");
}

static void liberaLista(Lista l) {
    while (l != NULL) {
        Lista tmp = l;
        l = l->next;
        free(tmp);
    }
}

/* =========================================================
   MAIN DI TEST
   ========================================================= */
void f(Lista head, Lista prec, Lista start_real);
int main(void) {
    int a[] = {4, 6, 2, 3, 9};
    int n = (int)(sizeof(a) / sizeof(a[0]));

    Lista l = creaListaDaArray(a, n);

    printf("Lista iniziale:\n");
    stampaLista(l);

    
    f(l, NULL, l);

    printf("Lista dopo la modifica:\n");
    stampaLista(l);

    printf("Output atteso (se la funzione e' corretta):\n");
    printf("[ 4 24 12 6 27 ]\n");

    liberaLista(l);
    return 0;
}


void prodottoPrecedente(Lista l) {
    /* TODO */
    (void)l; 
}


void f(Lista head, Lista prec, Lista start_real)
    {
        if(head==NULL)
            return;
        f(head->next, head, start_real);
        if(prec==NULL)
            return;
        head->valore=head->valore*prec->valore;
    }
