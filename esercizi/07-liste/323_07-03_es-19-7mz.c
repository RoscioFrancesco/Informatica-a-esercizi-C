//  Created by Francesco Roscio Ricon on 07/03/26.
typedef struct EL{
    int valore;
    int r;
    int c;
    struct EL *next;
}Nodo;
typedef Nodo * Lista;

#include <stdio.h>
#include <stdlib.h>
#define N 8
Lista inserisciincoda(Lista head, int val,  int r, int c);
Lista f(int mat[N][N]);
int main() {

}
int ver(int mat[N][N], int r, int c)
    {
    for(int scorri_r=-1; scorri_r<=1; scorri_r++)
        {
            for(int scorri_c=-1; scorri_c<=1; scorri_c++)
                {
                    if(mat[r+scorri_r][c+scorri_c]>=mat[r][c] && !(scorri_c==0 && scorri_r==0))
                        return 0;
                }
        }
    return 1;
    }
Lista inserisciincoda(Lista head, int val,  int r, int c)
    {
        if(head=NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->c=c;
                new->r=r;
                new->valore=val;
                new->next=NULL;
                return new;
            }
    head->next=inserisciincoda(head->next, val, r, c);
    return head;
    }
Lista f(int mat[N][N])
    {
    Lista new=NULL;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(ver(mat, r, c))
                        {
                            new=inserisciincoda(new, mat[r][c], r, c);
                        }
                }
        }
    return new;
    }
