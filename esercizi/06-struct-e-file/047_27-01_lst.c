//
//  main.c
//  lst
//
//  Created by Francesco Roscio Ricon on 27/01/26.
//
#include<stdio.h>
#include<stdlib.h>


typedef struct EL {
    int info;
    struct EL * prox;
} ElemLista;


typedef ElemLista * SottoLista;


typedef struct ELL {
    SottoLista lista;
    struct ELL * prox;
} NodoLista;
typedef NodoLista * ListaDiListe;


SottoLista InsInFondoInt(SottoLista lista,int elem );
ListaDiListe InsInFondoLista( ListaDiListe lista,SottoLista lis );
void VisualizzaListaInt(SottoLista lista );
void VisualizzaListaDiListe(ListaDiListe lista );
ListaDiListe costruisci();
int ripetiz(SottoLista head);
ListaDiListe pulisci(ListaDiListe head);
void distruggisottolista(SottoLista head);

int main(){
    ListaDiListe lis;
    lis=costruisci();
    printf("Lista (ogni elemento in una riga)\n");
    VisualizzaListaDiListe(lis);

    lis=pulisci(lis);
    
    
    printf("Lista dopo pulizia\n");
    VisualizzaListaDiListe(lis);
    
}



ListaDiListe costruisci(){
    int M[8][10]={5,4,1,5,2,7,-1,-1,-1,-1,1,6,9,1,5,7,9,0,-1,-1,1,5,1,1,2,8,9,0,-1,-1,
                  1,3,2,4,0,9,8,6,-1,-1,1,2,9,8,4,0,9,0,-1,-1,1,8,7,8,3,-1,-1,-1,-1,-1,
                  1,3,4,2,5,7,9,0,-1,-1,7,8,9,-1,-1,-1,-1,-1,-1,-1};
    int i,k;ListaDiListe ris=NULL; SottoLista temp=NULL;
    for(i=0;i<8;i++){
        temp=NULL;for(k=0;k<10;k++)if(M[i][k]!=-1)temp=InsInFondoInt(temp,M[i][k]);
        ris=InsInFondoLista(ris,temp);}
    return ris;
}


SottoLista InsInFondoInt(SottoLista lista,int elem ) {
    SottoLista punt;
    if(lista==NULL) { punt = malloc( sizeof(ElemLista) );
                     punt->prox = NULL; punt->info = elem; return  punt;
    }else{lista->prox = InsInFondoInt(lista->prox,elem); return lista;}
}


ListaDiListe InsInFondoLista(ListaDiListe lista,SottoLista lis ) {
   ListaDiListe punt;
   if(lista==NULL) { punt = malloc( sizeof(NodoLista) );
                     punt->prox=NULL; punt->lista=lis; return  punt;
   }else{lista->prox = InsInFondoLista(lista->prox,lis); return lista;}
}


void VisualizzaListaInt(SottoLista lista) {
    if (lista==NULL) printf(" ---| \n");
    else{printf(" %d ---> ", lista->info); VisualizzaListaInt( lista->prox );}
}
void VisualizzaListaDiListe( ListaDiListe lista ) {
    if(lista==NULL) printf("\n");
    else{VisualizzaListaInt(lista->lista); VisualizzaListaDiListe(lista->prox);}
}


int ripetiz(SottoLista head) // se trova una ripetizione
    {
    SottoLista i=head;
    if(head==NULL)
        return 0;
    while(i->prox!=NULL)
        {
            SottoLista j=i->prox;
            while(j!=NULL)
                {
                    if(i->info==j->info)
                        return 1;
                    j=j->prox;
                }
            i=i->prox;
        }
        return 0;
    }

ListaDiListe pulisci(ListaDiListe head)
    {
    ListaDiListe scorri=head;
    ListaDiListe prec=NULL;
    while(scorri!=NULL)
    {
        ListaDiListe succ=scorri->prox;
        if(ripetiz(scorri->lista))
            {
                if(prec==NULL)
                    {
                        head=succ;
                        distruggisottolista(scorri->lista);
                        free(scorri);
                        scorri=head;
                    }
                else
                    {
                        prec->prox=succ;
                        distruggisottolista(scorri->lista);
                        free(scorri);
                        scorri=succ;
                    }
            }
        else
            {
                prec=scorri;
                scorri=succ;
            }
    }
    return head;
    }
void distruggisottolista(SottoLista head)
    {
        if(head==NULL)
            return;
        while(head!=NULL)
            {
                SottoLista temp=head;
                head=head->prox;
                free(temp);
            }
    }



