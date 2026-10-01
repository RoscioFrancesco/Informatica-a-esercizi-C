//  Created by Francesco Roscio Ricon on 17/01/26.

//  Ad esempio, la lista:
//  casa -> sale -> postino -> rame -> meta -> sasso -> osteria -> salvia -> notare -> renna
//  diventa
//  postino -> sasso -> osteria -> salvia

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
int check (char stringa1[], char stringa2[]);
Lista Elimina_coppia(Lista head, Lista curr, Lista currpiu, Lista currpiupiu, Lista currmeno);
Lista funzione(Lista head, Lista curr, Lista currmeno);


int main(){
    Lista lis;
    lis=costruisci();
    VisualizzaListaStringhe(lis);

    
    printf("Lista dopo pulizia\n");
    lis=funzione(lis, lis, NULL);
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

int check (char stringa1[], char stringa2[])
{
    int len1=strlen(stringa1);
    int len2=strlen(stringa2);
    if(stringa1[len1-1]==stringa2[1]&& stringa1[len1-2]==stringa2[0])
        return 1;
    return 0;
}


Lista funzione(Lista head, Lista curr, Lista currmeno)
    {
        if(curr==NULL || curr->prox==NULL)
            return head;
    Lista curr_piu;
    curr_piu=curr->prox;
    Lista curr_piupiu=curr_piu->prox;
    if(check(curr->info, curr_piu->info))
        {
            head=Elimina_coppia(head, curr, curr_piu, curr_piupiu, currmeno);
            if(currmeno==NULL)
                return funzione(head, head, NULL);
            else
                return funzione(head, currmeno->prox, currmeno);
        }

    return funzione(head, curr->prox, curr);
    }


Lista Elimina_coppia(Lista head, Lista curr, Lista currpiu, Lista currpiupiu, Lista currmeno)
    {
        if(head==curr)
            {
                head=currpiupiu;
                free(curr);
                free(currpiu);
                currmeno=NULL;
                return head;
            }
    currmeno->prox=currpiupiu;
    free(curr);
    free(currpiu);
    return head;
    }




