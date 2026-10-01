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
albero creaAlbero1(); albero creaAlbero2(); albero creaAlbero3();
void print(albero t);
void stampa(albero T);
int wrapper(albero tree1, albero tree2);
void funzione(albero tree1, albero tree2, int *contatore);

int main(){
    int ris=0;
    albero T1,T2,T3;
    T1 = creaAlbero1(); T2 = creaAlbero2(); T3 = creaAlbero3();
    printf("\nT1: "); stampa(T1);
    printf("\nT2: "); stampa(T2);
    printf("\nT3: "); stampa(T3);

    int ris12=wrapper(T1, T2);
    printf("T1 e T2 hanno %d valori in comune", ris12);
    
    int ris23=wrapper(T2, T3);
    printf("\nT2 e T3 hanno %d valori in comune", ris23);
    
    int ris13=wrapper(T1, T3);
    printf("\nT1 e T3 hanno %d valori in comune", ris13);

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
int trovavalore(int k, albero tree)
    {
        if(tree==NULL)
            return 0;
        if(tree->val==k)
            return 1;
    return trovavalore(k, tree->left) || trovavalore(k, tree->right);
    }

void funzione(albero tree1, albero tree2, int *contatore)
    {
    if(tree1==NULL)
        return;
    *contatore=*contatore+trovavalore(tree1->val, tree2);
    funzione(tree1->left, tree2, contatore);
    funzione(tree1->right, tree2, contatore);
    }
int wrapper(albero tree1, albero tree2)
    {
    int contatore=0;
    funzione(tree1, tree2, &contatore);
    return contatore;
    }
