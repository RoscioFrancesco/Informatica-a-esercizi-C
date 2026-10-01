//
//  main.c
//  giorno -9 tde3 alberi 
//
//  Created by Francesco Roscio Ricon on 18/01/26.
//  Riferimento: Informatica A (061202), TDE gennaio 2026, a.a. 2025/26: https://forms.cloud.microsoft/e/U1bBujvcBe


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct n {
        char val;
        struct n * left;
        struct n * right;
} nodo;
typedef nodo * albero;


albero createVal(char val);
albero creaAlbero1();albero creaAlbero2();albero creaAlbero3();
void print(albero t);
void stampa(albero T);
int f(albero t,char str[]);
int verifica(albero t, char stringa[]);
int f(albero t, char stringa[]);
int funzione(albero t, char stringa[], int contatore);

int main(){
    int ris=0;
    char str1[100]="acacia",str2[100]="sacca";
    albero T1,T2,T3;
    T1 = creaAlbero1(); T2 = creaAlbero2(); T3 = creaAlbero3();
    printf("\nT1: "); stampa(T1);
    printf("\nT2: "); stampa(T2);
    printf("\nT3: "); stampa(T3);
    printf("\n");


   //LA FUNZIONE DA SVILUPPARE VIENE USATA QUI




   printf("%d\n",f(T1,str1));
   printf("%d\n",f(T1,str2));
   printf("%d\n",f(T2,str1));
   printf("%d\n",f(T2,str2));
   printf("%d\n",f(T3,str1));
   printf("%d\n",f(T3,str2));
   
   return 0;
}




albero creaAlbero1() {
    albero tmp = createVal('a');
    tmp->left = createVal('c');tmp->left->left = createVal('o');tmp->left->right = createVal('b');
    tmp->right = createVal('d');tmp->right->left = createVal('c');tmp->right->right = createVal('r');
    tmp->right->right->left = createVal('c'); tmp->right->right->right = createVal('a');
    return tmp;
}


albero creaAlbero2() {
    albero tmp = createVal('a');
    tmp->left = createVal('c');tmp->left->left = createVal('o');tmp->left->right = createVal('b');
    tmp->right = createVal('d');tmp->right->left = createVal('c');tmp->right->right = createVal('a');
    tmp->right->right->left = createVal('c'); tmp->right->right->right = createVal('a');
    return tmp;
}


albero creaAlbero3() {
    albero tmp = createVal('s');
    tmp->left = createVal('c');tmp->left->left = createVal('o');tmp->left->right = createVal('b');
    tmp->right = createVal('d');tmp->right->left = createVal('c');tmp->right->right = createVal('r');
    tmp->right->right->left = createVal('c'); tmp->right->right->right = createVal('a');
    return tmp;
}


void print(albero t){
       if(t==NULL)return;
       else{printf(" (");print(t->left);printf(" %c ",t->val);print(t->right);printf(") ");}
}


void stampa(albero T){print(T);printf("\n");}


albero createVal(char val) {
    albero tmp = malloc(sizeof(nodo));
    tmp->val = val;    tmp->left = NULL;    tmp->right = NULL;
    return tmp;
}


int funzione(albero t, char stringa[], int contatore)
    {
        if(t==NULL)
            return 1;
        if(t->left==NULL && t->right==NULL)
        {
            if(verifica(t, stringa))
                contatore++;
            if(contatore==2)
                return 1;
            else
                return 0;
        }
        if(verifica(t, stringa))
            contatore++;
    return  funzione(t->left, stringa, contatore)&&funzione(t->right, stringa, contatore);
    }
int verifica(albero t, char stringa[])
    {
    int i=0;
    while(i<strlen(stringa))
        {
            if(stringa[i]==t->val)
                return 1;
            i++;
        }
    return 0;
    }
int f(albero t, char stringa[])
    {
        int contatore=0;
        int ris=funzione(t, stringa, contatore);
        return ris;
    }
