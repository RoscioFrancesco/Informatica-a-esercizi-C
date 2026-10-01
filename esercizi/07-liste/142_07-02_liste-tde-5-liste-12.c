//  Created by Francesco Roscio Ricon on 07/02/26.

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

void stampaQuasiComuni(Lista lis[], int N);

/* =========================
   FUNZIONI DI SUPPORTO (per costruire/stampare dati di test)
   ========================= */
static Lista nuovoNodo(int x) {
    Lista n = (Lista)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->numero = x;
    n->next = NULL;
    return n;
}

static Lista pushBack(Lista head, int x) {
    Lista n = nuovoNodo(x);
    if (head == NULL) return n;
    Lista p = head;
    while (p->next != NULL) p = p->next;
    p->next = n;
    return head;
}

static void stampaLista(Lista l) {
    printf("[ ");
    while (l != NULL) {
        printf("%d ", l->numero);
        l = l->next;
    }
    printf("]");
}

static void stampaVettoreListe(Lista lis[], int N) {
    printf("=== VETTORE DI LISTE (N=%d) ===\n", N);
    for (int i = 0; i < N; i++) {
        printf("lista[%d] = ", i);
        stampaLista(lis[i]);
        printf("\n");
    }
    printf("\n");
}

static void freeLista(Lista l) {
    while (l != NULL) {
        Lista nx = l->next;
        free(l);
        l = nx;
    }
}

/* =========================
   MAIN (runnabile)
   ========================= */
int trovato(Lista head, int x);
int inquanteliste(int x, Lista lis[], int N);
int trovavalore(int x, Lista head);
int main(void) {

    int N = 4;
    Lista lis[4];

    /* Costruisco 4 liste di esempio */
    lis[0] = NULL;
    lis[0] = pushBack(lis[0], 1);
    lis[0] = pushBack(lis[0], 2);
    lis[0] = pushBack(lis[0], 3);
    lis[0] = pushBack(lis[0], 7);

    lis[1] = NULL;
    lis[1] = pushBack(lis[1], 2);
    lis[1] = pushBack(lis[1], 3);
    lis[1] = pushBack(lis[1], 4);
    lis[1] = pushBack(lis[1], 7);

    lis[2] = NULL;
    lis[2] = pushBack(lis[2], 2);
    lis[2] = pushBack(lis[2], 3);
    lis[2] = pushBack(lis[2], 5);
    lis[2] = pushBack(lis[2], 7);

    lis[3] = NULL;
    lis[3] = pushBack(lis[3], 2);
    lis[3] = pushBack(lis[3], 3);
    lis[3] = pushBack(lis[3], 6);
    /* qui NON metto 7 apposta, per creare un "quasi comune" */

    stampaVettoreListe(lis, N);

    printf("Numeri presenti in tutte le liste tranne una (output atteso se implementato):\n");
    stampaQuasiComuni(lis, N);
    printf("\n");

    /* cleanup */
    for (int i = 0; i < N; i++)
        freeLista(lis[i]);

    return 0;
}

/* =========================
   STUB: NON SVOLGE L'ESERCIZIO
   ========================= */
void stampaQuasiComuni(Lista lis[], int N)
    {
    Lista numeri_fighi=NULL;
    for(int i=0; i<N; i++)
        {
            Lista scorilista=lis[i];
            while(scorilista!=NULL)
                {
                    int ris=inquanteliste(scorilista->numero, &lis[0], N);
                    if(ris==N-1 && trovato(numeri_fighi, scorilista->numero)==0)
                        {
                            numeri_fighi=pushBack(numeri_fighi, scorilista->numero);
                        }
                    scorilista=scorilista->next;
                }
        }
        while(numeri_fighi!=NULL)
            {
                printf("%d", numeri_fighi->numero);
                numeri_fighi=numeri_fighi->next;
            }
    }


int trovavalore(int x, Lista head)
    {
        if(head==NULL)
            return 0;
        if(head->numero==x)
            return 1;
    return trovavalore(x, head->next);
    }
int inquanteliste(int x, Lista lis[], int N)
    {
    int somma=0;
    for(int i=0; i<N; i++)
        {
            somma=somma+trovavalore(x, lis[i]);
        }
    return somma;
    }
int trovato(Lista head, int x)
    {
        if(head==NULL)
            return 0;
    Lista scorri=head;
    while (scorri!=NULL) {
        if(scorri->numero==x)
            return 1;
        scorri=scorri->next;
    }
    return 0;
    }
