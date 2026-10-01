//  Created by Francesco Roscio Ricon on 24/01/26.


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
void scorrisomma(albero tree, int somma, int conta_livello, int*vettsomma, int*vettconta);
int calcolaprofondità(albero tree);
void f(albero tree);
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

void f(albero tree)
    {
        if(tree==NULL)
            return;
    int somma=0;
    int profondità=calcolaprofondità(tree);
    int *vett_somma=malloc(sizeof(int)*profondità);
    int i;
    for (int i = 0; i < profondità; i++) {
        vett_somma[i] = 0;
    }
    int *vett_contatore=malloc(sizeof(int)*profondità);
    for ( i = 0; i < profondità; i++) {
        vett_contatore[i] = 0;
    }
    scorrisomma(tree, somma, 0, vett_somma, vett_contatore);
    float *vett_media=malloc(sizeof(float)*profondità);
    for(i=0;i<profondità; i++)
        {
            vett_media[i]=(vett_somma[i]+0.0)/ vett_contatore[i];
        }
    free(vett_somma);
    free(vett_contatore);
    for(i=0; i<profondità;i++)
        {
            printf("%f-->", vett_media[i]);
        }
    free(vett_media);
    }
int max(int val1, int val2)
    {
        if(val1>val2)
            return val1;
        return val2;
    }

int calcolaprofondità(albero tree)
    {
        if(tree==NULL)
            return 0;
    int sx=calcolaprofondità(tree->left);
    int dx=calcolaprofondità(tree->right);
    return max(sx, dx)+ 1;
    }
void scorrisomma(albero tree, int somma, int conta_livello, int*vettsomma, int*vettconta)
    {
        if(tree==NULL)
            return;
    somma=somma+tree->val;
    vettconta[conta_livello]++;
    vettsomma[conta_livello]=vettsomma[conta_livello]+tree->val;
    scorrisomma(tree->left, somma, conta_livello+1, vettsomma, vettconta);
    scorrisomma(tree->right, somma, conta_livello+1, vettsomma, vettconta);
    }
