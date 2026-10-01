//  Created by Francesco Roscio Ricon on 04/02/26.
#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct Node {
    int numero;
    struct Node *next;
} Nodo;

typedef Nodo* Lista;



int contaPicchi(Lista head);   /* TODO */

/* =========================
   UTILITY (per test: cicli OK)
   ========================= */
static Lista newNode(int x, Lista next) {
    Lista n = (Lista)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->numero = x;
    n->next = next;
    return n;
}

static Lista fromArray(const int a[], int n) {
    Lista l = NULL;
    for (int i = n - 1; i >= 0; --i)
        l = newNode(a[i], l);
    return l;
}

static void printLista(Lista l) {
    while (l != NULL) {
        printf("%d ", l->numero);
        l = l->next;
    }
    printf("NULL\n");
}

static void freeLista(Lista l) {
    while (l != NULL) {
        Lista tmp = l->next;
        free(l);
        l = tmp;
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int ver(int prec, int now, int succ);
void f(Lista head, int *count);

int main(void) {
    /* esempio del testo */
    int a1[] = {4, 9, 12, 36, 16, 23, 87, 34, 18, 64, 33};
    Lista l1 = fromArray(a1, (int)(sizeof(a1)/sizeof(a1[0])));

    printf("Lista: ");
    printLista(l1);

    
    int nPicchi = contaPicchi(l1);

    printf("Numero di picchi: %d\n", nPicchi);
    printf("(Per l'esempio dato, atteso: 2)\n");

    freeLista(l1);

    /* test extra: troppo corta (nessun picco) */
    int a2[] = {10, 50};
    Lista l2 = fromArray(a2, 2);
    printf("\nLista: ");
    printLista(l2);
    printf("Numero di picchi: %d (atteso: 0)\n", contaPicchi(l2));
    freeLista(l2);

    /* test extra: picco singolo */
    int a3[] = {10, 30, 10}; /* 30/2=15 >10 e >10 => 30 è picco */
    Lista l3 = fromArray(a3, 3);
    printf("\nLista: ");
    printLista(l3);
    printf("Numero di picchi: %d (atteso: 1)\n", contaPicchi(l3));
    freeLista(l3);
}

void f(Lista head, int *count)
    {
        if(head==NULL || head->next==NULL)
            return;
    Lista scorri=head->next;
    Lista prec=head;
    while(scorri->next!=NULL)
        {
            Lista succ=scorri->next;
            if(ver(prec->numero, scorri->numero, succ->numero))
                {
                    (*count)++;
                }
            prec=scorri;
            scorri=succ;
        }
    }
int ver(int prec, int now, int succ)
{
    return (2*prec < now) && (2*succ < now);
}
int contaPicchi(Lista l1)
    {
        int count=0;
    f(l1, &count);
    return count;
    }

