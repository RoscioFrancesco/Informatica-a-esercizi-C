//
//  main.c
//  gen 22
//
//  Created by Francesco Roscio Ricon on 25/01/26.
//
#include <stdio.h>
#include <stdlib.h>


typedef struct n {
        int val;
        struct n * left, * right;
} nodo;
typedef nodo * Albero;


Albero createVal(int val);
Albero creaAlbero1();Albero creaAlbero2();Albero creaAlbero3();
void print(Albero t);
void stampa(Albero T);
void f(Albero TA, Albero TB);
int wrapper(Albero TB, int k);
void trovavalore(Albero TB, int k, int *somma);


int main(){
    int ris=0, valore = -1;
    Albero T1,T2,T3;
    T1 = creaAlbero1(); T2 = creaAlbero2(); T3 = creaAlbero3();
    printf("\nT1: "); stampa(T1);
    printf("\nT2: "); stampa(T2);
    printf("\nT3: "); stampa(T3);


    //
    // TODO: CHIAMATE DI TEST
    //
    printf("\nT1 in T2\n");f(T1,T2);
    printf("\nT2 in T1\n");f(T2,T1);
    printf("\nT1 in T3\n");f(T1,T3);
    printf("\nT3 in T1\n");f(T3,T1);
    printf("\nT2 in T3\n");f(T2,T3);
    printf("\nT3 in T2\n");f(T3,T2);


     //FUNZIONI AUSILIARIE CON PARAMETRI DIVERSI SONO MOLTO CONSIGLIATE


    return 0;
}


//SOLUZIONE




//FINE SOLUZIONE


Albero creaAlbero1() {
    Albero tmp = createVal(7);
    tmp->left = createVal(3);tmp->left->left = createVal(9);tmp->left->right = createVal(10);
    tmp->right = createVal(8);tmp->right->left = createVal(5);tmp->right->right = createVal(12);
    tmp->right->right->left = createVal(11); tmp->right->right->right = createVal(9);
    return tmp;
}


Albero creaAlbero2() {
    Albero tmp = createVal(7);
    tmp->right = createVal(7);tmp->right->right = createVal(9);tmp->right->left = createVal(10);
    tmp->left = createVal(7);tmp->left->right = createVal(9);tmp->left->left = createVal(12);
    tmp->left->left->right = createVal(11);tmp->left->left->left = createVal(6);
    return tmp;
}


Albero creaAlbero3() {
    Albero tmp = createVal(3);
    tmp->right = createVal(3);tmp->right->right = createVal(9);tmp->right->left = createVal(10);
    tmp->left = createVal(4);tmp->left->right = createVal(3);tmp->left->left = createVal(12);
    tmp->left->left->right = createVal(2);tmp->left->left->left = createVal(6);
    return tmp;
}


void print(Albero t){
       if(t==NULL)return;
       else{printf(" (");print(t->left);printf(" %d ",t->val);print(t->right);printf(") ");}
}


void stampa(Albero T){print(T);printf("\n");}


Albero createVal(int val) {
    Albero tmp = (Albero)malloc(sizeof(nodo));
    tmp->val = val;    tmp->left = NULL;    tmp->right = NULL;
    return tmp;
}


void trovavalore(Albero TB, int k, int *somma)
    {
        if(TB==NULL)
            return;
        if(TB->val==k)
            {
                *somma=*somma+1;
            }
    trovavalore(TB->left, k, somma);
    trovavalore(TB->right, k, somma);
    }
int wrapper(Albero TB, int k)
    {
    int somma=0;
    trovavalore(TB, k, &somma);
    return somma;
    }
void f(Albero TA, Albero TB)
    {
    if(TA==NULL)
        return;
    if(wrapper(TB, TA->val)>0)
    {
        printf("Il valore di TA %d compare %d volte in TB\n", TA->val, wrapper(TB, TA->val));
    }
    f(TA->left, TB);
    f(TA->right, TB);
    }


