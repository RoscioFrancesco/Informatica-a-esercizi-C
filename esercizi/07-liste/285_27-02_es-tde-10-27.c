//  Created by Francesco Roscio Ricon on 27/02/26.

#include <stdio.h>
#include <stdlib.h>

#define N 100

typedef struct NodeM {
    int numeri[N][N];
    struct NodeM *next;
} NodoM;

typedef NodoM *ListaM;

typedef struct NodeI {
    int numero;
    struct NodeI *next;
} NodoI;

typedef NodoI *ListaI;

ListaI sommaMaggioriDiK(int k, ListaM L);

NodoM* newNodoM(void) {
    NodoM *p = (NodoM*)malloc(sizeof(NodoM));
    if(!p) { printf("Errore malloc NodoM\n"); exit(1); }
    p->next = NULL;

    /* inizializzo tutta la matrice a 0 */
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            p->numeri[i][j] = 0;

    return p;
}

ListaM pushBackM(ListaM head, NodoM *node) {
    if(head == NULL) return node;
    NodoM *cur = head;
    while(cur->next != NULL) cur = cur->next;
    cur->next = node;
    return head;
}

/* ===== SUPPORTO: stampa ListaI ===== */
void stampaListaI(ListaI head) {
    printf("ListaI: ");
    while(head != NULL) {
        printf("%d", head->numero);
        if(head->next) printf(" -> ");
        head = head->next;
    }
    printf(" -> NULL\n");
}

/* (facoltativo) free lista matrici */
void freeListaM(ListaM head) {
    while(head != NULL) {
        ListaM tmp = head->next;
        free(head);
        head = tmp;
    }
}

/* (facoltativo) free lista interi */
void freeListaI(ListaI head) {
    while(head != NULL) {
        ListaI tmp = head->next;
        free(head);
        head = tmp;
    }
}
ListaI inserisciincoda(ListaI head, int x);

int main() {
    int k = 10;          /* soglia di esempio */
    ListaM L = NULL;

    /* =========================
       CREO 3 MATRICI NODI
       ========================= */

    /* --- MATRICE 1 --- */
    NodoM *m1 = newNodoM();
    /* metto alcuni valori >k e alcuni <=k */
    m1->numeri[0][0] = 5;     /* <=k */
    m1->numeri[0][1] = 11;    /* >k */
    m1->numeri[1][0] = 50;    /* >k */
    m1->numeri[2][2] = 10;    /* =k */
    m1->numeri[3][3] = 12;    /* >k */
    L = pushBackM(L, m1);

    /* --- MATRICE 2 --- */
    NodoM *m2 = newNodoM();
    m2->numeri[0][0] = 100;   /* >k */
    m2->numeri[0][1] = -3;    /* <=k (anche negativo) */
    m2->numeri[5][5] = 9;     /* <=k */
    m2->numeri[6][6] = 13;    /* >k */
    m2->numeri[7][7] = 14;    /* >k */
    L = pushBackM(L, m2);

    /* --- MATRICE 3 --- */
    NodoM *m3 = newNodoM();
    m3->numeri[0][0] = 10;    /* =k */
    m3->numeri[0][1] = 10;    /* =k */
    m3->numeri[1][1] = 8;     /* <=k */
    m3->numeri[2][2] = 7;     /* <=k */
    /* questa matrice ha pochi o zero >k, utile per test */
    L = pushBackM(L, m3);

    
    ListaI out = sommaMaggioriDiK(k, L);

    
    printf("k = %d\n", k);
    stampaListaI(out);

    /* free (facoltativi) */
    freeListaM(L);
    freeListaI(out);

    return 0;
}
int somma_mat(int mat[N][N], int k)
    {
    int sum=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(mat[r][c]>k)
                        sum=sum+mat[r][c];
                }
        }
    return sum;
    }
ListaI inserisciincoda(ListaI head, int x)
    {
        if(head==NULL)
            {
                ListaI new=(ListaI)malloc(sizeof(*new));
                new->next=NULL;
                new->numero=x;
                return new;
            }
    head->next=inserisciincoda(head->next, x);
    return head;
    }
ListaI sommaMaggioriDiK(int k, ListaM L)
    {
    ListaI new=NULL;
    ListaM scorri=L;
    while(scorri!=NULL)
        {
            new=inserisciincoda(new, somma_mat(scorri->numeri, k));
            scorri=scorri->next;
        }
    return new;
    }
