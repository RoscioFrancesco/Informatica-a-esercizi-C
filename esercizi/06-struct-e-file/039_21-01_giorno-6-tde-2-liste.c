//  Created by Francesco Roscio Ricon on 21/01/26.

#include<stdio.h>
#include<stdlib.h>

typedef struct EL {
    int info;
    struct EL * prox;
} ElemLista;

typedef ElemLista * SottoLista;

typedef struct ELD {
    double info;
    struct ELD * prox;
} ElemListaDouble;

typedef ElemListaDouble * ListaDouble;

typedef struct ELL {
    SottoLista lista;
    struct ELL * prox;
} NodoLista;
typedef NodoLista * ListaDiListe;

SottoLista InsInFondoInt(SottoLista lista,int elem );
ListaDiListe InsInFondoLista( ListaDiListe lista,SottoLista lis );
void VisualizzaListaDouble(ListaDouble lista );
void VisualizzaListaInt(SottoLista lista );
void VisualizzaListaDiListe(ListaDiListe lista );
ListaDiListe costruisci();
float calcola_media(SottoLista head);
ListaDouble funzione(ListaDiListe head);


int main(){
    ListaDiListe lis;
    ListaDouble ris=NULL;
    lis=costruisci();
    printf("Lista (ogni elemento in una riga)\n");
    VisualizzaListaDiListe(lis);

    ris=funzione(lis);

    printf("Lista delle medie\n");
    VisualizzaListaDouble(ris);

    return 0;
}
//
// TODO: SVILUPPARE QUI LE FUNZIONI RICHIESTE
//
ListaDiListe costruisci(){
    int M[5][10]={5,4,6,5,3,7,-1,-1,-1,-1,
                  1,6,9,1,5,5,9,0,-1,-1,
                  1,5,1,1,1,1,8,9,0,-1,
                  1,3,2,4,0,-1,-1,-1,-1,-1,
                  1,2,8,8,4,0,9,0,-1,-1};
    int i,k;ListaDiListe ris=NULL; SottoLista temp=NULL;
    for(i=0;i<5;i++){
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
void VisualizzaListaDouble(ListaDouble lista) {
    if (lista==NULL) printf(" ---| \n");
    else{printf(" %lf ---> ", lista->info); VisualizzaListaDouble( lista->prox );}
}
void VisualizzaListaDiListe( ListaDiListe lista ) {
    if(lista==NULL) printf("\n");
    else{VisualizzaListaInt(lista->lista); VisualizzaListaDiListe(lista->prox);}
}


ListaDouble funzione(ListaDiListe head)
    {
        if(head==NULL)
            return NULL;
        ListaDiListe scorri_liste=head;
    ListaDouble testa_lista_medie=NULL;
        while(scorri_liste!=NULL)
            {
                float media=calcola_media(scorri_liste->lista);
                ListaDouble new=(ListaDouble)malloc(sizeof(ElemListaDouble));
                new->info=media;
                new->prox=NULL;
                if(testa_lista_medie==NULL)
                    {
                        testa_lista_medie=new;
                    }
                else
                    {
                        ListaDouble scorrilistadouble=testa_lista_medie;
                        while(scorrilistadouble->prox!=NULL)
                            {
                                scorrilistadouble=scorrilistadouble->prox;
                            }
                        scorrilistadouble->prox=new;
                    }
                scorri_liste=scorri_liste->prox;
            }
    return testa_lista_medie;
    }
float calcola_media(SottoLista head)
    {
    SottoLista scorrinumeri=head;
    float somma=0;
    int contatore=0;
    while (scorrinumeri!=NULL) {
        somma=somma+scorrinumeri->info;
        contatore++;
        scorrinumeri=scorrinumeri->prox;
    }
    return (somma+0.0)/contatore;
    }
