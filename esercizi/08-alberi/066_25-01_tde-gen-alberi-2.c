//
//  main.c
//  tde gen alberi 2
//
//  Created by Francesco Roscio Ricon on 25/01/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct El {
    char nome[100];
    int punteggio;
    struct El *left, *right;
} Nodo;


typedef Nodo * Tree;

int max(int a, int b);
Tree nN(char nome[],int punteggio);
int altezza(Tree t);
void stampaSpazi(int n);
void stampaLivello(Tree t,int liv,int cur,int spaz);
void stampaAlbero(Tree t);
Tree costruisci1();
Tree costruisci2();
Tree costruisci3();
Tree costruisci4();
Tree costruisci5();
int controllaTorneo(Tree albero);
int verificaC(Tree albero);
int verificaA(Tree albero);
int verificab(Tree albero);
int lenmax(Tree albero);
int max(int a, int b);
int min(Tree albero);

int main(){
    Tree t1=costruisci1(),t2=costruisci2(),t3=costruisci3(),t4=costruisci4(),t5=costruisci5();
    stampaAlbero(t1);printf("\n");
    stampaAlbero(t2);printf("\n");
    stampaAlbero(t3);printf("\n");
    stampaAlbero(t4);printf("\n");
    stampaAlbero(t5);printf("\n");


    if(controllaTorneo(t1))
        printf("t1: OK\n");
    else printf("t1: NON OK\n");
    if(controllaTorneo(t2))
        printf("t2: OK\n");
    else printf("t2: NON OK\n");
    if(controllaTorneo(t3))
        printf("t3: OK\n");
    else printf("t3: NON OK\n");
    if(controllaTorneo(t4))
        printf("t4: OK\n");
    else printf("t4: NON OK\n");
    if(controllaTorneo(t5))
        printf("t5: OK\n");
    else printf("t5: NON OK\n");


    return 0;
}





Tree nN(char nome[],int punteggio){
    Tree nodo=(Tree)malloc(sizeof(Nodo));
    nodo->punteggio=punteggio;strcpy(nodo->nome,nome);
    nodo->left=NULL;nodo->right=NULL;
    return nodo;
}
int altezza(Tree t){int l,r;if(t==NULL)return 0;else{l=altezza(t->left);r=altezza(t->right);if(l>r)return(l+1);else return(r+1);}}
void stampaSpazi(int n){int i;for(i=0;i<n;i++){printf(" ");}}
void stampaLivello(Tree t,int liv,int cur,int spazi){
    if(t==NULL){if(liv>=cur)stampaSpazi(spazi);return;}
    if(liv==cur){stampaSpazi(spazi/4-4);printf("%s(%d)",t->nome,t->punteggio);stampaSpazi(spazi/4-4);}else if(liv>cur){stampaLivello(t->left,liv,cur+1,spazi/2);stampaLivello(t->right,liv,cur+1,spazi/2);}
}
void stampaAlbero(Tree t){int i,h=altezza(t);for(i=1;i<=h;i++){stampaLivello(t,i,1,100);printf("\n");}}
Tree costruisci1(){Tree r=nN("GG",0);r->left=nN("CC",50);r->right=nN("GG",80);r->left->left=nN("CC",100);r->left->right=nN("AA",90);r->right->left=nN("GG",30);r->right->right=nN("BB",20);return r;}
Tree costruisci2(){Tree r=nN("GG",0);r->left=nN("CC",50);r->right=nN("GG",80);r->left->left=nN("CC",100);r->left->right=nN("AA",90);r->right->left=nN("GG",30);r->right->right = nN("BB",50);return r;}
Tree costruisci3(){Tree r=nN("GG",0);r->left=nN("CC",50);r->right=nN("GG",80);r->left->left=nN("CC",100);r->right->left=nN("GG",30);r->right->right=nN("BB",20);return r;}
Tree costruisci4(){Tree r=nN("GG",0);r->left=nN("CC", 50);r->right=nN("GG",80);r->left->left=nN("CC",100);r->left->right=nN("AA",90);r->right->left=nN("GG",30);r->right->right=nN("BB",20);r->right->right->right=nN("BB",50);r->right->right->left=nN("DD",10);return r;}
Tree costruisci5(){Tree r=nN("GG",0);r->left=nN("CC",50);r->right=nN("GG",80);r->left->left=nN("CC",100);r->left->right=nN("AA",90);r->right->left=nN("HH",30);r->right->right=nN("BB",20);return r;}


int lenmax(Tree albero)
    {
        if(albero==NULL)
            return 0;
    int sx=lenmax(albero->right);
    int dx=lenmax(albero->left);
    return max(sx,dx)+1;
        
    }
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int min(Tree albero)
    {
        if(albero==NULL)
            return 0;
        if (albero->left == NULL)
            return 1 + min(albero->right);
        if (albero->right == NULL)
            return 1 + min(albero->left);
        int dx=min(albero->right)+1;
        int sx=min(albero->left)+1;
        if(dx<sx)
            return dx;
        else
            return sx;
    }

int verificab(Tree albero)
    {
        if(albero==NULL)
            {
                return 1;
            }
        if(albero->left==NULL && albero->right!=NULL)
            return 0;
        if(albero->left!=NULL && albero->right==NULL)
            return 0;
    return verificab(albero->left)&&verificab(albero->right);
    }
int verificaA(Tree albero)
    {
        if(min(albero)==lenmax(albero))
            return 1;
    return 0;
    }

int verificaC(Tree albero)
    {
        if(albero->left==NULL && albero->right==NULL)
            return 1;
        Tree temp;
        if(albero->left->punteggio==max(albero->left->punteggio, albero->right->punteggio))
            temp=albero->left;
        else
            temp=albero->right;
        if(strcmp(albero->nome, temp->nome)!=0)
            return 0;
    return verificaC(albero->left)&&verificaC(albero->right);
            
    }

int controllaTorneo(Tree albero)
    {
        if(verificaA(albero)&&verificab(albero))
            {
                if(verificaC(albero))
                    return 1;
                return 0;
            }
    return 0;
    }
