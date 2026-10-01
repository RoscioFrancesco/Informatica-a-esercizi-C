//
//  main.c
//  giorno -7 tde 2 liste
//
//  Created by Francesco Roscio Ricon on 20/01/26.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define N 5








typedef struct EL {
    int info;
    struct EL * prox;
} ElemLista;


typedef ElemLista * Lista;
typedef Lista VettLista[5];


Lista InsInFondoInt(Lista lista,int elem);
void VisualizzaListaInt(Lista lista);
void VisualizzaVettListaInt(VettLista vett);


void costruisciVett(VettLista v);
Lista costruisciLista(int v[],int lun);
float f(VettLista v,int lun);
float media(Lista lis);
//
// TODO: PROTOTIPI DELLA FUNZIONE RICHIESTA E EVENTUALI FUNZIONI AUSILIARIE
//


int main(){
    float ris;
    VettLista vet;
    costruisciVett(vet);
    VisualizzaVettListaInt(vet);


    //TODO: invocazione funzione e stampa
    //(in questo esercizio voi dovete stampare solo nel main)
    ris=f(vet,5);
    printf("%f",ris);


    return 0;
}



float media(Lista lis){
    int somma=0,cont=0;
    for(;lis!=NULL;lis=lis->prox){
        somma=somma+lis->info;
        cont++;
    }
    return (float)somma/cont;
}


float f(VettLista v,int lun){
    int i;
    float somma;
    somma=media(v[0]);
    for(i=1;i<lun;i++){
        somma=somma+media(v[i]);
    }
    return somma;
}




void costruisciVett(VettLista v){
    int m[N][N*2]={3,7,1,8,3,1,9,1,0,0,
                  1,4,2,4,8,2,0,8,2,7,
                  2,4,6,8,3,0,0,0,0,0,
                  1,6,8,3,8,9,3,0,0,0,
                  4,4,8,1,1,6,0,0,0,0};
    int i,lung[N]={8,10,5,7,6};
    
    for(i=0;i<N;i++)
        v[i]=costruisciLista(m[i],lung[i]);
}


Lista costruisciLista(int v[],int lun){
    Lista lis=NULL;    int i=0;
    for(i=0;i<lun;i++)
        lis=InsInFondoInt(lis,v[i]);
    return lis;
}


Lista InsInFondoInt(Lista lista,int elem){
    Lista punt;
    if(lista==NULL) { punt = (Lista)malloc( sizeof(ElemLista) );
                      punt->prox = NULL; punt->info=elem; return  punt;
    }else{lista->prox = InsInFondoInt(lista->prox,elem); return lista;}
}


void VisualizzaListaInt(Lista lista) {
    if (lista==NULL) printf(" ---| \n");
    else{printf(" %d ---> ", lista->info); VisualizzaListaInt( lista->prox );}
}


void VisualizzaVettListaInt(VettLista vett){
    int i;
    for(i=0;i<N;i++){
        VisualizzaListaInt(vett[i]);
        printf("\n");
    }
}
