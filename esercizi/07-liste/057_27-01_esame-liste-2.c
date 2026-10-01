//
//  main.c
//  ESAME liste 2
//
//  Created by Francesco Roscio Ricon on 27/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define N 4


typedef struct Nodo {
    char parola[N+1];
    struct Nodo *next;
} Nodo;


typedef Nodo * Lista;


void stampaLista(Lista head);
Lista nn(const char *s);
void a(Nodo **head, const char *s);
Lista crea1();
Lista crea2();
Lista crea3();
int compatibili( char *a,  char *b) {
    int diff = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] != b[i])
         diff++;
        if (diff > 1)
            return 0;
    }
    return diff == 1;
}
Nodo *nuovoNodo(const char *s) {
    Nodo *p = (Nodo *)malloc(sizeof(Nodo));
    if (!p)
        return NULL;
    strncpy(p->parola, s, N);
    p->parola[N] = '\0';
    p->next = NULL;
    return p;
}
void append(Nodo **head, const char *s) {
    Nodo *p = nuovoNodo(s);
    if (*head == NULL) {
        *head = p;
        return;
    }
    Nodo *cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = p;
}
void liberaLista(Nodo *head) {
    while (head) {
        Nodo *t = head;
        head = head->next;
        free(t);
    }
}
void stampaLista(Lista h);
Nodo *correggiBersaglio(Nodo *head);
int controllaBersaglio(Nodo *head);
Nodo *trovato(Nodo *head);
int main(void) {
    Lista L1=crea1();
    Lista L2=crea2();
    Lista L3=crea3();
    
    printf("L1:%d\n",controllaBersaglio(L1));
    printf("L2:%d\n",controllaBersaglio(L2));
    printf("L3:%d\n",controllaBersaglio(L3));
    
    stampaLista(L1);
    stampaLista(L2);
    stampaLista(L3);
    
    L1=correggiBersaglio(L1);
    L2=correggiBersaglio(L2);
    L3=correggiBersaglio(L3);
    
    stampaLista(L1);
    stampaLista(L2);
    stampaLista(L3);
}
Lista nn(const char *s){Lista p = (Nodo *)malloc(sizeof(Nodo));if(!p)return NULL;strncpy(p->parola,s,N);p->parola[N]='\0';p->next=NULL;return p;}
void a(Nodo **h,const char *s){Nodo *p=nn(s);if(*h==NULL){*h=p;return;}Nodo *c=*h;while(c->next)c=c->next;c->next=p;}
void stampaLista(Lista h){Lista c;for(c=h;c!=NULL;c=c->next){printf("%s",c->parola);if(c->next)printf("->");}printf("\n");}


Lista crea1(){Nodo *L=NULL;a(&L,"CANE");a(&L,"PANE");a(&L,"CASO");a(&L,"NASO");a(&L,"PALE");a(&L,"MALE");return L;}
Lista crea2(){Nodo *L=NULL;a(&L,"CANE");a(&L,"PANE");a(&L,"CASO");a(&L,"MARE");a(&L,"LAGO");return L;}
Lista crea3(){Nodo *L=NULL;a(&L,"CANE");a(&L,"PANE");a(&L,"LANE");return L;}

Nodo *correggiBersaglio(Nodo *head)
{
    Nodo *scorri=head;
    if(trovato(scorri)!=NULL && controllaBersaglio(scorri)==0)
    {
        Nodo *prec=trovato(scorri);// da qua in poi voglio eliminare
        Nodo *cerca=prec->next;
        int i=0;
        while(cerca!=NULL && compatibili(prec->parola, cerca->parola)==0) // cerca si ferma quando trova il prima falore valido e mentre scorro faccio la free
        {
            Nodo *temp=cerca;
            i++;
            cerca=cerca->next;
            free(temp);
        }
        prec->next=cerca;
    }
    
    return head;
}
Nodo *trovato(Nodo *head)
    {
    Nodo *cur = head;
    Nodo *prec=NULL;
    if(controllaBersaglio(head)==0)
    {
        while(cur->next!=NULL)
        {
            if(compatibili(cur->parola,cur->next->parola)==0 && prec!=NULL)
            {
                return cur;
            }
            prec=cur;
            cur=cur->next;
        }
    }
    return NULL;
}
int controllaBersaglio(Nodo *head) // questa funzione mi ridà un puntatore che punta alla parola da cui voglio iniziare a cancellare
    {
    Nodo *cur = head;
    while(cur->next!=NULL)
        {
            Nodo *succ=cur->next;
            if(compatibili(cur->parola, succ->parola)==0)
                return 0;
            cur=cur->next;
        }
    return 1;
    }
