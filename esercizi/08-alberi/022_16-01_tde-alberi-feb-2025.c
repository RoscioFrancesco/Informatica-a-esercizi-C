//
//  main.c
//  tde alberi feb 2025
//
//  Created by Francesco Roscio Ricon on 16/01/26.
// Riferimento: Informatica A (061202), TDE febbraio 2025, a.a. 2024/25: https://forms.office.com/e/Z4QRAS2ZuL
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
int checkTree(tree albero);
tree costruisciAlbero1();
tree costruisciAlbero2();
tree costruisciAlbero3();
tree costruisciAlbero4();
float media(tree albero);
int conteggio(tree albero);
int somma_sottoalbero(tree albero);

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


//AGGIUNGERE QUI FUNZIONI AUSILIARIE

tree cn(int val){
    tree newNode=(tree)malloc(sizeof(treeNode));
    newNode->val=val;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

tree costruisciAlbero1(){
    tree r=cn(1);
    r->left=cn(5);
    r->right=cn(7);
    r->left->left=cn(21);
    r->left->right=cn(38);
    r->right->left=cn(12);
    r->right->right=cn(24);
    r->left->left->left=cn(100);
    r->left->left->right=cn(83);
    r->left->right->left=cn(67);
    r->right->right->left=cn(91);
    r->right->right->right=cn(75);
    return r;
}

tree costruisciAlbero2(){
    tree r=cn(8);
    r->left=cn(4);
    r->right=cn(2);
    r->left->left=cn(6);
    r->left->right=cn(11);
    r->right->left=cn(10);
    r->right->right=cn(14);
    r->left->left->left=cn(18);
    r->left->left->right=cn(30);
    r->left->right->left=cn(54);
    r->right->right->left=cn(72);
    r->right->right->right=cn(75);
    return r;
}

tree costruisciAlbero3(){
    tree r=cn(10);
    r->left=cn(5);
    r->right=cn(15);
    r->left->left=cn(1);
    r->left->right=cn(7);
    r->right->left=cn(12);
    r->right->right=cn(20);
    r->left->left->left=cn(0);
    r->left->left->right=cn(2);
    r->left->right->left=cn(6);
    r->right->right->left=cn(18);
    r->right->right->right=cn(5);
    return r;
}

tree costruisciAlbero4(){
    tree r=cn(9);
    r->left=cn(4);
    r->right=cn(14);
    r->left->left=cn(1);
    r->left->right=cn(6);
    r->right->left=cn(10);
    r->right->right=cn(18);
    r->left->left->left=cn(0);
    r->left->left->right=cn(2);
    r->left->right->left=cn(5);
    r->right->right->left=cn(17);
    r->right->right->right=cn(30);
    return r;
}

int somma_sottoalbero(tree albero)
    {
        if(albero==NULL)
            return 0;
    return somma_sottoalbero(albero->left)+somma_sottoalbero(albero->right)+albero->val;
    }
int conteggio(tree albero)
    {
        if(albero==NULL)
            {
                return 0;
            }
    return conteggio(albero->left)+conteggio(albero->right)+1;
    }
float media(tree albero)
    {
    float media;
    int somma=somma_sottoalbero(albero);
    int count=conteggio(albero);
    media=(somma+0.0)/count;
    return media;
    }
int checkTree(tree albero)
    {
        if(albero==NULL)
            return 1;
        if(albero->left==NULL && albero->right==NULL)
            return 1;
    
        if (albero->left != NULL) {
            if (media(albero->left) <= albero->val) return 0;
        }

        if (albero->right != NULL) {
            if (media(albero->right) <= albero->val) return 0;
        }

    return checkTree(albero->left)&&checkTree(albero->right);
    }
