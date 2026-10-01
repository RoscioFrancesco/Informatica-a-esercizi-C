//  Created by Francesco Roscio Ricon on 18/01/26.

#include<stdio.h>
#include<stdlib.h>
#include<math.h>


typedef struct P {float x,y;
                  struct P * next; } Punto;
typedef Punto * ListaPunti;


typedef struct S {ListaPunti lisP;
                  struct S * next; } Spezzata;
typedef Spezzata * ListaSpezzate;




ListaPunti InsInFondoPunto(ListaPunti lista,float x,float y);
ListaSpezzate InsInFondoSpezzata( ListaSpezzate lista,ListaPunti lis );
void VisualizzaListaPunti(ListaPunti lista );
void VisualizzaListaSpezzate(ListaSpezzate lista );
ListaSpezzate costruisci();
float distanza(Punto * p1,Punto * p2);
void freespezzata(ListaPunti head);
ListaSpezzate sistemaListaSpezzate(ListaSpezzate head);

int main(){
    ListaSpezzate lis;
    lis=costruisci();
    VisualizzaListaSpezzate(lis);


    lis=sistemaListaSpezzate(lis);
    
    VisualizzaListaSpezzate(lis);


    return 0;
}


//
// TODO: SVILUPPARE QUI LE FUNZIONI RICHIESTE
//




float distanza(Punto * p1,Punto * p2){
    return sqrt((p1->x-p2->x)*(p1->x-p2->x)+(p1->y-p2->y)*(p1->y-p2->y));
}


ListaSpezzate costruisci(){
    int M[5][10]={1,0,2,0,0,2,0,1,-1,-1,
                  1,6,9,1,5,5,9,0,1,1,
                  1,30,1,1,111,1,80,9,0,1,
                  1,3,2,4,0,1,1,7,8,2,
                  1,32,8,88,45,0,90,0,1000,1};
    int i,k;ListaSpezzate ris=NULL; ListaPunti temp=NULL;
    for(i=0;i<5;i++){
        temp=NULL;for(k=0;k<10;k=k+2)if(M[i][k]!=-1)temp=InsInFondoPunto(temp,M[i][k],M[i][k+1]);
        ris=InsInFondoSpezzata(ris,temp);}
    return ris;
}


ListaPunti InsInFondoPunto(ListaPunti lista,float x,float y) {
    ListaPunti punt;
    if(lista==NULL) { punt = (ListaPunti)malloc( sizeof(Punto) );
                     punt->next = NULL; punt->x = x; punt->y = y; return  punt;
    }else{lista->next = InsInFondoPunto(lista->next,x,y); return lista;}
}


ListaSpezzate InsInFondoSpezzata( ListaSpezzate lista,ListaPunti lis ) {
   ListaSpezzate punt;
   if(lista==NULL) { punt = (ListaSpezzate)malloc( sizeof(Spezzata) );
                     punt->next=NULL; punt->lisP=lis; return  punt;
   }else{lista->next = InsInFondoSpezzata(lista->next,lis); return lista;}
}


void VisualizzaListaPunti(ListaPunti lista ){
    if (lista==NULL) printf(" ---| \n");
    else{printf(" (%.2f,%.2f) ---> ", lista->x, lista->y); VisualizzaListaPunti( lista->next );}
}


void VisualizzaListaSpezzate(ListaSpezzate lista ) {
    if(lista==NULL) printf("\n");
    else{VisualizzaListaPunti(lista->lisP); VisualizzaListaSpezzate(lista->next);}
}


float calcolalunghezzaspezzata(ListaPunti head)
    {
        float somma=0.0;
        while(head!=NULL && head->next!=NULL)
            {
                somma=somma+distanza(head, head->next);
                head=head->next;
            }
        return somma;
    }



ListaSpezzate sistemaListaSpezzate(ListaSpezzate head)
    {
    if(head==NULL)
        return head;
    ListaSpezzate scorrispezzate=head;
    ListaSpezzate scorrispezzate_prec=NULL;
    while (scorrispezzate!=NULL && scorrispezzate->next!=NULL) {
        ListaSpezzate scorrispezzate_next=scorrispezzate->next;
            if(calcolalunghezzaspezzata(scorrispezzate->next->lisP)<calcolalunghezzaspezzata(scorrispezzate->lisP))
                {
                    
                    scorrispezzate->next = scorrispezzate_next->next;
                    freespezzata(scorrispezzate_next->lisP);
                    free(scorrispezzate_next);
                    scorrispezzate = scorrispezzate->next;
                }
            else
                {
                    scorrispezzate_prec=scorrispezzate;
                    scorrispezzate=scorrispezzate->next;
                }
        }
    return head;
    }

void freespezzata(ListaPunti head)
    {
        if(head==NULL)
            return;
        while(head!=NULL)
            {
                ListaPunti temp=head;
                head=head->next;
                free(temp);
            }
    }
