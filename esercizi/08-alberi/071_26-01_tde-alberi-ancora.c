//
//  main.c
//  tde alberi ancora
//
//  Created by Francesco Roscio Ricon on 26/01/26.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct el {
    int val;
    struct el *left, *right;
} nodo;
typedef nodo* tree;
int FogliaSimili(tree albero1, tree albero2);
tree creaNodo(int val);
void scorri(tree albero, int *segna, int v[]);

int main() {
    tree albero1,albero2,albero3;
    albero1 = creaNodo(1);
    albero1->left = creaNodo(2);
    albero1->right = creaNodo(3);
    albero1->left->left = creaNodo(6);
    albero1->left->right = creaNodo(7);
    albero1->right->left = creaNodo(4);
    albero1->right->right = creaNodo(5);
    albero1->right->right->left = creaNodo(9);
    albero1->right->right->right = creaNodo(8);


    albero2 = creaNodo(10);
    albero2->left = creaNodo(20);
    albero2->right = creaNodo(30);
    albero2->left->left = creaNodo(6);
    albero2->left->right = creaNodo(7);
    albero2->right->left = creaNodo(4);
    albero2->right->right = creaNodo(5);
    albero2->right->right->left = creaNodo(9);
    albero2->right->right->right = creaNodo(8);


    albero3 = creaNodo(1);
    albero3->left = creaNodo(2);
    albero3->right = creaNodo(3);
    albero3->left->left = creaNodo(6);
    albero3->left->right = creaNodo(7);
    albero3->right->left = creaNodo(4);
    albero3->right->right = creaNodo(5);
    albero3->right->right->left = creaNodo(10);
    albero3->right->right->right = creaNodo(8);


    printf("Prima coppia di alberi: %d\n", FogliaSimili(albero1, albero2));
    printf("Seconda coppia di alberi: %d\n", FogliaSimili(albero1, albero3));
}


tree creaNodo(int val) {
    tree nuovoNodo = (tree)malloc(sizeof(nodo));
    nuovoNodo->val = val;
    nuovoNodo->left = NULL;
    nuovoNodo->right = NULL;
    return nuovoNodo;
}
int FogliaSimili(tree albero1, tree albero2)
    {
    int segna1=0;
    int segna2=0;
    int i=0;
    int *v1=malloc(sizeof(int)*8);
    for(i=0; i<8;i++)
        {
            v1[i]=0;
        }
    int *v2=malloc(sizeof(int)*8);
    for(i=0; i<8;i++)
        {
            v2[i]=0;
        }
    scorri(albero1, &segna1, v1);
    scorri(albero2, &segna2, v2);
    for(i=0; i<8; i++)
        {
            if(v1[i]!=v2[i])
            {
                free(v1);
                free(v2);
                return 0;
            }
        }
    free(v1);
    free(v2);
    return 1;
    }
void scorri(tree albero, int *segna, int v[])
    {
        if(albero==NULL)
            return;
        if(albero->left==NULL && albero->right==NULL)
            {
                v[*segna]=albero->val;
                (*segna)++;
                return;
            }
    scorri(albero->left, segna, v);
    scorri(albero->right, segna, v);
    }

