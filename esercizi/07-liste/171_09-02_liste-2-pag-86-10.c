//
//  main.c
//  liste 2 pag 86 -10
//
//  Created by Francesco Roscio Ricon on 09/02/26.
//

#include <stdio.h>
#include <stdlib.h>

#define N 4   /* costante predefinita, cambia pure */

/* =========================
   STRUTTURE (come da testo, typo corretto)
   ========================= */
typedef struct EL {
    int dato;
    struct EL *next;
} nodo;

typedef nodo *lista;

/* =========================
   PROTOTIPO FUNZIONE (ESERCIZIO)
   ========================= */

int verificaMatrice(lista l, int M[N][N]);  

/* =========================
   UTILITY LISTA
   ========================= */
static lista nuovoNodo(int x) {
    lista n = (lista)malloc(sizeof(nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = x;
    n->next = NULL;
    return n;
}

static lista inserisciInCoda(lista head, int x) {
    lista n = nuovoNodo(x);
    if (head == NULL) return n;
    lista cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
    return head;
}

static void stampaLista(lista l) {
    while (l != NULL) {
        printf("%d -> ", l->dato);
        l = l->next;
    }
    printf("NULL\n");
}

static void freeLista(lista l) {
    while (l != NULL) {
        lista tmp = l->next;
        free(l);
        l = tmp;
    }
}

/* =========================
   UTILITY MATRICE
   ========================= */
static void stampaMatrice(int M[N][N]) {
    printf("Matrice %dx%d:\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d", M[i][j]);
        }
        printf("\n");
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int scorrilista(lista head, int M[N][N]);
int cercav(int M[N][N], int x);
int trovainlista(int x, lista head);

int main(void) {
    /* Lista di esempio */
    lista l = NULL;
    l = inserisciInCoda(l, 5);
    l = inserisciInCoda(l, 2);
    l = inserisciInCoda(l, 9);

    /* Matrice di test (cambiala per provare casi diversi) */
    int M[N][N] = {
        {5, 7, 2, 0},
        {9, 2, 8, 1},
        {6, 5, 3, 2},
        {4, 9, 5, 2}
    };

    printf("=== INPUT ===\n");
    printf("Lista: ");
    stampaLista(l);
    printf("\n");
    stampaMatrice(M);
    
    int esito = verificaMatrice(l, M);
    printf("Esito verificaMatrice = %d\n", esito);

    freeLista(l);
    return 0;
}

int verificaMatrice(lista l, int M[N][N]) {
    if(scorrilista(l, M)==0)
        return 0;
    for(int r=0; r<N; r++)
        {
            int ris=0;
            for (int c=0; c<N; c++) {
                ris=ris+trovainlista(M[r][c], l);
            }
            if(ris<2)
                return 0;
        }
    return 1;
}

int cercav(int M[N][N], int x)
    {
    int count=0;
    for(int i=0; i<N; i++)
        {
            for(int j=0; j<N; j++)
                {
                    if(M[i][j]==x)
                        count++;
                }
        }
        return count;
    }
int scorrilista(lista head, int M[N][N])
    {
        if(head==NULL)
            return 0;
    while (head!=NULL) {
        if(cercav(M, head->dato)==0)
            return 0;
        head=head->next;
        }
    return 1;
    }
int trovainlista(int x, lista head)
    {
        if(head==NULL)
            return 0;
    while (head!=NULL) {
        if(head->dato==x)
            return 1;
        head=head->next;
    }
    return 0;
    }
