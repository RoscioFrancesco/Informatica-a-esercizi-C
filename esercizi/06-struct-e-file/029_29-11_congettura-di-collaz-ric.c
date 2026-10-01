//
//  main.c
//  congettura di collaz.ric
//
//  Created by Francesco Roscio Ricon on 29/11/25.
//
#include<stdio.h>
#include<stdlib.h>

typedef struct EL{
        int info;
        struct EL * prox;
} ElemLista;
typedef ElemLista * ListaDiElem;
int ListaVuota( ListaDiElem lista );
void VisualizzaLista( ListaDiElem lista );
ListaDiElem funz_collaz_ric(int n);
int main() {
    int num;
    ListaDiElem lista=NULL;
    printf("Inserire il numero");
    scanf("%d", &num);
    lista=funz_collaz_ric(num);
    VisualizzaLista(lista);
}
void VisualizzaLista( ListaDiElem lista ) {
    if ( ListaVuota(lista) )
        printf(" ---| \n");
    else {
        printf(" %d ---> ",lista->info);
        VisualizzaLista(lista->prox);
    }
}


int ListaVuota( ListaDiElem lista ) {
    return lista == NULL;
}

ListaDiElem funz_collaz_ric(int n)
    {
    ListaDiElem nodo;
    nodo=(ListaDiElem)malloc(sizeof(ElemLista));
    nodo->info=n;
        if(n==1)
        {
            nodo->prox=NULL;
            return nodo;
        }
    if(n%2==1)
        n=(3*n)+1;
    else
        n=n/2;
    nodo->prox=funz_collaz_ric(n);
    return nodo;
    }
