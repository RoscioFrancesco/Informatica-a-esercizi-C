//
//  main.c
//  giorno -7 tde 3 alberi
//
//  Created by Francesco Roscio Ricon on 20/01/26.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct ELs {
    char info[20];
    struct ELs * prox;
} ElemListaStringhe;


typedef ElemListaStringhe * ListaStringhe;


typedef struct ELc {
    char c;
    int n;
    struct ELc * prox;
} ElemListaCaratteri;


typedef ElemListaCaratteri * ListaCaratteri;




ListaStringhe InsInFondoStringa(ListaStringhe lista,char elem[] );
void VisualizzaListaStringhe(ListaStringhe lista );
void VisualizzaListaCaratteri(ListaCaratteri lista );
ListaStringhe costruisci();
int contacarattere(char stringa[], char lettera);
ListaCaratteri funzione(ListaCaratteri head, ListaStringhe parole);
ListaCaratteri ripulisci(ListaCaratteri head);
ListaCaratteri inizializzalista();

int main(){
    ListaStringhe lis;
    ListaCaratteri ris=NULL;
    lis=costruisci();
    VisualizzaListaStringhe(lis);


    ListaCaratteri lista_mia=inizializzalista();
    VisualizzaListaCaratteri(lista_mia);
    lista_mia=funzione(lista_mia, lis);
    
    printf("Lista risultato\n");
    VisualizzaListaCaratteri(lista_mia);
    printf("finale:\n");
    lista_mia=ripulisci(lista_mia);
    VisualizzaListaCaratteri(lista_mia);
    return 0;
}


//
// TODO: SVILUPPARE QUI LE FUNZIONI RICHIESTE
//




ListaStringhe costruisci(){
    ListaStringhe lis=NULL;
    lis=InsInFondoStringa(lis,"casa");lis=InsInFondoStringa(lis,"sale");lis=InsInFondoStringa(lis,"postino");
    lis=InsInFondoStringa(lis,"mamma");lis=InsInFondoStringa(lis,"meta");lis=InsInFondoStringa(lis,"sasso");
    lis=InsInFondoStringa(lis,"osteria");lis=InsInFondoStringa(lis,"salvia");lis=InsInFondoStringa(lis,"notare");
    lis=InsInFondoStringa(lis,"zucchero");
    
    return lis;
}


ListaStringhe InsInFondoStringa(ListaStringhe lista,char elem[]) {
    ListaStringhe punt;
    if(lista==NULL) { punt = malloc( sizeof(ElemListaStringhe) );
                     punt->prox = NULL; strcpy(punt->info,elem); return  punt;
    }else{lista->prox = InsInFondoStringa(lista->prox,elem); return lista;}
}


void VisualizzaListaStringhe(ListaStringhe lista) {
    if (lista==NULL) printf(" ---| \n");
    else{printf(" %s ---> ", lista->info); VisualizzaListaStringhe( lista->prox );}
}


void VisualizzaListaCaratteri(ListaCaratteri lista) {
    if (lista==NULL) printf(" ---| \n");
    else{printf(" (%c,%d) ---> ", lista->c, lista->n); VisualizzaListaCaratteri( lista->prox );}
}

ListaCaratteri inizializzalista()
    {
    char lettera='a';
    ListaCaratteri head=(ListaCaratteri)malloc(sizeof(ElemListaCaratteri));
    head->prox=NULL;
    head->c='a';
    ListaCaratteri puntatore=head;
    int i=0;
    for(i=1; i<26; i++)
        {
            ListaCaratteri new=(ListaCaratteri)malloc(sizeof(ElemListaCaratteri));
            new->c=lettera+i;
            new->n=0;
            new->prox=NULL;
            if(head->prox==NULL)
                {
                    head->prox=new;
                }
            else {
                puntatore->prox=new;
            }
            puntatore=new;
        }
    return head;
}

ListaCaratteri funzione(ListaCaratteri head, ListaStringhe parole)
    {
    ListaCaratteri scorrilettere=head;
    ListaStringhe scorri_parole=parole;
    
    while(scorrilettere!=NULL)
    {
        int contalettera=0;
        scorri_parole=parole;
        while(scorri_parole!=NULL)
        {
            int num_lettera_in_parola=contacarattere(scorri_parole->info, scorrilettere->c);
            contalettera=contalettera+num_lettera_in_parola;
            scorri_parole=scorri_parole->prox;
        }
        scorrilettere->n=contalettera;
        scorrilettere=scorrilettere->prox;
    }
    return head;
    }

int contacarattere(char stringa[], char lettera)
    {
    int i=0;
    int contatore=0;
    while(stringa[i]!='\0')
        {
            if(stringa[i]==lettera)
                contatore++;
            i++;
        }
    return contatore;
    }

ListaCaratteri ripulisci(ListaCaratteri head)
    {
    ListaCaratteri scorri_lettere=head;
    ListaCaratteri prev=NULL;
    while(scorri_lettere!=NULL)
        {
            ListaCaratteri succ=scorri_lettere->prox;
            if(scorri_lettere->n==0) // in questo caso voglio eliminare scorrilettere
                {
                    if(prev==NULL)
                        {
                            ListaCaratteri temp=head;
                            head=scorri_lettere->prox;
                            scorri_lettere=scorri_lettere->prox;
                            free(temp);
                        }
                    else
                        {
                            prev->prox=succ;
                            free(scorri_lettere);
                            scorri_lettere=succ;
                        }
                }
            else
                {
                    prev=scorri_lettere;
                    scorri_lettere=scorri_lettere->prox;
                }
        }
    return head;
    }
