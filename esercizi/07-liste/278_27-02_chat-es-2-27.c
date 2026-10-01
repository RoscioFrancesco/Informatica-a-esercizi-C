//
//  main.c
//  chat es 2 27
//
//  Created by Francesco Roscio Ricon on 27/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#define N 5

typedef struct {
    int dr;
    int dc;
    const char *name;
} Dir;

typedef struct EL{
    int r;
    int c;
    struct EL *next;
}Elemento;
typedef Elemento *Lista;
int esistePercorso(int M[][N], int r, int c);

/* (facoltativa) ricorsiva di supporto: tipicamente con visited per evitare loop */
int dfsPercorso(int M[][N], int r, int c, int visited[][N]);
int f(int M[][N], int r, int c, Lista *l);

/* =========================
   STAMPA MATRICE
   ========================= */
void stampaMatrice(const char *titolo, int M[][N]) {
    printf("\n%s\n", titolo);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d", M[i][j]);
        }
        printf("\n");
    }
}

/* =========================
   MAIN di TEST
   ========================= */
int trova(Lista head, int r, int c);
Lista inserisciincoda(Lista head, int r, int c);
int main(void) {
    /* Caso A: matrice con “salite” che possono portare a un bordo da alcuni punti */
    int A[N][N] = {
        {  1,  2,  3,  4,  5 },
        {  0,  9,  8,  7,  6 },
        { -1, 10, 11, 12, 13 },
        { -2, 15, 14, 20, 19 },
        { -3, 16, 17, 18, 21 }
    };

    /* Caso B: matrice “piatta” (tutti uguali): non esistono mosse strettamente crescenti */
    int B[N][N] = {
        { 5, 5, 5, 5, 5 },
        { 5, 5, 5, 5, 5 },
        { 5, 5, 5, 5, 5 },
        { 5, 5, 5, 5, 5 },
        { 5, 5, 5, 5, 5 }
    };

    /* Caso C: matrice con crescita solo “intrappolata” (potrebbe non arrivare al bordo da certi punti) */
    int C[N][N] = {
        {  1,  2,  3,  4,  5 },
        {  2, 50, 49, 48,  6 },
        {  3, 51,  1, 47,  7 },
        {  4, 52, 53, 46,  8 },
        {  5,  6,  7,  8,  9 }
    };

    stampaMatrice("Matrice A:", A);
    printf("\nTest su A:\n");
    printf("esistePercorso(A, 2, 1) = %d\n", esistePercorso(A, 2, 1));
    printf("esistePercorso(A, 0, 0) = %d\n", esistePercorso(A, 0, 0));
    printf("esistePercorso(A, 3, 3) = %d\n", esistePercorso(A, 3, 3));

    stampaMatrice("Matrice B:", B);
    printf("\nTest su B:\n");
    printf("esistePercorso(B, 2, 2) = %d\n", esistePercorso(B, 2, 2));
    printf("esistePercorso(B, 0, 4) = %d\n", esistePercorso(B, 0, 4));

    stampaMatrice("Matrice C:", C);
    printf("\nTest su C:\n");
    printf("esistePercorso(C, 2, 2) = %d\n", esistePercorso(C, 2, 2));
    printf("esistePercorso(C, 1, 1) = %d\n", esistePercorso(C, 1, 1));
    printf("esistePercorso(C, 4, 0) = %d\n", esistePercorso(C, 4, 0));

    return 0;
}

/* =========================
   STUB (NON RISOLVO)
   ========================= */
int f(int M[][N], int r, int c, Lista *l) {
    if(r==0 || c==0 || r==N-1 || c==N-1)
        return 1;
    if(trova(*l, r, c))
        return 0;
    *l=inserisciincoda(*l, r, c);
    int sopra=0;
    int sotto=0;
    int sx=0;
    int dx=0;
    if(M[r][c+1]>M[r][c])
        {
            dx=f(M, r, c+1, l);
        }
    if(M[r][c-1]>M[r][c])
        {
            sx=f(M, r, c-1, l);
        }
    if(M[r-1][c]>M[r][c])
        {
            sopra=f(M, r-1,c, l);
        }
    if(M[r+1][c]>M[r][c])
        {
            sotto=f(M, r+1, c, l);
        }
    return sx|| dx|| sopra|| sotto;
}
int trova(Lista head, int r, int c)
    {
        if(head==NULL)
            return 0;
        while(head!=NULL)
            {
                if(head->c==c && head->r==r)
                    return 1;
                head=head->next;
            }
    return 0;
    }
Lista inserisciincoda(Lista head, int r, int c)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->c=c;
                new->r=r;
                new->next=NULL;
                return new;
            }
    head->next=inserisciincoda(head->next, r, c);
    return head;
    }
int esistePercorso(int M[][N], int r, int c)
    {
    Lista new=NULL;
    return f(M, r, c, &new);
    }
