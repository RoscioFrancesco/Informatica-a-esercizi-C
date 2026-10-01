//
//  main.c
//  tde albero
//
//  Created by Francesco Roscio Ricon on 26/01/26.
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
int depth(albero t);
int max(int a,int b);
void inizializza(albero t,int v[],int liv);
void verifica(albero t,int elem[],int v[],int liv);
int prof_max(albero T);
int max(int a, int b);
int f(albero T);
int funz(albero T, int livello, int piano, int *val_piano);
int main(){
    int ris=0;
    albero T1,T2,T3;
    T1 = creaAlbero1(); T2 = creaAlbero2(); T3 = creaAlbero3();
    printf("\nT1: "); stampa(T1);
    printf("\nT2: "); stampa(T2);
    printf("\nT3: "); stampa(T3);
    
   printf("T1: %d\n",f(T1));
   printf("T2: %d\n",f(T2));
   printf("T3: %d\n",f(T3));
   
   return 0;
}
albero creaAlbero1() {
    albero tmp = createVal(7);
    tmp->left = createVal(3);tmp->left->left = createVal(9);tmp->left->right = createVal(9);
    tmp->right = createVal(8);tmp->right->left = createVal(9);tmp->right->right = createVal(9);
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

int funz(albero T, int livello_i, int piano, int *val_piano)
    {
        if(T==NULL)
            return 1;
        if(livello_i==piano)
            {
                if(*val_piano==-1)
                    *val_piano=T->val;
                else {
                    if(*val_piano!=T->val)
                        return 0;
                }
            }
    return funz(T->left, livello_i, piano+1, val_piano) && funz(T->right, livello_i, piano+1, val_piano);
    }

int max(int a, int b)
    {
    if(a>b)
        return a;
    return b;
}
int prof_max(albero T)
    {
        if(T==NULL)
            return 0;
    int sx=prof_max(T->left)+1;
    int dx=prof_max(T->right)+1;
    return max(sx,dx);
    }
int f(albero T)
    {
    int i;
    for(i=1; i<prof_max(T); i++)
        {
            int valpiano=-1;
            if(funz(T->right, i, 1, &valpiano) && funz(T->left, i, 1, &valpiano))
                return 1;
        }
    return 0;
    }

