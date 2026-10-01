//
//  main.c
//  tde lista di liste
//
//  Created by Francesco Roscio Ricon on 26/01/26.
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
ListaDiListe pulisci(ListaDiListe lDl);
void puliscisottolista(SottoLista head);
int trovaripetiz(SottoLista head);

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

int trovaripetiz(SottoLista head)
    {
    SottoLista i=head;
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
void puliscisottolista(SottoLista head)
    {
        while(head!=NULL)
            {
                SottoLista temp=head;
                head=head->prox;
                free(temp);
            }
    }
ListaDiListe pulisci(ListaDiListe lDl)
    {
    ListaDiListe scorrilDl=lDl;
    ListaDiListe prec=NULL;
    if(lDl==NULL)
        return lDl;
    while(scorrilDl!=NULL)
        {
            ListaDiListe succ=scorrilDl->prox;
            if(trovaripetiz(scorrilDl->lista))
                {
                    if(scorrilDl==lDl)
                        {
                            lDl=succ;
                            puliscisottolista(scorrilDl->lista);
                            free(scorrilDl);
                            scorrilDl=lDl;
                        }
                    else
                        {
                            prec->prox=succ;
                            puliscisottolista(scorrilDl->lista);
                            free(scorrilDl);
                            scorrilDl=succ;
                        }
                }
            else
                {
                    prec=scorrilDl;
                    scorrilDl=succ;
                }
        }
    return lDl;;
    }






