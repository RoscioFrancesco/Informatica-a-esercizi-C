//
//  main.c
//  postino->salvia con while
//
//  Created by Francesco Roscio Ricon on 25/01/26.
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

Lista funzione(Lista head);
void distruggicoppia(Lista a, Lista b);
Lista funzione_ric(Lista head);
int main(){
    Lista lis;
    lis=costruisci();
    VisualizzaListaStringhe(lis);


    lis=funzione_ric(lis);
    
    
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

int sonobelli(char parola1[], char parola2[])
    {
    int len1=strlen(parola1);
    int len2=strlen(parola2);
    if(parola1[len1-2]==parola2[0] && parola1[len1-1]==parola2[1])
        return 1;
    return 0;
    }
void distruggicoppia(Lista a, Lista b)
    {
    a->prox=NULL;
    free(a);
    b->prox=NULL;
    free(b);
    }
Lista funzione(Lista head)
    {
        if(head==NULL || head->prox==NULL)
            return head;
        Lista prec=NULL;
        Lista scorrilista=head;
        while (scorrilista->prox!=NULL && scorrilista!=NULL)
            {
                Lista b=scorrilista->prox;
                if(sonobelli(scorrilista->info, b->info))
                    {
                        if(prec==NULL)
                            {
                                head=b->prox;
                                distruggicoppia(scorrilista, b);
                                scorrilista=head;
                                prec=NULL;
                            }
                        else
                            {
                                if(b->prox==NULL)
                                    {
                                        prec->prox=NULL;
                                        distruggicoppia(scorrilista, b);
                                        return head;
                                    }
                                else
                                    {
                                        prec->prox=b->prox;
                                        distruggicoppia(scorrilista, b);
                                        scorrilista=prec->prox;
                                    }
                            }
                    }
                else
                    {
                        prec=scorrilista;
                        scorrilista=b;
                    }
                
            }
    return head;
    }
    
Lista funzione_ric(Lista head)
    {
        if(head==NULL || head->prox==NULL)
            {
                return head;
            }
        if(sonobelli(head->info, head->prox->info))
            {
                Lista temp1=head;
                Lista temp2=head->prox;
                Lista l=temp2->prox;
                distruggicoppia(temp1, temp2);
                return funzione_ric(l);
            }
    head->prox=funzione(head->prox);
    return head;
    }
