//
//  main.c
//  esercitaz alberi medie
//
//  Created by Francesco Roscio Ricon on 19/12/25.
// Riferimento: Informatica A (061202), TDE febbraio 2025, a.a. 2024/25: https://forms.office.com/e/Z4QRAS2ZuL

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct s_nodo {
        int val;
        struct s_nodo *left;
        struct s_nodo *right;
} nodo;
typedef nodo *albero;

albero creaAlbero();
albero createVal(int val);
void print(albero t);
void printConLivello(albero t,int liv);
int check_tree(albero t);
int contanodi(albero t);
int sommanodi(albero t);
float calcolamedia(albero t);

int main(){
  albero alb = creaAlbero();
  print(alb);
    int ris=check_tree(alb);
    printf("\n%d", ris);
}




albero creaAlbero() {
    albero tmp = createVal(1);
    tmp->left = createVal(2);
    tmp->right = createVal(21);

    tmp->left->left = createVal(4);
    tmp->left->right = createVal(5);

    tmp->right->left = createVal(6);
    tmp->right->right = createVal(7);

    return tmp;
}


albero createVal(int val) {
       albero tmp = malloc(sizeof(nodo));
       tmp->val = val;
       tmp->left = NULL;
       tmp->right = NULL;
       return tmp;
}


void print(albero t){
       if(t==NULL)
           return;
       printf(" (");
       print(t->left);
       printf(" %d ",t->val);
       print(t->right);
       printf(") ");
}


void printConLivello(albero t,int liv){
       if(t==NULL)
           return;
       printf(" (");
       printConLivello(t->left,liv+1);
       printf("(v: %d, l: %d)",t->val,liv);
       printConLivello(t->right,liv+1);
       printf(") ");
}


int check_tree(albero t)
    {
        if(t==NULL)
            return 1;
    if(t->left==NULL && t->right==NULL) return 1;
    if(t->left!=NULL && calcolamedia(t->left)<t->val)
        return 0;
    if(t->right!=NULL && calcolamedia(t->right)<t->val)
        return 0;
    return check_tree(t->right)&&check_tree(t->left);
    }
float calcolamedia(albero t)
    {
     if(t==NULL)
     {
         printf("Fanculo");
         return 1000000;
     }
    sommanodi(t);
    contanodi(t);
    return sommanodi(t)*1.0/contanodi(t);
    }
int sommanodi(albero t)
    {
    if(t==NULL)
        return 0;
    return t->val+sommanodi(t->left)+sommanodi(t->right);
}
int contanodi(albero t)
    {
        if(t==NULL)
            return 0;
    return 1+contanodi(t->left)+contanodi(t->right);
    }
