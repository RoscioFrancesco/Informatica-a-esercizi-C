//
//  main.c
//  liste tde 8 liste -12
//
//  Created by Francesco Roscio Ricon on 07/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA LISTA (interi)
   ========================= */
typedef struct nodo {
    int valore;
    struct nodo *next;
} nodo;

typedef nodo* Lista;

/* =========================
   PROTOTIPI FUNZIONI DA SVOLGERE (TODO)
   ========================= */
int listePerTre(Lista l);            /* TODO */
Lista correggiLista(Lista l, int *incremento);    /* TODO: modifica la lista e ritorna somma incrementi */

/* =========================
   UTILITY: CREA NODO
   ========================= */
static Lista newNode(int v) {
    Lista n = (Lista)malloc(sizeof(nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->valore = v;
    n->next = NULL;
    return n;
}

/* =========================
   UTILITY: INSERISCI IN CODA
   ========================= */
static Lista pushBack(Lista head, int v) {
    if (head == NULL) return newNode(v);
    head->next = pushBack(head->next, v);
    return head;
}

/* =========================
   UTILITY: STAMPA LISTA
   ========================= */
static void stampaLista(Lista l) {
    while (l != NULL) {
        printf("%d", l->valore);
        if (l->next) printf("->");
        l = l->next;
    }
    printf("\n");
}

/* =========================
   UTILITY: FREE LISTA
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
int f(Lista l, int val_prec, int* has_prec);
int main(void) {
    /* Caso 1: 2->3->7 (atteso listePerTre=0, dopo correggi: 2->6->18, incrementi=14) */
    Lista A = NULL;
    A = pushBack(A, 2);
    A = pushBack(A, 3);
    A = pushBack(A, 7);

    printf("Caso A iniziale: ");
    stampaLista(A);
    printf("listePerTre(A) = %d (atteso 0)\n", listePerTre(A));

    int incrA=0;
    A = correggiLista(A, &incrA);
    printf("Caso A dopo correggiLista: ");
    stampaLista(A);
    printf("Incrementi totali = %d (atteso 14)\n\n", incrA);

    /* Caso 2: 2 (atteso listePerTre=1, correggi non cambia nulla, incrementi=0) */
    Lista B = NULL;
    B = pushBack(B, 2);

    printf("Caso B iniziale: ");
    stampaLista(B);
    printf("listePerTre(B) = %d (atteso 1)\n", listePerTre(B));

    int incrB=0;
    B = correggiLista(B, &incrB);
    printf("Caso B dopo correggiLista: ");
    stampaLista(B);
    printf("Incrementi totali = %d (atteso 0)\n\n", incrB);

    /* Caso 3: 2->10->40 (atteso listePerTre=1, correggi non cambia nulla, incrementi=0) */
    Lista C = NULL;
    C = pushBack(C, 2);
    C = pushBack(C, 10);
    C = pushBack(C, 40);

    printf("Caso C iniziale: ");
    stampaLista(C);
    printf("listePerTre(C) = %d (atteso 1)\n", listePerTre(C));

    int incremento=0;
    C = correggiLista(C, &incremento);
    
    stampaLista(C);
    printf("Incrementi totali = %d (atteso 0)\n\n", incremento);

    /* cleanup */
    freeLista(A);
    freeLista(B);
    freeLista(C);

    return 0;
}




int listePerTre(Lista l) {
    int flag=0;
    return f(l, 0, &flag);
}

int f(Lista l, int val_prec, int* has_prec)
    {
        if(l==NULL || l->next==NULL)
            return 1;
        if(*has_prec==1)
            {
                if(l->valore<3*val_prec)
                    return 0;
            }
    *has_prec=1;
    return f(l->next, l->valore, has_prec);
    }

/* Modifica la lista aumentando i valori minimi necessari per rispettare il vincolo.
   Ritorna la somma totale degli incrementi applicati.
   Nota: un aumento può “propagare” sui successori. */
Lista correggiLista(Lista l, int *incremento) {
    if(l==NULL)
        return l;
    Lista scorri=l;
    while (scorri->next!=NULL) {
        Lista succ=scorri->next;
        if(succ->valore<3*scorri->valore)
            {
                int temp=succ->valore;
                succ->valore=3*scorri->valore;
                *incremento=*incremento+(succ->valore-temp);
            }
        scorri=succ;
    }
    return l;
}
