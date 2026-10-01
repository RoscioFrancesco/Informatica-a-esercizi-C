//
//  main.c
//  altri alberi
//
//  Created by Francesco Roscio Ricon on 25/01/26.
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
float wrapper(albero tree);
void funzione(albero tree, float somma, float *media_min, int contatore);

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
    printf("Il percorso di T1 con media di valori minima ha media: %f\n", wrapper(T1));
    printf("Il percorso di T2 con media di valori minima ha media: %f\n", wrapper(T2));
    printf("Il percorso di T3 con media di valori minima ha media: %f\n", wrapper(T3));


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


void funzione(albero tree, float somma, float *media_min, int contatore)
    {
        if(tree==NULL)
            return;
        somma=somma+tree->val;
        contatore++;
        if(tree->left==NULL && tree->right==NULL)
            {
                float media=(somma+0.0)/contatore;
                if(*media_min==0)
                {
                    *media_min=media;
                    return;
                }
                if(*media_min>media)
                    *media_min=media;
                return;
            }
    funzione(tree->left, somma, media_min, contatore);
    funzione(tree->right, somma, media_min, contatore);
    }
float wrapper(albero tree)
    {
    float media_min=0;
    funzione(tree, 0, &media_min, 0);
    return media_min;
    }
