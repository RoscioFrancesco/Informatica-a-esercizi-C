//  Created by Francesco Roscio Ricon on 22/01/26.


#include <stdio.h>
#include <stdlib.h>

// Struttura dell'albero binario
typedef struct ET {
    int val;
    struct ET *left, *right;
} treeNode;

typedef treeNode *tree;

int funzione(tree albero);
// Funzioni
tree cn(int val);
void stampaAlbero(tree r, int spazio);
int checkTree(tree r);
tree costruisciAlbero1();
tree costruisciAlbero2();
tree costruisciAlbero3();
tree costruisciAlbero4();
int funzione(tree albero);
void media_albero(tree albero, int *somma, int *contatore);
int checkTree(tree albero);

int main() {
    tree t1=costruisciAlbero1();
    tree t2=costruisciAlbero2();
    tree t3=costruisciAlbero3();
    tree t4=costruisciAlbero4();

    printf("Albero 1: %d\n", funzione(t1));
    printf("Albero 2: %d\n", funzione(t2));
    printf("Albero 3: %d\n", funzione(t3));
    printf("Albero 4: %d\n", funzione(t4));

    return 0;
}



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


int funzione(tree albero)
    {
        if(albero==NULL)
            return 0;
        if(albero->right==NULL && albero->left==NULL)
            return 1;
        if(albero->right==NULL && albero->left!=NULL)
            {
                if(albero->val%2==0 && albero->left->val%2==0)
                    return 0;
                if(albero->val%2==1 && albero->left->val%2==1)
                    return 0;
                return funzione(albero->left);
            }
        if(albero->right!=NULL && albero->left==NULL)
        {
            if(albero->val%2==0 && albero->right->val%2==0)
                return 0;
            if(albero->val%2==1 && albero->right->val%2==1)
                return 0;
            return funzione(albero->right);
        }
        if(albero->val%2==0)
            {   if(albero->right->val%2==1 && albero->left->val%2==1)
                return funzione(albero->left) ||  funzione(albero->right);
                if(albero->right->val%2==1)
                    return funzione(albero->right);
                if(albero->left->val%2==1)
                    return funzione(albero->left);
                
            return 0;
            }
        else {
                if(albero->right->val%2==0 && albero->left->val%2==0)
                    return funzione(albero->left) || funzione(albero->right);
            
                if(albero->left->val%2==0)
                    return funzione(albero->left);
            
                if(albero->right->val%2==0)
                    return funzione(albero->right);
            return 0;
        }
        
    }
