//
//  main.c
//  es 4 chat -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//
//Un nodo viene eliminato se:
//dato < somma di tutti i nodi rimasti alla sua sinistra
//MA:
//ogni eliminazione modifica la somma cumulativa
//la somma deve considerare solo i nodi attualmente presenti
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo *next;
} Nodo;

typedef Nodo* lista;

static lista pushBack(lista L, int x) {
    if (L == NULL) {
        lista n = (lista)malloc(sizeof(Nodo));
        n->dato = x;
        n->next = NULL;
        return n;
    }
    L->next = pushBack(L->next, x);
    return L;
}

static lista buildFromArray(const int a[], int n) {
    lista L = NULL;
    for (int i = 0; i < n; i++) L = pushBack(L, a[i]);
    return L;
}

static void stampaLista(lista L) {
    while (L != NULL) {
        printf("%d", L->dato);
        if (L->next) printf(" -> ");
        L = L->next;
    }
    printf("\n");
}

static void liberaLista(lista L) {
    while (L) {
        lista t = L;
        L = L->next;
        free(t);
    }
}

/* ============================
   ESERCIZIO 4 (DA SVOLGERE)
   ============================ */


/* STUB: compila e gira, ma NON risolve l'esercizio */
void f(lista *l, int *count);

int assorbi(lista *L) {
    int count=0;
    f(L, &count);
    return count;
}

/* ============================
   MAIN DI TEST
   ============================ */
int main(void) {
    /* TEST 1: eliminazioni a catena (somma cambia “al volo”) */
    int a1[] = {10, 9, 5, 20, 1, 30};
    /* Scansione (solo per capire l’atteso):
       - 10 resta (primo nodo mai eliminabile), somma=10
       - 9 < 10 -> eliminato, somma resta 10
       - 5 < 10 -> eliminato, somma resta 10
       - 20 < 10? no -> resta, somma=30
       - 1 < 30 -> eliminato, somma resta 30
       - 30 < 30? no (strict) -> resta, somma=60
       Output: 10 -> 20 -> 30, rimossi=3
    */
    lista L1 = buildFromArray(a1, (int)(sizeof(a1)/sizeof(a1[0])));

    printf("=== TEST 1 ===\n");
    printf("Input:\n");
    stampaLista(L1);

    int rimossi1 = assorbi(&L1);

    printf("Output (ottenuto) lista:\n");
    stampaLista(L1);
    printf("Rimossi (ottenuto): %d\n", rimossi1);

    printf("Output ATTESO (corretto):\n");
    printf("Lista: 10 -> 20 -> 30\n");
    printf("Rimossi: 3\n\n");

    liberaLista(L1);

    /* TEST 2: nessuna eliminazione (tutti >= somma sinistra) */
    int a2[] = {3, 3, 6, 12};
    /* - 3 resta, somma=3
       - 3 < 3? no -> resta, somma=6
       - 6 < 6? no -> resta, somma=12
       - 12 < 12? no -> resta
       Output invariato, rimossi=0
    */
    lista L2 = buildFromArray(a2, (int)(sizeof(a2)/sizeof(a2[0])));

    printf("=== TEST 2 ===\n");
    printf("Input:\n");
    stampaLista(L2);

    int rimossi2 = assorbi(&L2);

    printf("Output (ottenuto) lista:\n");
    stampaLista(L2);
    printf("Rimossi (ottenuto): %d\n", rimossi2);

    printf("Output ATTESO (corretto):\n");
    printf("Lista: 3 -> 3 -> 6 -> 12\n");
    printf("Rimossi: 0\n\n");

    liberaLista(L2);

    /* TEST 3: primo non eliminabile, ma tutti gli altri sì */
    int a3[] = {1, 0, 0, 0, 2};
    /* - 1 resta, somma=1
       - 0 < 1 -> elimina
       - 0 < 1 -> elimina
       - 0 < 1 -> elimina
       - 2 < 1? no -> resta
       Output: 1 -> 2, rimossi=3
    */
    lista L3 = buildFromArray(a3, (int)(sizeof(a3)/sizeof(a3[0])));

    printf("=== TEST 3 ===\n");
    printf("Input:\n");
    stampaLista(L3);

    int rimossi3 = assorbi(&L3);

    printf("Output (ottenuto) lista:\n");
    stampaLista(L3);
    printf("Rimossi (ottenuto): %d\n", rimossi3);

    printf("Output ATTESO (corretto):\n");
    printf("Lista: 1 -> 2\n");
    printf("Rimossi: 3\n\n");

    liberaLista(L3);

    return 0;
}
//Un nodo viene eliminato se:
//    dato < somma di tutti i nodi RIMASTI alla sua sinistra

int ver(lista head, lista nodo)
    {
    int somma=0;
    if(head==NULL || nodo==NULL)
        return 0;
    while(head!=NULL)
        {
            if(head==nodo)
                break;
            somma=somma+head->dato;
            head=head->next;
        }
        if(nodo->dato<somma)
            return 1;
    return 0;
    }
void f(lista *l, int *count)
    {
        if(*l==NULL)
            return;
        lista *pp=l;
        while(*pp!=NULL)
            {
                if(ver(*l, *pp))
                    {
                        lista temp=(*pp);
                        (*pp)=(*pp)->next;
                        free(temp);
                        (*count)++;
                        pp=l;
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
