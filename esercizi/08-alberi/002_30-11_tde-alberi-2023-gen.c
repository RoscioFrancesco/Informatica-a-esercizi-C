//
//  main.c
//  tde alberi 2023 gen
//
//  Created by Francesco Roscio Ricon on 30/11/25.
// Riferimento: Informatica A (061202), TDE gennaio 2023, a.a. 2022/23: https://forms.office.com/e/sHUPtML1tR
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
int f(albero t,char str[]);
int letteratrovata(char lettera, char stringa[]);
int funzione(albero t, char stringa[], int contatore);
int main(){
    
    char str1[100]="acacia",str2[100]="sacca";
    albero T1,T2,T3;
    T1 = creaAlbero1(); T2 = creaAlbero2(); T3 = creaAlbero3();
    printf("\nT1: "); stampa(T1);
    printf("\nT2: "); stampa(T2);
    printf("\nT3: "); stampa(T3);
    printf("\n");

   printf("%d\n",f(T1,str1));
   printf("%d\n",f(T1,str2));
   printf("%d\n",f(T2,str1));
   printf("%d\n",f(T2,str2));
   printf("%d\n",f(T3,str1));
   printf("%d\n",f(T3,str2));
   
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
int letteratrovata(char lettera, char stringa[])
    {
    int i=0;
        while(stringa[i]!='\0')
            {
                if(stringa[i]==lettera)
                    return 1;
                i++;
            }
        return 0;
    }
int funzione(albero t, char stringa[], int contatore)
    {
        if(t==NULL)
            return 0;
        if(letteratrovata(t->val, stringa))
            contatore++;
        if(t->left==NULL && t->right==NULL)
            return contatore;
    funzione(t->left, stringa, contatore);
    funzione(t->right, stringa, contatore);
    }
int f(albero t,char str[])
    {
    int contatore=0;
        if(funzione(t, str,contatore)==2)
            return 1;
    return 0;
   }
//void salvalunghezzacammini(Tree t, int livello, int array[], int *i)
//    {
//        if(t==NULL)
//            return;
//    if(t->left==NULL && t->right==NULL)
//        {
//            array[*i]=livello;
//            (*i)++;
//            return;
//        }
//    livello++;
//    salvalunghezzacammini(t->left, livello, array, i);
//    salvalunghezzacammini(t->right, livello, array, i);
//    }
