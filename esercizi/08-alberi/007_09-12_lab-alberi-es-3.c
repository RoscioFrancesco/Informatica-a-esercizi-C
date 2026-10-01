//  Created by Francesco Roscio Ricon on 09/12/25.

//  Con gli alberi di esempio del codice fornito l'output deve essere:
//  T1 e T2 hanno 8 elementi comuni
//  T1 e T3 hanno 7 elementi comuni
//  T2 e T3 hanno 7 elementi comuni


#include <stdio.h>
#include <stdlib.h>


typedef struct n {
        int val;
        struct n * left;
struct n * right;
} nodo;
typedef nodo * albero;


albero createVal(int val);
albero creaAlbero1(); albero creaAlbero2(); albero creaAlbero3();
void print(albero t);
void stampa(albero T);
int wrapper(albero t1, albero t2);
void funzione_scorri1(albero t1, int *comuni, albero t2);
int cerca2(int sherlock, albero t2);
int wrapper(albero t1, albero t2);

int main(){
    int ris=0;
    albero T1,T2,T3;
    T1 = creaAlbero1(); T2 = creaAlbero2(); T3 = creaAlbero3();
    printf("\nT1: "); stampa(T1);
    printf("\nT2: "); stampa(T2);
    printf("\nT3: "); stampa(T3);
    
    ris=wrapper(T1, T3);
    printf("%d", ris);
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

void funzione_scorri1(albero t1, int *comuni, albero t2)
    {
        if(t1==NULL || t2==NULL)
            return;
    if(cerca2(t1->val, t2))
        (*comuni)++;
    funzione_scorri1(t1->left, comuni, t2);
    funzione_scorri1(t1->right, comuni, t2);
    
    
    }
int wrapper(albero t1, albero t2)
    {
    int comuni=0;
    funzione_scorri1(t1, &comuni, t2);
    return comuni;
    }
int cerca2(int sherlock, albero t2)
    {
        if(t2==NULL)
            return 0;
        if(sherlock==t2->val)
            return 1;
        return cerca2(sherlock, t2->left)+cerca2(sherlock, t2->right);

    }
