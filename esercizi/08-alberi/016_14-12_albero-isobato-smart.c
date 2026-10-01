
//  Created by Francesco Roscio Ricon on 14/12/25.

//Un albero si dice isobato se tutti i cammini dalla radice alle foglie hanno la stessa lunghezza.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct s_nodo {
        int val;
        struct s_nodo *left;
        struct s_nodo *right;
} nodo;
typedef nodo *albero;
int funzione(albero t);
albero creaAlbero();
albero createVal(int val);
void print(albero t);
void cammino_min(albero t, int *contatore, int piano);
int wrapper_camminomin(albero t);
void printConLivello(albero t,int liv);
int wrapper_camminomax(albero t);
int funzione(albero t);
void cammino_max(albero t, int *contatore, int piano);
void cammino_min(albero t, int *contatore, int piano);

int main(){
  albero alb = creaAlbero();
  print(alb);
    int ris=funzione(alb);
    printf("%d", ris);
}




albero creaAlbero() {
    albero tmp = createVal(1);
    tmp->left = createVal(2);
    tmp->right = createVal(3);

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
void cammino_max(albero t, int *contatore, int piano)
    {
        if(t==NULL)
            return;
        if(piano>*contatore)
            *contatore=piano;
    cammino_max(t->left, contatore, piano+1);
    cammino_max(t->right, contatore, piano+1);
    }
int wrapper_camminomax(albero t)
    {
    int contatore=1;
    cammino_max(t, &contatore, 1);
    return contatore;
    }

int wrapper_camminomin(albero t)
    {
    int contatore=-1;
    cammino_min(t, &contatore, 1);
    return contatore;
    }
void cammino_min(albero t, int *contatore, int piano)
    {
        if(t==NULL)
            return;
        if(t->left==NULL && t->right==NULL)
        {
            if(piano<=*contatore || *contatore==-1)
                {
                    *contatore=piano;
                }
        }
    cammino_min(t->left, contatore, piano+1);
    cammino_min(t->right, contatore, piano+1);
    }
int funzione(albero t)
    {
    int max=wrapper_camminomax(t);
    int min=wrapper_camminomin(t);
    if(max==min)
        return 1;
    return 0;
    }
