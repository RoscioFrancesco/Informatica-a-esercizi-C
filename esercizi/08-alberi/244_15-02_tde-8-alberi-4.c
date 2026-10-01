//
//  main.c
//  tde 8 alberi -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//

#include <stdio.h>
#include <stdlib.h>
typedef struct n {
        int val;
        struct n * left;
        struct n * right;
} nodo;
typedef nodo * albero;


albero createVal(int val);
albero creaAlbero1();albero creaAlbero2();albero creaAlbero3();
void print(albero t);
void stampa(albero T);
void f(albero t);


int main(){
    int ris=0;
    albero T1,T2,T3;
    T1 = creaAlbero1(); T2 = creaAlbero2(); T3 = creaAlbero3();
    printf("\nT1: "); stampa(T1);
    printf("\nT2: "); stampa(T2);
    printf("\nT3: "); stampa(T3);


   //LA FUNZIONE DA SVILUPPARE VIENE USATA QUI




   f(T1);
   f(T2);
   f(T3);
   
   return 0;
}



albero creaAlbero1() {
    albero tmp = createVal(7);
    tmp->left = createVal(3);tmp->left->left = createVal(9);tmp->left->right = createVal(10);
    tmp->right = createVal(8);tmp->right->left = createVal(5);tmp->right->right = createVal(12);
    tmp->right->right->left = createVal(11); tmp->right->right->right = createVal(6);
    return tmp;
}


albero creaAlbero2() {
    albero tmp = createVal(7);
    tmp->right = createVal(3);tmp->right->right = createVal(9);tmp->right->left = createVal(10);
    tmp->left = createVal(1);tmp->left->right = createVal(5);tmp->left->left = createVal(12);
    tmp->left->left->right = createVal(11);tmp->left->left->left = createVal(6);
    return tmp;
}


albero creaAlbero3() {
    albero tmp = createVal(7);
    tmp->right = createVal(3);tmp->right->right = createVal(9);tmp->right->left = createVal(10);
    tmp->left = createVal(4);tmp->left->right = createVal(5);tmp->left->left = createVal(12);
    tmp->left->left->right = createVal(2);tmp->left->left->left = createVal(6);
    return tmp;
}


void print(albero t){
       if(t==NULL)return;
       else{printf(" (");print(t->left);printf(" %d ",t->val);print(t->right);printf(") ");}
}


void stampa(albero T){print(T);printf("\n");}


albero createVal(int val) {
    albero tmp = malloc(sizeof(nodo));
    tmp->val = val;    tmp->left = NULL;    tmp->right = NULL;
    return tmp;
}

int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int pr(albero tree)
    {
        if(tree==NULL)
            return 0;
    int sx=pr(tree->left);
    int dx=pr(tree->right);
    return 1+max(sx, dx);
    }
void raccoglidati(float somme[], albero tree, int livello, int count[])
    {
        if(tree==NULL)
            return;
    somme[livello]=somme[livello]+tree->val;
    (count[livello])++;
    raccoglidati(somme, tree->left, livello+1, count);
    raccoglidati(somme, tree->right, livello+1, count);
    }
void f(albero t)
    {
    int depth=pr(t);
    float *somme=malloc(sizeof(float)*depth);
    int *count=malloc(sizeof(int)*depth);
    for(int i=0; i<depth; i++)
        {
            somme[i]=0;
            count[i]=0;
        }
    raccoglidati(somme, t, 0, count);
    for(int i=0; i<depth; i++)
        {
            printf("livello %d, ha media %f\n",i, (somme[i]/count[i]) );
        }
    
    }
