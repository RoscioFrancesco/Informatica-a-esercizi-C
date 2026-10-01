//
//  main.c
//  liste prova2
//
//  Created by Francesco Roscio Ricon on 23/11/25.
//

#include <stdio.h>
#include <stdlib.h>
//come prima cosa definisco il tipo strutturato nodo
typedef struct el
{
    int x;
    struct el *next;
}Nodo;
int main()
{
//    metto nodo nell'heap
    Nodo *t;
    t=(Nodo*)malloc(sizeof(Nodo));
    t->x=7;
    t->next=NULL;
//  quella sopra è una lista con un solo nodo e la messa a terra;
    Nodo *b;
    b=(Nodo*)malloc(sizeof(Nodo));
    b->x=8;
    b->next=NULL;
    t->next=b;
    Nodo *temp;
    temp=t;
    Nodo *curr;
    curr=t;
    while(t!=NULL)
        {
            printf("%d-->", t->x);
            t=t->next;
        }
    while(curr != NULL) {
        temp = curr;        // salvo nodo corrente
        curr = curr->next;  // passo al prossimo nodo
        free(temp);         // libero nodo corrente
    }
}
