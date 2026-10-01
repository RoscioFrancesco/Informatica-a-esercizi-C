//
//  main.c
//  tde altro
//
//  Created by Francesco Roscio Ricon on 26/01/26.
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
ListaStringhe IFS(ListaStringhe lista,char elem[] );
void VisualizzaListaStringhe(ListaStringhe lista );
void VisualizzaListaCaratteri(ListaCaratteri lista );
ListaStringhe costruisci();
ListaCaratteri iniz();
ListaCaratteri f(ListaStringhe start);
ListaCaratteri trova(ListaCaratteri head, char l);
ListaCaratteri parola(ListaCaratteri head, char parola[]);
ListaCaratteri pulisci(ListaCaratteri head);
ListaCaratteri funz(ListaStringhe ls);
int main(){
    ListaStringhe lis;
    ListaCaratteri ris=NULL;
    lis=costruisci();
    VisualizzaListaStringhe(lis);
    printf("Lista risultato\n");
    ris=funz(lis);
    VisualizzaListaCaratteri(ris);
}
ListaStringhe costruisci(){
    ListaStringhe lis=NULL;
    lis=IFS(lis,"casa");lis=IFS(lis,"sale");lis=IFS(lis,"postino");
    lis=IFS(lis,"mamma");lis=IFS(lis,"meta");lis=IFS(lis,"sasso");
    lis=IFS(lis,"osteria");lis=IFS(lis,"salvia");lis=IFS(lis,"notare");
    lis=IFS(lis,"zucchero");
    return lis;
}
ListaStringhe IFS(ListaStringhe lista,char elem[]) {
    ListaStringhe punt;
    if(lista==NULL) { punt = malloc( sizeof(ElemListaStringhe) );
                     punt->prox = NULL; strcpy(punt->info,elem); return  punt;
    }else{lista->prox = IFS(lista->prox,elem); return lista;}
}
void VisualizzaListaStringhe(ListaStringhe lista) {
    if (lista==NULL)printf(" ---| \n");
    else{printf(" %s ---> ",lista->info);VisualizzaListaStringhe(lista->prox);}
}
void VisualizzaListaCaratteri(ListaCaratteri lista) {
    if (lista==NULL)printf(" ---| \n");
    else{printf(" (%c,%d) ---> ",lista->c,lista->n);VisualizzaListaCaratteri(lista->prox);}
}
ListaCaratteri iniz()
    {
    int i=0;
    ListaCaratteri head=NULL;
    for(i=0; i<26; i++)
    {
        ListaCaratteri new=(ListaCaratteri)malloc(sizeof(ElemListaCaratteri));
        new->n=0;
        new->prox=NULL;
        new->c='a'+i;
        ListaCaratteri s=head;
        if(head==NULL)
            head=new;
        else
            {
                while(s->prox!=NULL)
                    s=s->prox;
                s->prox=new;
            }
        }
    return head;
    }
ListaCaratteri trova(ListaCaratteri head, char l)
    {
        if(head==NULL)
            return head;
    ListaCaratteri s=head;
    while (s!=NULL) {
        if(s->c==l)
            (s->n)++;
        s=s->prox;
        }
    return head;
    }
ListaCaratteri parola(ListaCaratteri head, char parola[])
    {
    int i=0;
    while(parola[i]!='\0')
        {
            head=trova(head, parola[i]);
            i++;
        }
    return head;
    }
ListaCaratteri f(ListaStringhe start)
    {
        if(start==NULL)
            return NULL;
    ListaStringhe sS=start;
    ListaCaratteri head=iniz();
    while (sS!=NULL) {
        head=parola(head, sS->info);
        sS=sS->prox;
        }
    return head;
    }
ListaCaratteri pulisci(ListaCaratteri head)
    {
    ListaCaratteri sc=head;
    ListaCaratteri prec=NULL;
    while (sc!=NULL) {
        ListaCaratteri succ=sc->prox;
        if(sc->n==0)
            {
                if(prec==NULL)
                {
                    head=succ;
                    free(sc);
                    sc=head;
                }
                else
                    {
                    prec->prox=succ;
                    free(sc);
                    sc=succ;
                    }
            }
    else
        {
            prec=sc;
            sc=succ;
        }
    }
    return head;
}
ListaCaratteri funz(ListaStringhe ls)
{
ListaCaratteri head=f(ls);
head=pulisci(head);
return head;
}


