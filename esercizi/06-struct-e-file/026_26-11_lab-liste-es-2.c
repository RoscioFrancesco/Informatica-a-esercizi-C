//  Created by Francesco Roscio Ricon on 26/11/25.

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
void VisualizzaLista( ListaDiElem lista );
float faimedia(ListaDiElem lista1, ListaDiElem lista2);
ListaDiElem prendicomuni(ListaDiElem listaunica);
int trovavalore(ListaDiElem lista, int x);
ListaDiElem unisciliste(ListaDiElem Lista1, ListaDiElem Lista2);

int main() {
    ListaDiElem lista=NULL,lista1=NULL,lista2=NULL, listaunica=NULL, listacomuni=NULL;
    lista1=crea1();
    lista2=crea2();
    VisualizzaLista(lista1);
    printf("\n\n");
    VisualizzaLista(lista2);
    printf("\n\n");
    float media;
    media=faimedia(lista1, lista2);
    printf("%f", media);
    printf("\n\n");
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

ListaDiElem unisciliste(ListaDiElem Lista1, ListaDiElem Lista2)
{
    ListaDiElem temp;
    temp=Lista1;
    if(Lista1==NULL)
        return Lista2;
    if(Lista2==NULL)
        return Lista1;
    while(temp->prox!=NULL)
        {
            temp=temp->prox;
        }
    temp->prox=Lista2;
    return Lista1;
}
int trovavalore(ListaDiElem lista, int x)
{
    ListaDiElem temp = lista;

    while (temp != NULL)
    {
        if (temp->info == x)
            return 1;

        temp = temp->prox;
    }

    return 0;
}
ListaDiElem prendicomuni(ListaDiElem listaunica)
{
    ListaDiElem nuova = listaunica;
    ListaDiElem temp = listaunica;

    while (temp != NULL)
    {
        if (trovavalore(nuova, temp->info))
        {
            nuova = InsInTesta(nuova, temp->info);
        }
        temp = temp->prox;
    }
    return nuova;
}
float faimedia(ListaDiElem lista1, ListaDiElem lista2)
    {
    int somma=0;
    float media=0;
    int contatore=0;
    while (lista1->prox!=NULL)
    {
        while(lista2->prox!=NULL)
            {
                if(lista1->info==lista2->info)
                    {
                        somma=somma+lista1->info;
                        contatore++;
                        break;
                    }
                lista2=lista2->prox;
            }
        lista1=lista1->prox;
        }
    media=(somma+(0.0))/contatore;
    return media;
    }
