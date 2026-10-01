//
//  main.c
//  tde 1 alberi -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//
#include <stdio.h>
#include <stdlib.h>


// Struttura dell'albero binario
typedef struct ET {
    int val;
    struct ET *left, *right;
} treeNode;


typedef treeNode *tree;


// Funzioni
tree cn(int val);
void stampaAlbero(tree r, int spazio);
int checkTree(tree r);
tree costruisciAlbero1();
tree costruisciAlbero2();
tree costruisciAlbero3();
tree costruisciAlbero4();

float mediasottoalbero(tree albero);
void datisottoalbero(tree albero, float *somma, int *count);

int main() {
    tree t1=costruisciAlbero1();
    tree t2=costruisciAlbero2();
    tree t3=costruisciAlbero3();
    tree t4=costruisciAlbero4();


    printf("Albero 1: %d\n", checkTree(t1));
    printf("Albero 2: %d\n", checkTree(t2));
    printf("Albero 3: %d\n", checkTree(t3));
    printf("Albero 4: %d\n", checkTree(t4));


    return 0;
}


int checkTree(tree r) {
    if(r==NULL)
        return 0;
    if(r->left==NULL && r->right==NULL)
        return 1;
    int sx=1;
    int dx=1;
    if(r->left!=NULL)
        {
            if(!(mediasottoalbero(r->left)>=r->val))
                return 0;
            sx=checkTree(r->left);
        }
    if(r->right!=NULL)
        {
            if(!(mediasottoalbero(r->right)>=r->val))
                return 0;
            dx=checkTree(r->right);
        }
    return sx&&dx;
}


//AGGIUNGERE QUI FUNZIONI AUSILIARIE


tree cn(int val){tree newNode=(tree)malloc(sizeof(treeNode));newNode->val=val;newNode->left=NULL;newNode->right=NULL;return newNode;}
tree costruisciAlbero1(){tree r=cn(1);r->left=cn(5);r->right=cn(7);r->left->left=cn(21);r->left->right=cn(38);r->right->left=cn(12);r->right->right=cn(24);r->left->left->left=cn(100);r->left->left->right=cn(83);r->left->right->left=cn(67);r->right->right->left=cn(91);r->right->right->right=cn(75);return r;}
tree costruisciAlbero2(){tree r=cn(8);r->left=cn(4);r->right=cn(2);r->left->left=cn(6);r->left->right=cn(11);r->right->left=cn(10);r->right->right=cn(14);r->left->left->left=cn(18);r->left->left->right=cn(30);r->left->right->left=cn(54);r->right->right->left=cn(72);r->right->right->right=cn(75);return r;}
tree costruisciAlbero3(){tree r=cn(10);r->left=cn(5);r->right=cn(15);r->left->left=cn(1);r->left->right=cn(7);r->right->left=cn(12);r->right->right=cn(20);r->left->left->left=cn(0);r->left->left->right=cn(2);r->left->right->left=cn(6);r->right->right->left=cn(18);r->right->right->right=cn(5);return r;}
tree costruisciAlbero4(){tree r=cn(9);r->left=cn(4);r->right=cn(14);r->left->left=cn(1);r->left->right=cn(6);r->right->left=cn(10);r->right->right=cn(18);r->left->left->left=cn(0);r->left->left->right=cn(2);r->left->right->left=cn(5);r->right->right->left=cn(17);r->right->right->right=cn(30);return r;}


//si dice mediamente crescente se, per ogni suo nodo N, entrambe le medie dei due sottoalberi di N sono maggiori o uguali al valore nel nodo N.
void datisottoalbero(tree albero, float *somma, int *count)
    {
        if(albero==NULL)
            return;
        *somma=(*somma)+albero->val;
        (*count)++;
    datisottoalbero(albero->left, somma, count);
    datisottoalbero(albero->right, somma, count);
    }
float mediasottoalbero(tree albero)
    {
    float somma=0;
    int count=0;
    datisottoalbero(albero, &somma, &count);
    return somma/count;
    }

