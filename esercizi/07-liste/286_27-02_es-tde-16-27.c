//
//  main.c
//  es tde 16 27
//
//  Created by Francesco Roscio Ricon on 27/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct n {
    int info;
    struct n *next;
} nodo;

typedef nodo *Lista;

typedef struct li {
    Lista lis;            // sottolista (lista di interi)
    struct li *next;      // prossimo nodo della lista di liste
} lisNodo;

typedef lisNodo *ListaDiListe;

/* ===== PROTOTIPO ===== */
ListaDiListe spezza(Lista L, int k);   // NON IMPLEMENTARE QUI

/* ===== FUNZIONI DI SUPPORTO per il main (creazione/stampa/free) ===== */
nodo* newNodo(int v) {
    nodo *p = (nodo*)malloc(sizeof(nodo));
    if(!p){ printf("malloc failed\n"); exit(1); }
    p->info = v;
    p->next = NULL;
    return p;
}

Lista inserisciCoda(Lista head, int v) {
    nodo *p = newNodo(v);
    if(head == NULL) return p;
    nodo *cur = head;
    while(cur->next != NULL) cur = cur->next;
    cur->next = p;
    return head;
}

Lista buildListaFromArray(const int a[], int n) {
    Lista L = NULL;
    for(int i=0;i<n;i++) L = inserisciCoda(L, a[i]);
    return L;
}

void stampaLista(Lista L) {
    printf("{ ");
    for(nodo *cur=L; cur!=NULL; cur=cur->next) {
        printf("%d", cur->info);
        if(cur->next) printf(", ");
    }
    printf(" }");
}

void stampaListaDiListe(ListaDiListe LL) {
    int idx = 1;
    for(lisNodo *cur=LL; cur!=NULL; cur=cur->next, idx++) {
        printf("L%d = ", idx);
        stampaLista(cur->lis);
        printf("\n");
    }
}

void freeLista(Lista L) {
    while(L) {
        nodo *tmp = L->next;
        free(L);
        L = tmp;
    }
}

void freeListaDiListe(ListaDiListe LL) {
    while(LL) {
        lisNodo *tmp = LL->next;
        /* ogni sottolista è allocata a parte -> va liberata */
        freeLista(LL->lis);
        free(LL);
        LL = tmp;
    }
}

Lista copia(Lista head, int k);
ListaDiListe funz(Lista head, int k);

int main(void) {

    int k = 4;
    int vals[] = {3, 7, 1, 4, 2, 8, 4, 3, 2, 9};
    int n = sizeof(vals)/sizeof(vals[0]);

    Lista L = buildListaFromArray(vals, n);

    printf("Lista L = ");
    stampaLista(L);
    printf("\n\nk = %d\n\n", k);

    
    ListaDiListe LL = funz(L, k);

    printf("Lista di liste (output di spezza):\n");
    stampaListaDiListe(LL);

    /* controllo: L non deve essere modificata */
    printf("\nControllo: L dopo spezza (deve essere identica):\n");
    stampaLista(L);
    printf("\n");

    /* cleanup */
    freeListaDiListe(LL);
    freeLista(L);

    return 0;
}
Lista copia(Lista head, int k)
    {
    Lista new=NULL;
    for(int i=0; i<k && head!=NULL; i++)
        {
            new=inserisciCoda(new, head->info);
            head=head->next;
        }
    return new;
    }
ListaDiListe inserisciLDL(ListaDiListe head, Lista l, int k)
    {
        if(head==NULL)
            {
                ListaDiListe new=(ListaDiListe)malloc(sizeof(*new));
                new->next=NULL;
                new->lis=copia(l, k);
                return new;
            }
    head->next=inserisciLDL(head->next, l, k);
    return head;
    }
ListaDiListe funz(Lista head, int k)
    {
    ListaDiListe new=NULL;
    Lista scorri=head;
    while(scorri!=NULL)
        {
            new=inserisciLDL(new, scorri, k);
            for(int i=0; i<k && scorri!=NULL; i++)
                {
                    scorri=scorri->next;
                }
        }
    return new;
    }
