//  Created by Francesco Roscio Ricon on 14/12/25.

//Un albero si dice isobato se tutti i cammini dalla radice alle foglie hanno la stessa lunghezza.

#include <stdio.h>
#include <stdlib.h>

typedef struct s_nodo {
        int val;
        struct s_nodo *left;
        struct s_nodo *right;
} nodo;
typedef nodo *albero;

typedef struct EL{
    int x;
    struct EL *next;
}vagone;
typedef vagone *treno;

treno aggiungiincoda(treno lista, int val);
albero creaAlbero();
albero createVal(int val);
int wrapper(albero t);
void print(albero t);
void printConLivello(albero t,int liv);
int misuraprimopercorso(albero t);
int funzione_misurapath(albero t, int contatore, int len);
int main(){
  albero alb = creaAlbero();
  print(alb);
    int ris=wrapper(alb);
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

int funzione_misurapath(albero t, int contatore, int len)
    {
        if(t==NULL)
            return 0;
        if(t->left==NULL && t->right==NULL)
            {
                if(contatore==len)
                    return 0;
                else
                    return 1;
            }
    
    return funzione_misurapath(t->right, contatore+1, len)+funzione_misurapath(t->left, contatore+1, len);
        
    }

int wrapper(albero t)
    {
    int ris;
    int len=misuraprimopercorso(t);
    ris=funzione_misurapath(t, 0, len);
    if(ris==0)
        return 1;
    return 0;
    }
int misuraprimopercorso(albero t)
{
    int len = 0;
    while (t->left != NULL || t->right != NULL) {
        if (t->left != NULL)
            t = t->left;
        else
            t = t->right;
        len++;
    }
    return len;
}
