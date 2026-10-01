//
//  main.c
//  es 1 5mz
//
//  Created by Francesco Roscio Ricon on 05/03/26.
//funzione che prendendo in entrata un albero di interi e una lista di interi verifica che in almeno uno dei percorsi radice-foglia compaiono tutti gli interi presenti nella lista

typedef struct EL{
    int x;
    struct EL *sx;
    struct EL *dx;
}Nodo;
typedef Nodo *Tree;

typedef struct ES{
    int x;
    struct ES *next;
}Vagone;
typedef Vagone *Lista;

#include <stdio.h>

int main() {
    
}
int trova(Lista l, int x)
    {
        if(l==NULL)
            return 0;
        while(l!=NULL)
            {
                if(l->x==x)
                    return 1;
                l=l->next;
            }
    return 0;
    }
int cammino(Tree t, Lista l, int count, int num)
    {
        if(t==NULL)
            return 0;
        if(num==count && t->dx==NULL && t->sx==NULL)
            return 1;
        if(trova(l, t->x))
            {
                count++;
            }
    return cammino(t->dx, l, count, num) || cammino(t->sx, l, count, num);
    }
int conta(Lista l)
    {
    int c=0;
    while(l!=NULL)
        {
            c++;
            l=l->next;
        }
    return c;
    }
int f(Tree t, Lista l)
    {
    int num=conta(l);
    return cammino(t, l, 0, num);
    }
