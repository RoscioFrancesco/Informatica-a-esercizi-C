//
//  main.c
//  tde alberi 2024 gen
//
//  Created by Francesco Roscio Ricon on 30/11/25.
//
// Riferimento: Informatica A (061202), TDE gennaio 2024, a.a. 2023/24: https://forms.office.com/e/REVRfR3pbc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct El {
    char nome[100];
    int punteggio;
    struct El *left, *right;
} Nodo;

typedef struct Es {
    char nome[100];
    struct Es *info;
    int cammino
} Nodo_lista;

typedef Nodo * Tree;
typedef Nodo_lista * Lista;

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

int max(int a, int b);
int condiz2(Tree t);
int condiz1(Tree t);
void salvalunghezzacammini(Tree t, int livello, int array[], int *i);

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
    if(condiz1(t)&&condiz2(t))
        {
            int array[100];
            int i=0;
            int livello=0;
            salvalunghezzacammini(t, livello, array, &i);
            int temp=i;
            int flag=0;
            for(i=0; i<temp; i++)
                {
                    if(array[i]!=array[0])
                        flag=1;
                }
            if(flag==0)
                return 1;
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


//- ogni nodo è una foglia o ha due figli;
int condiz1(Tree t)
    {
        if(t==NULL)
            return 1;
        if(t->left==NULL && t->right==NULL)
            return 1;
        if(t->left!=NULL && t->right!=NULL)
            return condiz1(t->left)&&condiz1(t->right);
    return 0;
    }
//- ogni nodo genitore ha lo stesso nome del nodo figlio con punteggio più alto.

int condiz2(Tree t) // chiaro
{
    if(t == NULL)
        return 1; // albero vuoto ok

    if(t->left == NULL && t->right == NULL)
        return 1; // foglia ok

    // nodo con due figli
    Tree figlio_max;
    if(t->left->punteggio >= t->right->punteggio)
        figlio_max = t->left;
    else
        figlio_max = t->right;

    // il nome del genitore deve corrispondere al figlio con punteggio maggiore
    if(strcmp(t->nome, figlio_max->nome) != 0)
        return 0;

    // ricorsione su entrambi i figli
    return condiz2(t->left) && condiz2(t->right);
}
//- tutti i cammini hanno la stessa lunghezza;
// prima calcolo la profondità e poi verifico che qs profondità coincida con la lunghezza di ogni cammino;
int profondità (Tree t)
    {
        if(t==NULL)
            return 0;
    return max(profondità(t->left), profondità(t->right))+1;
    } // conosco il livello massimo a cui devo arrivare in ogni cammino
int max(int a, int b)
    {
        if(a>b)
            return a;
        else
            return b;
    }
void salvalunghezzacammini(Tree t, int livello, int array[], int *i)
    {
        if(t==NULL)
            return;
    if(t->left==NULL && t->right==NULL)
        {
            array[*i]=livello;
            (*i)++;
            return;
        }
    livello++;
    salvalunghezzacammini(t->left, livello, array, i);
    salvalunghezzacammini(t->right, livello, array, i);
    }
// lasciato in sospeso
