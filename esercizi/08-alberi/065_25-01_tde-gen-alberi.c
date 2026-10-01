//
//  main.c
//  tde gen alberi
//
//  Created by Francesco Roscio Ricon on 25/01/26.
//
#include <stdio.h>
#include <stdlib.h>


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
int verifica(char parola[], char lettera);
int f(albero tree, char parola[]);
int funzione(albero tree, int contatore, char parola[]);

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

// Riferimento: Informatica A (061202), TDE gennaio 2026, a.a. 2025/26: https://forms.cloud.microsoft/e/U1bBujvcBe

int verifica(char parola[], char lettera)
    {
    int i=0;
    while(parola[i]!='\0')
        {
            if(parola[i]==lettera)
                return 1;
            i++;
        }
    return 0;
    }

int funzione(albero tree, int contatore, char parola[])
    {
    if(tree==NULL)
        return 0;
    if(verifica(parola, tree->val))
        contatore++;
    
    if(tree->left==NULL && tree->right==NULL)
        {
            if(contatore==2)
                return 1;
            return 0;
        }
    if (tree->left == NULL)
            return funzione(tree->right, contatore, parola);

    if (tree->right == NULL)
            return funzione(tree->left, contatore, parola);
    
    return funzione(tree->left, contatore, parola) && funzione(tree->right, contatore, parola);
}

int f(albero tree, char parola[])
    {
    return funzione(tree, 0, parola);
    }
