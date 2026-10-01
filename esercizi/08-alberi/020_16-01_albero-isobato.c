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
int lenmax(albero tree);
int funzione(albero tree);
int lenmin(albero tree);
int lenmax(albero tree);

int main(){
  albero alb = creaAlbero();
  print(alb);
    int ris=funzione(alb);
    printf("%d", ris);
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

int lenmax(albero tree)
    {
        if(tree==NULL)
            return 0;
    int len_dx=lenmax(tree->right);
    int len_sx=lenmax(tree->left);
    if(len_dx>len_sx)
        return len_dx+1;
    else
        return len_sx+1;
    }
int lenmin(albero tree)
    {
        if(tree==NULL)
            return 0;
        if(tree->left==NULL && tree->right==NULL)
            return 1;
        if(tree->left==NULL)
            return lenmin(tree->right)+1;
        if(tree->right==NULL)
            return lenmin(tree->left)+1;
    int sx=lenmin(tree->left)+1;
    int dx=lenmin(tree->right)+1;
    if(sx>dx)
        return dx;
    return sx;
    }
int funzione(albero tree)
    {
        if(lenmin(tree)==lenmax(tree))
            return 1;
    return 0;
    }
