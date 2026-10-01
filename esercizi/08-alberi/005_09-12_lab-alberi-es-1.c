//  Created by Francesco Roscio Ricon on 09/12/25.

#include <stdio.h>
#include <stdlib.h>


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


int f(albero t);
int sommapari(albero t);
int prod(albero t);
void max_pari(albero t, int *max);
void wrapper(albero t, int *max);
int main(){
  int ris=0;
  albero alb = creaAlbero();
  print(alb);
  printf("\n");
  printConLivello(alb,1);
  printf("\n");
    ris=prod(alb);
    int max;
    wrapper(alb, &max);
    
  
  printf("\n\n%d\n\n", max);
  fflush(stdin);
  return 0;
}




albero creaAlbero() {
       albero tmp = createVal(7);
       tmp->left = createVal(3);
       tmp->left->left = createVal(9);
       tmp->left->right = createVal(10);
       tmp->right = createVal(8);
       tmp->right->left = createVal(5);
       tmp->right->right = createVal(12);
       tmp->right->right->left = createVal(11);
       tmp->right->right->right = createVal(6);


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
int sommapari(albero t)
    {
        if(t==NULL)
            return 0;
        if(t->val%2==0)
            return sommapari(t->left)+sommapari(t->right)+ t->val;
    
        return sommapari(t->left)+sommapari(t->right);
    }

// - la funzione che calcola il prodotto di tutti i nodi dell’albero contenenti un valore divisibile per 3
int prod(albero t)
{
    if(t==NULL)
        return 1;
    if(t->val%3==0)
        return prod(t->left)*prod(t->right)*t->val;
    
    return  prod(t->left)*prod(t->right);
}

void max_pari(albero t, int *max)
    {
        if(t==NULL)
        {
            return;
        }
        if(*max<t->val && t->val%2==0)
            {
                *max=t->val;
            }
    max_pari(t->left, max);
    max_pari(t->right, max);
    }
void wrapper(albero t, int *max)
    {
    *max=0;
    max_pari(t, max);
    }

