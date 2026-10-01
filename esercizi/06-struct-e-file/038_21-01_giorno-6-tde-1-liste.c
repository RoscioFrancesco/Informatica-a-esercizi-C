//  Created by Francesco Roscio Ricon on 21/01/26.

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
ListaDiListe funzione(ListaDiListe head);
int detector(SottoLista start);




int main(){
    ListaDiListe lis;
    lis=costruisci();
    printf("Lista (ogni elemento in una riga)\n");
    VisualizzaListaDiListe(lis);


    lis=funzione(lis);
    
    
    printf("Lista dopo pulizia\n");
    VisualizzaListaDiListe(lis);


    return 0;
}


//
// TODO: SVILUPPARE QUI LE FUNZIONI RICHIESTE
//




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

int detector(SottoLista start)
    {
        SottoLista scorri_sottolista1=start;
        while(scorri_sottolista1!=NULL && scorri_sottolista1->prox!=NULL)
            {
                SottoLista scorri_sottolista2=scorri_sottolista1->prox;
                while(scorri_sottolista2!=NULL)
                    {
                        if(scorri_sottolista1->info==scorri_sottolista2->info)
                            return 1;
                        scorri_sottolista2=scorri_sottolista2->prox;
                    }
                scorri_sottolista1=scorri_sottolista1->prox;
            }
    return 0;
    }

ListaDiListe funzione(ListaDiListe head)
    {
    ListaDiListe scorri_lista_di_liste=head;
    ListaDiListe prec=NULL;
    while(scorri_lista_di_liste!=NULL)
        {
            ListaDiListe succ=scorri_lista_di_liste->prox;
            if(detector(scorri_lista_di_liste->lista))
                {
                    if(prec==NULL)
                        {
                            head=succ;
                            free(scorri_lista_di_liste);
                            scorri_lista_di_liste=succ;
                        }
                    else
                        {
                            prec->prox=succ;
                            free(scorri_lista_di_liste);
                            scorri_lista_di_liste=succ;
                        }
                }
            else{
                prec=scorri_lista_di_liste;
                scorri_lista_di_liste=succ;
            }
        }
    return head;
    }





