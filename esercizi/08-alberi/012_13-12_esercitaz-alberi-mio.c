//
//  main.c
//  esercitaz alberi mio
//
//  Created by Francesco Roscio Ricon on 13/12/25.
//
// do input k, la funzione ri ritorna 1  se ci sono k elementi uguali tra loro;
// faccio lista in cui mi salvo il valore ed il count;

#include <stdio.h>
#include <stdlib.h>


typedef struct s_nodo {
        int val;
        struct s_nodo *left;
        struct s_nodo *right;
} nodo;
typedef nodo *albero;

int scorrialbero(albero t, int k);
int funzione(albero t, int k, albero rad);
albero creaAlbero();
albero createVal(int val);
void scorrialbero_2(albero t, int x, int *contatore);

void print(albero t);
void printConLivello(albero t,int liv);
int scorrialbero(albero t, int k);

int main(){
  albero alb = creaAlbero();
  print(alb);
    int ris;
    int k;
    printf("\n");
    k=1;
    ris=funzione(alb, k, alb);
    printf("%d", ris);
}




albero creaAlbero() {
       albero tmp = createVal(7);
       tmp->left = createVal(3);
       tmp->left->left = createVal(9);
       tmp->left->right = createVal(0);
       tmp->right = createVal(9);
       tmp->right->left = createVal(5);
       tmp->right->right = createVal(10);
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
int funzione(albero t, int k, albero rad)
    {
        if(t==NULL)
            return 0;
        if(k==scorrialbero(rad, t->val))
            return 1;
    return funzione(t->left, k, rad) || funzione(t->right, k, rad);
    }
int scorrialbero(albero t, int x)
    {
    int contatore=0;
    scorrialbero_2(t, x, &contatore);
    return contatore;
    }
void scorrialbero_2(albero t, int x, int *contatore)
    {
        if(t==NULL)
            return;
        if(t->val==x)
            (*contatore)++;
            scorrialbero_2(t->left, x, contatore);
    scorrialbero_2(t->right, x, contatore);
    }
