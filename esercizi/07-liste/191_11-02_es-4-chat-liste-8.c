//
//  main.c
//  es 4 chat liste  -8
//
//  Created by Francesco Roscio Ricon on 11/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE
   ========================= */

typedef struct nodo {
    int valore;
    struct nodo *next;
} Nodo;

typedef Nodo *Lista;

typedef struct nodo2 {
    Lista l;
    struct nodo2 *next;
} Nodo2;

typedef Nodo2 *ListaListe;

/* =========================
   PROTOTIPO FUNZIONE ESAME
   ========================= */

ListaListe filtraListe(ListaListe LL);

/* =========================
   FUNZIONI DI SUPPORTO
   ========================= */

Lista inserisciInCoda(Lista head, int val) {
    Nodo *nuovo = (Nodo*)malloc(sizeof(Nodo));
    nuovo->valore = val;
    nuovo->next = NULL;

    if (head == NULL)
        return nuovo;

    Nodo *scorri = head;
    while (scorri->next != NULL)
        scorri = scorri->next;

    scorri->next = nuovo;
    return head;
}

ListaListe inserisciListaInCoda(ListaListe head, Lista l) {
    Nodo2 *nuovo = (Nodo2*)malloc(sizeof(Nodo2));
    nuovo->l = l;
    nuovo->next = NULL;

    if (head == NULL)
        return nuovo;

    Nodo2 *scorri = head;
    while (scorri->next != NULL)
        scorri = scorri->next;

    scorri->next = nuovo;
    return head;
}

/* =========================
   STAMPA
   ========================= */

void stampaLista(Lista l) {
    while (l != NULL) {
        printf("%d -> ", l->valore);
        l = l->next;
    }
    printf("NULL");
}

void stampaListaListe(ListaListe LL) {
    int i = 1;
    while (LL != NULL) {
        printf("Sottolista %d: ", i);
        stampaLista(LL->l);
        printf("\n");
        LL = LL->next;
        i++;
    }
}

/* =========================
   LIBERAZIONE MEMORIA
   ========================= */

void liberaLista(Lista l) {
    while (l != NULL) {
        Nodo *tmp = l;
        l = l->next;
        free(tmp);
    }
}

void liberaListaListe(ListaListe LL) {
    while (LL != NULL) {
        Nodo2 *tmp = LL;
        liberaLista(LL->l);
        LL = LL->next;
        free(tmp);
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
void distruggisottlista(Lista head);
float media(Lista head);
ListaListe f(ListaListe head);
int crescente(Lista head);
int main() {

    ListaListe LL = NULL;

    /* Sottolista 1 (crescente, media = 2) */
    Lista l1 = NULL;
    l1 = inserisciInCoda(l1, 1);
    l1 = inserisciInCoda(l1, 2);
    l1 = inserisciInCoda(l1, 3);
    LL = inserisciListaInCoda(LL, l1);

    /* Sottolista 2 (crescente, media = 5) */
    Lista l2 = NULL;
    l2 = inserisciInCoda(l2, 4);
    l2 = inserisciInCoda(l2, 5);
    l2 = inserisciInCoda(l2, 6);
    LL = inserisciListaInCoda(LL, l2);

    /* Sottolista 3 (NON crescente) */
    Lista l3 = NULL;
    l3 = inserisciInCoda(l3, 10);
    l3 = inserisciInCoda(l3, 8);
    l3 = inserisciInCoda(l3, 12);
    LL = inserisciListaInCoda(LL, l3);

    /* Sottolista 4 (crescente ma media inferiore alla precedente valida) */
    Lista l4 = NULL;
    l4 = inserisciInCoda(l4, 2);
    l4 = inserisciInCoda(l4, 3);
    LL = inserisciListaInCoda(LL, l4);

    printf("=== PRIMA DEL FILTRO ===\n");
    stampaListaListe(LL);

    LL = filtraListe(LL);

    printf("\n=== DOPO IL FILTRO ===\n");
    stampaListaListe(LL);

    liberaListaListe(LL);

    return 0;
}
int crescente(Lista head)
    {
        if(head==NULL || head->next==NULL)
            return 1;
        if(!(head->next->valore>head->valore))
            return 0;
    return crescente(head->next);
    }
float media(Lista head)
    {
    if(head==NULL)
        return 0;
    float somma=0;
    float count=0;
    while (head!=NULL) {
        somma=somma+head->valore;
        count++;
        head=head->next;
    }
    return somma/count;
    }
void distruggisottlista(Lista head)
    {
        if(head==NULL)
            return;
    Lista temp=head->next;
    free(head);
    distruggisottlista(temp);
    }
ListaListe filtraListe(ListaListe head)
    {
        if(head==NULL)
            return head;
    ListaListe scorri=head;
        ListaListe prec=NULL;
    while (scorri!=NULL)
    {
        ListaListe succ=scorri->next;
        if(!(crescente(scorri->l) && prec!=NULL && media(scorri->l)>media(prec->l)))
            {
                if(prec==NULL)
                    {
                        head=succ;
                        distruggisottlista(scorri->l);
                        free(scorri);
                        scorri=head;
                    }
                else
                {
                    prec->next=succ;
                    distruggisottlista(scorri->l);
                    free(scorri);
                    scorri=succ;
                }
            }
        else
            {
                prec=scorri;
                scorri=succ;
            }
        
    }
        return head;
    }
