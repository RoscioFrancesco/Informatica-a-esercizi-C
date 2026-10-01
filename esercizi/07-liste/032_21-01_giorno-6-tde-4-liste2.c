//  Created by Francesco Roscio Ricon on 21/01/26.

#include <stdio.h>
#include <stdlib.h>

/* ====== Lista di input ====== */
typedef struct nd1 {
    int valore;
    struct nd1 *next;
} Nodo;

typedef Nodo *Lista;

/* ====== Lista risultato ====== */
typedef struct nd2 {
    int valore;
    int quanteVolte;
    struct nd2 *next;
} NodoRisultato;

typedef NodoRisultato *ListaRisultato;

/* ====== Funzioni utili ====== */
Nodo *newNodo(int v) {
    Nodo *n = (Nodo *)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->valore = v;
    n->next = NULL;
    return n;
}

NodoRisultato *newNodoRisultato(int v, int count) {
    NodoRisultato *n = (NodoRisultato *)malloc(sizeof(NodoRisultato));
    if (!n) { perror("malloc"); exit(1); }
    n->valore = v;
    n->quanteVolte = count;
    n->next = NULL;
    return n;
}

Lista pushBack(Lista l, int v) {
    Nodo *n = newNodo(v);
    if (l == NULL) return n;

    Nodo *cur = l;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return l;
}

void stampaLista(Lista l) {
    printf("[ ");
    while (l != NULL) {
        printf("%d-->", l->valore);
        l = l->next;
    }
    printf("]\n");
}

void stampaListaRisultato(ListaRisultato r) {
    printf("[ ");
    while (r != NULL) {
        printf("(%d --> %d) ", r->valore, r->quanteVolte);
        r = r->next;
    }
    printf("]\n");
}

void freeLista(Lista l) {
    while (l != NULL) {
        Nodo *tmp = l;
        l = l->next;
        free(tmp);
    }
}

void freeListaRisultato(ListaRisultato r) {
    while (r != NULL) {
        NodoRisultato *tmp = r;
        r = r->next;
        free(tmp);
    }
}
ListaRisultato crea_nodo(ListaRisultato head, int valore);
int trovato(int val, ListaRisultato head);
ListaRisultato funzione(Lista start);

int main() {
    Lista L = NULL;

    /* Lista di test:
       [ 3 5 3 2 5 5 7 2 3 ]
       quindi risultato atteso (ordine non importante):
       (3->3) (5->3) (2->2) (7->1)
    */
    L = pushBack(L, 3);
    L = pushBack(L, 5);
    L = pushBack(L, 3);
    L = pushBack(L, 2);
    L = pushBack(L, 5);
    L = pushBack(L, 5);
    L = pushBack(L, 7);
    L = pushBack(L, 2);
    L = pushBack(L, 3);

    printf("Lista input: ");
    stampaLista(L);

    ListaRisultato R;
    R=funzione(L);

    printf("Lista risultato: ");
    stampaListaRisultato(R);

    freeLista(L);
    freeListaRisultato(R);

    return 0;
}

ListaRisultato funzione(Lista start)
    {
    Lista scorri_lista=start;
    ListaRisultato head=NULL;
    while(scorri_lista!=NULL)
        {
            int val=scorri_lista->valore;
            if(trovato(val, head))
                {
                    ListaRisultato scorri_risulatati=head;
                    while(scorri_risulatati->valore!=val)
                        {
                            scorri_risulatati=scorri_risulatati->next;
                        }
                    (scorri_risulatati->quanteVolte)++;
                }
            else
                {
                    head=crea_nodo(head, val);
                }
            scorri_lista=scorri_lista->next;
        }
    return head;
    }

ListaRisultato crea_nodo(ListaRisultato head, int valore)
    {
    ListaRisultato new=(ListaRisultato)malloc(sizeof(NodoRisultato));
    new->next=NULL;
    new->quanteVolte=1;
    new->valore=valore;
    
    if(head==NULL)
        {
            return new;
        }
    ListaRisultato scorri_risulatati=head;
    while(scorri_risulatati->next!=NULL)
        {
            scorri_risulatati=scorri_risulatati->next;
        }
    scorri_risulatati->next=new;
    return head;
    }
int trovato(int val, ListaRisultato head)
    {
        if(head==NULL)
            return 0;
    ListaRisultato scorri_risulatati=head;
        while(scorri_risulatati!=NULL)
            {
                if(scorri_risulatati->valore==val)
                    {
                        return 1;
                    }
                scorri_risulatati=scorri_risulatati->next;
            }
    return 0;
    }
