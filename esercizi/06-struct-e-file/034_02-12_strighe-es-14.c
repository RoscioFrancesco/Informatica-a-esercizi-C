//  Created by Francesco Roscio Ricon on 02/12/25.

#include<stdio.h>
#include<stdlib.h>
typedef struct EL{
        int info;
        struct EL * prox;
} ElemLista;
typedef ElemLista * ListaDiElem;


int ListaVuota( ListaDiElem lista );
ListaDiElem InsInTesta( ListaDiElem lista, int elem );
ListaDiElem crea1();
ListaDiElem crea2();
ListaDiElem funz(ListaDiElem head, int x);
void VisualizzaLista( ListaDiElem lista );
ListaDiElem eliminalista_ric(ListaDiElem lista, int x);
ListaDiElem scegli(ListaDiElem lista, int x);
ListaDiElem funz_ric(ListaDiElem head, int x)
;
int main() {
    ListaDiElem lista=NULL,lista1=NULL,lista2=NULL, listaunica=NULL;
    lista1=crea1();
    lista2=crea2();
    VisualizzaLista(lista1);
    printf("\n\n");
    VisualizzaLista(lista2);
    printf("\n\n");
    lista1=funz_ric(lista1, 40);
    VisualizzaLista(lista1);
    
}


void VisualizzaLista( ListaDiElem lista ) {
    if ( ListaVuota(lista) )
        printf(" ---| \n");
    else {
        printf(" %d ---> ",lista->info);
        VisualizzaLista(lista->prox);
    }
}


ListaDiElem InsInTesta( ListaDiElem lista, int elem ) {
    ListaDiElem punt;
    punt = (ListaDiElem) malloc(sizeof(ElemLista));
    punt->info = elem;
    punt->prox = lista;
    return  punt;
}


int ListaVuota( ListaDiElem lista ) {
    return lista == NULL;
}


ListaDiElem crea1() {
    ListaDiElem lis=NULL;
    lis=InsInTesta( lis, 2 );
    lis=InsInTesta( lis, 12 );
    lis=InsInTesta( lis, 1 );
    lis=InsInTesta( lis, 4 );
    lis=InsInTesta( lis, 8 );
    lis=InsInTesta( lis, 34 );
    lis=InsInTesta( lis, 78 );
    lis=InsInTesta( lis, 26 );
    lis=InsInTesta( lis, 33 );
    lis=InsInTesta( lis, 11 );
    lis=InsInTesta( lis, 67 );
    lis=InsInTesta( lis, 83 );
    lis=InsInTesta( lis, 92 );
    return lis;
}


ListaDiElem crea2() {
    ListaDiElem lis=NULL;
    lis=InsInTesta( lis, 2 );
    lis=InsInTesta( lis, 10 );
    lis=InsInTesta( lis, 15 );
    lis=InsInTesta( lis, 48 );
    lis=InsInTesta( lis, 82 );
    lis=InsInTesta( lis, 11 );
    lis=InsInTesta( lis, 92 );
    lis=InsInTesta( lis, 22 );
    lis=InsInTesta( lis, 36 );
    lis=InsInTesta( lis, 19 );
    lis=InsInTesta( lis, 69 );
    return lis;
}
ListaDiElem funz(ListaDiElem head, int x)
    {
    ListaDiElem scorri=head;
    if(scorri==NULL)
        return NULL;
    // con questo while no nsto facendo il primo nodo;
    if(head->info>x)
        {
            ListaDiElem temp1=head;
            head=head->prox;
            free(temp1);
            scorri=head;
        }
    while(scorri->prox!=NULL)
        {
            if(scorri->prox->info>x)
                {
                    ListaDiElem temp=scorri->prox;
                    scorri->prox=scorri->prox->prox;
                    free(temp);
                }
            else
                {
                    scorri=scorri->prox;
                }
        }
        return head;
    }
// ora la scrivo ricorsivamente

ListaDiElem funz_ric(ListaDiElem head, int x)
{
    if (head == NULL)
        return NULL;

    head->prox = funz_ric(head->prox, x);

    if (head->info < x)
    {
        ListaDiElem temp = head->prox;
        free(head);
        return temp;
    }

    return head;
}
