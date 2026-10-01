//
//  main.c
//  tde 1 -1
//
//  Created by Francesco Roscio Ricon on 18/02/26.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct n{
    char codice[100];
    int punteggio;
    struct n * next;
} nodo;
typedef nodo * Lista;

Lista InsInFondo(Lista lista,char c[],int p);
void VisualizzaLista(Lista lista );
Lista costruisci();
Lista caux(Lista lista,int i);
Lista f(Lista head);

int main(){
    Lista lis,risultato;
    lis=costruisci();
    VisualizzaLista(lis);
    printf("\n\n");


    risultato=f(lis);
    VisualizzaLista(risultato);
    
    return 0;
}


//
// TODO: SVILUPPARE QUI LE FUNZIONI RICHIESTE
//






Lista costruisci(){ return caux(NULL,0);}
Lista caux(Lista lista,int i){
    int p[50]={57, 63, 70, 88, 91, 97, 57, 59, 66, 88, 94, 92, 77, 61, 68, 75, 85, 94, 68, 77, 63, 89, 85, 100, 57, 77, 59, 97, 68, 60, 87, 92, 94, 66, 61, 68, 75, 63, 89, 68, 75, 94, 57, 63, 75, 66, 92, 61, 77, 70};
    char c[50][20]={"c2", "c1", "c3", "c1", "c5", "c2", "c5", "c4", "c5", "c1", "c3", "c4", "c4", "c5", "c1", "c5", "c2", "c2", "c5", "c2", "c3", "c1", "c5", "c3", "c1", "c3", "c3", "c2", "c2", "c1", "c3", "c3", "c1", "c4", "c3", "c4", "c4", "c4", "c1", "c1", "c2", "c2", "c4", "c2", "c2", "c5", "c5", "c3", "c4", "c3"};
    if(i==50) return NULL;
    lista= (Lista)malloc( sizeof(nodo) );    lista->codice[0]=c[i][0]; lista->codice[1]=c[i][1]; lista->codice[2]=c[i][2]; lista->punteggio = p[i];    lista->next = caux(lista->next,i+1); return lista;
}


void VisualizzaLista(Lista lista ){
    if (lista==NULL) printf(" ---| \n");
    else{printf(" (%s,%i) ---> ", lista->codice, lista->punteggio); VisualizzaLista( lista->next );}
}
Lista trovata(Lista head, char codice[])
    {
    if(head==NULL)
        return NULL;
    while(head!=NULL)
        {
            if(strcmp(head->codice, codice)==0)
                {
                    return head;
                }
            head=head->next;
        }
    return head;
    }
Lista f(Lista head)
    {
    Lista new=NULL;
    while(head!=NULL)
        {
            Lista punt=trovata(new, head->codice);
            if(punt==NULL)
                {
                    new=InsInFondo(new, head->codice, head->punteggio);
                }
            else
                {
                    punt->punteggio=punt->punteggio+head->punteggio;
                }
            head=head->next;
        }
    return new;
    }
Lista InsInFondo(Lista lista,char c[],int p)
    {
        if(lista==NULL)
            {
                Lista new=(Lista)malloc(sizeof(*new));
                new->next=NULL;
                new->punteggio=p;
                strcpy(new->codice, c);
                return new;
            }
        lista->next=InsInFondo(lista->next, c, p);
        return lista;
    }
