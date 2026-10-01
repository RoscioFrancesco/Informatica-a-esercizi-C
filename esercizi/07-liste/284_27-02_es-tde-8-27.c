//  Created by Francesco Roscio Ricon on 27/02/26.

#include <stdio.h>
#include <stdlib.h>
#define N 20
typedef int matrice[N][N];
typedef matrice matmat[N][N];

int maxK(matmat mm);             // punto (b)

void initZero(matmat mm) {
    for(int a=0; a<N; a++)
        for(int b=0; b<N; b++)
            for(int i=0; i<N; i++)
                for(int j=0; j<N; j++)
                    mm[a][b][i][j] = 0;
}

typedef struct EL{
    int num;
    struct EL*next;
}Elemento;
typedef Elemento* Lista;

/* stampa solo una matrice interna mm[a][b] (utile per controllare) */
void printMatrice(matrice m) {
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++)
            printf("%3d ", m[i][j]);
        printf("\n");
    }
}
int conta(matrice a, int k);
int scorri(matmat T, int k);
int almenoK(matmat T, int k);
int maxK(matmat mm);

int main() {
    matmat mm;

    /* 1) inizializza tutto a 0 */
    initZero(mm);

    /*
      2) COSTRUISCO UN CASO DI TEST "MISTO"
         - alcune matrici interne con molte occorrenze di 3
         - alcune matrici interne con molte occorrenze di 2
         - il resto resta a 0
    */

    /* --- Matrice interna mm[0][0]: metto 3 per 3 volte (>=3 volte) --- */
    mm[0][0][0][0] = 3;
    mm[0][0][0][1] = 3;
    mm[0][0][0][2] = 3;

    /* --- Matrice interna mm[0][1]: metto 3 per 3 volte (>=3 volte) --- */
    mm[0][1][1][0] = 3;
    mm[0][1][1][1] = 3;
    mm[0][1][1][2] = 3;

    /* --- Matrice interna mm[1][0]: metto 3 per 3 volte (>=3 volte) --- */
    mm[1][0][2][0] = 3;
    mm[1][0][2][1] = 3;
    mm[1][0][2][2] = 3;

    /* --- Matrice interna mm[1][1]: metto 2 per 2 volte (>=2 volte) --- */
    mm[1][1][0][0] = 2;
    mm[1][1][0][1] = 2;

    /* --- Matrice interna mm[2][2]: metto 2 per 2 volte (>=2 volte) --- */
    mm[2][2][1][0] = 2;
    mm[2][2][1][1] = 2;

    /*
      3) STAMPE DI CONTROLLO (opzionali)
         stampo solo alcune matrici interne che ho “toccato”
    */
    printf("=== mm[0][0] ===\n");
    printMatrice(mm[0][0]);

    printf("\n=== mm[0][1] ===\n");
    printMatrice(mm[0][1]);

    printf("\n=== mm[1][0] ===\n");
    printMatrice(mm[1][0]);

    printf("\n=== mm[1][1] ===\n");
    printMatrice(mm[1][1]);

    printf("\n=== mm[2][2] ===\n");
    printMatrice(mm[2][2]);

    
    printf("\n=== TEST (a) ===\n");
    printf("almenoK(mm, 2) = %d\n", almenoK(mm, 2));
    printf("almenoK(mm, 3) = %d\n", almenoK(mm, 3));
    printf("almenoK(mm, 4) = %d\n", almenoK(mm, 4));

    printf("\n=== TEST (b) ===\n");
    printf("maxK(mm) = %d\n", maxK(mm));

    return 0;
}
int conta(matrice a, int k)
    {
    int count=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(a[r][c]==k)
                        count++;
                }
        }
        if(count==k)
            return 1;
    return 0;
    }
int almenoK(matmat T, int k)
    {
    int count_matrici=0;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    count_matrici=count_matrici+conta(T[r][c], k);
                    
                }
        }
        if(count_matrici>=k)
            return 1;
    return 0;
    }
int trova_in_lista(Lista head, int x)
    {
        if(head==NULL)
            return 0;
        while(head!=NULL)
            {
                if(head->num==x)
                    return 1;
                head=head->next;
            }
    return 0;
    }

Lista inseriscincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=NULL;
                new->num=x;
                return new;
            }
    head->next=inseriscincoda(head->next, x);
    return head;
    }

Lista riempi(matmat A)
    {
    Lista head=NULL;
    for(int scorri_r=0; scorri_r<N; scorri_r++)
        {
            for(int scorri_c=0; scorri_c<N; scorri_c++)
                {
                    for(int r=0; r<N; r++)
                        {
                            for(int c=0; c<N; c++)
                                {
                                    if(trova_in_lista(head, A[scorri_r][scorri_c][r][c])==0)
                                        {
                                            head=inseriscincoda(head, A[scorri_r][scorri_c][r][c]);
                                        }
                                }
                        }
                }
        }
    return head;
    }
int maxK(matmat mm)
    {
    Lista el=NULL;
    el=riempi(mm);
    int max=0;
    while(el!=NULL)
        {
            if(almenoK(mm, el->num))
                {
                    if(el->num>max)
                        {
                            max=el->num;
                        }
                }
            el=el->next;
        }
    return max;
    }
