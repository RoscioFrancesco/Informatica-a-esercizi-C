//  Created by Francesco Roscio Ricon on 09/02/26.

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct Node {
    int numero;
    struct Node *next;
} Nodo;

typedef Nodo *Lista;

/* =========================
   PROTOTIPO FUNZIONE (ESERCIZIO)
   ========================= */
int crescitaLenta(Lista lis);   

/* =========================
   UTILITY PER CREARE LISTE
   ========================= */
static Lista nuovoNodo(int x) {
    Lista n = (Lista)malloc(sizeof(Nodo));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->numero = x;
    n->next = NULL;
    return n;
}

static Lista inserisciInCoda(Lista head, int x) {
    Lista n = nuovoNodo(x);
    if (head == NULL)
        return n;
    Lista cur = head;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = n;
    return head;
}

/* =========================
   STAMPA LISTA
   ========================= */
static void stampaLista(Lista l) {
    while (l != NULL) {
        printf("%d -> ", l->numero);
        l = l->next;
    }
    printf("NULL\n");
}

/* =========================
   FREE LISTA
   ========================= */
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
int f(Lista head, int *hasprec, int diff_prec);
int main(void) {

    /* Esempio OK: 7 45 67 78 */
    Lista l1 = NULL;
    l1 = inserisciInCoda(l1, 7);
    l1 = inserisciInCoda(l1, 45);
    l1 = inserisciInCoda(l1, 67);
    l1 = inserisciInCoda(l1, 78);

    /* Esempio OK: 7 9 11 13 */
    Lista l2 = NULL;
    l2 = inserisciInCoda(l2, 7);
    l2 = inserisciInCoda(l2, 9);
    l2 = inserisciInCoda(l2, 11);
    l2 = inserisciInCoda(l2, 13);

    /* Esempio NO: 7 45 38 47 */
    Lista l3 = NULL;
    l3 = inserisciInCoda(l3, 7);
    l3 = inserisciInCoda(l3, 45);
    l3 = inserisciInCoda(l3, 38);
    l3 = inserisciInCoda(l3, 47);

    /* Esempio NO: 7 45 234 247 */
    Lista l4 = NULL;
    l4 = inserisciInCoda(l4, 7);
    l4 = inserisciInCoda(l4, 45);
    l4 = inserisciInCoda(l4, 234);
    l4 = inserisciInCoda(l4, 247);

    printf("Lista 1: ");
    stampaLista(l1);

    printf("Lista 2: ");
    stampaLista(l2);

    printf("Lista 3: ");
    stampaLista(l3);

    printf("Lista 4: ");
    stampaLista(l4);


    
    printf("Lista 1 crescita lenta? %d\n", crescitaLenta(l1));
    printf("Lista 2 crescita lenta? %d\n", crescitaLenta(l2));
    printf("Lista 3 crescita lenta? %d\n", crescitaLenta(l3));
    printf("Lista 4 crescita lenta? %d\n", crescitaLenta(l4));
    

    freeLista(l1);
    freeLista(l2);
    freeLista(l3);
    freeLista(l4);

    return 0;
}



int f(Lista head, int *hasprec, int diff_prec)
    {
        if(head==NULL || head->next==NULL)
            return 1;
        if(head->numero>=head->next->numero)
            return 0;
        if(*hasprec==1)
            {
                if(head->next->numero-head->numero>diff_prec)
                    return 0;
            }
    (*hasprec)=1;
    return f(head->next, hasprec, head->next->numero-head->numero);
    }
int crescitaLenta(Lista lis)
    {
        int hasprec=0;
    return f(lis, &hasprec, 0);
    }
