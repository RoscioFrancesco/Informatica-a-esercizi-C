//
//  main.c
//  tde 1 alberi -5
//
//  Created by Francesco Roscio Ricon on 14/02/26.
// Riferimento: Informatica A (061202), TDE gennaio 2024, a.a. 2023/24: https://forms.office.com/e/REVRfR3pbc
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
int controllaTorneo(Tree t);


// TODO PROTOTIPI

int checkprofondità(int livello, int check, Tree t);
int check3(Tree albero);
int chech2(Tree t);
int depth(Tree t);
int max(int a, int b);
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


//funzione da modificare e funzioni da aggiungere
int controllaTorneo(Tree t){
    int d=depth(t);
    printf("check 1:%d\n", checkprofondità(0, d, t));
    printf("check 2:%d\n", chech2(t));
    if(checkprofondità(0, d, t)&&chech2(t))
    {
        printf("check 3:%d\n", check3(t));
        return check3(t);
    }
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


int depth(Tree t)
    {
        if(t==NULL)
            return 0;
    int sx=depth(t->left);
    int dx=depth(t->right);
    return max(sx, dx)+1;
    }
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int checkprofondità(int livello, int check, Tree t)
    {
        if(t==NULL)
            return 0;
    livello++;
        if(t->left==NULL && t->right==NULL)
            {
                if(livello!=check)
                    return 0;
                return 1;
            }
    return checkprofondità(livello, check, t->left) && checkprofondità(livello, check, t->right);
    }

int chech2(Tree t)
    {
        if(t==NULL)
            return 1;
        if(t->left==NULL && t->right==NULL)
            return 1;
        if(t->left==NULL || t->right==NULL)
            return 0;
    return chech2(t->left)&&chech2(t->right);
    }
//- ogni nodo genitore ha lo stesso nome del nodo figlio con punteggio più alto.

int check3(Tree albero)
    {
        if(albero==NULL)
            return 1;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
    int massimo=max(albero->left->punteggio, albero->right->punteggio);
    if(albero->left->punteggio==massimo)
        {
            if(strcmp(albero->left->nome, albero->nome)!=0)
                return 0;
        }
    if(albero->right->punteggio==massimo)
        {
            if(strcmp(albero->right->nome, albero->nome)!=0)
                return 0;
        }
    return check3(albero->left)&&check3(albero->right);
    }
