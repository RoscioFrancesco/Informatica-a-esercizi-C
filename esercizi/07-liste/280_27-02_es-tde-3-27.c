//
//  main.c
//  es tde 3 27
//
//  Created by Francesco Roscio Ricon on 27/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#define N 4
typedef struct EL {
    int dato;
    struct EL *next;
} nodo;

typedef nodo* lista;

/* ===== PROTOTIPI ===== */
int verifica(lista L, int M[N][N]);


lista push_front(lista L, int x) {
    nodo *n = (nodo*)malloc(sizeof(nodo));
    n->dato = x;
    n->next = L;
    return n;
}

void stampaLista(lista L) {
    printf("Lista: ");
    while (L != NULL) {
        printf("%d ", L->dato);
        L = L->next;
    }
    printf("\n");
}

void stampaMatrice(int M[N][N]) {
    printf("Matrice %dx%d:\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d", M[i][j]);
        }
        printf("\n");
    }
}

void freeLista(lista L) {
    while (L != NULL) {
        nodo *tmp = L;
        L = L->next;
        free(tmp);
    }
}
int contienetutti(int mat[N][N], lista head);
int due_per_riga(int mat[N][N], lista head);
int f(int mat[N][N], lista head);
int main(void) {
    /* =========================
       TEST 1 (ATTESO: 1)
       - La matrice contiene tutti gli elementi della lista
       - Ogni riga contiene almeno 2 elementi della lista
       ========================= */
    lista L1 = NULL;
    L1 = push_front(L1, 7);
    L1 = push_front(L1, 3);
    L1 = push_front(L1, 9);

    int M1[N][N] = {
        { 3,  7,  0,  1},  // contiene 3 e 7  -> ok (2 elementi lista)
        { 9,  2,  3,  7},  // contiene 9,3,7  -> ok
        { 4,  9,  7,  8},  // contiene 9 e 7  -> ok
        { 3,  6,  9,  5}   // contiene 3 e 9  -> ok
    };

    printf("=== TEST 1 ===\n");
    stampaLista(L1);
    stampaMatrice(M1);
    printf("Risultato verifica(L1, M1) = %d\n\n", f(M1, L1));

    /* =========================
       TEST 2 (ATTESO: 0)
       - La matrice contiene tutti gli elementi della lista
       - MA esiste almeno una riga con meno di 2 elementi della lista
       ========================= */
    lista L2 = NULL;
    L2 = push_front(L2, 4);
    L2 = push_front(L2, 1);
    L2 = push_front(L2, 8);

    int M2[N][N] = {
        { 1,  4,  9,  2},  // contiene 1 e 4 -> ok
        { 8,  7,  6,  5},  // contiene SOLO 8 -> NO (meno di 2)
        { 4,  1,  3,  8},  // contiene 4,1,8 -> ok
        { 0,  8,  1,  4}   // contiene 8,1,4 -> ok
    };

    printf("=== TEST 2 ===\n");
    stampaLista(L2);
    stampaMatrice(M2);
    printf("Risultato verifica(L2, M2) = %d\n\n", f(M2, L2));

    freeLista(L1);
    freeLista(L2);

    return 0;
}

int trova(int x, lista head)
    {
        if(head==NULL)
            return 0;
    lista scorri=head;
    while(scorri!=NULL)
        {
            if(x==scorri->dato)
                return 1;
            scorri=scorri->next;
        }
    return 0;
    }
int num(lista head)
    {
    int count=0;
        while(head!=NULL)
            {
                count++;
                head=head->next;
            }
    return count;
    }
int f(int mat[N][N], lista head)
    {
        if(head==NULL)
            return 0;
    int numeroelementi=0;
    for(int r=0; r<N; r++)
        {
            int count=0;
            for(int c=0; c<N; c++)
                {
                    if(trova(mat[r][c], head))
                        {
                            numeroelementi++;
                            count++;
                        }
                }
            if(count<2)
                return 0;
        }
    if(num(head)!=numeroelementi)
        return 0;
    return 1;
    }
