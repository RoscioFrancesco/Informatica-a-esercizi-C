//  Created by Francesco Roscio Ricon on 19/01/26.

#include <stdio.h>
#include <stdlib.h>


typedef struct el {
    int val;
    struct el *left, *right;
} nodo;


typedef nodo* tree;


tree creaNodo(int val);
int FogliaSimili(tree albero1, tree albero2);
void riempiarray(tree albero, int array[], int *segnaposto);

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
    
    
    int array_primo[8]={0,0,0,0,0,0,0,0};
    int array_secondo[8]={0,0,0,0,0,0,0,0};

    printf("Prima coppia di alberi: %d\n", FogliaSimili(albero1, albero2));
    printf("Seconda coppia di alberi: %d\n", FogliaSimili(albero1, albero3));


    return 0;
}




tree creaNodo(int val) {
    tree nuovoNodo = (tree)malloc(sizeof(nodo));
    nuovoNodo->val = val;
    nuovoNodo->left = NULL;
    nuovoNodo->right = NULL;
    return nuovoNodo;
}

void riempiarray(tree albero, int array[], int *segnaposto)
    {
        if(albero==NULL)
            return;
        if(albero->left==NULL && albero->right==NULL)
            {
                array[*segnaposto]=albero->val;
                *segnaposto=*segnaposto+1;
            }
    riempiarray(albero->left, array, segnaposto);
    riempiarray(albero->right, array, segnaposto);
    }

int FogliaSimili(tree albero1, tree albero2)
    {
    int segnaposto1=0;
    int segnaposto2=0;
        int array_primo[8]={0,0,0,0,0,0,0,0};
        int array_secondo[8]={0,0,0,0,0,0,0,0};
    
    riempiarray(albero1, array_primo, &segnaposto1);
    riempiarray(albero2, array_secondo, &segnaposto2);
    int i;
    for(i=0; i<8; i++)
        {
            if(array_primo[i]!=array_secondo[i])
                return 0;
        }
        return 1;
    }

