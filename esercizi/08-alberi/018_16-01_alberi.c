//  Created by Francesco Roscio Ricon on 16/01/26.

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
int funzione(albero tree_origine, int k, albero current_root);
int contaoccorenze (albero root, int curr);

int main(){
  albero alb = creaAlbero();
  print(alb);
    int k=3;
    int ris=funzione(alb, k, alb);
    printf("\n%d", ris);
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

int contaoccorenze (albero root, int curr)
    {
    if(root==NULL)
        return 0;// caso base albero vuoto
    int count=0;
    if(curr==root->val)
        count=1;
    return count+contaoccorenze(root->left,curr)+contaoccorenze(root->right, curr);
    }
int funzione(albero tree_origine, int k, albero current_root)
    {
        if(tree_origine==NULL)
            return 0;
        if(current_root==NULL)
            return 0;
    
        if(k==contaoccorenze(tree_origine, current_root->val))
            return 1;
        int ris_dx=funzione(tree_origine, k, current_root->right);
        int ris_sx=funzione(tree_origine, k, current_root->left);
    return ris_dx || ris_sx;
    }
