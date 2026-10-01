//
//  main.c
//  es 3 chat -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* ============================
   STRUTTURE DATI
   ============================ */
typedef struct Nodo {
    int dato;
    struct Nodo *next;
} Nodo;

typedef Nodo* lista;

/* ============================
   HELPERS: build / print / free
   ============================ */
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
   ESERCIZIO 3 (DA SVOLGERE)
   ============================ */


/* STUB: compila e gira, ma NON risolve l'esercizio */
lista eliminaBlocchiAlternatiMassimali(lista L);

/* ============================
   MAIN DI TEST
   ============================ */
int main(void) {
    /* TEST 1: un blocco alternato massimale lungo (>=4) da eliminare */
    int a1[] = {1, 5, 2, 6, 3, 10};   /* 1<5>2<6>3<10 : alternato massimale lungo 6 */
    lista L1 = buildFromArray(a1, (int)(sizeof(a1)/sizeof(a1[0])));

    printf("=== TEST 1 ===\n");
    printf("Input:\n");
    stampaLista(L1);
    L1 = eliminaBlocchiAlternatiMassimali(L1);
    printf("Output (ottenuto):\n");
    stampaLista(L1);
    printf("Output ATTESO (corretto):\n");
    printf("(lista vuota)\n\n");

    liberaLista(L1);

    /* TEST 2: blocchi piccoli (1-2) NON si eliminano, blocco alternato da 3 NON si elimina */
    int a2[] = {4, 1, 3, 2, 2, 7};
    /* 4>1<3 (lunghezza 3 alternato) -> NON eliminare
       poi 3>2 (coppia) -> NON eliminare
       poi 2=2 rompe (uguaglianza non è < o >), poi 2<7 (coppia) -> NON eliminare */
    lista L2 = buildFromArray(a2, (int)(sizeof(a2)/sizeof(a2[0])));

    printf("=== TEST 2 ===\n");
    printf("Input:\n");
    stampaLista(L2);
    L2 = eliminaBlocchiAlternatiMassimali(L2);
    printf("Output (ottenuto):\n");
    stampaLista(L2);
    printf("Output ATTESO (corretto):\n");
    printf("4 -> 1 -> 3 -> 2 -> 2 -> 7\n\n");

    liberaLista(L2);

    /* TEST 3: due blocchi alternati separati da un tratto NON alternato */
    int a3[] = {9, 1, 8, 2, 7, 7,  3, 10, 4, 9, 5};
    /* Primo pezzo: 9>1<8>2<7 (lunghezza 5, alternato massimale) -> ELIMINARE
       poi 7=7 rompe
       Secondo pezzo: 3<10>4<9>5 (lunghezza 5, alternato massimale) -> ELIMINARE
       Risultato: rimane solo "7 -> 7" */
    lista L3 = buildFromArray(a3, (int)(sizeof(a3)/sizeof(a3[0])));

    printf("=== TEST 3 ===\n");
    printf("Input:\n");
    stampaLista(L3);
    L3 = eliminaBlocchiAlternatiMassimali(L3);
    printf("Output (ottenuto):\n");
    stampaLista(L3);
    printf("Output ATTESO (corretto):\n");
    printf("7 -> 7\n\n");

    liberaLista(L3);

    /* TEST 4: blocco alternato in mezzo, testa e coda restano */
    int a4[] = {100,  1, 5, 2, 6, 3,  200};
    /* In mezzo: 1<5>2<6>3 (lunghezza 5) -> ELIMINARE
       Restano: 100 -> 200 */
    lista L4 = buildFromArray(a4, (int)(sizeof(a4)/sizeof(a4[0])));

    printf("=== TEST 4 ===\n");
    printf("Input:\n");
    stampaLista(L4);
    L4 = eliminaBlocchiAlternatiMassimali(L4);
    printf("Output (ottenuto):\n");
    stampaLista(L4);
    printf("Output ATTESO (corretto):\n");
    printf("100 -> 200\n\n");

    liberaLista(L4);

    return 0;
}

int lunghezzaBloccoAlternatoMassimale(lista start)
{
    if (start == NULL || start->next == NULL)
        return 1;   // un solo nodo

    int len = 1;

    lista curr = start;
    lista next = start->next;

    /* Se i primi due sono uguali non c'è alternanza */
    if (curr->dato == next->dato)
        return 1;

    /* Determino il primo verso */
    int crescente = (curr->dato < next->dato);
    len = 2;

    curr = next;
    next = next->next;

    while (next != NULL)
    {
        if (crescente)
        {
            /* Dovevo avere un ">" */
            if (curr->dato > next->dato)
            {
                len++;
                crescente = 0;   // ora deve essere <
            }
            else
                break;
        }
        else
        {
            /* Dovevo avere un "<" */
            if (curr->dato < next->dato)
            {
                len++;
                crescente = 1;   // ora deve essere >
            }
            else
                break;
        }

        curr = next;
        next = next->next;
    }

    return len;
}
lista eliminaK(lista head, int K)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<K && head!=NULL; i++)
        {
            lista temp=head->next;
            free(head);
            head=temp;
        }
    return head;
    }
void f(lista *l)
    {
        if(*l==NULL)
            return;
        lista *pp=l;
        while(*pp!=NULL)
            {
                int len=lunghezzaBloccoAlternatoMassimale(*pp);
                if(len>=4)
                    {
                        (*pp)=eliminaK((*pp), len);
                        pp=l;
                    }
                else
                    {
                        pp=&(*pp)->next;
                    }
            }
    }
lista eliminaBlocchiAlternatiMassimali(lista L)
    {
    f(&L);
    return L;
    }
