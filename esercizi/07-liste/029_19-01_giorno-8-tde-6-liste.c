//
//  main.c
//  giorno -8 tde 6 liste
//
//  Created by Francesco Roscio Ricon on 19/01/26.
//
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
int  stampa(ListaPoligoni lista);
ListaPoligoni  funzione(ListaPoligoni lista, int max);




int main() {
    // Creazione di una lista di poligoni di esempio
    ListaPoligoni lista=costruisci();


    printf("Lista iniziale:\n");
    VisualizzaListaPoligoni(lista);


    int max=stampa(lista);
    lista=funzione(lista, max);

    printf("Lista dopo l'eliminazione:\n");
    VisualizzaListaPoligoni(lista);
    
     max=stampa(lista);
    

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

float distanza(Poligono a, Poligono b)
    {
    float distanza=sqrtf((a->x-b->x)*(a->x-b->x)+(a->y-b->y)*(a->y-b->y));
        return distanza;
    }

int  stampa(ListaPoligoni lista)
{
    if(lista==NULL)
        return 0;
    int max=0;
    ListaPoligoni scorri=lista;
    while(scorri!=NULL)
    {
        Poligono scorripunti=scorri->lisP;
        
        int somma_diagonali=0;
        int contatore=0;
        float media;
        while(scorripunti!=NULL)
        {
            Poligono scorripunti_succ=scorripunti->next;
            while(scorripunti_succ!=NULL)
            {
                somma_diagonali=somma_diagonali+distanza(scorripunti, scorripunti_succ);
                contatore++;
                scorripunti_succ=scorripunti_succ->next;
            }
            scorripunti=scorripunti->next;
        }
        media=somma_diagonali/contatore;
        if(media>max)
        {
            max=media;
        }
        printf("%f\n", media);
        scorri=scorri->next;
    }
    return max;
}

ListaPoligoni  funzione(ListaPoligoni lista, int max)
{
    ListaPoligoni scorrilista_new=lista;
    ListaPoligoni scorrilista_prec=NULL;
    while(scorrilista_new!=NULL)
    {
        ListaPoligoni scorrilista_succ=scorrilista_new->next;
        Poligono scorripunti=scorrilista_new->lisP;
        
        int somma_diagonali=0;
        int contatore=0;
        float media;
        while(scorripunti!=NULL)
        {
            Poligono scorripunti_succ=scorripunti->next;
            while(scorripunti_succ!=NULL)
            {
                somma_diagonali=somma_diagonali+distanza(scorripunti, scorripunti_succ);
                contatore++;
                scorripunti_succ=scorripunti_succ->next;
            }
            scorripunti=scorripunti->next;
        }
        media=somma_diagonali/contatore;
        ListaPoligoni succ=scorrilista_new->next;
        if (media==max)
        {
            
            if(scorrilista_prec==NULL)
            {
                lista=succ;
                free(scorrilista_new);
                return lista;
            }
            else
            {
                scorrilista_prec->next=scorrilista_succ;
                free(scorrilista_new);
                scorrilista_new=scorrilista_succ;
            }
        }
        else
        {
            scorrilista_prec=scorrilista_new;
            scorrilista_new=succ;
        }
    }
    return lista;
}
