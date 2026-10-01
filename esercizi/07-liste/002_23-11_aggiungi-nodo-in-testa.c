//
//  main.c
//  aggiungi nodo in testa
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
typedef Nodo *Lista;
Lista inseriscinuovovalore(Lista l);
void stampalista(Lista l);
int main() {
    Lista l;
    l=(Lista)malloc(sizeof(Nodo));
    l->x=7;
    l->next=NULL;
    int continua=1;
    while(continua==1)
    {
        printf("Vuoi inserire un nuovo valore? 1/0");
        scanf("%d", &continua);
        if(continua!=1)
            break;
        l=inseriscinuovovalore(l);
    }
    stampalista(l);
    printf("NULL");
}
Lista inseriscinuovovalore(Lista l)
    {
        int x;
        printf("Inserire il nuovo valore");
        scanf("%d", &x);
        Lista pnew;
        pnew=(Lista)malloc(sizeof(Nodo));
        pnew->x=x;
        pnew->next=l;
        return pnew; // sto ridando l'indirizzo della nuova testa, che ho legato la resto
    }
void stampalista(Lista l) //indirizzo passato per copia non sotfacendo garbage pk non sto perdendo l'indirizzo della testa
    {
        while(l!=NULL)
        {
            printf("%d-->", l->x);
            l=l->next;
        }
    }
