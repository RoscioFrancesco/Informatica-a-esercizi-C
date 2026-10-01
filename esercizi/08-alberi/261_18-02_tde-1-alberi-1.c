//
//  main.c
//  tde 1 alberi -1
//
//  Created by Francesco Roscio Ricon on 18/02/26.
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

void f(albero t, int *flag, float *media, float somma, int count)
    {
        if(t==NULL)
            return;
        somma=somma+t->val;
        count++;
        if(t->left==NULL && t->right==NULL)
        {
            float m_now=somma/count;
            if(*flag==0)
            {
                *media=m_now;
                *flag=1;
            }
            else
            {
                if(m_now<*media)
                {
                    *media=m_now;
                }
            }
        }
    f(t->left, flag, media, somma, count);
    f(t->right, flag, media, somma, count);
    }

float costoMinimoMedio(albero T)
    {
        if(T==NULL)
            return 0;
        int flag=0;
    float media=0;
    f(T, &flag, &media, 0, 0);
    return media;
    }
