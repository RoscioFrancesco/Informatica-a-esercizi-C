//
//  main.c
//  tde 3 1mz
//
//  Created by Francesco Roscio Ricon on 01/03/26.
//


#include <stdio.h>
#include <stdlib.h>
#define N 100
typedef struct NodeM { int numeri[N][N];
                      struct NodeM * next; } NodoM;
typedef NodoM * ListaM;

typedef struct NodeI { int numero;
                      struct NodeI * next; } NodoI;
typedef NodoI * ListaI;
int trovamax(int mat[N][N]);
int trova_val(int mat[N][N], int K);
ListaI inseriscincoda(ListaI head, int x);
ListaI f(ListaM head, int k);


int trova_val(int mat[N][N], int K)
    {
    int max=trovamax(mat);
    if(max<K)
        return 0;
    int min=max;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(mat[r][c]>K && mat[r][c]<min)
                        {
                            min=mat[r][c];
                        }
                }
        }
    return min;
    }
int trovamax(int mat[N][N])
    {
    int max=mat[0][0];
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    if(mat[r][c]>max)
                        {
                            max=mat[r][c];
                        }
                }
        }
    return max;
    }

ListaI inseriscincoda(ListaI head, int x)
    {
        if(head==NULL)
            {
                ListaI new=(ListaI)malloc(sizeof(*new));
                new->next=NULL;
                new->numero=x;
                return new;
            }
        head->next=inseriscincoda(head->next, x);
        return head;
    }
ListaI f(ListaM head, int k)
    {
    ListaI new=NULL;
        while(head!=NULL)
            {
                int num=trova_val(head->numeri, k);
                if(num!=0)
                    {
                        new=inseriscincoda(new, num);
                    }
                head=head->next;
            }
    return new;
    }
