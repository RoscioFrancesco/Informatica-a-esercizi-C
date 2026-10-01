//
//  main.c
//  casa-->postino ter
//
//  Created by Francesco Roscio Ricon on 24/01/26.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct EL {
    char info[100];
    struct EL * prox;
} ElemLista;


typedef ElemLista * Lista;




Lista InsInFondoStringa(Lista lista,char elem[] );
void VisualizzaListaStringhe(Lista lista );
Lista costruisci();
int sonobelli(char parola1[], char parola2[]);
void distruggi(Lista a, Lista b);
Lista funzione(Lista lista1);



int main(){
    Lista lis;
    lis=costruisci();
    VisualizzaListaStringhe(lis);


    lis=funzione(lis);
    
    
    printf("Lista dopo pulizia\n");
    VisualizzaListaStringhe(lis);


    return 0;
}


Lista costruisci(){
    Lista lis=NULL;
    lis=InsInFondoStringa(lis,"casa");lis=InsInFondoStringa(lis,"sale");lis=InsInFondoStringa(lis,"postino");
    lis=InsInFondoStringa(lis,"rame");lis=InsInFondoStringa(lis,"meta");lis=InsInFondoStringa(lis,"sasso");
    lis=InsInFondoStringa(lis,"osteria");lis=InsInFondoStringa(lis,"salvia");lis=InsInFondoStringa(lis,"notare");
    lis=InsInFondoStringa(lis,"renna");
    
    return lis;
}


Lista InsInFondoStringa(Lista lista,char elem[]) {
    Lista punt;
    if(lista==NULL) { punt = malloc( sizeof(ElemLista) );
                     punt->prox = NULL; strcpy(punt->info,elem); return  punt;
    }else{lista->prox = InsInFondoStringa(lista->prox,elem); return lista;}
}


void VisualizzaListaStringhe(Lista lista) {
    if (lista==NULL) printf(" ---| \n");
    else{printf(" %s ---> ", lista->info); VisualizzaListaStringhe( lista->prox );}
}


int sonobelli(char parola1[], char parola2[])
    {
    int len1=strlen(parola1);
    int len2=strlen(parola2);
    if(parola1[len1-1]==parola2[1] && parola1[len1-2]==parola2[0])
        return 1;
    return 0;
    }

Lista funzione(Lista lista1)
    {
        if(lista1==NULL || lista1->prox==NULL)
            return lista1;
        if(sonobelli(lista1->info, lista1->prox->info)) // caso base
            {
                Lista temp1=lista1;
                Lista temp2=temp1->prox;
                Lista l=temp2->prox;
                distruggi(temp1, temp2);
                return funzione(l);
            }
        else
            {
                lista1->prox=funzione(lista1->prox);
                return lista1;
            }
    
    }

void distruggi(Lista a, Lista b)
    {
    a->prox=NULL;
    free(a);
    b->prox=NULL;
    free(b);
    }




