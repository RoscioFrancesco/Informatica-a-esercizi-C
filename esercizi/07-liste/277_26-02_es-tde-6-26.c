//
//  main.c
//  es tde 6 26
//
//  Created by Francesco Roscio Ricon on 26/02/26.
//
#include <stdio.h>
#include <stdlib.h>

#define N 4
typedef struct EL{
    int num;
    struct EL* next;
}Elemento;
typedef Elemento *Lista;
int ver(int mat[N][N], int r, int c);
Lista f(int mat[N][N]);
void stampa(Lista head);

int main()
    {
    int M[N][N]={
        {1,2,3,4},
        {5,6,200,8},
        {9,10,11,12},
        {13,14,15,15},
    };
    Lista l=f(M);
    stampa(l);
    }
int ver(int mat[N][N], int r, int c)
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
Lista inseriscincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->num=x;
                new->next=NULL;
                return new;
            }
    head->next=inseriscincoda(head->next, x);
    return head;
    }
Lista f(int mat[N][N])
    {
    Lista new=NULL;
    for(int r=1; r<N-1; r++)
        {
            for(int c=1; c<N-1; c++)
                {
                    if(ver(mat, r, c))
                        {
                            new=inseriscincoda(new, mat[r][c]);
                        }
                }
        }
    return new;
    }

void stampa(Lista head)
    {
        while(head!=NULL)
            {
                printf("%d", head->num);
                head=head-> next;
            }
    }
