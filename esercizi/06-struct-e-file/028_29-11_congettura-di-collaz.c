//
//  main.c
//  congettura di collaz
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
ListaDiElem funzcollatz_iter(int num, ListaDiElem lista);
int ListaVuota( ListaDiElem lista );
ListaDiElem InsInTesta( ListaDiElem lista, int elem );
void VisualizzaLista( ListaDiElem lista );
int main() {
    int num;
    ListaDiElem lista=NULL;
    printf("Inserire il numero");
    scanf("%d", &num);
    lista=funzcollatz_iter(num, lista);
    VisualizzaLista(lista);
}

//ListaDiElem funzcollatz_iter(int num, ListaDiElem lista)
//    {
//    ListaDiElem temp=lista;
//    ListaDiElem temp2=temp;
//    while(num!=1)
//        {
//
//            ListaDiElem nodo=(ListaDiElem)malloc(sizeof(ElemLista));
//            temp2->prox=nodo;
//            temp2=nodo;
//            nodo->info=num;
//            if(num%2==0)
//                num=num/2;
//            if(num%2==1)
//                num=(3*num)+1;
//        }
//    temp->prox=NULL;
//    return lista;
//    }

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
ListaDiElem InsInCoda(ListaDiElem lista, int elem) {
    ListaDiElem nodo = (ListaDiElem)malloc(sizeof(ElemLista));
    nodo->info = elem;
    nodo->prox = NULL;

    if (lista == NULL) {
        return nodo;
    } else {
        ListaDiElem temp = lista;
        while (temp->prox != NULL)
            temp = temp->prox;
        temp->prox = nodo;
        return lista;
    }
}

ListaDiElem funzcollatz_iter(int num, ListaDiElem lista) {
    lista = InsInCoda(lista, num);
    while (num != 1) {
        if (num % 2 == 0)
            num = num / 2;
        else
            num = 3 * num + 1;
        lista = InsInCoda(lista, num);
    }
    return lista;
}


