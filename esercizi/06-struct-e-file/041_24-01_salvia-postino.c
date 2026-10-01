//  Created by Francesco Roscio Ricon on 24/01/26.

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
int sonobelli(char stringa1[], char stringa2[]);
void cancellacoppia(Lista nodo1, Lista nodo2);
Lista funzione (Lista lista1);
Lista costruisci();
//
// TODO: PROTOTIPI DELLE FUNZIONI RICHIESTE
//

int main(){
    Lista lis;
    lis=costruisci();
    VisualizzaListaStringhe(lis);


    //TODO: invocazione funzione
    lis=funzione(lis);
    printf("Lista dopo pulizia\n");
    VisualizzaListaStringhe(lis);


    return 0;
}


//
// TODO: SVILUPPARE QUI LE FUNZIONI RICHIESTE
//




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

Lista funzione (Lista lista1)
    {
    if(lista1==NULL || lista1->prox==NULL)
        return lista1;

    int len1=strlen(lista1->info);
    int len2=strlen(lista1->prox->info);
        if(sonobelli(lista1->info, lista1->prox->info))
        {
            Lista temp=lista1;
            Lista temp2 = lista1 -> prox;
            Lista l = temp2 -> prox;
            cancellacoppia(temp, temp->prox);
            return funzione(l);
        }
        else
        {
            lista1->prox = funzione(lista1->prox);
            return lista1;
        }
            
    }
int sonobelli(char stringa1[], char stringa2[])
    {
    int len1=strlen(stringa1);
    int len2=strlen(stringa2);
        if(stringa1[len1-1]==stringa2[1] && stringa1[len1-2]==stringa2[0] && len1>3 && len2>3)
            return 1;
    return 0;
    }
void cancellacoppia(Lista nodo1, Lista nodo2)
    {
    nodo2->prox=NULL;
    free(nodo2);
    nodo1->prox=NULL;
    free(nodo1);
    }
