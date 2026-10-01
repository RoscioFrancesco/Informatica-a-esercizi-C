//
//  prova funzione.h
//  lab.es6
//
//  Created by Francesco Roscio Ricon on 08/11/25.
//
#include <stdio.h>
#define N 100
void acquisici_matrice(M[N][N], n_reale);
int main() {
    int n_reale, r, c;
    int M[N][N];
    printf("Inserisci dimensioni reali matrice n*n");
    scanf("%d", &n_reale);
    acquisici_matrice(M, n_reale);
    for(r=0; r<n_reale; r++)
        {
            for(c=0; c<n_reale; c++)
            {
                printf("%d", M[r][c]);
            }
            printf("\n");
        }

}
void acquisici_matrice(M[N][N], n_reale)
    {
    int r,c;
    for(r=0; r<n_reale; r++)
        {
            for(c=0; c<n_reale; c++)
            {
                printf("Inserisci l'elemento [%d][%d]", r,c);
                scanf("%d", &M[r][c]);
            }
        }
    }
