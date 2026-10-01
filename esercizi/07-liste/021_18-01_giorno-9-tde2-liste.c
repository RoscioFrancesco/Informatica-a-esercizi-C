//  Created by Francesco Roscio Ricon on 18/01/26.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct P {
    float x, y;
    struct P *next;
} Punto;


typedef Punto *Poligono;


typedef struct S {
    Poligono lisP;
    struct S *next;
} Pol;


typedef Pol *ListaPoligoni;


ListaPoligoni costruisci();
Poligono InsInFondoPunto(Poligono lista,float x,float y);
ListaPoligoni InsInFondoPoligono( ListaPoligoni lista,Poligono lis );
void VisualizzaPoligono(Poligono lista );
void VisualizzaListaPoligoni(ListaPoligoni lista );
float distanza(Poligono punto_a, Poligono punto_b);
float mediaListaPoligoni (ListaPoligoni lista_poligoni);
float calcolaperimetro(Poligono lista_punti);
ListaPoligoni rimuoviPoligoniCorti(ListaPoligoni head);


int main() {
    // Creazione di una lista di poligoni di esempio
    ListaPoligoni lista=costruisci();


    printf("Lista iniziale:\n");
    VisualizzaListaPoligoni(lista);

    float media=mediaListaPoligoni(lista);
    


    printf("Lista dopo l'eliminazione dei poligoni con perimetro sotto la media:\n");
    lista=rimuoviPoligoniCorti(lista);
    VisualizzaListaPoligoni(lista);

    printf("%f", media);
    return 0;
}


//AGGIUNGERE QUI LE FUNZIONI


ListaPoligoni costruisci(){
    int M[5][10]={0,0,1,0,2,2,1,1,-1,-1,
                  1,6,9,1,5,5,1,9,0,8,
                  1,3,1,4,4,4,4,2,3,1,
                  1,3,2,4,0,2,0,0,-1,-1,
                  1,32,8,8,5,0,-1,-1,-1,-1};
    int i,k;ListaPoligoni ris=NULL; Poligono temp=NULL;
    for(i=0;i<5;i++){
        temp=NULL;for(k=0;k<10;k=k+2)if(M[i][k]!=-1)temp=InsInFondoPunto(temp,M[i][k],M[i][k+1]);
        ris=InsInFondoPoligono(ris,temp);}
    return ris;
}




Poligono InsInFondoPunto(Poligono lista,float x,float y) {
    Poligono punt;
    if(lista==NULL) { punt = (Poligono)malloc( sizeof(Punto) );
                     punt->next = NULL; punt->x = x; punt->y = y; return  punt;
    }else{lista->next = InsInFondoPunto(lista->next,x,y); return lista;}
}


ListaPoligoni InsInFondoPoligono( ListaPoligoni lista,Poligono lis ) {
   ListaPoligoni punt;
   if(lista==NULL) { punt = (ListaPoligoni)malloc( sizeof(Pol) );
                     punt->next=NULL; punt->lisP=lis; return  punt;
   }else{lista->next = InsInFondoPoligono(lista->next,lis); return lista;}
}


void VisualizzaPoligono(Poligono lista ){
    if (lista==NULL) printf(" ---| \n");
    else{printf(" (%.2f,%.2f) ---> ", lista->x, lista->y); VisualizzaPoligono( lista->next );}
}


void VisualizzaListaPoligoni(ListaPoligoni lista ) {
    if(lista==NULL) printf("\n");
    else{VisualizzaPoligono(lista->lisP); VisualizzaListaPoligoni(lista->next);}
}


float mediaListaPoligoni (ListaPoligoni lista_poligoni)
    {
    ListaPoligoni scorri=lista_poligoni;
    int num_poligoni=0;
    float somma=0;
        while(scorri!=NULL)
            {
                somma=somma+calcolaperimetro(scorri->lisP);
                num_poligoni++;
                scorri=scorri->next;
            }
    float media=somma/num_poligoni;
    return media;
    }
float calcolaperimetro_senzaunlato(Poligono lista_punti)
    {
        if(lista_punti==NULL || lista_punti->next==NULL)
            return 0.0;
    Poligono punto_a=lista_punti;
    Poligono punto_b=lista_punti->next;
    float dist=distanza(punto_a, punto_b);
    return calcolaperimetro_senzaunlato(lista_punti->next)+dist;
    }

float distanza(Poligono punto_a, Poligono punto_b)
    {
    return sqrtf(((punto_a->x-punto_b->x)*(punto_a->x-punto_b->x))+((punto_a->y-punto_b->y)*(punto_a->y-punto_b->y)));
    }


float calcolaperimetro(Poligono lista_punti)
    {
    
    if (lista_punti == NULL || lista_punti->next == NULL)
            return 0.0f; // perimetro nullo per 0 o 1 punto
    
    Poligono alfa=lista_punti;
    Poligono temp=lista_punti;
    while(temp->next!=NULL)
        {
            temp=temp->next;
        }
    Poligono omega=temp;
    float ultimolato=distanza(alfa, omega);
    return calcolaperimetro_senzaunlato(lista_punti)+ultimolato;
    }


ListaPoligoni rimuoviPoligoniCorti(ListaPoligoni head)
    {
    float media=mediaListaPoligoni(head);
    if (head == NULL) return NULL;
    ListaPoligoni scorrilista=head;
    ListaPoligoni scorrilista_prec=NULL;
    while(scorrilista!=NULL)
        {
            
            ListaPoligoni scorrilista_succ = scorrilista->next;
            if(calcolaperimetro(scorrilista->lisP)<media)
                {
                    if(scorrilista==head)
                        {
                            head=scorrilista_succ;
                        }
                    else
                        {
                            scorrilista_prec->next=scorrilista_succ;
                        }
                    free(scorrilista->lisP);
                        free(scorrilista);
                        scorrilista = scorrilista_succ;
                        
                }
            else {
                scorrilista_prec=scorrilista;
                scorrilista=scorrilista_succ;
            }
            
        }
    return head;
    }
