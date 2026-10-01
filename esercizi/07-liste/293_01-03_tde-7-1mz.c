//
//  main.c
//  tde 7 1mz
//
//  Created by Francesco Roscio Ricon on 01/03/26.

#include <stdio.h>
#include <stdlib.h>
#define N 4
typedef struct EL{
    int x;
    int occ;
    struct EL *next;
}Vagone;
typedef Vagone *Lista;
int f(int mat[N][N]);
void distruggi(Lista head);
int main()
{
    int mat[N][N]={
        {1,2,3,4},
        {2,5,6,7},
        {3,9,10,12},
        {1,3,7,8}
    };
    printf("%d", f(mat));
}
Lista inserisciincoda(Lista head, int x)
    {
        if(head==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=NULL;
                new->occ=1;
                new->x=x;
                return new;
            }
        head->next=inserisciincoda(head->next, x);
        return head;
    }
Lista trova(Lista head, int x)
    {
        if(head==NULL)
            return NULL;
    Lista scorri=head;
    while(scorri!=NULL)
        {
            if(scorri->x==x)
                return scorri;
            scorri=scorri->next;
        }
    return NULL;
    }
int f(int mat[N][N])
    {
    Lista new=NULL;
    for(int r=0; r<N; r++)
        {
            for(int c=0; c<N; c++)
                {
                    Lista punt=trova(new, mat[r][c]);
                    if(punt==NULL)
                        {
                            new=inserisciincoda(new, mat[r][c]);
                        }
                    else
                        {
                            (punt->occ)++;
                        }
                }
        }
    int count=0;
    Lista temp=new;
    while(new!=NULL)
        {
            count++;
            new=new->next;
        }
    distruggi(temp);
    return count;
    }
void distruggi(Lista head)
    {
        if(head==NULL)
            return;
    Lista temp=head->next;
    free(head);
    head=temp;
    distruggi(head);
    }
