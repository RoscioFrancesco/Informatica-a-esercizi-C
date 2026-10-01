//
//  main.c
//  tde 3 28
//
//  Created by Francesco Roscio Ricon on 28/02/26.
//

#include <stdio.h>
#include <stdlib.h>

#define N 100

typedef struct nodo {
    int i, j;
    float val;
    struct nodo *next;
} Nodo;
typedef Nodo * Lista;

Lista estraiMassimiLocali(float M[N][N]);   

int ver(int r, int c, float mat[N][N]);

void inizializzaMatrice(float M[N][N]) {
    /* 1) Base liscia: una "ciotola" (valori più bassi al centro) */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float di = (float)(i - 50);
            float dj = (float)(j - 50);
            M[i][j] = -(di*di + dj*dj) / 1000.0f;   /* valori negativi, variazione lenta */
        }
    }

    /* 2) Picchi isolati (massimi locali certi) */
    M[20][20] = 10.0f;
    M[70][40] = 12.0f;
    M[55][80] = 11.0f;
    M[10][90] = 9.5f;

    /* 3) Picchi ai bordi per testare la gestione dei bordi */
    M[0][0]   = 8.0f;     /* angolo */
    M[0][50]  = 7.0f;     /* bordo alto */
    M[99][99] = 8.5f;     /* angolo opposto */
    M[99][10] = 7.5f;     /* bordo basso */

    /* 4) Plateau 3x3: NON deve generare massimi locali (non è strettamente maggiore) */
    for (int i = 30; i <= 32; i++) {
        for (int j = 60; j <= 62; j++) {
            M[i][j] = 5.0f;
        }
    }
}

Lista inserisciincoda(Lista head, float x, int r, int c);

int main(void) {
    static float M[N][N];   /* static: evita stack overflow */
    inizializzaMatrice(M);

    Nodo *L = estraiMassimiLocali(M);

    /* stampa di debug (solo per vedere se la lista esiste) */
    printf("Lista massimi locali (debug):\n");
    for (Nodo *p = L; p != NULL; p = p->next) {
        printf("(%d,%d) -> %.3f\n", p->i, p->j, p->val);
    }

    return 0;
}
int ver(int r, int c, float mat[N][N])
    {
    for(int scorri_r=-1; scorri_r<=1; scorri_r++)
        {
            for(int scorri_c=-1; scorri_c<=1; scorri_c++)
                {
                    if(!(scorri_c==0 && scorri_r==0) && mat[r+scorri_r][c+scorri_c]>=mat[r][c])
                        return 0;
                }
        }
    return 1;
    }
Lista inserisciincoda(Lista head, float x, int r, int c)
{
    if(head==NULL)
        {
            Lista new=(Lista)malloc(sizeof(*new));
            new->next=NULL;
            new->i=r;
            new->j=c;
            new->val=x;
            return new;
        }
    head->next=inserisciincoda(head->next, x, r, c);
    return head;
    }

Lista estraiMassimiLocali(float M[N][N])
    {
    Lista new=NULL;
    for(int r=1; r<N-1; r++)
        {
            for(int c=1; c<N-1; c++)
                {
                    if(ver(r, c, M))
                        {
                            new=inserisciincoda(new, M[r][c], r, c);
                        }
                }
        }
    return new;
    }
