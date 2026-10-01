//
//  main.c
//  tde 2 liste -13
//
//  Created by Francesco Roscio Ricon on 06/02/26.
#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   STRUTTURE (come da testo)
   ========================================================= */
typedef struct EL {
    int dato;
    struct EL *next;
} nodo;

typedef nodo *lista;

lista intersezioneUgualeOccorrenze(lista L1, lista L2); /* TODO */

nodo* newNodo(int x, nodo* next)
{
    nodo* n = malloc(sizeof(nodo));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->dato = x;
    n->next = next;
    return n;
}

void stampaLista(lista L)
{
    printf("[ ");
    while (L != NULL) {
        printf("%d ", L->dato);
        L = L->next;
    }
    printf("]\n");
}

void liberaLista(lista L)
{
    while (L != NULL) {
        nodo* tmp = L->next;
        free(L);
        L = tmp;
    }
}

/* =========================================================
   MAIN DI TEST
   ========================================================= */
void liberaLista(lista L);
void stampaLista(lista L);
int main(void)
{
    /*
        L1 = 3 5 3 7 8 5
        L2 = 5 3 3 9 5

        Occorrenze:
        3 → 2 volte in entrambe  ✅
        5 → 2 volte in entrambe  ✅
        7 → solo in L1 ❌
        8 → solo in L1 ❌
        9 → solo in L2 ❌

        Output atteso (ordine a scelta):
        [ 3 5 ]
    */

    lista L1 = newNodo(3,
                newNodo(5,
                newNodo(3,
                newNodo(7,
                newNodo(8,
                newNodo(5, NULL))))));

    lista L2 = newNodo(5,
                newNodo(3,
                newNodo(3,
                newNodo(9,
                newNodo(5, NULL)))));

    printf("Lista L1: ");
    stampaLista(L1);

    printf("Lista L2: ");
    stampaLista(L2);

    lista R = intersezioneUgualeOccorrenze(L1, L2);

    printf("Risultato: ");
    stampaLista(R);

    liberaLista(L1);
    liberaLista(L2);
    liberaLista(R);

    return 0;
}
lista inseriscincoda(lista head, int x)
    {
        if(head==NULL)
            {
                lista new=(lista)malloc(sizeof(*new));
                new->dato=x;
                new->next=NULL;
                return new;
            }
        head->next=inseriscincoda(head->next, x);
        return head;
    }
int trovamax(lista head)
    {
        if(head==NULL)
            return 0;
        lista scorri=head;int max=0;
        while(scorri!=NULL)
            {
                if(scorri->dato>max)
                    max=scorri->dato;
                scorri=scorri->next;
            }
    return max;
    }
int *riempivettore(lista head, int *lenvett)
    {
    int num_celle=trovamax(head);
    int *vett=malloc(sizeof(int)*(num_celle+1));
    for(int i=0; i<num_celle; i++)
        vett[i]=0;
    lista scorri=head;
    while (scorri!=NULL) {
        vett[scorri->dato]=vett[scorri->dato]+1;;
        scorri=scorri->next;
    }
    *lenvett=num_celle;
    return vett;
    }
lista intersezioneUgualeOccorrenze(lista L1, lista L2)
    {
    int len1=0;
    int len2=0;
    int *vett1=riempivettore(L1, &len1);
    int *vett2=riempivettore(L2, &len2);
    lista new=NULL;
    for(int i=0; i<len1 && i<len2; i++)
        {
            if(vett1[i]==vett2[i] && vett1[i]!=0)
                new=inseriscincoda(new, i);
        }
    free(vett1);
    free(vett2);
    return new;
    }
