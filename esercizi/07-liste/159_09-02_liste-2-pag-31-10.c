//
//  main.c
//  liste 2 pag 31 -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct Elem {
    int x;
    int y;
    struct Elem *next;
} Punto;

typedef Punto *Linea;


int scorciatoia(Linea A, Linea B);   /* 1 se A è scorciatoia di B, 0 altrimenti */
int estende(Linea A, Linea B);       /* 1 se A estende B, 0 altrimenti */
Linea concatena(Linea A, Linea B);   
float tortuosita(Linea A);           /* lunghezza(A) / distanza(estremi) */

/* =========================
   SUPPORTO (utility per test)
   ========================= */
static Punto *nuovoPunto(int x, int y) {
    Punto *p = (Punto *)malloc(sizeof(Punto));
    if (!p) { perror("malloc"); exit(1); }
    p->x = x;
    p->y = y;
    p->next = NULL;
    return p;
}

static Linea push_back(Linea L, int x, int y) {
    Punto *n = nuovoPunto(x, y);
    if (L == NULL) return n;
    Punto *cur = L;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return L;
}

static void stampaLinea(Linea L) {
    printf("[");
    while (L != NULL) {
        printf("(%d,%d)", L->x, L->y);
        if (L->next != NULL) printf(" -> ");
        L = L->next;
    }
    printf("]\n");
}

/* utile per debug: numero punti */
static int lunghezzaNodi(Linea L) {
    int c = 0;
    while (L != NULL) { c++; L = L->next; }
    return c;
}

/* libera tutta la linea */
static void freeLinea(Linea L) {
    while (L != NULL) {
        Punto *tmp = L->next;
        free(L);
        L = tmp;
    }
}

/* clona una linea (per fare test senza “rompere” le originali) */
static Linea clonaLinea(Linea L) {
    Linea out = NULL;
    while (L != NULL) {
        out = push_back(out, L->x, L->y);
        L = L->next;
    }
    return out;
}

/* =========================
   MAIN DI TEST
   ========================= */
float lenlinea(Linea head);
int contiene(Linea A, Linea B);
int confrontapunti(Punto a, Punto b);
int estende(Linea A, Linea B);


int main(void) {
    /* Spezzata B (esempio) */
    Linea B = NULL;
    B = push_back(B, 0, 0);
    B = push_back(B, 1, 0);
    B = push_back(B, 2, 0);
    B = push_back(B, 3, 1);

    /* Spezzata A (stessi estremi di B, ma “più diretta” - esempio) */
    Linea A = NULL;
    A = push_back(A, 0, 0);
    A = push_back(A, 3, 1);

    /* Spezzata C (altra) */
    Linea C = NULL;
    C = push_back(C, 10, 10);
    C = push_back(C, 11, 10);

    printf("Linea A (%d punti): ", lunghezzaNodi(A));
    stampaLinea(A);
    printf("Linea B (%d punti): ", lunghezzaNodi(B));
    stampaLinea(B);
    printf("Linea C (%d punti): ", lunghezzaNodi(C));
    stampaLinea(C);

    
    printf("\nscorciatoia(A, B) = %d\n", scorciatoia(A, B));
    printf("scorciatoia(B, A) = %d\n", scorciatoia(B, A));

    printf("\nestende(B, A) = %d\n", estende(B, A));
    printf("estende(A, B) = %d\n", estende(A, B));
}


int scorciatoia(Linea A, Linea B)
    {
        if(A->x!=B->x || A->y!=B->y)
            return 0;
        Linea scorriA=A;
        Linea scorriB=B;
        while(scorriA->next!=NULL)
            {
                scorriA=scorriA->next;
            }
    while (  scorriB->next!=NULL) {
        scorriB=scorriB->next;
        }
        if(scorriA->x!=scorriB->x || scorriA->y!=scorriB->y)
            return 0;
        if(lenlinea(A)<lenlinea(B))
            return 1;
    return 0;
    }
float distanza2punt(Punto A, Punto B)
    {
    int x=A.x-B.x;
    int y=A.y-B.y;
    return sqrtf(x*x+y*y);
    }
float lenlinea(Linea head)
    {
        if(head==NULL)
            return 0;
    float somma=0;
    while (head!=NULL && head->next!=NULL) {
        somma=somma+distanza2punt(*head, *(head->next));
        head=head->next;
    }
    return somma;
    }
int estende(Linea A, Linea B)
    {
        if(A==NULL || B==NULL)
            return 0;
    Linea scorriA=A;
    Linea scorriB=B;
    while (scorriA->next!=NULL) {
        scorriA=scorriA->next;
    }
    while (scorriB->next!=NULL) {
        scorriB=scorriB->next;
    }
    if(confrontapunti(*scorriA, *scorriB)==0)
        return 0;
    return contiene(A, B);
    }
int confrontapunti(Punto a, Punto b)
    {
        if(a.x==b.x && a.y==b.y)
            return 1;
    return 0;
    }
int contiene(Linea A, Linea B)
    {
        if(A==NULL || B==NULL)
            return 0;
    Linea scorriA=A;
        while(scorriA!=NULL)
            {
                if(confrontapunti(*scorriA, *B))
                    {
                        Linea scorriB=B;
                        Linea riscorriA=scorriA;
                        while (scorriB!=NULL && riscorriA!=NULL && confrontapunti(*scorriB, *riscorriA)) {
                            riscorriA=riscorriA->next;
                            scorriB=scorriB->next;
                        }
                        if(scorriB==NULL)
                            return 1;
                    }
                scorriA=scorriA->next;
            }
        return 0;
    }
