//  Created by Francesco Roscio Ricon on 16/01/26.

//  Un albero si dice artussiano se e solo se è composto da:
//
//  nodi foglia
//  nodi con un solo figlio
//  nodi con due figli aventi lo stesso numero di discendenti


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

int main(){
  albero alb = creaAlbero();
  print(alb);
    
}




albero creaAlbero() {
    albero tmp = createVal(1);
    tmp->left = createVal(2);
    tmp->right = createVal(1);

    tmp->left->left = createVal(4);
    tmp->left->right = createVal(5);

    tmp->right->left = createVal(6);
    tmp->right->right = createVal(1);

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

//  Un albero si dice artussiano se e solo se è composto da:
//
//  nodi foglia
//  nodi con un solo figlio
//  nodi con due figli aventi lo stesso numero di discendenti

int lenmax(albero tree)
    {
        if(tree==NULL)
            return 0;
    int dx=lenmax(tree->right)+1;
    int sx=lenmax(tree->left)+1;
    if(dx>sx)
        return dx;
    return sx;
    }
int lenmin(albero tree)
    {
        if(tree==NULL)
            return 0;
        if(tree->left==NULL && tree->right==NULL)
            return 0;
        if(tree->left==NULL)
            return lenmin(tree->right)+1;
        if(tree->right==NULL)
            return lenmin(tree->left)+1;
    int sx=lenmin(tree->left)+1;
    int dx=lenmin(tree->right)+1;
    if(sx<dx)
        return sx;
    return dx;
    }

int controlla_numnodi(albero tree)
    {
        if(tree==NULL)
            return 0;
    return controlla_numnodi(tree->left)+controlla_numnodi(tree->right)+1;
    }
int funzionetot(albero tree)
    {
        if(tree==NULL)
            return 0;
        if(tree->left==NULL && tree->right==NULL)
            return 1;
        if(tree->left==NULL)
            {
                albero temp=tree->right;
                if(temp->left==NULL && temp->right==NULL)
                    return 1;
                return 0;
            }
        if(tree->right==NULL)
            {
                albero temp=tree->left;
                if(temp->left==NULL && temp->right==NULL)
                    return 1;
                return 0;
            }
        if(controlla_numnodi(tree->left)!=controlla_numnodi(tree->right))
            return 0;
    return funzionetot(tree->left) && funzionetot(tree->right);
    }
