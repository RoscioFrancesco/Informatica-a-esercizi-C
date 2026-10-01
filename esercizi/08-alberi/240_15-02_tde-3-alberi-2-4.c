//
//  main.c
//  tde 3 alberi 2 -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct n {
    int val;
    struct n *left;
    struct n *right;
} nodo;
typedef nodo *albero;


albero createVal(int val);
albero creaAlbero1();
albero creaAlbero2();
albero creaAlbero3();


void print(albero t);
void stampa(albero T);
float costoMinimoMedio(albero T);

float wrapper(albero t);
void f(albero t, float *min, int *hasprec, float somma, int count);
int main() {
    albero T1, T2, T3;
    T1 = creaAlbero1();
    T2 = creaAlbero2();
    T3 = creaAlbero3();


    printf("\nT1: ");
    stampa(T1);
    printf("\nT2: ");
    stampa(T2);
    printf("\nT3: ");
    stampa(T3);


    // visualizzazione risultati e invocazione funzione
    printf("Il percorso di T1 con media di valori minima ha media: %f\n", costoMinimoMedio(T1));
    printf("Il percorso di T2 con media di valori minima ha media: %f\n", costoMinimoMedio(T2));
    printf("Il percorso di T3 con media di valori minima ha media: %f\n", costoMinimoMedio(T3));


    return 0;
}


float costoMinimoMedio(albero T){
    return wrapper(T);
}


albero creaAlbero1() {
    albero tmp = createVal(7);
    tmp->left = createVal(3);
    tmp->left->left = createVal(9);
    tmp->left->right = createVal(10);
    tmp->right = createVal(8);
    tmp->right->left = createVal(5);
    tmp->right->right = createVal(12);
    tmp->right->right->left = createVal(11);
    tmp->right->right->right = createVal(6);
    return tmp;
}


albero creaAlbero2() {
    albero tmp = createVal(8);
    tmp->left = createVal(5);
    tmp->right = createVal(12);
    tmp->right->left = createVal(11);
    tmp->right->right = createVal(6);
    return tmp;
}


albero creaAlbero3() {
    albero tmp = createVal(8);
    tmp->left = createVal(5);
    tmp->right = createVal(0);
    tmp->right->left = createVal(1);
    tmp->right->right = createVal(5);
    return tmp;
}


void print(albero t) {
    if (t == NULL)return;
    else {
        printf(" (");
        print(t->left);
        printf(" %d ", t->val);
        print(t->right);
        printf(") ");
    }
}


void stampa(albero T) {
    print(T);
    printf("\n");
}


albero createVal(int val) {
    albero tmp = (albero)malloc(sizeof(nodo));
    tmp->val = val;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}


void f(albero t, float *min, int *hasprec, float somma, int count)
    {
        if(t==NULL)
            return;
        somma=somma+t->val;
        count++;
        if(t->left==NULL && t->right==NULL)
            {
                if(*hasprec==0)
                    {
                        *hasprec=1;
                        *min=(somma/count);
                    }
                else
                    {
                        float now=(somma)/count;
                        if(now<*min)
                            *min=now;
                    }
            }
    f(t->left, min, hasprec, somma, count);
    f(t->right, min, hasprec, somma, count);
    }

float wrapper(albero t)
    {
    float min=0;
    int hasprec=0;
    f(t, &min, &hasprec, 0, 0);
    return min;
    }
