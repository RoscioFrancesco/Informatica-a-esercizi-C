//
//  main.c
//  tde 7 -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
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
int contafoglie(tree t);
int f(tree t1, tree t2);
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


    printf("Prima coppia di alberi: %d\n", f(albero1, albero2));
    printf("Seconda coppia di alberi: %d\n", f(albero1, albero3));


    return 0;
}


int FogliaSimili(tree albero1, tree albero2) {
    //MODIFICARE QUI E USARE FUNZIONI AUSILIARIE
    //SUGGERIMENTO: SERVIRSI DI UN ARRAY PER MEMORIZZARE LE FOGLIE
    
    return 1;
}


tree creaNodo(int val) {
    tree nuovoNodo = (tree)malloc(sizeof(nodo));
    nuovoNodo->val = val;
    nuovoNodo->left = NULL;
    nuovoNodo->right = NULL;
    return nuovoNodo;
}
int contafoglie(tree t)
    {
        if(t==NULL)
            return 0;
        if(t->left==NULL && t->right==NULL)
            return 1;
    return contafoglie(t->left)+contafoglie(t->right);
    }

void riempivett(tree t, int vett[], int *scorri)
    {
        if(t==NULL)
            return;
        if(t->left==NULL && t->right==NULL)
            {
                vett[*scorri]=t->val;
                (*scorri)++;
            }
    riempivett(t->left, vett, scorri);
    riempivett(t->right, vett, scorri);
    }
int f(tree t1, tree t2)
    {
    int len1=contafoglie(t1);
    int len2=contafoglie(t2);
    if(len1!=len2)
        return 0;
    int *v1=malloc(sizeof(int)*len1);
    int *v2=malloc(sizeof(int)*len2);
    int scorri1=0;
    int scorri2=0;
    riempivett(t1, v1, &scorri1);
    riempivett(t2, v2, &scorri2);
    for(int i=0; i<len1; i++)
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
