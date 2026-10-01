//  Created by Francesco Roscio Ricon on 08/02/26.

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE DATI
   ========================= */

/* sottolista di interi ordinata */
typedef struct NodoInt {
    int valore;
    struct NodoInt *next;
} NodoInt;

typedef NodoInt *ListaInt;

/* lista di liste */
typedef struct NodoLista {
    ListaInt lista;
    struct NodoLista *next;
} NodoLista;

typedef NodoLista *ListaListe;


ListaListe eliminaSottolisteRipetute(ListaListe L);

static ListaInt nuovoNodoInt(int v) {
    ListaInt n = (ListaInt)malloc(sizeof(*n));
    if (!n) { perror("malloc"); exit(1); }
    n->valore = v;
    n->next = NULL;
    return n;
}

static ListaListe nuovoNodoLista(ListaInt l) {
    ListaListe n = (ListaListe)malloc(sizeof(*n));
    if (!n) { perror("malloc"); exit(1); }
    n->lista = l;
    n->next = NULL;
    return n;
}

/* inserimenti in coda per comodità */
static ListaInt pushInt(ListaInt head, int v) {
    if (head == NULL) return nuovoNodoInt(v);
    ListaInt p = head;
    while (p->next) p = p->next;
    p->next = nuovoNodoInt(v);
    return head;
}

static ListaListe pushLista(ListaListe head, ListaInt l) {
    if (head == NULL) return nuovoNodoLista(l);
    ListaListe p = head;
    while (p->next) p = p->next;
    p->next = nuovoNodoLista(l);
    return head;
}

/* =========================
   STAMPA
   ========================= */
static void stampaListaInt(ListaInt l) {
    printf("[ ");
    while (l) {
        printf("%d ", l->valore);
        l = l->next;
    }
    printf("]");
}

static void stampaListaListe(ListaListe L) {
    printf("=== LISTA DI SOTTOLISTE ===\n");
    int i = 1;
    while (L) {
        printf("%d) ", i++);
        stampaListaInt(L->lista);
        printf("\n");
        L = L->next;
    }
    printf("\n");
}

/* =========================
   FREE
   ========================= */
static void freeListaInt(ListaInt l) {
    while (l) {
        ListaInt nx = l->next;
        free(l);
        l = nx;
    }
}

static void freeListaListe(ListaListe L) {
    while (L) {
        ListaListe nx = L->next;
        freeListaInt(L->lista);
        free(L);
        L = nx;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
void distruggilista(ListaInt head);
int main(void) {
    ListaListe L = NULL;

    /*
        Creo sottoliste ordinate:
        [1 2 3 4]        -> OK
        [5 5 7]          -> RIPETUTI
        [1 2 2 3]        -> RIPETUTI
        [8 9 10]         -> OK
    */

    ListaInt l1 = NULL;
    l1 = pushInt(l1, 1);
    l1 = pushInt(l1, 2);
    l1 = pushInt(l1, 3);
    l1 = pushInt(l1, 4);

    ListaInt l2 = NULL;
    l2 = pushInt(l2, 5);
    l2 = pushInt(l2, 5);
    l2 = pushInt(l2, 7);

    ListaInt l3 = NULL;
    l3 = pushInt(l3, 1);
    l3 = pushInt(l3, 2);
    l3 = pushInt(l3, 2);
    l3 = pushInt(l3, 3);

    ListaInt l4 = NULL;
    l4 = pushInt(l4, 8);
    l4 = pushInt(l4, 9);
    l4 = pushInt(l4, 10);

    L = pushLista(L, l1);
    L = pushLista(L, l2);
    L = pushLista(L, l3);
    L = pushLista(L, l4);

    printf("Prima dell'eliminazione:\n");
    stampaListaListe(L);

    L = eliminaSottolisteRipetute(L);

    printf("Dopo l'eliminazione:\n");
    stampaListaListe(L);
    printf("(atteso: restano solo [1 2 3 4] e [8 9 10])\n");

    freeListaListe(L);
    return 0;
}
int trovaripetiz(ListaInt head) // 1 se trova ripetizioni
    {
        if(head==NULL)
            return 0;
        ListaInt scorri=head;
        while(scorri!=NULL)
            {
                ListaInt succ=scorri->next;
                while (succ!=NULL) {
                    if(scorri->valore==succ->valore)
                        return 1;
                    succ=succ->next;
                }
                scorri=scorri->next;
            }
        return 0;
    }
ListaListe eliminaSottolisteRipetute(ListaListe head)
    {
        if(head==NULL)
            return head;
        if(trovaripetiz(head->lista))
            {
                ListaListe temp=head->next;
                distruggilista(head->lista);
                free(head);
                return eliminaSottolisteRipetute(temp);
            }
    head->next=eliminaSottolisteRipetute(head->next);
    return head;
    }
void distruggilista(ListaInt head)
    {
        if(head==NULL)
            return;
        ListaInt succ=head->next;
        free(head);
    distruggilista(succ);
    }
