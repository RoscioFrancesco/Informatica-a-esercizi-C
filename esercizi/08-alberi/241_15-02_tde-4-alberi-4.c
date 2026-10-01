//
//  main.c
//  tde 4 alberi -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//

#include <stdio.h>
#include <stdlib.h>
typedef struct n {
        char val;
        struct n * left;
        struct n * right;
} nodo;
typedef nodo * albero;


albero createVal(int val);
albero creaAlbero1();albero creaAlbero2();albero creaAlbero3();
void print(albero t);
void stampa(albero T);
int f(albero t);


int main(){
    int ris=0;
    albero T1,T2,T3;
    T1 = creaAlbero1(); T2 = creaAlbero2(); T3 = creaAlbero3();
    printf("\nT1: "); stampa(T1);
    printf("\nT2: "); stampa(T2);
    printf("\nT3: "); stampa(T3);


   //LA FUNZIONE DA SVILUPPARE VIENE USATA QUI




   if(f(T1)==1)
        printf("T1 ok\n");
    else printf("T1 non ok\n");


   if(f(T2)==1)
        printf("T2 ok\n");
    else printf("T2 non ok\n");


   if(f(T3)==1)
        printf("T3 ok\n");
    else printf("T3 non ok\n");


    return 0;
}



albero creaAlbero1() {
    albero tmp = createVal('a');
    tmp->left = createVal('e');tmp->left->left = createVal('b');tmp->left->right = createVal('z');
    tmp->right = createVal('o');tmp->right->left = createVal('f');tmp->right->right = createVal('e');
    tmp->right->right->left = createVal('g'); tmp->right->right->right = createVal('t');
    return tmp;
}


albero creaAlbero2() {
    albero tmp = createVal('h');
    tmp->right = createVal('r');tmp->right->right = createVal('b');tmp->right->left = createVal('a');
    tmp->left = createVal('s');tmp->left->right = createVal('l');tmp->left->left = createVal('e');
    tmp->left->left->right = createVal('p');tmp->left->left->left = createVal('a');
    return tmp;
}


albero creaAlbero3() {
    albero tmp = createVal('b');
    tmp->right = createVal('c');tmp->right->right = createVal('t');tmp->right->left = createVal('a');
    tmp->left = createVal('e');tmp->left->right = createVal('c');tmp->left->left = createVal('i');
    tmp->left->left->right = createVal('a');tmp->left->left->left = createVal('o');
    return tmp;
}


void print(albero t){
       if(t==NULL)return;
       else{printf(" (");print(t->left);printf(" %c ",t->val);print(t->right);printf(") ");}
}


void stampa(albero T){print(T);printf("\n");}


albero createVal(int val) {
    albero tmp = malloc(sizeof(nodo));
    tmp->val = val;    tmp->left = NULL;    tmp->right = NULL;
    return tmp;
}
int èfoglia(albero t)
    {
        if(t->left==NULL && t->right==NULL)
            return 1;
    return 0;
    }
int èvocale(albero t)
    {
    char lett=t->val;
    if(lett=='a' || lett=='e' || lett=='i' || lett=='o' || lett=='u')
        return 1;
    return 0;
    }
int verificasottoalbero(albero t)
    {
        if(t==NULL)
            return 1;
        if(èvocale(t) && èfoglia(t))
            return 0;
        return verificasottoalbero(t->left)&&verificasottoalbero(t->right);
    }
int f(albero t)
    {
        if(t==NULL)
            return 1;
        if(!èfoglia(t) && èvocale(t))
            {
                if((verificasottoalbero(t->left)&&verificasottoalbero(t->right))==0)
                    return 0;
            }
    return f(t->left)&&f(t->right);
    }
