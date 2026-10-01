//
//  main.c
//  funzione popola lista
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
Nodo * riempilista(int num);
int main() {
    int num;
    printf("Quanti elementi vuoi inserire nella lista?");
    scanf("%d", &num);
    Nodo *t;
    t=riempilista(num);
}
Nodo * riempilista(int num)
    {
    Nodo *head = NULL;
    Nodo *temp = NULL;
    int i;
    for(i=0; i<num; i++)
        {
            Nodo *nodo= (Nodo*)malloc(sizeof(Nodo));
            scanf("%d", &(nodo->x));
            nodo->next=NULL;
            if(head==NULL)  // se è il primo passaggio
                {
                    head=nodo;
                    temp=nodo;
                }
            else
                {
                    temp->next = nodo; // collega il nodo precedente
                    temp = nodo;
                }
        }
    return head;
    }
