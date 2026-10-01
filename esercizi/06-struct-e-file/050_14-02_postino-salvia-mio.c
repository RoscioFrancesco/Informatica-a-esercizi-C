//
//  main.c
//  postino salvia mio
//
//  Created by Francesco Roscio Ricon on 14/02/26.
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

void f(Lista *l);
Lista eliminaK(Lista head, int k);
int blocco(Lista head);
int main(){
    Lista lis;
    lis=costruisci();
    VisualizzaListaStringhe(lis);

    f(&lis);
    printf("Lista dopo pulizia\n");
    VisualizzaListaStringhe(lis);


    return 0;
}


Lista costruisci(){
    Lista lis=NULL;
    lis=InsInFondoStringa(lis,"casa");lis=InsInFondoStringa(lis,"sale");lis=InsInFondoStringa(lis,"leura");
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


int sonobelli(char parola1[], char parola2[]) // devo eliminare i belli
    {
    int len1=strlen(parola1);
    int len2=strlen(parola2);
    if(parola1[len1-1]==parola2[1] && parola1[len1-2]==parola2[0])
        return 1;
    return 0;
    }
int blocco(Lista head)
    {
        if(head==NULL || head->prox==NULL)
            return 0;
        int count=0;
        while(head!=NULL && head->prox!=NULL)
            {
                if(sonobelli(head->info, head->prox->info)==0)
                    break;
                count++;
                head=head->prox;
            }
    printf("\ncount:%d", count);
        return count;
    }
Lista eliminaK(Lista head, int k)
    {
        if(head==NULL)
            return head;
    for(int i=0; i<=k && head!=NULL; i++)
        {
            Lista temp=head->prox;
            free(head);
            head=temp;
        }
    return head;
    }
void f(Lista *l)
    {
        if(*l==NULL)
            return;
        Lista *pp=l;
        while(*pp!=NULL)
            {
                int len=0;
                len=blocco(*pp);
                if(len>0)
                    {
                        *pp=eliminaK(*pp, len);
                        pp=l;
                    }
                else
                    {
                        pp=&(*pp)->prox;
                    }
            }
    }
